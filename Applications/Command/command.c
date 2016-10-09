#include "command.h"
#include "../../UART/UART_Services.h"
#include "../../Ring_Buffers/FIFO_SRAM.h"
#include "string.h"
#include "../../REVA_Faraday.h"
#include "../Device_Config/Device_Config.h"
#include <msp430.h>
#include "../Telemetry/Telemetry.h"
#include "../Telemetry/Telem_RF.h"
#include "../../RF_Network_Stack/rf.h"
#include "../../RF_Network_Stack/rf_transport.h"
#include "../../HAL/GPIO.h"
#include "../../Faraday_HAL/Misc_Functions.h"
#include "../HAB/App_HAB.h"
#include "../MSG/MSG.h"

/////////////////////////////////////////
// UART Service FIFO DEFINITIONS
/////////////////////////////////////////
#define CMD_FIFO_SIZE 123
#define CMD_FIFO_ELEMENT_CNT 1

//Telemetry Application FIFO Packet Buffers
volatile fifo_sram_state_machine command_state_machine;

#define APP_COMMAND_RF_PACKET_PAYLOAD_LEN 42
#define APP_COMMAND_RF_PACKET_FIFO_COUNT 2

#define APP_CMD_SOURCE_LOCAL 0
#define APP_CMD_SOURCE_RF 1

unsigned char app_packet_buf_rx[APP_COMMAND_RF_PACKET_PAYLOAD_LEN];

//Application FIFO Packet Buffers
volatile fifo_sram_state_machine app_command_rf_tx_fifo_state_machine;

//Application FIFO Packet Buffers
volatile fifo_sram_state_machine app_command_rf_tx_rfconfig_fifo_state_machine;

//Application FIFO Packet Buffers
volatile fifo_sram_state_machine app_command_rx_fifo_state_machine;

//Application RF FIFO Buffer - RX
volatile fifo_sram_state_machine app_command_rx_rf_fifo_state_machine;

/////////////////////////////////////////
// RF Command Definitions
/////////////////////////////////////////
#define RF_PAYLOAD_MAX_LEN 42

/////////////////////////////////////////
// Command Packet Definitions
/////////////////////////////////////////
#define CMD_DATAGRAM_COMMAND_PKT_LEN 123
#define CMD_DATAGRAM_COMMAND_LEN 1
#define CMD_DATAGRAM_COMMAND_LOC 0



#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LEN 1
#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC 1
#define CMD_DATAGRAM_PAYLOAD_LEN 119
#define CMD_DATAGRAM_PAYLOAD_LOC 2
#define CMD_DATAGRAM_ERRORDETECTION_LEN 2
#define CMD_DATAGRAM_ERRORDETECTION_LOC 121

#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN 9
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LOC 0
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LEN 1
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LOC 9
#define CMD_DATAGRAM_COMMAND_DEVICE_ID_LEN 1
#define CMD_DATAGRAM_COMMAND_DEVICE_ID_LOC 10
#define CMD_DATAGRAM_COMMAND_DATAGRAM_LEN 32
#define CMD_DATAGRAM_COMMAND_DATAGRAM_LOC 11
#define CMD_DATAGRAM_COMMAND_CHK16_LEN 2
#define CMD_DATAGRAM_COMMAND_CHK16_LOC 40

#define CMD_DATAGRAM_COMMAND_PKT_RF_LEN 29
#define CMD_DATAGRAM_COMMAND_LOC_RF 0
#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC_RF 1
#define CMD_DATAGRAM_PAYLOAD_LOC_RF 2
#define CMD_DATAGRAM_ERRORDETECTION_LOC_RF 27

/*
 * This funciton initializes any variables, structs, FIFO's, or hardware needed for operation
 */
void app_init_command(void){
	//Application FIFO
	fifo_sram_init(&command_state_machine, 5000, CMD_FIFO_SIZE, CMD_FIFO_ELEMENT_CNT);
	fifo_sram_init(&app_command_rf_tx_rfconfig_fifo_state_machine, 5123, APP_COMMAND_RF_CONFIG_LEN, APP_COMMAND_RF_PACKET_FIFO_COUNT);

	init_app_command_rf_fifo();
}


void init_app_command_rf_fifo(void){
	//Application FIFO
	fifo_sram_init(&app_command_rf_tx_fifo_state_machine, 5161, APP_COMMAND_RF_PACKET_PAYLOAD_LEN, APP_COMMAND_RF_PACKET_FIFO_COUNT);
	fifo_sram_init(&app_command_rx_fifo_state_machine, 5407, APP_COMMAND_RF_PACKET_PAYLOAD_LEN, APP_COMMAND_RF_PACKET_FIFO_COUNT);
}

/*
 * This is the standard FIFO put() command required by the function pointer architecture of the FIFO inteface to devices
 * such as UART or RF. This funciton is called by those service routines when needing to interact with the application.
 */
void app_command_put(unsigned char *data_pointer, unsigned char length){
	put_fifo_sram(&command_state_machine, data_pointer);
	__no_operation();
}


/////////////////////////////////////////
// Application Functions
/////////////////////////////////////////

/*
 * Housekeeping functions that are called to perform routine actions needed for program execution.
 * i.e. Check FIFO buffers and process data.
 */
void app_command_housekeep(void){
	if(command_state_machine.inwaiting>0){
		static unsigned char temp_buffer[CMD_FIFO_SIZE];
		get_fifo_sram(&command_state_machine, temp_buffer);
		app_command_parse(temp_buffer, APP_CMD_SOURCE_LOCAL);
		}
	app_command_rf_housekeeping();
}

/*
 * This function is used to parse a recieved packet from the device FIFO.
 */
void app_command_parse(unsigned char *packet, unsigned char source){
	volatile unsigned int chksum = 0;
	volatile unsigned int chksum_rx = 0;
	volatile COMMAND_PACKET_STRUCT packet_parsed;
	if(source == APP_CMD_SOURCE_LOCAL){
		//Parse the high level command packet
		memcpy(&packet_parsed.command, &packet[CMD_DATAGRAM_COMMAND_LOC], CMD_DATAGRAM_COMMAND_LEN);
		memcpy(&packet_parsed.payload_len, &packet[CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC], CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LEN);
		memcpy(&packet_parsed.payload, &packet[CMD_DATAGRAM_PAYLOAD_LOC], CMD_DATAGRAM_PAYLOAD_LEN); //Make lengths definitions at top/header!
		memcpy(&packet_parsed.error_detection_16, &packet[CMD_DATAGRAM_ERRORDETECTION_LOC], CMD_DATAGRAM_ERRORDETECTION_LEN);

		//Check the checksum to determine if the command packet is not corrupt
		//Parse out expected checksum value
		chksum = compute_checksum_16(CMD_DATAGRAM_COMMAND_PKT_LEN-CMD_DATAGRAM_ERRORDETECTION_LEN, &packet[0]); //BUG: Now I don't need the +2 here to account for the CRC bytes? Gotta get this straight.
		chksum_rx |= packet_parsed.error_detection_16[0]<<8;
		chksum_rx |= packet_parsed.error_detection_16[1];
	}
	else if(source == APP_CMD_SOURCE_RF){
		memcpy(&packet_parsed.command, &packet[CMD_DATAGRAM_COMMAND_LOC_RF], CMD_DATAGRAM_COMMAND_LEN);
		memcpy(&packet_parsed.payload_len, &packet[CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC_RF], CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LEN);
		memcpy(&packet_parsed.payload, &packet[CMD_DATAGRAM_PAYLOAD_LOC_RF], CMD_DATAGRAM_PAYLOAD_LEN); //Make lengths definitions at top/header!
		memcpy(&packet_parsed.error_detection_16, &packet[CMD_DATAGRAM_ERRORDETECTION_LOC_RF], CMD_DATAGRAM_ERRORDETECTION_LEN);

		//Check the checksum to determine if the command packet is not corrupt
		//Parse out expected checksum value
		chksum = compute_checksum_16(CMD_DATAGRAM_COMMAND_PKT_RF_LEN-CMD_DATAGRAM_ERRORDETECTION_LEN, &packet[0]); //BUG: Now I don't need the +2 here to account for the CRC bytes? Gotta get this straight.
		chksum_rx |= packet_parsed.error_detection_16[0]<<8;
		chksum_rx |= packet_parsed.error_detection_16[1];
	}

	__no_operation();
	if((chksum == chksum_rx)){
		switch (packet_parsed.command){
			//Command = ECHO
			case 1:
				uart_send(2, 62, packet_parsed.payload);
				break;

			//Command = READ_MEMORY
			case 2:
				//read memory [mem_address_H, mem_address_L, length]
				COMMAND_PACKET_READ_MEMORY_SEND_STRUCT read_memory_send_packet_struct;
				unsigned int addr;
				unsigned char read_len;

				//Parse command packet
				addr = packet_parsed.payload[0]<<8;
				read_memory_send_packet_struct.memory_address_h = packet_parsed.payload[0];
				addr |= packet_parsed.payload[1];
				read_memory_send_packet_struct.memory_address_l = packet_parsed.payload[1];
				read_len = packet_parsed.payload[2];

				//Check if length is too long
				if(read_len<=CMD_READ_MEMORY_MAX_LENGTH){
					//Copy memory contents for specified length into packet to be sent back to UART
					memcpy(&read_memory_send_packet_struct.payload, addr, read_len);
					uart_send(CMD_READ_MEMORY_UART_PORT, read_len, read_memory_send_packet_struct.payload);
				}
				else{
					//Error, length was too long. Send back error report?
				}
				break;

			//Command = UPDATE RAM DEVICE PARAMETERS
			case 4:
				app_device_config_update_ram_parameter(packet_parsed.payload[0], &packet_parsed.payload[1]);
				break;

			case 5:
				//app_command_led_toggle_test();
				app_cmd_gpio(packet_parsed.payload);
				break;

			case 6:
				//app_command_led_toggle_test();
				CC430_Program_Freq(packet_parsed.payload[0], packet_parsed.payload[1], packet_parsed.payload[2]);
				break;

			case 7: //Send local UART telemetry now
				//Report local telemetry now
				application_telemetry_send_self();
				break;

			case 8: //Send RF telemetry now
				telem_rf();
				break;

			case 9: //Send Single RF Packet (Command)
				app_cmd_rf_single_pkt(&packet_parsed.payload);
				break;

			case 10: //Update RF power setting
				Faraday_RF_PWR_Change(packet_parsed.payload[0]);
				break;

			case 11: //Device debug flash reset
				app_device_config_device_debug_reset();
				break;

			case 12: //Send device debug telemetry packet UART
				application_telemetry_send_device_debug_telem();
				break;

			case 13: //Send device settings telemetry packet UART
				application_send_telemetry_packet_1();
				break;

			case 14:
				//Activate HAB Application Cutdown Event (Will cancel active auto-cutdown timer)
				application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_1);
				break;

			case 15:
				//Reset HAB auto-cutdown timer
				application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_1);
				break;

			case 16:
				//Disable HAB Auto-Cutdown timer
				application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_0);
				break;

			case 17: //Reset HAB Application Cutdown Event State Machine IDLE
				application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_0);;
				break;

			case 18: //Basic RF packet forward command (Experimental/Debug use)
				AppMessageExperimentalPut(packet_parsed.payload, packet_parsed.payload_len);
				break;

			case 255:
				//Device Configuration
				if(packet_parsed.payload_len <= MAX_CONFIGURATION_UPDATE_PACKET_LEN){
					//Write payload to device configuration flash memory. NOTE: This will overwrite all 128 bytes even though the buffer is only 124 bytes for configuration, this measn the last couple bytes are junk in flash memory.
					app_device_config_write_buffer(packet_parsed.payload, packet_parsed.payload_len);
					//Reloead device RAM configurations since the flash was just updated
					app_device_config_load_default();
				}
				break;

			default:
				break;
			}
	}
	else{
		//Checksum failed
	}
}


void app_command_led_toggle_test(void){
	P3OUT ^= LED_2;
}

void app_cmd_gpio(unsigned char *cmd_gpio_packet){
	GPIO_COMMAND_PACKET_STRUCT gpio_packet;
	gpio_packet.port_3_on = cmd_gpio_packet[0];
	gpio_packet.port_4_on = cmd_gpio_packet[1];
	gpio_packet.port_5_on = cmd_gpio_packet[2];
	gpio_packet.port_3_off = cmd_gpio_packet[3];
	gpio_packet.port_4_off = cmd_gpio_packet[4];
	gpio_packet.port_5_off = cmd_gpio_packet[5];

	gpio_update(3, gpio_packet.port_3_on, 1);
	gpio_update(4, gpio_packet.port_4_on, 1);
	gpio_update(5, gpio_packet.port_5_on, 1);
	gpio_update(3, gpio_packet.port_3_off, 0);
	gpio_update(4, gpio_packet.port_4_off, 0);
	gpio_update(5, gpio_packet.port_5_off, 0);
}


void app_command_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config){
	unsigned char i;
	APP_COMMAND_RF_PACKET_STRUCT packet_struct_app_command;
	APP_COMMAND_PACKET_CONFIG_STRUCT packet_struct_app_command_config;

	//Place destination callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_app_command_config.RF_L2_destination_callsign[i] = RF_L2_destination_callsign[i];
	}
	packet_struct_app_command_config.RF_L2_destination_callsign_len = RF_L2_destination_callsign_len;
	packet_struct_app_command_config.RF_L2_source_callsign_len = RF_L2_source_callsign_len;
	packet_struct_app_command_config.RF_L2_destination_identifier = RF_L2_destination_identifier;
	packet_struct_app_command_config.RF_L2_packet_config = RF_L2_packet_config;
	packet_struct_app_command_config.RF_L2_packet_type = RF_L2_packet_type;

	//Place source callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_app_command_config.RF_L2_source_callsign[i] = RF_L2_source_callsign[i];
	}
	packet_struct_app_command_config.RF_L2_source_indetifier = RF_L2_source_indetifier;
	packet_struct_app_command_config.RF_L4_service_number = RF_L4_service_number;

	packet_struct_app_command.payload_length = payload_len;

	//Place destination callsign into packet struct
	for(i=0; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_app_command.payload[i] = payload_buffer[i];
	}

	//Pad destination callsign
	for(i=payload_len; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_app_command.payload[i] = 0xFF; //Padding
	}

	__no_operation();
	put_fifo_sram(&app_command_rf_tx_fifo_state_machine, &packet_struct_app_command);
	put_fifo_sram(&app_command_rf_tx_rfconfig_fifo_state_machine, &packet_struct_app_command_config);
}

void app_command_rf_housekeeping(void){
	/*
	 * Move APPLICATION RF FIFO packet(s) into the RF stack and transmit
	 */
	if(app_command_rf_tx_fifo_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		unsigned char app_packet_buf[APP_COMMAND_RF_PACKET_PAYLOAD_LEN];
		unsigned char app_packet_rf_config_buf[APP_COMMAND_RF_CONFIG_LEN];
		APP_COMMAND_PACKET_CONFIG_STRUCT test_struct;

		//GET() APPLICATION packet from APPLICATION UART FIFO
		get_fifo_sram(&app_command_rf_tx_fifo_state_machine, app_packet_buf);
		get_fifo_sram(&app_command_rf_tx_rfconfig_fifo_state_machine, app_packet_rf_config_buf);

		//Parse RF config packet to place RF stack info into the RF transmit function
		unsigned char i;
		unsigned char RF_L4_service_number = app_packet_rf_config_buf[0];
		char RF_L2_source_callsign[6];
		unsigned char RF_L2_source_callsign_len = app_packet_rf_config_buf[7];
		unsigned char RF_L2_source_indetifier = app_packet_rf_config_buf[8];
		char RF_L2_destination_callsign[6];
		unsigned char RF_L2_destination_callsign_len = app_packet_rf_config_buf[15];
		unsigned char RF_L2_destination_identifier = app_packet_rf_config_buf[16];
		unsigned char RF_L2_packet_type = app_packet_rf_config_buf[17];
		unsigned char RF_L2_packet_config = app_packet_rf_config_buf[18];

		for(i=0; i<RF_L2_source_callsign_len;i++){
			RF_L2_source_callsign[i] = app_packet_rf_config_buf[1+i];
		}

		for(i=0; i<RF_L2_source_callsign_len;i++){
			RF_L2_destination_callsign[i] = app_packet_rf_config_buf[9+i];
		}

		//Transmit APPLICATION FIFO packet into RF stack
		rf_service_tx(&app_packet_buf, APP_COMMAND_RF_PACKET_PAYLOAD_LEN, RF_L4_service_number, &RF_L2_source_callsign , RF_L2_source_callsign_len, RF_L2_source_indetifier, &RF_L2_destination_callsign, RF_L2_destination_callsign_len, RF_L2_destination_identifier, RF_L2_packet_type, RF_L2_packet_config);
	}
	else{
		//Nothing in FIFO
	}

	if(app_command_rx_fifo_state_machine.inwaiting>0){
		unsigned char app_packet_buf[APP_COMMAND_RF_PACKET_PAYLOAD_LEN];
		get_fifo_sram(&app_command_rx_fifo_state_machine, app_packet_buf);
		app_command_parse(app_packet_buf, APP_CMD_SOURCE_RF);
	}
}

void app_command_rf_rx_put(unsigned char *packet){
	//Put into the same local command queue
	put_fifo_sram(&app_command_rx_fifo_state_machine, packet);
}

void app_cmd_rf_single_pkt(unsigned char *packet){
	RF_COMMAND_PACKET_STRUCT rf_cmd_pkt;
	memcpy(&rf_cmd_pkt.checksum_16, &packet[CMD_DATAGRAM_COMMAND_CHK16_LOC], CMD_DATAGRAM_COMMAND_CHK16_LEN);
	memcpy(&rf_cmd_pkt.dest_callsign, &packet[CMD_DATAGRAM_COMMAND_CALLSIGN_LOC], CMD_DATAGRAM_COMMAND_CALLSIGN_LEN);
	memcpy(&rf_cmd_pkt.dest_callsign_len, &packet[CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LOC], CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LEN);
	memcpy(&rf_cmd_pkt.dest_device_id, &packet[CMD_DATAGRAM_COMMAND_DEVICE_ID_LOC], CMD_DATAGRAM_COMMAND_DEVICE_ID_LEN);
	memcpy(&rf_cmd_pkt.cmd_app_datagram_remote, &packet[CMD_DATAGRAM_COMMAND_DATAGRAM_LOC], CMD_DATAGRAM_COMMAND_DATAGRAM_LEN);

	rf_service_tx(&rf_cmd_pkt.cmd_app_datagram_remote, RF_PAYLOAD_MAX_LEN, 2, &local_callsign , local_callsign_len, local_device_id, rf_cmd_pkt.dest_callsign, 6, rf_cmd_pkt.dest_device_id, 0, 0);
}
