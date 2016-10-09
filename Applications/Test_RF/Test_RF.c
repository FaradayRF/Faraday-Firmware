/*
 * Test_RF.c
 *
 *  Created on: Mar 30, 2016
 *      Author: Brent
 */


#include "test_RF.h"
#include "../../RF_Network_Stack/rf_transport.h"
#include "../../RF_Network_Stack/rf.h"
#include "../../Ring_Buffers/FIFO.h"
#include "string.h"
#include "uart_bridge.h"
#include "../../UART/UART_L4.h"

unsigned char cnt_test_rf = 0;



/////////////////////////////////////////
// RF TEST FIFO UART DEFINITIONS
/////////////////////////////////////////
#define TEST_RF_PACKET_PAYLOAD_LEN 43
#define TEST_RF_PACKET_FIFO_COUNT 2

unsigned char app_packet_buf_rx[TEST_RF_PACKET_PAYLOAD_LEN];

//Application FIFO Packet Buffers
volatile fifo_state_machine test_rf_tx_fifo_state_machine;
volatile unsigned char test_rf_tx_fifo_buffer[TEST_RF_PACKET_PAYLOAD_LEN*TEST_RF_PACKET_FIFO_COUNT];

//Application FIFO Packet Buffers
volatile fifo_state_machine test_rf_tx_rfconfig_fifo_state_machine;
volatile unsigned char test_rf_tx_rfconfig_fifo_buffer[TEST_RF_RF_CONFIG_LEN*TEST_RF_PACKET_FIFO_COUNT];

//Application FIFO Packet Buffers
volatile fifo_state_machine test_rf_rx_fifo_state_machine;
volatile unsigned char test_rf_rx_fifo_buffer[TEST_RF_PACKET_PAYLOAD_LEN*TEST_RF_PACKET_FIFO_COUNT];

/////////////////////////////////////////
// END TEST RF FIFO UART DEFINITIONS
/////////////////////////////////////////

/////////////////////////////////////////
// APPLICATION FIFO UART DEFINITIONS
/////////////////////////////////////////
//#define APP_TEST_RF_PACKET_PAYLOAD_LEN 8
#define APP_TEST_RF_PACKET_FIFO_COUNT 1

volatile fifo_state_machine app_test_rf_uart_state_machine;
volatile unsigned char app_test_rf_uart_fifo_buffer[TEST_RF_PACKET_PAYLOAD_LEN*1];

/////////////////////////////////////////
// END APPLICATION FIFO UART DEFINITIONS
/////////////////////////////////////////

void application_test_rf_telemetry_initialize(void){
	//initialize FIFO's
	init_app_test_rf_fifo();
}
void init_app_test_rf_fifo(void){
	//Application FIFO
	test_rf_tx_fifo_state_machine.debug = 0;
	test_rf_tx_fifo_state_machine.element_size = TEST_RF_PACKET_PAYLOAD_LEN;
	test_rf_tx_fifo_state_machine.head = 0;
	test_rf_tx_fifo_state_machine.inwaiting = 0;
	test_rf_tx_fifo_state_machine.length = 0;
	test_rf_tx_fifo_state_machine.max_inwait = 0;
	test_rf_tx_fifo_state_machine.tail = 0;
	test_rf_tx_fifo_state_machine.buffer_size = TEST_RF_PACKET_PAYLOAD_LEN*TEST_RF_PACKET_FIFO_COUNT;

	//Application FIFO
	test_rf_tx_rfconfig_fifo_state_machine.debug = 0;
	test_rf_tx_rfconfig_fifo_state_machine.element_size = TEST_RF_RF_CONFIG_LEN;
	test_rf_tx_rfconfig_fifo_state_machine.head = 0;
	test_rf_tx_rfconfig_fifo_state_machine.inwaiting = 0;
	test_rf_tx_rfconfig_fifo_state_machine.length = 0;
	test_rf_tx_rfconfig_fifo_state_machine.max_inwait = 0;
	test_rf_tx_rfconfig_fifo_state_machine.tail = 0;
	test_rf_tx_rfconfig_fifo_state_machine.buffer_size = TEST_RF_RF_CONFIG_LEN*TEST_RF_PACKET_FIFO_COUNT;

	//Application FIFO
	test_rf_rx_fifo_state_machine.debug = 0;
	test_rf_rx_fifo_state_machine.element_size = TEST_RF_PACKET_PAYLOAD_LEN;
	test_rf_rx_fifo_state_machine.head = 0;
	test_rf_rx_fifo_state_machine.inwaiting = 0;
	test_rf_rx_fifo_state_machine.length = 0;
	test_rf_rx_fifo_state_machine.max_inwait = 0;
	test_rf_rx_fifo_state_machine.tail = 0;
	test_rf_rx_fifo_state_machine.buffer_size = TEST_RF_PACKET_PAYLOAD_LEN*TEST_RF_PACKET_FIFO_COUNT;

	uart_bridge_init(&app_test_rf_uart_state_machine, TEST_RF_PACKET_PAYLOAD_LEN, APP_TEST_RF_PACKET_FIFO_COUNT);

}
void test_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config){

	unsigned char i;
	TEST_RF_PACKET_STRUCT packet_struct_test_rf;
	TEST_RF_PACKET_CONFIG_STRUCT packet_struct_test_rf_config;

	//Place destination callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_test_rf_config.RF_L2_destination_callsign[i] = RF_L2_destination_callsign[i];
	}
	packet_struct_test_rf_config.RF_L2_destination_callsign_len = RF_L2_destination_callsign_len;
	packet_struct_test_rf_config.RF_L2_source_callsign_len = RF_L2_source_callsign_len;
	packet_struct_test_rf_config.RF_L2_destination_identifier = RF_L2_destination_identifier;
	packet_struct_test_rf_config.RF_L2_packet_config = RF_L2_packet_config;
	packet_struct_test_rf_config.RF_L2_packet_type = RF_L2_packet_type;
	//Place source callsign into packet struct
	for(i=0; i<6; i++){
		packet_struct_test_rf_config.RF_L2_source_callsign[i] = RF_L2_source_callsign[i];
	}
	packet_struct_test_rf_config.RF_L2_source_indetifier = RF_L2_source_indetifier;
	packet_struct_test_rf_config.RF_L4_service_number = RF_L4_service_number;

	packet_struct_test_rf.payload_length = payload_len;

	//Place destination callsign into packet struct
	for(i=0; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_test_rf.payload[i] = payload_buffer[i];
	}

	//Pad destination callsign
	for(i=payload_len; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
		packet_struct_test_rf.payload[i] = 0xFF; //Padding
	}

	__no_operation();

	put_fifo(&test_rf_tx_fifo_state_machine, &test_rf_tx_fifo_buffer, &packet_struct_test_rf);
	put_fifo(&test_rf_tx_rfconfig_fifo_state_machine, &test_rf_tx_rfconfig_fifo_buffer, &packet_struct_test_rf_config);
}

void test_rf(void){
	unsigned char payload[4] = "ABC";
	payload[3] = cnt_test_rf;
	cnt_test_rf++;

	//application_send_uart_packet();
	TEST_RF_PACKET_STRUCT app_test_rf_packet_struct;
	//test_rf_send_rf_packet(&payload, 4, 0xAA, "KB1LQD", 6, 0x31, "TEST1", 5, 0x36, 0xab, 7);
	test_rf_send_rf_packet(&payload, 4, 0xAA, "KB1LQD", 6, 0x31, "TEST-2", 6, 0x37, 0xab, 7);
	//rf_service_tx(&payload, 3, 0xAA, "KB1LQD", 6, 0x31, "TEST1", 5, 0x36, 0xab, 7);

	__no_operation();


	__no_operation();
}

void app_test_rf_rx_put(unsigned char *packet){
	put_fifo(&test_rf_rx_fifo_state_machine, &test_rf_rx_fifo_buffer, (unsigned char *)packet);
	//__delay_cycles(500000); //BUG - Race condition again? Does it only do this on the first pass?
}

void app_test_rf_housekeeping(void){

	//Check if RF->UART fifo ready to place data into UART stack
	if(app_test_rf_uart_state_machine.inwaiting>0){
		unsigned char app_packet_buf_rx2[TEST_RF_PACKET_PAYLOAD_LEN];
		//Transmit APPLICATOIN UART FIFO packet into UART stack
		get_fifo(&app_test_rf_uart_state_machine, (unsigned char *)test_rf_rx_fifo_buffer, (unsigned char *)app_packet_buf_rx2);
		unsigned char service_number = 10;
		uart_transport_tx_packet(service_number, TEST_RF_PACKET_PAYLOAD_LEN, app_packet_buf_rx2);
		__no_operation();
	}

	if(test_rf_rx_fifo_state_machine.inwaiting>0){
			//Create temporary array to store packet from APPLICATION

			get_fifo(&test_rf_rx_fifo_state_machine, (unsigned char *)test_rf_rx_fifo_buffer, (unsigned char *)app_packet_buf_rx);
			__no_operation();
			//put_fifo(&app_test_rf_uart_state_machine, &app_test_rf_uart_fifo_buffer, (unsigned char *)app_packet_buf_rx);
			//uart_bridge_send(&app_test_rf_uart_state_machine, (unsigned char *)app_test_rf_uart_fifo_buffer, app_packet_buf_rx);
			__no_operation();
	}

	/*
	 * Move APPLICATION UART FIFO packet(s) into the UART stack and transmit
	 */
	if(test_rf_tx_fifo_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		unsigned char app_packet_buf[TEST_RF_PACKET_PAYLOAD_LEN];
		unsigned char app_packet_rf_config_buf[TEST_RF_RF_CONFIG_LEN];
		TEST_RF_PACKET_CONFIG_STRUCT test_struct;
		//GET() APPLICATION packet from APPLICATION UART FIFO
		get_fifo(&test_rf_tx_fifo_state_machine, test_rf_tx_fifo_buffer, (unsigned char *)app_packet_buf);
		get_fifo(&test_rf_tx_rfconfig_fifo_state_machine, test_rf_tx_rfconfig_fifo_buffer, (unsigned char *)app_packet_rf_config_buf);
		//get_fifo(&test_rf_tx_rfconfig_fifo_state_machine, test_rf_tx_rfconfig_fifo_buffer, (unsigned char *)app_packet_rf_config_buf);

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
		rf_service_tx(&app_packet_buf, TEST_RF_PACKET_PAYLOAD_LEN, RF_L4_service_number, &RF_L2_source_callsign , RF_L2_source_callsign_len, RF_L2_source_indetifier, &RF_L2_destination_callsign, RF_L2_destination_callsign_len, RF_L2_destination_identifier, RF_L2_packet_type, RF_L2_packet_config);
	}
	else{
		//Nothing in FIFO
		__no_operation();
	}


	__no_operation();
}

