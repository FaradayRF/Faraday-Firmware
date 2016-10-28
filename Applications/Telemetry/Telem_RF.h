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



/** @brief RF telemetry packet container
 *
 *	This simple structure is used to build an RF telemetry packet fragment packet and simple holds and entire packet in
 *	its payload member.
 *
 */
typedef struct telem_rf_PACKET {
	unsigned char payload_length; /**< Payload length in bytes */
	unsigned char payload[TELEM_RF_PACKET_PAYLOAD_LEN]; /**< Payload data byte array */
} telem_rf_PACKET_STRUCT;






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




/**@brief
 *
 *
 *
 */
void init_app_telem_rf_fifo(void);


/**@brief
 *
 *
 *
 */
void telem_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config);


/**@brief
 *
 *
 *
 */
void telem_rf(void);


/**@brief
 *
 *
 *
 */
void app_telem_rf_rx_put(unsigned char *packet);


/**@brief
 *
 *
 *
 */
void app_telem_rf_housekeeping(void);


/**@brief
 *
 *
 *
 */
void app_telem_rf_pkt_1_state_machine(unsigned char *packet);

#endif /* APPLICATIONS_telem_rf_telem_rf_H_ */
