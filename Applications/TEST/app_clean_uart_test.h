/*
 * app_clean_uart_test.h
 *
 *  Created on: Mar 21, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_APP_CLEAN_UART_TEST_H_
#define APPLICATIONS_APP_CLEAN_UART_TEST_H_

#define APP_PACKET_PAYLOAD_LEN 64
typedef struct APP_PACKET {
	unsigned char sequence_number;
	unsigned char payload_length;
	unsigned char payload[APP_PACKET_PAYLOAD_LEN];
} APP_PACKET_STRUCT;

void init_app_clean_uart_test(void);
void app_uart_tx_test(void);
void create_packet(volatile APP_PACKET_STRUCT *buffer_struct, unsigned char sequence_number, unsigned char payload_length, unsigned char *payload);
unsigned char app_uart_tx_test_put_tx(unsigned char *payload);
unsigned char app_uart_tx_test_get_tx(unsigned char *get_buffer_ptr);
unsigned char app_uart_tx_test_isempty_tx(void);
void app_uart_tx_test_housekeeping(void);
unsigned char application_test_put_tx(unsigned char *payload);
unsigned char application_test_get_tx(unsigned char *get_buffer_ptr);

#endif /* APPLICATIONS_APP_CLEAN_UART_TEST_H_ */
