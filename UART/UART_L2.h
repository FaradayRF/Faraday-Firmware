/*
 * UART_L2.h
 *
 *  Created on: Mar 8, 2016
 *      Author: Brent
 */

#ifndef UART_UART_L2_H_
#define UART_UART_L2_H_

/////////////////////////////////////////////////////
//Define UART datalink framing constants and variables
///////////////////////////////////////////////////////Frame State Machine
#define UART_DATALINK_RX_STATE_IDLE 0x00 //Standby for start byte
#define UART_DATALINK_RX_STATE_START 0x01 //Start byte received
#define UART_DATALINK_RX_STATE_ESC 0x02 //Escape byte received
#define UART_DATALINK_RX_STATE_STOP 0x03 //Stop byte received
#define UART_DATALINK_RX_START_BYTE 0x7b
#define UART_DATALINK_RX_STOP_BYTE 0x7c
#define UART_DATALINK_RX_ESC_BYTE 0x7d




//TX Framing
#define UART_DATALINK_FRAMING_START_BYTE 0x7b
#define UART_DATALINK_FRAMING_STOP_BYTE 0x7c
#define UART_DATALINK_FRAMING_ESC_BYTE 0x7d



#define UART_TX_BUFFER_SIZE 128*3
#define UART_L2_PACKET_LENGTH 128
#define UART_L2_PAYLOAD_LENGTH 125
#define UART_L2_PKT_TYPE_LOC 0
#define UART_L2_PKT_CONFIG_LOC 1
#define UART_L2_PKT_PAYLOAD_LEN_LOC 2
#define UART_L2_PKT_HEADER_LEN_OFFSET 3
typedef struct UART_L2_PACKET {
	unsigned char packet_type;
	unsigned char packet_config;
	unsigned char payload_length;
	unsigned char payload[UART_L2_PAYLOAD_LENGTH];
} UART_DATALINK_PACKET_STRUCT;



typedef struct UART_L2_PACKET_MSP430_BUFFER {
	unsigned char uart_datalink_tx_rdy_flag;
	unsigned int uart_datlink_tx_byte_current;
	unsigned char uart_datlink_tx_startbyte_flag;
	unsigned char uart_datlink_tx_stopbyte_flag;
	unsigned char uart_datlink_tx_escape_flag;
	unsigned char uart_datlink_tx_escape_buffer;
	unsigned char uart_datalink_tx_tx_pkt_buffer[UART_L2_PAYLOAD_LENGTH];
} UART_DATALINK_PACKET_MSP430_BUFFER_STRUCT;

void init_uart(void);
void uart_datalink_create_packet(volatile UART_DATALINK_PACKET_STRUCT *buffer_struct, unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);
unsigned char uart_datalink_put_tx(unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);
unsigned char uart_datalink_get_tx(unsigned char *get_buffer_ptr);
unsigned char uart_datalink_isempty_tx(void);
void uart_datalink_tx_housekeep(void);
void uart_datalink_rx_housekeep(void);
void uart_tx_datalink_isr(void);


//Receiver
unsigned char uart_datalink_byte_isempty_rx(void);
void uart_datalink_rx_put_byte(volatile unsigned char *data_byte);
//
//RX Byte Escaping
unsigned char uart_datalink_rx_frame_parser_check_state(void);
void uart_datalink_rx_frame_parser_change_state(unsigned char state);
void uart_datalink_rx_frame_parser_state_idle(unsigned char new_byte);
void uart_datalink_rx_frame_parser_state_start(unsigned char new_byte);
void uart_datalink_rx_frame_parser_state_stop(void);
void uart_datalink_rx_frame_parser_state_esc(unsigned char new_byte);
void uart_datalink_rx_framer_parser_parse_byte(unsigned char new_byte);
void uart_datalink_rx_pass_higher_layer(unsigned char datagram_len, unsigned char *datagram);

#endif /* UART_UART_L2_H_ */
