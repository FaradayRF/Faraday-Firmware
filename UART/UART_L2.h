/** @file UART_L2.h
 *  @brief Faraday UART Network Stack - Layer 2 Protocol
 *
 *  This source file provides the layer 2 (datalink) layer protocol of the Faraday
 *  UART network stack. This layer provides byte framing between the CC430 hardware UART
 *  and defines a layer 2 protocol.
 *
 */

#ifndef UART_UART_L2_H_
#define UART_UART_L2_H_


/** @name UART Layer 2 Receive Framing Definitions
* 	@brief UART layer 2 protocol receive framing definitions
*
* 	These definitions define the constants used to define the layer 2 receive frame
* 	used in the layer 2 protocol. Constants such as start, stop, and escape
* 	bytes are defined.
*
@{**/
#define UART_DATALINK_RX_STATE_IDLE 0x00 /**< Idle State */
#define UART_DATALINK_RX_STATE_START 0x01 /**< Start Byte Received State */
#define UART_DATALINK_RX_STATE_ESC 0x02 /**< Escape Byte Received State */
#define UART_DATALINK_RX_STATE_STOP 0x03 /**< Stop Byte Received State */
#define UART_DATALINK_RX_START_BYTE 0x7b /**< Start Byte */
#define UART_DATALINK_RX_STOP_BYTE 0x7c /**< Stop Byte */
#define UART_DATALINK_RX_ESC_BYTE 0x7d /**< Escape Byte */
/** @}*/



/** @name UART Layer 2 Transmit Framing Definitions
* 	@brief UART layer 2 protocol transmit framing definitions
*
* 	These definitions define the constants used to define the layer 2 transmit frame
* 	used in the layer 2 protocol. Constants such as start, stop, and escape
* 	bytes are defined.
*
@{**/
#define UART_DATALINK_FRAMING_START_BYTE 0x7b /**< Start Byte */
#define UART_DATALINK_FRAMING_STOP_BYTE 0x7c /**< Stop Byte */
#define UART_DATALINK_FRAMING_ESC_BYTE 0x7d /**< Escape Byte */
/** @}*/


/** @name UART Layer 2 Protocol Definitions
* 	@brief UART layer 2 protocol definitions that implement the higher level portions of the layer and packet structure
*
* 	UART layer 2 protocol definitions that implement the higher level portions of the layer and packet structure.
* 	The default packet configuration and buffer sizes are defined here.
*
@{**/
#define UART_TX_BUFFER_SIZE 128*3
#define UART_L2_PACKET_LENGTH 128
#define UART_L2_PAYLOAD_LENGTH 125
#define UART_L2_PKT_TYPE_LOC 0
#define UART_L2_PKT_CONFIG_LOC 1
#define UART_L2_PKT_PAYLOAD_LEN_LOC 2
#define UART_L2_PKT_HEADER_LEN_OFFSET 3
/** @}*/


/** @brief UART Layer 2 Packet Definiton Structure
 *
 * A structure that defines the layer 2 packet used by the Faraday UART network stack.
 * This structure is used to directly make the packet and place into the transmit
 * routine(s).
 *
 */
typedef struct UART_L2_PACKET {
	unsigned char packet_type;
	unsigned char packet_config;
	unsigned char payload_length;
	unsigned char payload[UART_L2_PAYLOAD_LENGTH];
} UART_DATALINK_PACKET_STRUCT;


/** @brief UART Layer 2 Transmit Framing State Machine
 *
 * This structure defines the structure used to maintain the state machine
 * that controls the byte framing of the Layer 2 UART transmit protocol.
 *
 */
typedef struct UART_L2_PACKET_MSP430_BUFFER {
	unsigned char uart_datalink_tx_rdy_flag;
	unsigned int uart_datlink_tx_byte_current;
	unsigned char uart_datlink_tx_startbyte_flag;
	unsigned char uart_datlink_tx_stopbyte_flag;
	unsigned char uart_datlink_tx_escape_flag;
	unsigned char uart_datlink_tx_escape_buffer;
	unsigned char uart_datalink_tx_tx_pkt_buffer[UART_L2_PAYLOAD_LENGTH];
} UART_DATALINK_PACKET_MSP430_BUFFER_STRUCT;

/**@brief
 *
 *
 *
 */
void init_uart(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_create_packet(volatile UART_DATALINK_PACKET_STRUCT *buffer_struct, unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);


/**@brief
 *
 *
 *
 */
unsigned char uart_datalink_put_tx(unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);


/**@brief
 *
 *
 *
 */
unsigned char uart_datalink_get_tx(unsigned char *get_buffer_ptr);


/**@brief
 *
 *
 *
 */
unsigned char uart_datalink_isempty_tx(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_tx_housekeep(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_housekeep(void);


/**@brief
 *
 *
 *
 */
void uart_tx_datalink_isr(void);


//Receiver
/**@brief
 *
 *
 *
 */
unsigned char uart_datalink_byte_isempty_rx(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_put_byte(volatile unsigned char *data_byte);


//RX Byte Escaping
/**@brief
 *
 *
 *
 */
unsigned char uart_datalink_rx_frame_parser_check_state(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_frame_parser_change_state(unsigned char state);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_frame_parser_state_idle(unsigned char new_byte);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_frame_parser_state_start(unsigned char new_byte);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_frame_parser_state_stop(void);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_frame_parser_state_esc(unsigned char new_byte);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_framer_parser_parse_byte(unsigned char new_byte);


/**@brief
 *
 *
 *
 */
void uart_datalink_rx_pass_higher_layer(unsigned char datagram_len, unsigned char *datagram);

#endif /* UART_UART_L2_H_ */
