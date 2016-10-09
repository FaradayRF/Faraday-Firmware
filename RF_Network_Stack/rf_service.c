/*
 * rf_service.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Brent
 */

#include "rf_service.h"
#include "../Ring_Buffers/FIFO.h"

#define RF_SERVICE_ELEMENT_COUNT 8

static volatile void (*srvc_open_func_ptrs[RF_SERVICE_ELEMENT_COUNT]) (unsigned char *data_pointer, unsigned char data_length);
static volatile unsigned char rx_service_port_broadcast_rule_array[RF_SERVICE_ELEMENT_COUNT];

void rf_rx_service_open(unsigned char service_number, void (*func_ptr)(void), unsigned char broadcast_rx_allowed){
	if(srvc_open_func_ptrs[service_number] == 0){
		//Register function with transport layer function pointer "service port"
		srvc_open_func_ptrs[service_number] = func_ptr;
		//Save broadcast functionality rule (i.e. is it safe for this port to receive non-directed packets?). BUG NOTE: This technically may break OSI layer abstraction a bit by combining Layer 2 and Layer 4.
		if(broadcast_rx_allowed != 0){
			rf_rx_service_broadcast_rule_open(service_number);
		}
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

void rf_rx_service_close(unsigned char service_number){
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

//void rf_rx_service_app_put(unsigned char service_number, unsigned char *data){
//	//char test = "12345678";
//	//unsigned char i;
//	if((service_number <RF_SERVICE_ELEMENT_COUNT) && (srvc_open_func_ptrs[service_number] != 0)){
//		__no_operation();
//		(*srvc_open_func_ptrs[service_number]) (data, 8);
//		__no_operation();
//	}
//	else{
//		__no_operation(); //Bad service port or registration, not a valid pointer in array.
//	}
//
//
//}

void rf_rx_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len){
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

void rf_rx_service_broadcast_rule_open(service_number){
	rx_service_port_broadcast_rule_array[service_number] = 1;
}

unsigned char rf_rx_service_broadcast_rule_get(service_number){
	return rx_service_port_broadcast_rule_array[service_number];
}
