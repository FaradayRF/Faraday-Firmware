/*
 * MSG.h
 *
 *  Created on: Jun 11, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_MSG_MSG_H_
#define APPLICATIONS_MSG_MSG_H_


typedef struct APP_MSG_UART_PKT {
	unsigned char cmd;
	char dest_callsign[9];
	unsigned char dest_id;
	unsigned char data_len;
	unsigned char data[42];
} APP_MSG_UART_PKT_STRUCT;

typedef struct APP_MSG_RF_PKT {
	unsigned char sequence;
	unsigned char payload_len;
	unsigned char data[38];
	unsigned char error_detect_16[2];
} APP_MSG_RF_PKT_STRUCT;

void init_app_msg(void);
void app_msg_put(unsigned char *data_pointer, unsigned char length);
void app_msg_rf_rx_put(unsigned char *data_pointer, unsigned char length);
void app_msg_housekeeping(void);
void app_msg_uart_parse(unsigned char *packet);

#endif /* APPLICATIONS_MSG_MSG_H_ */
