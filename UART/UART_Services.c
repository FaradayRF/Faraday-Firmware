/*
 * UART_Services.c
 *
 *  Created on: Apr 2, 2016
 *      Author: Brent
 */

#include "UART_Services.h"
#include "UART_L4.h"

#define RF_SERVICE_ELEMENT_COUNT 8

//static volatile void (*srvc_open_func_ptrs[RF_SERVICE_ELEMENT_COUNT]) (unsigned char *data_pointer, unsigned char data_length);
volatile void (*srvc_open_func_ptrs[RF_SERVICE_ELEMENT_COUNT]) (unsigned char *data_pointer, unsigned char data_length);

void uart_send(unsigned char service_number, unsigned char payload_length, unsigned char *payload){
	uart_transport_tx_packet(service_number,payload_length, payload);
}

void uart_service_open(unsigned char service_number, void (*func_ptr)(void)){
	if(srvc_open_func_ptrs[service_number] == 0){
		srvc_open_func_ptrs[service_number] = func_ptr;
		__no_operation();
	}
	else{
		__no_operation(); //Service Number already in use!
	}

//expected function example:
//	void command_put(unsigned char *data_pointer, unsigned char length){
//		put_fifo(&command_state_machine, &command_fifo_buffer, data_pointer);
//		__no_operation();
//	}

}

void uart_service_close(unsigned char service_number){
	if((service_number <RF_SERVICE_ELEMENT_COUNT) && srvc_open_func_ptrs[service_number] != 0){
		srvc_open_func_ptrs[service_number] = 0;
		__no_operation();
	}
	else{
		__no_operation(); //Service Number was not in use!
}

//expected function example:
//	void command_put(unsigned char *data_pointer, unsigned char length){
//		put_fifo(&command_state_machine, &command_fifo_buffer, data_pointer);
//		__no_operation();
//	}

}

void uart_service_app_put(unsigned char service_number, unsigned char *data){
	//char test = "12345678";
	//unsigned char i;
	if((service_number <RF_SERVICE_ELEMENT_COUNT) && (srvc_open_func_ptrs[service_number] != 0)){
		__no_operation();
		(*srvc_open_func_ptrs[service_number]) (data, 8);
		__no_operation();
	}
	else{
		__no_operation(); //Bad service port or registration, not a valid pointer in array.
	}


}

void uart_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len){
	//Recieved a new uart packet from external device
	//ALL APPLICATIONS MUST BUFFER AS FULL UART HIGH LEVEL FRAME
	if((service_number <RF_SERVICE_ELEMENT_COUNT) && (srvc_open_func_ptrs[service_number] != 0)){
			__no_operation();
			(*srvc_open_func_ptrs[service_number]) (data, service_number);
			__no_operation();
		}
	else{
		__no_operation(); //Bad service port or registration, not a valid pointer in array.
	}
}


