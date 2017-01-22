/** @file Telem_RF.h
 *  @brief CC430 radio module telemetry application
 *
 *  The CC430 radio module telemetry appliation provides faraday telemetry functionality over the
 *  CC430 radio module. The main reason for splitting UART and RF telemetry is due to the needs
 *  to fragment telemetry going over RF due to smalle MTU size. The telemetry packets are
 *  identical between local and RF.
 *
 *  @todo Increase MTU size for RF functionality
 *
 */


#ifndef APPLICATIONS_telem_rf_telem_rf_H_
#define APPLICATIONS_telem_rf_telem_rf_H_


/** @name RF Telemetry Packet Constants
* 	@brief Constants that define the RF telemetry packet(s)
*
*	RF telemetry packet constants that define configurations such as packet lengths, fragmentation counts, and
*	index locations.
*
@{**/
#define TELEM_RF_PACKET_PACKET_ID_LOC 0 /**< RF Telemetry packet ID packet index location */
#define TELEM_RF_PACKET_1_LEN 123 /**< RF Telemetry packet type 1 lengt - 123 bytes to match telemetry fixed packet LENGTH */
#define TELEM_RF_PACKET_1_FRAG_END_LEN 6 /**< RF telemetry maximum packet fragment count - Hardcoded to avoid packet overruns in noisy environments due to simple stack design */
#define TELEM_RF_FRAGMENT_MAX_LEN 39 /**< RF Telemetry maximum fragment packet length */
#define TELEM_RF_PACKET_PAYLOAD_LEN 42 /**< Maximum RF telemetry packet length - MTU of the RF network stack */
#define telem_rf_RF_CONFIG_LEN 19 /**< RF network stack configuration packet length */
/** @}*/



/** @name FIFO Constants
*
*	RF Telemetry FIFO buffer constants
*
@{**/
#define TELEM_RF_PACKET_FIFO_COUNT 8 /**< RF Telemetry packet FIFO element count */
/** @}*/





/** @brief RF command configuration structure
 *
 *	This structure is used to hold the RF network stack information needed to properly transmit the command
 *	to the remote device.
 *
 */
typedef struct telem_rf_PACKET_CONFIG {
	unsigned char RF_L4_service_number; /**< RF network stack layer 4 service number */
	char RF_L2_source_callsign[6]; /**< RF network stack layer 2 local callsign */
	unsigned char RF_L2_source_callsign_len; /**< RF network stack layer 2 local callsign length in bytes */
	unsigned char RF_L2_source_indetifier; /**< RF network stack layer 2 local callsign ID number */
	char RF_L2_destination_callsign[6]; /**< RF network stack layer 2 destination device callsign */
	unsigned char RF_L2_destination_callsign_len; /**< RF network stack layer 2 destination device callsign length in bytes */
	unsigned char RF_L2_destination_identifier; /**< RF network stack layer 2 destination device callsign ID number */
	unsigned char RF_L2_packet_type; /**< RF network stack layer 2 packet type number */
	unsigned char RF_L2_packet_config; /**< RF network stack layer 2 packet configuration bitmask */

} telem_rf_PACKET_CONFIG_STRUCT;


/** @brief RF telemetry packet structure
 *
 *	This structure defines the RF telemetry fragmentation packet. This packet is used to define the packet type, fragmentation
 *	sequence, and contain the fragmented telemetry packet as payload.
 *
 */

typedef struct TELEMETRY_RF_PACKET_DATAGRAM {
	unsigned char packet_type; /**< Packet type field */
	unsigned char sequence; /**< Packet (fragmentation) sequence number */
	unsigned char data_length; /**< Data byte array length used in bytes */
	unsigned char data[39]; /**< Data byte array */
} TELEMETRY_RF_PACKET_DATAGRAM_STRUCT;




/**@brief Initialize RF telemetry FIFO's
 *
 *	This function is used to initialize the RF telemetry application FIFO buffers.
 *
 */
void init_app_telem_rf_fifo(void);


/**@brief RF telemetry function to send an RF packet
 *
 *	This is a single function that allows an RF network stack layer 4 packet to be transmitted in a single function call.
 *
 *	@param payload_buffer Pointer to the Layer 4 (transport) payload to be transmitted
 *	@param payload_len Layer 4 (transport) payload length in bytes
 *	@param RF_L4_service_number Layer 4 (transport) service port number that will be assigned to the layer 4 packet
 *	@param RF_L2_source_callsign Layer 2 (datalink) source callsign (local device - for identification purpose)
 *	@param RF_L2_source_callsign_len Layer 2 (datalink) source callsign length in bytes (local device - for identification purpose)
 *	@param RF_L2_source_indetifier Layer 2 (datalink) source device ID number (local device - for identification purpose)
 *	@param RF_L2_destination_callsign Layer 2 (datalink) destination callsign to address MAC layer packet to
 *	@param RF_L2_destination_callsign_len Layer 2 (datalink) destination callsign length in bytes
 *	@param RF_L2_destination_identifier Layer 2 (datalink) destination device ID to address MAC layer packet to
 *	@param RF_L2_packet_type Layer 2 (datalink) packet type identifier (for handling and parsing multiple packet types - see packet documentation)
 *	@param RF_L2_packet_config Layer 2 (datalink) packet configuration bitmask
 *
 *	@todo This should be consolidated with rf_transport.h's rf_service_tx() function!
 *
 */
void telem_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config);


/**@brief Create a new telemetry packet and transmit over RF
 *
 *	This function initiates the creation of a new telemetry application packet and then fragments that packet into smaller
 *	RF telemetry packets in order to be transmitted through the RF network stack's smaller MTU.
 *
 */
void telem_rf(void);


/**@brief Function pointer "PUT()" routine for RF telemetry
 *
 * This is the standard FIFO put() command required by the function pointer architecture of the FIFO inteface to devices
 * to the RF network stack. This funciton is called by those service routines when needing to interact with the application.
 *
 * @param packet A pointer to the data to be placed into the RF telemetry application FIFO
 *
 */
void app_telem_rf_rx_put(unsigned char *packet);


/**@brief RF telemetry housekeeping routine
 *
 *	The RF telemetry housekeeping routine should be executed on a reoccuring basis and provides the FIFO checking and other
 *	operations needed to operate the applications functionality. This function will primarally check FIFO buffers for new
 *	data to retrieve and if so perform the intended operations on the retrieved FIFO data.
 *
 */
void app_telem_rf_housekeeping(void);


/**@brief RF telemetry received packet state machine
 *
 *	This function accepts a received RF telemetry packet and will parse and re-assemble the fragmented packet into a full
 *	telemetry packet from a stream of fragmented telemetry packets.The state machine is very basic and its primary function
 *	is to parse the RF telemetry packet type and sequence numbers into start, sequence, and stop fragmentation packets that
 *	allow proper reassembly.
 *
 *	@param packet A pointer to the received RF telemetry packet
 *
 */
void app_telem_rf_pkt_1_state_machine(unsigned char *packet);


/**@brief RF telemetry beacon interval housekeeping routine
 *
 *	The RF telemetry housekeeping routine that operates the 1Hz beacon interval counter functionality. This routine should be
 *	executed once every second! Incrementing counters and invoking RF telemetry packet creation and transmission after counting
 *	the full interval in seconds contained in the device configuration respectively is performed in this function.
 *
 *	@warning This function must be execute once per second for proper operation (timing)!
 *
 */
void app_telem_rf_housekeeping_interval(void);

#endif /* APPLICATIONS_telem_rf_telem_rf_H_ */
