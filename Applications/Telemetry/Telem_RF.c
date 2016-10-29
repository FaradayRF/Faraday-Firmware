/** @file Telem_RF.c
 *  @brief CC430 radio module telemetry application
 *
 *  The CC430 radio module telemetry appliation provides faraday telemetry functionality over the
 *  CC430 radio module. The main reason for splitting UART and RF telemetry is due to the needs
 *  to fragment telemetry going over RF due to smalle MTU size. The telemetry packets are
 *  identical between local and RF.
 *
 *  @todo Increase MTU size for RF functionality
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "Telem_RF.h"
#include "string.h"

/* telemetry application includes */
#include "telemetry.h"

/* faraday rf network stack includes */
#include "../../RF_Network_Stack/rf_transport.h"
#include "../../RF_Network_Stack/rf.h"

/* fifo includes */
#include "../../Ring_Buffers/FIFO_SRAM.h"


/* faraday uart network stack includes */
#include "../../UART/UART_L4.h"

/* faraday global variables includes */
#include "../../Faraday_Globals.h"

/* device configuratino application includes */
#include "../Device_Config/Device_Config.h"

/* faraday hardware abstraction includes */
#include "../../HAL/gps.h"
#include "../../Faraday_HAL/Misc_Functions.h"
#include "../../REVA_Faraday.h"
#include "../../HAL/GPIO.h"

/////////////////////////////////////////
// RF TEST FIFO UART DEFINITIONS
/////////////////////////////////////////


/** @name SRAM FIFO State Machine Structure Variables
* 	@brief Structures that contain the needed members that operate the SRAM FIFO state machine operations
*
* 	Structures that contain the needed members that operate the SRAM FIFO state machine operations
*
@{**/
volatile fifo_sram_state_machine telem_rf_tx_fifo_state_machine; /**< RF telemetry transmit SRAM fifo state machine structure */
volatile fifo_sram_state_machine telem_rf_tx_rfconfig_fifo_state_machine; /**< RF telemetry transmit RF network stack packet configuration fifo state machine structure */
volatile fifo_sram_state_machine telem_rf_rx_fifo_state_machine; /**< RF telemetry receive SRAM fifo state machine structure */
volatile fifo_sram_state_machine app_telem_rf_uart_state_machine; /**< RF telemetrr RF to UART receive bring SRAM FIFO state machine structure */
/** @}*/



/** @name Globals Misc.
* 	@brief Variables that are global in this source file
*
* 	@todo These should all be moved and optimized out of global if possible!
*
@{**/
volatile unsigned char app_packet_buf_rx2[TELEM_RF_PACKET_PAYLOAD_LEN]; /**< Telemetry application receive buffer (this should be function local!)*/
volatile unsigned int rf_telemetry_interval_counter_int = 0; /**< RF beacon telemetry transmission interval counter variable */
/** @}*/

/** @name RF Telemetry Packet Fragmentation Variables
* 	@brief Variables for the fragmentation and resassembly of telemetry packets over RF
*
* 	These variables(s) are used to fragment and reassemble the fragmented telemetry packets as transfered over the RF telemetry packet protocol.
*
@{**/
volatile unsigned char telem_rf_pkt_1_state_machine_data[TELEM_RF_PACKET_1_LEN]; /**< RF Telemetry data bytearray for use by the rf telemetry state machine */
/** @}*/


void init_app_telem_rf_fifo(void){
	fifo_sram_init(&telem_rf_tx_fifo_state_machine, 378, TELEM_RF_PACKET_PAYLOAD_LEN ,TELEM_RF_PACKET_FIFO_COUNT);
	fifo_sram_init(&telem_rf_tx_rfconfig_fifo_state_machine, 714, telem_rf_RF_CONFIG_LEN ,TELEM_RF_PACKET_FIFO_COUNT);
	fifo_sram_init(&telem_rf_rx_fifo_state_machine, 866, TELEM_RF_PACKET_PAYLOAD_LEN ,TELEM_RF_PACKET_FIFO_COUNT);
	fifo_sram_init(&app_telem_rf_uart_state_machine, 1202, TELEM_RF_PACKET_PAYLOAD_LEN ,TELEM_RF_PACKET_FIFO_COUNT);

}


void telem_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config){

	unsigned char i;
	telem_rf_PACKET_STRUCT packet_struct_telem_rf;
	telem_rf_PACKET_CONFIG_STRUCT packet_struct_telem_rf_config;

	//Place destination callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_telem_rf_config.RF_L2_destination_callsign[i] = RF_L2_destination_callsign[i];
	}
	packet_struct_telem_rf_config.RF_L2_destination_callsign_len = RF_L2_destination_callsign_len;
	packet_struct_telem_rf_config.RF_L2_source_callsign_len = RF_L2_source_callsign_len;
	packet_struct_telem_rf_config.RF_L2_destination_identifier = RF_L2_destination_identifier;
	packet_struct_telem_rf_config.RF_L2_packet_config = RF_L2_packet_config;
	packet_struct_telem_rf_config.RF_L2_packet_type = RF_L2_packet_type;
	//Place source callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_telem_rf_config.RF_L2_source_callsign[i] = RF_L2_source_callsign[i];
	}
	packet_struct_telem_rf_config.RF_L2_source_indetifier = RF_L2_source_indetifier;
	packet_struct_telem_rf_config.RF_L4_service_number = RF_L4_service_number;

	packet_struct_telem_rf.payload_length = payload_len;

	//Place destination callsign into packet struct
	for(i=0; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_telem_rf.payload[i] = payload_buffer[i];
	}

	//Pad destination callsign
	for(i=payload_len; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_telem_rf.payload[i] = 0xFF; //Padding
	}
	put_fifo_sram(&telem_rf_tx_fifo_state_machine, &packet_struct_telem_rf.payload[0]); //packet_struct_telem_rf needs &packet_struct_telem_rf due to direct struct not buffer array?
	put_fifo_sram(&telem_rf_tx_rfconfig_fifo_state_machine, &packet_struct_telem_rf_config);
}


void telem_rf(void){
	unsigned char telem_packet_buffer[TELEM_RF_PACKET_1_LEN]; //It is very important that this is the correct size, if too small the buffer write will overflow and be upredicatable to system performance
	application_telem_create_rf_pkt(telem_packet_buffer, local_callsign, local_callsign_len, local_device_id, local_callsign, local_callsign_len, local_device_id);
	unsigned char telem_packet_buffer2[TELEM_RF_PACKET_1_LEN];
	unsigned char i2;
	for (i2=0; i2<TELEM_RF_PACKET_1_LEN; i2++){
		telem_packet_buffer2[i2] = i2;
	}

	unsigned char i;
	unsigned char frag_buf[42];
	TELEMETRY_RF_PACKET_DATAGRAM_STRUCT rf_telem_datagram_struct;
	rf_telem_datagram_struct.packet_type = 1;
	//unsigned char testbuf[94];


	for(i=0; i<4; i++){
		rf_telem_datagram_struct.sequence = i;

		if(i==3){
			rf_telem_datagram_struct.data_length = TELEM_RF_PACKET_1_FRAG_END_LEN;//Hardcoded to avoid RX buffer overrun if corrupted until better fragmenation implementation exists //(TELEM_RF_PACKET_1_LEN)%TELEM_RF_FRAGMENT_MAX_LEN; //Make sure this is module the actual telem packet since we are ONLY sending the TELEM_PKT_3_LEN size NOT the full UART fixed size of 124
                                          			rf_telem_datagram_struct.sequence = 255;
			memcpy(&rf_telem_datagram_struct.data, &telem_packet_buffer[i*TELEM_RF_FRAGMENT_MAX_LEN], rf_telem_datagram_struct.data_length);
		}

		else{
			rf_telem_datagram_struct.data_length = TELEM_RF_FRAGMENT_MAX_LEN;
			memcpy(&rf_telem_datagram_struct.data, &telem_packet_buffer[i*TELEM_RF_FRAGMENT_MAX_LEN], rf_telem_datagram_struct.data_length);
		}

		telem_rf_send_rf_packet(&rf_telem_datagram_struct, 42, 5, local_callsign, local_callsign_len, local_device_id, "CQCQCQ", 6, 0, 0, i);
	}
}


void app_telem_rf_rx_put(unsigned char *packet){
	//put_fifo(&telem_rf_rx_fifo_state_machine, &telem_rf_rx_fifo_buffer, (unsigned char *)packet);
	put_fifo_sram(&telem_rf_rx_fifo_state_machine, packet);
}


void app_telem_rf_housekeeping(void){
	//Check if RF->UART fifo ready to place data into UART stack
	if(app_telem_rf_uart_state_machine.inwaiting>0){
		//unsigned char app_packet_buf_rx2[TELEM_RF_PACKET_PAYLOAD_LEN];

		//Get telemetry RF packet from FIFO
		get_fifo_sram(&app_telem_rf_uart_state_machine, (unsigned char *)app_packet_buf_rx2);

		//Determine packet type and decode packet type accordingly
		switch(app_packet_buf_rx2[TELEM_RF_PACKET_PACKET_ID_LOC]){
		case 1:
			app_telem_rf_pkt_1_state_machine(&app_packet_buf_rx2);
			break;
		}

	}

	if(telem_rf_rx_fifo_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		static unsigned char app_packet_buf_rx[TELEM_RF_PACKET_PAYLOAD_LEN];

		get_fifo_sram(&telem_rf_rx_fifo_state_machine, app_packet_buf_rx);

		//TEMP: Send RF telem receieved packet over RF (WARNING: NOT IN UART telem format)
		put_fifo_sram(&app_telem_rf_uart_state_machine, app_packet_buf_rx);

	}

	/*
	 * Move APPLICATION UART FIFO packet(s) into the UART stack and transmit
	 */
	if(telem_rf_tx_fifo_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		unsigned char app_packet_buf[TELEM_RF_PACKET_PAYLOAD_LEN];
		unsigned char app_packet_rf_config_buf[telem_rf_RF_CONFIG_LEN];
		telem_rf_PACKET_CONFIG_STRUCT test_struct;

		//GET() APPLICATION packet from APPLICATION UART FIFO
		get_fifo_sram(&telem_rf_tx_fifo_state_machine, app_packet_buf);
		get_fifo_sram(&telem_rf_tx_rfconfig_fifo_state_machine, app_packet_rf_config_buf);

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
		rf_service_tx(&app_packet_buf, TELEM_RF_PACKET_PAYLOAD_LEN, RF_L4_service_number, &RF_L2_source_callsign , RF_L2_source_callsign_len, RF_L2_source_indetifier, &RF_L2_destination_callsign, RF_L2_destination_callsign_len, RF_L2_destination_identifier, RF_L2_packet_type, RF_L2_packet_config);
	}
	else{
		//Nothing in FIFO
	}
}


void app_telem_rf_pkt_1_state_machine(unsigned char *packet){
	unsigned char pkt_type = packet[0];
	unsigned char pkt_seq = packet[1];
	unsigned char payload_len = packet[2];
	unsigned char *payload_ptr = &packet[3];
	unsigned char *addr_ptr = &telem_rf_pkt_1_state_machine_data[0];
	switch(pkt_seq){
	case 0:
		memcpy(addr_ptr, payload_ptr, TELEM_RF_FRAGMENT_MAX_LEN);
		break;

	case 1:
		memcpy(addr_ptr+TELEM_RF_FRAGMENT_MAX_LEN, payload_ptr, TELEM_RF_FRAGMENT_MAX_LEN);
		break;

	case 2:
		memcpy(addr_ptr+TELEM_RF_FRAGMENT_MAX_LEN*2, payload_ptr, TELEM_RF_FRAGMENT_MAX_LEN);
		break;

	case 255:
		memcpy(addr_ptr + TELEM_RF_FRAGMENT_MAX_LEN*3, payload_ptr, TELEM_RF_PACKET_1_FRAG_END_LEN);//Hardcoding length to avoid packet overflow issues if corrupt until better fragmentation implementation is made.
		unsigned int chksum = 0;
		chksum = compute_checksum_16(TELEM_RF_PACKET_1_LEN-2, &telem_rf_pkt_1_state_machine_data[0]); //BUG: Now I don't need the +2 here to account for the CRC bytes? Gotta get this straight.

		//Parse out expected checksum value
		unsigned int chksum_rx = 0;
		chksum_rx |= telem_rf_pkt_1_state_machine_data[121]<<8;
		chksum_rx |= telem_rf_pkt_1_state_machine_data[122];

		//Check if checksum RX == checksum computed to update only a good packet to the telem protocols local APRF callsign (This is kinda wierd... better way to not do this?)
		if(chksum_rx == chksum){
			memcpy(&telem_rf_pkt_1_state_machine_data[11]+3, local_callsign, local_callsign_len); // +3 due to datagram offset of telemetry packet
			telem_rf_pkt_1_state_machine_data[(21+3)] = local_device_id;

			//Flip APRF bit to 1 to indicate from RF
			telem_rf_pkt_1_state_machine_data[1] = 1;

			//recompute checksum for computer proxy with updated RX'd packet data
			chksum = compute_checksum_16(TELEM_RF_PACKET_1_LEN-2, &telem_rf_pkt_1_state_machine_data[0]);
			telem_rf_pkt_1_state_machine_data[121] = chksum>>8;
			telem_rf_pkt_1_state_machine_data[122] = chksum;

			//Send RX'd RF packet over uart to the local computer
			application_send_uart_packet(&telem_rf_pkt_1_state_machine_data); //Expects a telemetry datagram sized payload, using telemetry UART interface not telemetry RF (might need updating buffer size)!
		}
		else{
			//Drop the packet since it's corrupt.
		}
		break;

	default:
		break;

		}

}


void app_telem_rf_housekeeping_interval(void){
	if((check_bitmask(telem_boot_bitmask,RF_BEACON_BOOT_ENABLE)) && ((rf_telemetry_interval_counter_int>=telem_default_rf_interval) || telem_default_rf_interval == 1) && (telem_default_rf_interval != 0)){
		//Reset counter
		rf_telemetry_interval_counter_int = 0;

		//send uart local telemetry
		telem_rf();
	}
	else{
		rf_telemetry_interval_counter_int++;
	}
}
