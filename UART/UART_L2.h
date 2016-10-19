/** @file UART_L2.h
 *  @brief Faraday UART Network Stack - Layer 2 Protocol
 *
 *  This header file provides the layer 2 (datalink) layer protocol of the Faraday
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

/**@brief Initialize UART Layer 2 TX/RX State Machines
 *
 *	This function initializes the Layer 2 UART transmit and receive state machines. Initialize
 *	values such as packet lengths and buffer sizes are initialized into the statemachines for
 *	proper operation.
 *
 */
void init_uart(void);




/**@brief Create UART Layer 2 Packet
 *
 *  This function creates a Layer 2 UART Packet for transmission. The function accepts several parameters
 *  that define the packet type, configuration bits, and other information.
 *
 *  @param buffer_struct Pointer to a UART_DATALINK_PACKET_STRUCT structure that will be filled with the supplied parameters/data
 *  @param packet_type A byte that describes the packet type which indicates how to parse the packet when received
 *  @param packet_config Configuration bytes to support link communication and flag sharing. Not yet implemented
 *  @param payload_length Length of the payload data in bytes
 *  @param payload A pointer to the byte/array of data to be packed into the packet
 *
 */
void uart_datalink_create_packet(volatile UART_DATALINK_PACKET_STRUCT *buffer_struct, unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);


/**@brief Create and transmit UART layer 2 packet
 *
 *	This function implements several other function to both create a UART layer 2 packet from the supplied parameters
 *	and will then place the packet into the transmit FIFO for UART transmission.
 *
 *  @param packet_type A byte that describes the packet type which indicates how to parse the packet when received
 *  @param packet_config Configuration bytes to support link communication and flag sharing. Not yet implemented
 *  @param payload_length Length of the payload data in bytes
 *  @param payload A pointer to the byte/array of data to be packed into the packet
 *
 *  @retval status The function returns the status of the FIFO Put() operations. If (status == 1) then placing packet into FIFO was successfull
 *
 */
unsigned char uart_datalink_put_tx(unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload);


/**@brief Get a UART layer 2 packet from receive buffer
 *
 *	This function is used to retrieve a waiting UART layer 2 byte in the UART receive buffer if present.
 *
 *	@param get_buffer_ptr Pointer to an array that will be filled with the received byte if present in the receive buffer
 *
 *	@retval status The function returns the status of the receive buffer Get() routine. If (status == 1) then retrieval of a byte was successful.
 *
 */
unsigned char uart_datalink_get_tx(unsigned char *get_buffer_ptr);


/**@brief Check if UART Layer 2 transmit buffer is empty
 *
 *	This function is used to check if the transmit buffer is empty or contains at least 1 byte waiting for
 *	retrieval. This is a very useful function to create higher level "checks" to determine if there is waiting
 *	data to be retrieved without actually "popping" the data out of the FIFO.
 *
 *	@retval Returns 1 if buffer is empty. Returns 0 if buffer NOT empty.
 *
 */
unsigned char uart_datalink_isempty_tx(void);


/**@brief UART layer 2 transmit housekeeping
 *
 *  UART layer 2 transmit housekeeping routine that performs actions needed on a reoccuring basis to enable the
 *  layer 2 protocol functionality. Actions such a checking for new data waiting to be transmitted are performed.
 *
 *  The transmit UART houskeeping retrieves a waiting byte to be transmitted over UART into a global structure
 *  and intializes control flags used for transmission. The hal_uart_set_uctxifg() function sets the UART controller
 *  transmit interrupt flag to 1 and begins the interrupt base UART transmissions. After each byte the interrupts will
 *  cause the next byte to be retrieved until the buffer is empty. An analogy can be made to "kicking" a wheel that
 *  keeps rolling until the bottom of the hill.
 *
 *  If data is continuously loaded into the buffer the transmissions will
 *  continously occure until new data is no longer placed into the buffer and the buffer empties.
 *
 */
void uart_datalink_tx_housekeep(void);





/**@brief UART layer 2 transmit interrupt service routine
 *
 * This function contains all the needed actions that are to be performed when a UART transmit interrupt occures.
 * Transmit interrupts occur when a prior byte has completed transmission and the device is ready for the next byte
 * if available. The ISR routine checks if another byte is waiting for be transmitted and transmits it if so, otherwise
 * the ISR stops the transmit "wheel" from turning and enters an inactive state.
 *
 */
void uart_tx_datalink_isr(void);



/**@brief Check if UART Layer 2 receive buffer is empty
 *
 *	This function is used to check if the receive buffer is empty or contains at least 1 packet waiting for
 *	retrieval. This is a very useful function to create higher level "checks" to determine if there is waiting
 *	data to be retrieved without actually "popping" the data out of the FIFO.
 *
 *	@retval Returns 1 if buffer is empty. Returns 0 if buffer NOT empty.
 *
 */
unsigned char uart_datalink_byte_isempty_rx(void);


/**@brief Place a byte into the receive buffer for uart layer 2
 *
 *	This function allows you to place a received uart byte into the recieve buffer for further
 *	parsing.
 *
 *	@param data_byte A pointer to the byte that will be placed into the receive byte buffer
 *
 */
void uart_datalink_rx_put_byte(volatile unsigned char *data_byte);

/**@brief UART layer 2 receive housekeeping
 *
 *  UART layer 2 receive housekeeping routine that performs actions needed on a reoccuring basis to enable the
 *  layer 2 protocol functionality. Actions such a checking for new data waiting to be retrieve are performed.
 *
 *  The receive housekeeping actions retrieve a waiting UART packet from the buffer if available and then parses
 *  it. When the parsing routine is complete it moves the parsed packet to the network layer above.
 *
 *  @note A while() loop is used to retrieve, parse, and move data to the next highest network layer continuously until the receive buffer is empty.
 *
 */
void uart_datalink_rx_housekeep(void);


//////////////////
//RX Byte Escaping
//////////////////

/**@brief Check the current UART receiver byte frame parser state machine state
 *
 *  This function checks and returns the current state of the state machine responsible for
 *  parsing received bytes into frames that contain UART layer 2 packets. The UART layer 2
 *  implements a simple byte escape framing protocol.
 *
 *  @retval uart_datalink_frame_rx_state Returns the current state of the receive byte frame parsing state machine
 *
 */
unsigned char uart_datalink_rx_frame_parser_check_state(void);


/**@brief Change the current state of the receive byte frame parser state machine
 *
 *	This function allows you to change the current state of the receive byte frame parser state machine.
 *
 */
void uart_datalink_rx_frame_parser_change_state(unsigned char state);



/**@brief UART layer 2 receiver frame parser IDLE state routine
 *
 *	This is the IDLE state state machine routine that contains the operations executed
 *	during IDLE state on each received byte. In IDLE the state machine searches for the START
 *	byte.
 *
 *	If the START byte is found then the following bytes contain a new packet. The reception
 *	of an IDLE byte resets the packet saving buffers and sets the state machine into the next
 *	state (Start)
 *
 *	@param new_byte The byte to be parsed by the receive byte escape state machine
 *
 */
void uart_datalink_rx_frame_parser_state_idle(unsigned char new_byte);



/**@brief UART layer 2 receiver frame parser START state routine
 *
 *	This is the START state state machine routing that contains the operations executed
 *	during START state on each received byte. In START state each byte is expected to be part of
 *	a packet. The START state searches for new data bytes, ESCAPE byte, STOP byte, and START
 *	bytes.
 *
 *	- START byte: If a START byte is received a new frame is assumed to have started and all prior data will be reset
 *	- STOP byte: If a STOP byte is received this indicates the end of a frame and the state machine will tranfer the parsed frame contents to the appropriate functions for further parsing of layer 2 packets
 *	- ESCAPE byte: If an ESCAPE byte is recieved this indicates that the following byte is a START/STOP/ESCAPE byte but is actually a portion of the data and should be treat accordingly
 *
 *	@param new_byte The byte to be parsed by the receive byte escape state machine
 *
 */
void uart_datalink_rx_frame_parser_state_start(unsigned char new_byte);


/**@brief UART layer 2 receiver frame parser STOP state routine
 *
 *  This is the STOP state state machine routing that contains the operations executed
 *	during STOP state on each received byte. In STOP state the frame is complete and
 *	ready to be passed to the higher layer interface. The parser uart_datalink_rx_framer_parser_parse_byte()
 *	actually handles the removal and passing of payload data to the higher layer. This STOP state simply
 *	needs to change the state machine to IDLE state since all STOP actions are complete when the state
 *	machine operates the STOP routine (parser already performed STOP state actions immediately after rescieving STOP).
 *
 */
void uart_datalink_rx_frame_parser_state_stop(void);


/**@brief UART layer 2 receiver frame parser ESCAPE state routine
 *
 *	This is the ESCAPE state state machine routing that contains the operations executed
 *	during ESCAPE state on each received byte. In ESCAPE state the next byte will be a
 *	START/STOP/ESCAPE byte but is actually a portion of data to be parsed and saved. If
 *	the next byte is not a START/STOP/ESCAPE byte then corruption has occured and is an
 *	error (no error indication provided).
 *
 *	@param new_byte The byte to be parsed by the receive byte escape state machine
 *
 */
void uart_datalink_rx_frame_parser_state_esc(unsigned char new_byte);


/**@brief UART layer 2 receiver high level state machine parser
 *
 *	This function is the high level parser routine that when executed checks the current
 *	state machine state and operates the respective state routine to properly parse the
 *	received framing/data byte.
 *
 *	@param new_byte The byte to be parsed by the receive byte escape state machine
 *
 */
void uart_datalink_rx_framer_parser_parse_byte(unsigned char new_byte);


/**@brief UART layer 2 receiver higher OSI layer interface
 *
 *	This function is used to pass the parsed UART layer 2 packet data payload into the next higher OSI layer in the network stack.
 *	This is the only location in the UART layer 2 protocol that must know about and interact with the next higher OSI layer
 *	services.
 *
 *	@param datagram_len The length of the supplied datagram (packet) in bytes
 *	@param datagram A pointer to the byte array containing the UART layer 2 data payload which is actually a higher layer packet
 *
 *	@todo Update this interface with a function pointer based interface that can be dynamically "registered" like the UART Layer 4 service ports. This will remove the need to include layer 4 header files and function calls.
 *
 */
void uart_datalink_rx_pass_higher_layer(unsigned char datagram_len, unsigned char *datagram);

#endif /* UART_UART_L2_H_ */
