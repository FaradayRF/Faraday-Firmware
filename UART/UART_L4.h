/** @file UART_L4.h
 *  @brief Faraday UART Network Stack - Layer 4 Protocol
 *
 *  This header file provides the layer 4 (TRANSPORT) layer protocol of the Faraday
 *  UART network stack. The primary purpose of the network layer is to provide a method
 *  for higher lever layers/applications to interact with only data intended for a specific
 *  "service port." Registering a service port to an application/layer allows that
 *  application/layer interface to receive/send data without having to deal with data
 *  intended for other applications/layers. This is very much like a TCP/UDP port.
 *
 *
 *  \b <b>UART Layer 4 Key Points<b>
 *
 *  - UART layer 4 is a fixed length protocol
 *  - This layer is unreliable (not error detected/corrected) and interacts with packets only
 *
 */

#ifndef UART_UART_L4_H_
#define UART_UART_L4_H_


/** @name UART Layer 4 Protocol Constant Definitions
* 	@brief Definitions for the UART layer 4 protocol
*
* 	These definitions define the constants used to define the layer 4 packets and packet
* 	parsing functions.
*
@{**/
#define UART_L4_TX_BUFFER_SIZE 125
#define UART_L4_PACKET_LENGTH 125
#define UART_L4_PAYLOAD_LENGTH 123
/** @}*/


/** @brief A structure that defines the UART layer 4 packet
 * This structure contains all the information and fields regarding the UART layer 4 protocol packet. After filling
 * the structure fields with information the structure itself can directly be used as a packet.
 *
 * @warning When using structure data directly as a packet be careful of memory alignment issues!
 */
typedef struct UART_L4_PACKET {
	unsigned char service_number;
	unsigned char payload_length;
	unsigned char payload[UART_L4_PAYLOAD_LENGTH]; // 44 instead of 45 due to UART transport layer limitation of 63 payload bytes... BUG! Fix!
} UART_TRANSPORT_PACKET_STRUCT;


/**@brief Create a UART layer 4 packet
 *
 *	This function creates a UART layer 4 packet with the supplied function arguments.
 *
 *	@param buffer_struct A pointer to a UART_TRANSPORT_PACKET_STRUCT structure that will be filled with the packet information provides in other arguments. This is the packet created after function completion.
 *	@param service_number An unsigned char that defines the "service port" that the UART layer 4 packet will be assigned to. This acts much like a TCP/UCP "port" and usually used to assign a packet to an application directly
 *	@param payload_length Length of the payload data supplied in the arguement "payload"
 *	@param payload The data to be encapsulated in the layer 4 packet
 *
 *
 */


void uart_transport_create_packet(volatile UART_TRANSPORT_PACKET_STRUCT *buffer_struct, unsigned char service_number, unsigned char payload_length, unsigned char *payload); //Change from void!


/**@brief Transmit data over a UART layer 4 service port
 *
 *	This is a high level function that uses multiple functions to create a UART layer 4 packet and place the packet into the
 *	correct buffers for further transmission over UART. This data supplied will be encapsulated in a packet assigned the
 *	supplied service port number and eventually passed to the lower layer interface in the UART network stack.
 *
 *	@param service_number An unsigned char that defines the "service port" that the UART layer 4 packet will be assigned to. This acts much like a TCP/UCP "port" and usually used to assign a packet to an application directly
 *	@param payload_length Length of the payload data supplied in the arguement "payload"
 *	@param payload The data to be encapsulated in the layer 4 packet
 *
 */
unsigned char uart_transport_tx_packet(unsigned char service_number, unsigned char payload_length, unsigned char *payload);


/**@brief Interface for lower network layer
 *
 *	This function provides an interface for a lower layer in the network stack to pass a UART layer 4 packet
 *	into the receive buffer of UART layer 4. This packet will then be parsed and handled accordingly. This is
 *	an interface between the two layers and a layer 4 packet will be encapsulated as "payload" data in a lower
 *	layer packet.
 *
 *	@param datagram_len Length of the datagram supplied in the arguement "datagram"
 *	@param datagram A pointer to the UART layer 4 datagram (packet) byte array
 *
 *	@todo This should be replaced with a function pointer interface to avoid having to "include" this header file in lower layer source files to maintain OSI layer insulation.
 *
 */
unsigned char uart_transport_rx_packet(unsigned char datagram_len, unsigned char *datagram);

#endif /* UART_UART_L4_H_ */
