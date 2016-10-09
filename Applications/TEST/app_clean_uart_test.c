/*
 * app_clean_uart_test.c
 *
 *  Created on: Mar 21, 2016
 *      Author: Brent
 */


#include "app_clean_uart_test.h"

#include "../../Ring_Buffers/FIFO.h"
#include "../../UART/UART_L4.h"

//Packet Ring Buffer
volatile fifo_state_machine app_clean_uart_test_state_machine;
volatile unsigned char app_clean_uart_test_fifo_buffer[APP_PACKET_PAYLOAD_LEN];

volatile fifo_state_machine app_clean_uart_test_state_machine_2;
volatile unsigned char app_clean_uart_test_fifo_buffer_2[APP_PACKET_PAYLOAD_LEN*3];



//Packet Struct
volatile APP_PACKET_STRUCT app_pkt_struct;

//TEMP
volatile unsigned char packet2[APP_PACKET_PAYLOAD_LEN], status2;
volatile unsigned char packet[APP_PACKET_PAYLOAD_LEN], status;

void init_app_clean_uart_test(void){
	//Application UART FIFO
	app_clean_uart_test_state_machine.debug = 0;
	app_clean_uart_test_state_machine.element_size = APP_PACKET_PAYLOAD_LEN;
	app_clean_uart_test_state_machine.head = 0;
	app_clean_uart_test_state_machine.inwaiting = 0;
	app_clean_uart_test_state_machine.length = 0;
	app_clean_uart_test_state_machine.max_inwait = 0;
	app_clean_uart_test_state_machine.tail = 0;
	app_clean_uart_test_state_machine.buffer_size = APP_PACKET_PAYLOAD_LEN;

	//Application buffer
	app_clean_uart_test_state_machine_2.debug = 0;
	app_clean_uart_test_state_machine_2.element_size = APP_PACKET_PAYLOAD_LEN;
	app_clean_uart_test_state_machine_2.head = 0;
	app_clean_uart_test_state_machine_2.inwaiting = 0;
	app_clean_uart_test_state_machine_2.length = 0;
	app_clean_uart_test_state_machine_2.max_inwait = 0;
	app_clean_uart_test_state_machine_2.tail = 0;
	app_clean_uart_test_state_machine_2.buffer_size = APP_PACKET_PAYLOAD_LEN*3;
}


void app_uart_tx_test(void){
	/*
	 * This is to test the new uart network stack as of March 2016. This should clean up the process, reduce size, and implement a cleaner "buffer" functionality.
	 * Needs:
	 * - Create a FIFO of size MAX (MAX = 1 for now...) packet for application as FIFO for the interface between applications and UART. the FIFO will act
	 * as a "flow control" mechanism to let the application fragment large packets or otherwise buffer multiple packets and work through them until completion.
	 */

	// [payload_len, payload] up to 123
	volatile unsigned char status_final;

	//unsigned char test[64], i;// = {0,1,0x7b,3,0x7c};
	//unsigned char test2[4] = "Test";
	//test[0] = testcnt;
	//testcnt++;
	//for(i=1; i<63; i++){
	//	test[i] = i;
	//}
	//uart_transport_create_packet(&uart_tx_transport_pkt_struct, 0x33, 5, test);
	create_packet(&app_pkt_struct, 0, 4, "Test");
	application_test_put_tx((unsigned char *)&app_pkt_struct);
	create_packet(&app_pkt_struct, 1, 5, "Test2");
	application_test_put_tx((unsigned char *)&app_pkt_struct);
	__no_operation();
	//app_uart_tx_test_put_tx(&app_pkt_struct);
	//status_final = uart_transport_tx_packet(0x31, 4, test2);
}

void create_packet(volatile APP_PACKET_STRUCT *buffer_struct, unsigned char sequence_number, unsigned char payload_length, unsigned char *payload){

	buffer_struct->payload_length = payload_length;

	unsigned char i;
	//Place destination callsign into packet struct
	for(i=0; i<payload_length; i++){
		buffer_struct->payload[i] = payload[i];
	}

	//Pad destination callsign
	for(i=payload_length; i<APP_PACKET_PAYLOAD_LEN; i++){
		buffer_struct->payload[i] = 0xFF; //Padding
	}
}

unsigned char app_uart_tx_test_put_tx(unsigned char *payload){
	//Place into buffer queue
	unsigned char status;
	status = put_fifo(&app_clean_uart_test_state_machine, &app_clean_uart_test_fifo_buffer, payload);
	return status;

}

unsigned char app_uart_tx_test_get_tx(unsigned char *get_buffer_ptr){
	unsigned char result;
	result = get_fifo(&app_clean_uart_test_state_machine, app_clean_uart_test_fifo_buffer, get_buffer_ptr);
	return result;
}

unsigned char app_uart_tx_test_isempty_tx(void){
	if(app_clean_uart_test_state_machine.inwaiting>0){
		return 1;
	}
	else{
		return 0;
	}
}

unsigned char application_test_put_tx(unsigned char *payload){
	//Place into buffer queue
	unsigned char status;
	status = 0;
	if(1==1){//app_clean_uart_test_state_machine.inwaiting==0){ //BUG: NEED TO MAKE THIS A DEFINITION OR OTHER TYPE OF CHECK TO MAX/FULL FIFO
		__no_operation();
		status = put_fifo(&app_clean_uart_test_state_machine_2, &app_clean_uart_test_fifo_buffer_2, payload);
	}
	else{
		__no_operation();
	}

	return status;

}

unsigned char application_test_get_tx(unsigned char *get_buffer_ptr){
	unsigned char result;
	result = get_fifo(&app_clean_uart_test_state_machine_2, app_clean_uart_test_fifo_buffer_2, get_buffer_ptr);
	return result;
}

void app_uart_tx_test_housekeeping(void){

	if((app_clean_uart_test_state_machine_2.inwaiting>0) & (app_clean_uart_test_state_machine.inwaiting == 0)){
		__no_operation();

		status2 = application_test_get_tx(&packet2);
		app_uart_tx_test_put_tx(&packet2);
		//status = uart_transport_tx_packet(0x31, APP_PACKET_PAYLOAD_LEN, packet);

	}
	else{
		__no_operation(); //Nothing in FIFO
	}

	//Move Application UART interface FIFO packet into UART FIFO Transport layer
	if(app_clean_uart_test_state_machine.inwaiting>0){
		__no_operation();

		status = app_uart_tx_test_get_tx(&packet);
		status = uart_transport_tx_packet(0x31, APP_PACKET_PAYLOAD_LEN, packet);

	}
	else{
		__no_operation(); //Nothing in FIFO
	}

	__no_operation();
}

