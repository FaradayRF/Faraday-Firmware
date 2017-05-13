/*
 * rf_packet.c
 *
 *  Created on: May 13, 2017
 *      Author: Brent
 */

/* FIFO includes */
#include "../../Ring_Buffers/FIFO_SRAM.h"


/** @name RF Packet application FIFO state machines
* 	@brief State machine variables for the RF Packet application.
*
*	State machine variables for the RF Packet application.
*
@{**/
volatile fifo_sram_state_machine rf_packet_app_uart_rx_state_machine; /**< Command application FIFO state machine structure */
/** @}*/

/** @name RF Packet Application Definitions
* 	@brief constants used in the RF Packet application functionality
*
*	Constants used in the RF Packet application functionality.
*
*
@{**/
#define APP_RF_PACKET_PAYLOAD_LEN 42 /**< Maximum RF packet length to determine maximum RF command command payload FIFO element size*/
#define APP_RF_PACKET_FIFO_COUNT 5 /**< RF command packet FIFO element count */
/** @}*/

void app_init_app_rf_packet(void){
	//Application FIFO
	fifo_sram_init(&rf_packet_app_uart_rx_state_machine, 6000, APP_RF_PACKET_PAYLOAD_LEN, APP_RF_PACKET_FIFO_COUNT);
}

void app_rf_packet_uart_rx_put(unsigned char *data_pointer, unsigned char length){
	put_fifo_sram(&rf_packet_app_uart_rx_state_machine, data_pointer);
	__no_operation();
}


void app_rf_packet_housekeeping(void){
	/*
	 * Move APPLICATION RF FIFO packet(s) into the RF stack and transmit
	 */
	if(rf_packet_app_uart_rx_state_machine.inwaiting>0){
		unsigned char app_packet_buf[APP_RF_PACKET_PAYLOAD_LEN];
		get_fifo_sram(&rf_packet_app_uart_rx_state_machine, app_packet_buf);
		//app_command_parse(app_packet_buf, APP_CMD_SOURCE_RF);
	}
}
