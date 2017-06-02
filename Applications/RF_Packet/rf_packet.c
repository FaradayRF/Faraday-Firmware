/*
 * rf_packet.c
 *
 *  Created on: May 13, 2017
 *      Author: Brent
 */

/* FIFO includes */
#include "../../Ring_Buffers/FIFO_SRAM.h"

/* rf includes */
#include "../../RF_Network_Stack/rf.h"
#include "../../RF_Network_Stack/rf_transport.h"

/* faraday uart network stack includes */
#include "../../UART/UART_Services.h"

/* device configuratino application includes */
#include "../Device_Config/Device_Config.h"


/** @name RF Packet application FIFO state machines
* 	@brief State machine variables for the RF Packet application.
*
*	State machine variables for the RF Packet application.
*
@{**/
volatile fifo_sram_state_machine rf_packet_app_uart_rx_state_machine; /**< Command application FIFO state machine structure */
volatile fifo_sram_state_machine rf_packet_app_rf_rx_state_machine; /**< Command application FIFO state machine structure */
volatile fifo_sram_state_machine rf_packet_app_uart_tx_state_machine; /**< FIFO buffer used to flow control the applications access to the UART network stack transmit FIFO */

/** @}*/

/** @name RF Packet Application Definitions
* 	@brief constants used in the RF Packet application functionality
*
*	Constants used in the RF Packet application functionality.
*
*
@{**/
#define APP_RF_PACKET_PAYLOAD_LEN 41 /**< Maximum RF packet length to determine maximum RF command command payload FIFO element size*/
#define APP_RF_PACKET_FIFO_COUNT 5 /**< RF command packet FIFO element count */
/** @}*/

void app_init_app_rf_packet(void){
	//Application FIFO
	fifo_sram_init(&rf_packet_app_uart_rx_state_machine, 6000, APP_RF_PACKET_PAYLOAD_LEN, APP_RF_PACKET_FIFO_COUNT);
	fifo_sram_init(&rf_packet_app_rf_rx_state_machine, 6204, APP_RF_PACKET_PAYLOAD_LEN, APP_RF_PACKET_FIFO_COUNT);
	//fifo_sram_init(&rf_packet_app_uart_tx_state_machine, 6420, APP_RF_PACKET_PAYLOAD_LEN, APP_RF_PACKET_FIFO_COUNT);
}

void app_rf_packet_uart_rx_put(unsigned char *data_pointer, unsigned char length){
	__no_operation();
	switch(app_rf_packet_parse(data_pointer)){
		case 0: // Data Frame
			put_fifo_sram(&rf_packet_app_uart_rx_state_machine, data_pointer);
			break;
		case 1: // Control Frame
			__no_operation();
			break;
	}
}

void app_rf_packet_rf_rx_put(unsigned char *packet){
	//put_fifo(&telem_rf_rx_fifo_state_machine, &telem_rf_rx_fifo_buffer, (unsigned char *)packet);
	put_fifo_sram(&rf_packet_app_rf_rx_state_machine, packet);
}

//void app_rf_packet_uart_tx_put(unsigned char *data_pointer, unsigned char length){
//	put_fifo_sram(&rf_packet_app_uart_tx_state_machine, data_pointer);
//	__no_operation();
//}




void app_rf_packet_housekeeping(void){
	/*
	 * Move APPLICATION RF FIFO packet(s) into the RF stack and transmit
	 */
	if(rf_packet_app_uart_rx_state_machine.inwaiting>0){
		unsigned char app_packet_buf[APP_RF_PACKET_PAYLOAD_LEN];
		get_fifo_sram(&rf_packet_app_uart_rx_state_machine, app_packet_buf);
		__no_operation();
		app_rf_packet_rf_tx(app_packet_buf);
		//app_command_parse(app_packet_buf, APP_CMD_SOURCE_RF);
	}

	if(rf_packet_app_rf_rx_state_machine.inwaiting>0){
			unsigned char app_packet_buf[APP_RF_PACKET_PAYLOAD_LEN];
			get_fifo_sram(&rf_packet_app_rf_rx_state_machine, app_packet_buf);
			__no_operation();
			//app_rf_packet_rf_tx(app_packet_buf);
			//app_command_parse(app_packet_buf, APP_CMD_SOURCE_RF);
			//Transmit APPLICATOIN UART FIFO packet into UART stack
			uart_send(1, APP_RF_PACKET_PAYLOAD_LEN, app_packet_buf);
		}
}


void app_rf_packet_rf_tx(unsigned char *packet){
	//RF_COMMAND_PACKET_STRUCT rf_cmd_pkt;
	/*memcpy(&rf_cmd_pkt.checksum_16, &packet[CMD_DATAGRAM_COMMAND_CHK16_LOC], CMD_DATAGRAM_COMMAND_CHK16_LEN);
	memcpy(&rf_cmd_pkt.dest_callsign, &packet[CMD_DATAGRAM_COMMAND_CALLSIGN_LOC], CMD_DATAGRAM_COMMAND_CALLSIGN_LEN);
	memcpy(&rf_cmd_pkt.dest_callsign_len, &packet[CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LOC], CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LEN);
	memcpy(&rf_cmd_pkt.dest_device_id, &packet[CMD_DATAGRAM_COMMAND_DEVICE_ID_LOC], CMD_DATAGRAM_COMMAND_DEVICE_ID_LEN);
	memcpy(&rf_cmd_pkt.cmd_app_datagram_remote, &packet[CMD_DATAGRAM_COMMAND_DATAGRAM_LOC], CMD_DATAGRAM_COMMAND_DATAGRAM_LEN);
	*/

	rf_service_tx(packet, APP_RF_PACKET_PAYLOAD_LEN, 1, local_callsign, local_callsign_len, local_device_id, "CQCQCQ", 6, 0, 0, 0);
}

unsigned char app_rf_packet_parse(unsigned char *packet){
	return packet[0];
}
