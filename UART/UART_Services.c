/** @file UART_Services.c
 *  @brief Faraday UART Network Stack - Layer 4 Services
 *
 *  This source file provides the layer 4 (TRANSPORT) layer protocol services. Providing service functions
 *  allows the protocol to be interacted with in an abstracted method that better suites layer isolation
 *  and layer modularity.
 *
 */

/* standard includes */
#include "UART_Services.h"

/* faraday uart layer 4 */
#include "UART_L4.h"



/** @name Initializing UART Receive Service Port Function Pointer Array
    @{ **/
volatile void (*srvc_open_func_ptrs[UART_SERVICE_ELEMENT_COUNT]) (unsigned char *data_pointer, unsigned char data_length); /**< A function pointer array that holds the pointer to the functions where data will be put into when received on the "service port" */
/** @} */


void uart_send(unsigned char service_number, unsigned char payload_length, unsigned char *payload){
	uart_transport_tx_packet(service_number,payload_length, payload);
}

void uart_service_open(unsigned char service_number, void (*func_ptr)(void)){
	if(srvc_open_func_ptrs[service_number] == 0){
		srvc_open_func_ptrs[service_number] = func_ptr;
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
	if((service_number <UART_SERVICE_ELEMENT_COUNT) && srvc_open_func_ptrs[service_number] != 0){
		srvc_open_func_ptrs[service_number] = 0;
	}
	else{
		__no_operation(); //Service Number was not in use!
}



}


void uart_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len){
	//Recieved a new uart packet from external device
	//ALL APPLICATIONS MUST BUFFER AS FULL UART HIGH LEVEL FRAME
	if((service_number <UART_SERVICE_ELEMENT_COUNT) && (srvc_open_func_ptrs[service_number] != 0)){
			(*srvc_open_func_ptrs[service_number]) (data, service_number);
		}
	else{
		__no_operation(); //Bad service port or registration, not a valid pointer in array.
	}
}


