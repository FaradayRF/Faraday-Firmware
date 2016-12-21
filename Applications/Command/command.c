/** @file command.c
 * 	@brief Firmware application that performs command and control
 *
 * 	This program performs general command and control for Faraday. Toggling GPIO and
 * 	initiating specific program/functions are some of the use-cases of this program.
 * 	The command program has its own defined packet protocol that resides at Layer 7
 * 	(Application) that is used to filter and parse commands and respective data.
 *
 * 	@todo Update MAX_CONFIGURATION_UPDATE_PACKET_LEN to implement Device_Configuration application
 * 	or layer 4 UART transport MTU definitions.
 *
 * 	@todo Update APP_COMMAND_PAYLOAD_MAX_LEN to implement RF network stack definitions instead of implementing
 * 	a seperate definition.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "command.h"
#include "string.h"

/* uart includes */
#include "../../UART/UART_Services.h"

/* rf includes */
#include "../../RF_Network_Stack/rf.h"
#include "../../RF_Network_Stack/rf_transport.h"

/* telemetry application includes */
#include "../Telemetry/Telemetry.h"
#include "../Telemetry/Telem_RF.h"

/* FIFO includes */
#include "../../Ring_Buffers/FIFO_SRAM.h"

/* device configuration includes */
#include "../Device_Config/Device_Config.h"

/* faraday hardware abstraction layer includes */
#include "../../HAL/GPIO.h"
#include "../../Faraday_HAL/Misc_Functions.h"
#include "../../REVA_Faraday.h"

/* high altitude balloon application includes */
#include "../HAB/App_HAB.h"

/* message application includes */
#include "../MSG/MSG.h"


/** @name Command application FIFO state machines
* 	@brief State machine variables for the command application.
*
*	State machine variables for the command application.
*
@{**/
volatile fifo_sram_state_machine command_state_machine; /**< Command application FIFO state machine structure */
/** @}*/


/** @name RF Command Application FIFO Structures
* 	@brief Structure variables used in the RF command functionality
*
*	Structure variables used in the RF command functionality.
*
@{**/
volatile fifo_sram_state_machine app_command_rf_tx_fifo_state_machine; /**< RF command transmit FIFO state machine */
volatile fifo_sram_state_machine app_command_rf_tx_rfconfig_fifo_state_machine; /**< RF command transmit configuration FIFO state machine */
volatile fifo_sram_state_machine app_command_rx_fifo_state_machine; /**< RF command receive FIFO state machine */
volatile fifo_sram_state_machine app_command_rx_rf_fifo_state_machine; /**< RF command receive configuration FIFO state machine */
/** @}*/




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


void app_command_put(unsigned char *data_pointer, unsigned char length){
	put_fifo_sram(&command_state_machine, data_pointer);
	__no_operation();
}


void app_command_housekeep(void){
	if(command_state_machine.inwaiting>0){
		static unsigned char temp_buffer[CMD_FIFO_SIZE];
		get_fifo_sram(&command_state_machine, temp_buffer);
		app_command_parse(temp_buffer, APP_CMD_SOURCE_LOCAL);
		}
	app_command_rf_housekeeping();
}


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

	if((chksum == chksum_rx)){
		switch (packet_parsed.command){
			//Command = ECHO
			case 1:
				uart_send(2, 62, packet_parsed.payload);
				break;

			//Command = READ_MEMORY
			case 2:
				__no_operation(); // Need this NOP here to avoid "declaration cannot have label" error. *BUG*
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

				//
			case 4:
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

			case 254:
				//Factory Reset device configuration
				app_device_config_load_default();

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

void app_command_rf_housekeeping(void){
	/*
	 * Move APPLICATION RF FIFO packet(s) into the RF stack and transmit
	 */
	if(app_command_rf_tx_fifo_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		unsigned char app_packet_buf[APP_COMMAND_RF_PACKET_PAYLOAD_LEN];
		unsigned char app_packet_rf_config_buf[APP_COMMAND_RF_CONFIG_LEN];
		APP_COMMAND_RF_CONFIG_STRUCT test_struct;

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

	rf_service_tx(&rf_cmd_pkt.cmd_app_datagram_remote, APP_COMMAND_RF_PACKET_PAYLOAD_LEN, 2, &local_callsign , local_callsign_len, local_device_id, rf_cmd_pkt.dest_callsign, 6, rf_cmd_pkt.dest_device_id, 0, 0);
}
