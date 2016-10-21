/** @file rf_transport.h
 * 	@brief The layer 4 RF experimental protocol
 *
 * 	These functions create the experimental RF layer 4 (transport) protocol. The protocol is a fixed length protocol and provides
 * 	no error detection. Packet fragmentation is not supported and therefor the layer 4 protocol packets much be equal to or smaller
 * 	than the maximum transmissible unit of the lower layers.
 *
 */


#ifndef RF_NETWORK_STACK_RF_TRANSPORT_H_
#define RF_NETWORK_STACK_RF_TRANSPORT_H_

/** @name Automatic Cutdown Event State Machine Definitions
* 	@brief Definitions for the state machine based function that performs automatic timed based cutdown of a HAB used the Faraday MOSFET as control.
@{**/
#define RF_TRANPORT_PACKET_LEN 44 /**< Transport packet total fixed length length*/
#define RF_TRANPORT_PAYLOAD_MAX_LEN 42 /**< Transport payload fixed length length */
#define RF_TRANPORT_PACKET_PAYLOAD_LEN_LOC 0 /**< Packet index location where payload length is stored */
#define RF_TRANPORT_PACKET_PAYLOAD_LOC 1 /**< Packet index location where the first payload byte is located */
#define RF_TRANPORT_PACKET_SERVICE_NUMBER_LOC 43 /**< Packet index location where the layer 4 protocol service port number is stored */
/** @}*/

/** @brief RF layer 4 transport packet structure
 *
 * A structure that defines and holds the layer 4 (transport) packet fields.
 *
 */
typedef struct RF_TRANSPORT_PACKET {
	unsigned char payload_length; /**< The length of the payload data contained within the packet in bytes*/
	unsigned char payload[RF_TRANPORT_PAYLOAD_MAX_LEN]; /**< An array that contains the payload data*/
	unsigned char service_number; /**< The layer 4 (transport) service port number */

} RF_TRANSPORT_PACKET_STRUCT;


/** @brief High level function used to transmit a full RF packet
 *
 *	High level function used to transmit a full RF packet using all network layers in one function.
 *
 *	@param L4_payload_buffer Pointer to the Layer 4 (transport) payload to be transmitted
 *	@param L4_payload_len Layer 4 (transport) payload length in bytes
 *	@param L4_service_number Layer 4 (transport) service port number that will be assigned to the layer 4 packet
 *	@param L2_src_callsign Layer 2 (datalink) source callsign (local device - for identification purpose)
 *	@param L2_src_callsign_len Layer 2 (datalink) source callsign length in bytes (local device - for identification purpose)
 *	@param L2_src_callsign_id Layer 2 (datalink) source device ID number (local device - for identification purpose)
 *	@param L2_dest_callsign Layer 2 (datalink) destination callsign to address MAC layer packet to
 *	@param L2_dest_callsign_len Layer 2 (datalink) destination callsign length in bytes
 *	@param L2_dest_callsign_id Layer 2 (datalink) destination device ID to address MAC layer packet to
 *	@param L2_packet_type Layer 2 (datalink) packet type identifier (for handling and parsing multiple packet types - see packet documentation)
 *	@param L2_packet_config Layer 2 (datalink) packet configuration bitmask
 *
 *	@bug This should be simplified in the layer 4 source and service moved to the service source file. Layer isolation should be improved.
 *
 */
void rf_service_tx(unsigned char *L4_payload_buffer,
		unsigned char L4_payload_len,
		unsigned char L4_service_number,
		char *L2_src_callsign,
		unsigned char L2_src_callsign_len,
		unsigned char L2_src_callsign_id,
		char *L2_dest_callsign,
		unsigned char L2_dest_callsign_len,
		unsigned char L2_dest_callsign_id,
		unsigned char L2_packet_type,
		unsigned char L2_packet_config);


/** @brief Create a layer 4 (transport) packet
 *
 *	This function is used to create a layer 4 transport layer packet.
 *
 *	@param payload_buffer Pointer to the Layer 4 (transport) payload to be transmitted
 *	@param payload_len Layer 4 (transport) payload length in bytes
 *	@param service_number Layer 4 (transport) service port number that will be assigned to the layer 4 packet
 *	@param packet_struct A pointer to a RF_TRANSPORT_PACKET_STRUCT that will be filled with layer 4 packet information using supplied function arguments
 *
 *	@retval 1 if packet successfully create, 0 if packet create FAIL (due to payload data being too long)
 *
 */
unsigned char rf_transport_tx_create_packet(unsigned char *payload_buffer, unsigned char payload_len, unsigned char service_number, RF_TRANSPORT_PACKET_STRUCT *packet_struct);


/** @brief Parse a layer 4 (transport) packet
 *
 *	This function is used to parse a layer 4 transport layer packet into a defined structure.
 *
 *	@param packet Pointer to the Layer 4 (transport) payload to be parsed into a structure
 *	@param broadcast_status MAC layer broadcast allowance status. 1 if service port number is allowed to accept a broadcast addressed packet, 0 if not.
 *
 */
void rf_transport_parse(unsigned char *packet, unsigned char broadcast_status);


#endif /* RF_NETWORK_STACK_RF_TRANSPORT_H_ */
