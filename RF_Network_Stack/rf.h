/** @file rf.h
 * 	@brief The layer 2 RF experimental protocol
 *
 * 	These functions create the experimental RF layer 2 (datalink) protocol. The protocol is a fixed length protocol and provides
 * 	no error detection. Packet fragmentation is not supported.
 *
 * 	The current implementation of the protocol utilizes the CC430 packet handling hardware that limits the packet to 64 bytes. Updates
 * 	are known through CC430 application notes that all unlimited packet size as well as handling all packet functions in firmware for
 * 	maximum flexability. These updates would greatly increase throughput.
 *
 */

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
	unsigned char source_identifier; /**< source callsign ID number */
	char destination_callsign[6]; /**< Destination callsign char array */
	unsigned char destination_identifier; /**< Destination callsign ID number */
	unsigned char packet_type; /**< Packet type byte */
	unsigned char packet_config; /**< Packet configuration byte bitmask */
	unsigned char payload_length; /**< Packet payload length byte */
	unsigned char payload[44]; /**< Payload data byte array */
	unsigned char rssi; /**< Receive signal strength indicator */
	unsigned char lqi; /**< Link quality indicator */
} RF_DATALINK_PACKET_STRUCT;



/**@brief Initialize the CC430 radio to default operation
 *
 *	Initialize the CC430 radio to default operation.
 *
 */
void init_radio_faraday(void);


/**@brief Load default CC430 frequency
 *  Update the CC430 HAL "RfSettings" frequency registers definitions with supplied values.
 *  Reference the CC430 users guide for more information about the CC430 radio registers.
 *
 *  @param freq2 MSB index of the 3 byte radio module register
 *  @param freq1 Index [1] of the 3 byte radio module register
 *  @param freq0 LSB index of the 3 byte radio module register
 */
void radio_load_default_frequency(unsigned char freq2, unsigned char freq1, unsigned char freq0);


/**@brief Initialize layer 2 radio FIFO buffers
 *
 *	Initialize layer 2 radio FIFO buffers used for both transmit and receive.
 *
 */
void init_rf_fifo(void);


/**@brief Perform CC430 radio module manual calibration
 *  Perform CC430 radio module manual calibration routine that re-calibrates the PLL. This is only needed
 *  in specific situations and if not used correctly can cause the radio to miss packets or otherwise error.
 */
void radio_manual_calibration_idle(void);


/**@brief Place CC430 radio into IDLE state
 *
 *	Place CC430 radio into IDLE state.
 *
 */
void radio_manual_idle(void);


/**@brief Perform routine to enable both CC430 and external amplifier for transmit operation
 *
 *  Perform routine to enable both CC430 and external amplifier for transmit operation.
 *
 */
void TransmitOn(void);


/**@brief Place data into the CC430 packet handling hardware and transmit the data
 *
 *	Place data into the CC430 packet handling hardware and transmit the data.
 *
 *	@param buffer A pointer to the data to be transmitted
 *	@param Length in bytes of the data to be transmitted
 *
 */
void Transmit(unsigned char *buffer, unsigned char length);


/**@brief Perform routine routine to enable both CC430 and external amplifier for receive opertion
 *
 * Perform routine routine to enable both CC430 and external amplifier for receive opertion.
 *
 */
void ReceiveOn(void);


/**@brief Perform routine routine to disable both CC430 and external amplifier for receive opertion
 *
 *	Perform routine routine to disable both CC430 and external amplifier for receive opertion
 *
 */
void ReceiveOff(void);


/**@brief A function that holds the routines needed to operation the ISR
 *
 *	This function performs the needed checks and routines to operate the CC430 layer 2 operations that
 *	must be performed on the interrupt serive routine interrupts.
 *
 */
void radio_isr(void);


/**@brief Function used to place data to be transmitted into the transmit FIFO buffer
 *
 * This function is used to put data into the layer 2 transmit FIFO buffer for transmission.
 *
 * @param packet_data_pointer Pointer to the data to be transmitted
 * @param length Length in bytes of the data to be transmitted
 *
 */
void rf_tx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length);


/**@brief Gets the next packet in the transmit FIFO and transmits it
 *
 * This function is used to retrieve a waiting packet from the transmit FIFO buffer and transmit it using
 * the CC430 packet handling hardware.
 *
 */
void rf_get_next_tx_fifo(void);


/**@brief Check if a packet is waiting in the transmit FIFO
 *
 *  Check if a packet is waiting in the transmit FIFO to be transmited.
 *
 *  @retval Returns 1 if 1 or more packets are waiting in the FIFO to be transmitted. Returns 0 if no packets are waiting.
 *
 */
unsigned char rf_check_tx_fifo(void);


/**@brief Main housekeeping routine function
 *
 * This is the main housekeeping routine used to perform checks for needed actions that operate the layer 2 protocol. The
 * actions perform include checking FIFO's for waiting data to be retrieved and performed actions accordingly.
 *
 */
void rf_housekeeping(void);


/**@brief Fill rf_datalink_packet_tx_struct with data to create a layer 2 transmit packet
 *
 *	This function is used to build a layer 2 transmit packet using the packet structure (rf_datalink_packet_tx_struct). Supplied information in the
 *	function arguments provide the data to fill the packet fields as defined.
 *
 *	@param src_callsign A pointer to the packet's source callsign characters
 *	@param src_callsign_len Source callsign length in bytes
 *	@param src_callsign_id Source callsign ID number
 *	@param dest_callsign A pointer to the packet's destination callsign characters
 *	@param dest_callsign_len Destination callsign length in bytes
 *	@param dest_callsign_id Destination callsign ID number
 *	@param packet_type A byte that describes the packet type to allow multuple packet types to be supported
 *	@param packet_config A bitmask that allows packet and protocol configuration settings/flags
 *	@param payload_len Length in bytes of the supplied payload data
 *
 *	@retval Returns 1 if packet creation was successful and 0 if not (due to payload/callsign size too large)
 *
 */
unsigned char rf_tx_datalink_packet(char *src_callsign, unsigned char src_callsign_len, unsigned char src_callsign_id, char *dest_callsign, unsigned char dest_callsign_len, unsigned char dest_callsign_id, unsigned char packet_type, unsigned char packet_config, unsigned char payload_len, unsigned char *payload);


/**@brief
 *
 */
//void rf_send_test_rf_1(void);


/**@brief Abstraction function used to place a transmit packet into the transmit FIFO
 *
 *  Abstraction function used to place a transmit packet into the transmit FIFO.
 *
 *  @param packet_data_pointer A pointer to a structure variable of type RF_DATALINK_PACKET_STRUCT that contains the defined and filled packet data
 *
 */
void rf_rawpacket_tx(RF_DATALINK_PACKET_STRUCT *packet_data_pointer); // 2/23/2016 - BSALMI - I think this is how we should move to passing structs!


/**@brief Parse a received layer 2 packet
 *
 * This function is used to parse a supplied raw layer 2 packet as received into a structure defined with
 * fields expected for the received packet type.
 *
 * @param packet A pointer to the received raw packet bytearray to be parsed.
 *
 */
void rf_datalink_parse(unsigned char *packet);


/**@brief Update the current RF frequency
 *
 *  This function is used to update the current CC430 radio module frequency.
 *  Reference the CC430 users guide for more information about the CC430 radio registers.
 *
 *  @param freq2 MSB index of the 3 byte radio module register
 *  @param freq1 Index [1] of the 3 byte radio module register
 *  @param freq0 LSB index of the 3 byte radio module register
 *
 */
void CC430_Program_Freq(unsigned char freq2, unsigned char freq1, unsigned char freq0);

/**@brief Check the RF layer 2 transmitting flag byte
 *
 *  This function returns the current layer 2 RF network stack transmitting flag. This is useful
 *  to query whether Faraday is current in RF transission mode or not.
 *
 *	@retval transmitting_flag
 *
 */
unsigned char CC430_Check_Transmitting_Flag(void);

#endif /* RF_NETWORK_STACK_RF_H_ */
