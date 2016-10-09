/*
 * uart_bridge.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Brent
 */

#include "uart_bridge.h"
//#include "../../UART/UART_L4.h"
#include "../../Ring_Buffers/FIFO.h"
volatile unsigned char uart_bridge_packet_buf[123];

void uart_bridge_send(fifo_state_machine *state_machine, unsigned char *fifo_buffer, unsigned char *packet){
	put_fifo(state_machine, fifo_buffer, packet);
}

//unsigned char uart_bridge_receive(fifo_state_machine *state_machine, unsigned char *fifo_buffer, unsigned char *packet){
//	if(state_machine->inwaiting>0){
//		//Create temporary array to store packet from APPLICATION
//
//		//GET() APPLICATION packet from APPLICATION UART FIFO
//		get_fifo(state_machine, fifo_buffer, (unsigned char *)uart_bridge_packet_buf);
//		//Transmit APPLICATOIN UART FIFO packet into UART stack
//		//unsigned char service_number = 0x31;
//		//uart_transport_tx_packet(service_number, APP_TELEM_PACKET_PAYLOAD_LEN, app_packet_buf);
//		__no_operation();
//	}
//	else{
//		//Nothing in FIFO
//		__no_operation();
//	}
//
//
//}

void uart_bridge_init(fifo_state_machine *state_machine, unsigned char bufsize, unsigned char elem_size){
	state_machine->debug = 0;
	state_machine->element_size = bufsize;
	state_machine->head = 0;
	state_machine->inwaiting = 0;
	state_machine->length = 0;
	state_machine->max_inwait = 0;
	state_machine->tail = 0;
	state_machine->buffer_size = bufsize*elem_size;
}
