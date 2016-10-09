/*
 * MSG.c
 *
 *  Created on: Jun 11, 2016
 *      Author: Brent
 */

#include "MSG.h"
#include "../../Ring_Buffers/FIFO_SRAM.h"
#include "../../RF_Network_Stack/rf_transport.h"
#include "../Device_Config/Device_Config.h"
#include "../../UART/UART_Services.h"

/////////////////////////////////////////
// APPLICATION FIFO UART DEFINITIONS
/////////////////////////////////////////
#define APP_MSG_DATA_LEN 42
#define APP_MSG_FIFO_COUNT 5
#define APP_MSG_UART_FIFO_COUNT 5
#define APP_MSG_RF_FIFO_COUNT 5

#define MSG_PACKET_MAX_LEN 42 //Should be max size of RF packet

//Telemetry Application FIFO Packet Buffers
volatile fifo_sram_state_machine msg_rx_state_machine;
volatile fifo_sram_state_machine msg_UART_rx_state_machine;
volatile fifo_sram_state_machine msg_UART_tx_state_machine;
volatile fifo_sram_state_machine msg_RF_rx_state_machine;

/*
 * init_app_msg()
 *
 * This initializes the application message program and fifo's
 */
void init_app_msg(void){
	fifo_sram_init(&msg_rx_state_machine, 4096, APP_MSG_DATA_LEN, APP_MSG_FIFO_COUNT);
	fifo_sram_init(&msg_UART_rx_state_machine, 4305, APP_MSG_DATA_LEN, APP_MSG_UART_FIFO_COUNT);
	fifo_sram_init(&msg_UART_tx_state_machine, 4515, APP_MSG_DATA_LEN, APP_MSG_UART_FIFO_COUNT);
	fifo_sram_init(&msg_RF_rx_state_machine, 4725, APP_MSG_DATA_LEN, APP_MSG_RF_FIFO_COUNT);
}

/*
 * This is the standard FIFO put() command required by the function pointer architecture of the FIFO inteface to devices
 * such as UART or RF. This funciton is called by those service routines when needing to interact with the application.
 */
void app_msg_put(unsigned char *data_pointer, unsigned char length){
	//put_fifo(&rf_rx_telem_state_machine, &rf_rx_telem_fifo_buffer, data_pointer);
	if(length<=MSG_PACKET_MAX_LEN){
		put_fifo_sram(&msg_UART_rx_state_machine, data_pointer);
	}
	else{
		//None
	}
}

void app_msg_rf_rx_put(unsigned char *data_pointer, unsigned char length){
	//put_fifo(&rf_rx_telem_state_machine, &rf_rx_telem_fifo_buffer, data_pointer);
	put_fifo_sram(&msg_RF_rx_state_machine, data_pointer);
}

void app_msg_housekeeping(void){
	//Check UART RX FIFO
	if(msg_UART_rx_state_machine.inwaiting > 0){
		volatile unsigned char msg_uart_buffer[APP_MSG_DATA_LEN];
		//GET() APPLICATION packet from FIFO
		//get_fifo(&app_telem_state_machine, app_telem_state_machine_fifo_buffer, (unsigned char *)app_packet_buf);
		get_fifo_sram(&msg_UART_rx_state_machine, msg_uart_buffer);
		__no_operation();
		app_msg_uart_parse(msg_uart_buffer);
	}
	else{
		//No action
	}

	//Check RF RX FIFO
	if(msg_RF_rx_state_machine.inwaiting>0){
		unsigned char msg_rf_buffer[APP_MSG_DATA_LEN];
		//GET() APPLICATION packet from FIFO
		//get_fifo(&app_telem_state_machine, app_telem_state_machine_fifo_buffer, (unsigned char *)app_packet_buf);
		get_fifo_sram(&msg_RF_rx_state_machine, msg_rf_buffer);
		__no_operation();
		//Put message into UART TX for reception
		put_fifo_sram(&msg_UART_tx_state_machine, msg_rf_buffer);
	}
	else{
		//No action
	}

	//Check UART TX FIFO
	if(msg_UART_tx_state_machine.inwaiting>0){
		unsigned char msg_uart_tx_buffer[APP_MSG_DATA_LEN];
		get_fifo_sram(&msg_UART_tx_state_machine, msg_uart_tx_buffer);
		uart_send(3, APP_MSG_DATA_LEN, msg_uart_tx_buffer);
	}
	else{
		//No Action
	}
}

void app_msg_uart_parse(unsigned char *packet){
	volatile APP_MSG_UART_PKT_STRUCT uart_msg_packet;

	//Parse received UART message packet into struct
	uart_msg_packet.cmd = packet[0];
	memcpy(&uart_msg_packet.dest_callsign,&packet[1],9);
	uart_msg_packet.dest_id = packet[10];
	uart_msg_packet.data_len = packet[11];
	memcpy(&uart_msg_packet.data,&packet[12],42);

	if(uart_msg_packet.data[0] == 255){//Needed?
		__no_operation();
	}
	//Send message over RF (Should create a RF FIFO interface eventually)
	//BUG: THIS FUNCTION ONLY SUPPORTS 6 LETER CALLSIGNS. SHOULD FIX
	rf_service_tx(&uart_msg_packet.data, uart_msg_packet.data_len, 3, local_callsign , local_callsign_len, local_device_id, &uart_msg_packet.dest_callsign, 6, uart_msg_packet.dest_id, 0, 0);

	__no_operation();
}

void AppMessageExperimentalPut(unsigned char *packet, unsigned char length){
	//Message packet should already be in the correct packet format for TX parsing
	app_msg_uart_parse(packet);
	}
