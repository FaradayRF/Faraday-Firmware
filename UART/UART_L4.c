/*
 * UART_L4.c
 *
 *  Created on: Mar 14, 2016
 *      Author: Brent
 */


#include "UART_L4.h"
#include "UART_L2.h"
#include "UART_Services.h"

//Packet Struct
//volatile UART_TRANSPORT_PACKET_STRUCT uart_tx_transport_pkt_struct;

void uart_transport_create_packet(volatile UART_TRANSPORT_PACKET_STRUCT *buffer_struct, unsigned char service_number, unsigned char payload_length, unsigned char *payload){

	buffer_struct->service_number = service_number;
	buffer_struct->payload_length = payload_length;

	unsigned char i;
	//Place destination callsign into packet struct
	for(i=0; i<payload_length; i++){
		buffer_struct->payload[i] = payload[i];
	}

	//Pad destination callsign
	for(i=payload_length; i<UART_L4_PAYLOAD_LENGTH; i++){
		buffer_struct->payload[i] = 0xFF; //Padding
	}
}

unsigned char uart_transport_tx_packet(unsigned char service_number, unsigned char payload_length, unsigned char *payload){
	UART_TRANSPORT_PACKET_STRUCT uart_tx_transport_pkt_struct;
	//Create transport packet
	uart_transport_create_packet(&uart_tx_transport_pkt_struct, service_number, payload_length, payload);
	unsigned char status;
	//Place tranport packet into datalink packet to transmit
	status = uart_datalink_put_tx(0xFF, 0x00, UART_L4_PACKET_LENGTH, &uart_tx_transport_pkt_struct);
	return status;
}

//May not be needed
void uart_transport_tx_housekeep(){
	__no_operation();
}
unsigned char uart_transport_rx_packet(unsigned char datagram_len, unsigned char *datagram){
	//Parse transport layer packet
	unsigned char service_number;
	unsigned char payload_len;
	unsigned char payload[UART_L4_PAYLOAD_LENGTH];

	service_number = datagram[0];
	payload_len = datagram[1];

	unsigned char i;
	if(payload_len<=UART_L4_PAYLOAD_LENGTH){
		//Parse payload into new buffer. Probably inefficient, should just pass pointer?
		for(i=2; i<payload_len+2; i++){
			payload[i-2] = datagram[i];
		}
		//Pass to UART Service function for program IO using Uart.
		uart_stack_rx(service_number, payload, payload_len);
		return 1;
	}
	else{
		__no_operation(); //Shouldn't get here. Bad packet length, caught to avoid overflow.
		return 0;
	}
}
