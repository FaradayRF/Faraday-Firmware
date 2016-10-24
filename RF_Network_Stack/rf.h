#ifndef RF_NETWORK_STACK_RF_H_
#define RF_NETWORK_STACK_RF_H_



/** @name Radio Transmit/Receive Layer 2 Packet Definitions
* 	@brief Basic low level packet definitions for Layer 2 (Datalink)
@{**/
#define TX_PACKET_LEN 61 /**< Transmit packet size */
#define RX_PACKET_LEN 61 /**< Receive packet size */
#define RX_PKT_HANDLE_APPEND_LEN 2 /**< Packet hardware receive append data byte size */
/** @}*/



/** @name RF Layer 2 FIFO Definitions
* 	@brief Layer 2 definitions that support the FIFO buffers
*
* 	@bug Why is RF_DATALINK_PACKET_PAYLOAD_LEN 62 bytes instead of 61? RX extra footer bytes?
* 	@bug All of this should be updated to be in the main definitions and not FIFO specific!
*
@{**/
#define RF_DATALINK_PACKET_PAYLOAD_LEN 62 /**< FIFO definition for packet length */
#define RF_DATALINK_PACKET_FIFO_COUNT 5 /**< FIFO definition for max number of packets to hold in a FIFO */
#define RF_DATALINK_PACKET_RX_FOOTER_LEN 2 /**< FIFO definition for receive footer byte count */
/** @}*/



/** @name RF Layer 2 Packet Parsing Definitions
* 	@brief Layer 2 definitions that support the parsing of packets
*
* 	@bug Layer 2 is the only layer with a callsign length of 6 bytes instead of 9!
* 	@bug Is RF_DATALINK_PKT_PKT_LEN_LOC really needed???
*
@{**/
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC 0 /**< Source callsign packet index location */
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN 6 /**< Source callsign length packet index location */
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_ID_LOC 6 /**< Source callsign ID number packet index location */
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC 7 /**< Destination callsign packet index location */
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN 6 /**< Destination callsign length packet index location */
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_ID_LOC 13 /**< Destination callsign ID number packet index location */
#define RF_DATALINK_PKT_PKT_TYPE_LOC 14 /**< Layer 2 packet type byte packet index location */
#define RF_DATALINK_PKT_PKT_CONFIG_LOC 15 /**< Layer 2 packet configuration bitmask byte packet index location */
#define RF_DATALINK_PKT_PKT_LEN_LOC 16 /**< Layer 2 packet length byte packet index location */
#define RF_DATALINK_PKT_PAYLOAD_LOC 17 /**< Layer 2 payload data packet index location */
#define RF_DATALINK_PKT_PAYLOAD_LEN 44 /**< Layer 2 payload length byte packet index location */
#define RF_DATALINK_PKT_LQI_LOC 61 /**< CC430 Layer 2 receive appended Link Quality Indicator byte packet index location */
#define RF_DATALINK_PKT_RSSI_LOC 62 /**< CC430 Layer 2 receive appended receive signal strength indicator packet index location */
/** @}*/


/** @brief Layer 2 packet structure
*
* 	This structure holds all of the layer 2 packet fields and is used to create/parse
* 	datalink layer packets.
*
* 	@bug 44 instead of 45 due to UART transport layer limitation of 63 payload bytes...
*
@{**/
typedef struct RF_L2_PACKET {
	char source_callsign[RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN]; /**< Source callsign char array */
	unsigned char source_indetifier; /**< source callsign ID number */
	char destination_callsign[6]; /**< Destination callsign char array */
	unsigned char destination_identifier; /**< Destination callsign ID number */
	unsigned char packet_type; /**< Packet type byte */
	unsigned char packet_config; /**< Packet configuration byte bitmask */
	unsigned char payload_length; /**< Packet payload length byte */
	unsigned char payload[44]; /**< Payload data byte array */
	unsigned char rssi; /**< Receive signal strength indicator */
	unsigned char lqi; /**< Link quality indicator */
} RF_DATALINK_PACKET_STRUCT;



/**@brief
 *
 */
void init_radio_faraday(void);


/**@brief
 *
 */
void radio_load_defaults(unsigned char freq2, unsigned char freq1, unsigned char freq0);


/**@brief
 *
 */
void init_rf_fifo(void);


/**@brief
 *
 */
void radio_manual_calibration_idle(void);


/**@brief
 *
 */
void radio_manual_idle(void);


/**@brief
 *
 */
void TransmitOn(void);


/**@brief
 *
 */
void Transmit(unsigned char *buffer, unsigned char length);


/**@brief
 *
 */
void ReceiveOn(void);


/**@brief
 *
 */
void ReceiveOff(void);


/**@brief
 *
 */
void radio_isr(void);


/**@brief
 *
 */
void radio_housekeeping(void);


/**@brief
 *
 */
void radio_tx(unsigned char *buffer, unsigned char buffer_len);


/**@brief
 *
 */
void rf_tx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length);


/**@brief
 *
 */
unsigned char rf_tx_inwait_packet_buffer(void);


/**@brief
 *
 */
unsigned char rf_tx_get_packet_buffer(unsigned char *buffer);


/**@brief
 *
 */
void rf_rx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length);


/**@brief
 *
 */
unsigned char rf_rx_get_packet_buffer(unsigned char *buffer);


/**@brief
 *
 */
void rf_get_next_tx_fifo(void);


/**@brief
 *
 */
unsigned char rf_check_tx_fifo(void);


/**@brief
 *
 */
void rf_housekeeping(void);


/**@brief
 *
 */
unsigned char rf_tx_datalink_packet(char *src_callsign, unsigned char src_callsign_len, unsigned char src_callsign_id, char *dest_callsign, unsigned char dest_callsign_len, unsigned char dest_callsign_id, unsigned char packet_type, unsigned char packet_config, unsigned char payload_len, unsigned char *payload);


/**@brief
 *
 */
void rf_send_test_rf_1(void);


/**@brief
 *
 */
void rf_rawpacket_tx(RF_DATALINK_PACKET_STRUCT *packet_data_pointer); // 2/23/2016 - BSALMI - I think this is how we should move to passing structs!


/**@brief
 *
 */
void rf_datalink_parse(unsigned char *packet);


/**@brief
 *
 */
void CC430_Program_Freq(unsigned char freq2, unsigned char freq1, unsigned char freq0);

#endif /* RF_NETWORK_STACK_RF_H_ */
