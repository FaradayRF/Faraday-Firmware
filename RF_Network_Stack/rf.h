#ifndef RF_NETWORK_STACK_RF_H_
#define RF_NETWORK_STACK_RF_H_

//RF Datalink PACKET Parse Definitions
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC 0
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN 6
#define RF_DATALINK_PKT_SOURCE_CALLSIGN_ID_LOC 6
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC 7
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN 6
#define RF_DATALINK_PKT_DESTINATION_CALLSIGN_ID_LOC 13
#define RF_DATALINK_PKT_PKT_TYPE_LOC 14
#define RF_DATALINK_PKT_PKT_CONFIG_LOC 15
#define RF_DATALINK_PKT_PKT_LEN_LOC 16
#define RF_DATALINK_PKT_PAYLOAD_LOC 17
#define RF_DATALINK_PKT_PAYLOAD_LEN 44
#define RF_DATALINK_PKT_LQI_LOC 61 //Needs bitmask due to CRC bit
#define RF_DATALINK_PKT_RSSI_LOC 62


char mycall[6];
char cqcall[6];


typedef struct RF_L2_PACKET {
	char source_callsign[6];
	unsigned char source_indetifier;
	char destination_callsign[6];
	unsigned char destination_identifier;
	unsigned char packet_type;
	unsigned char packet_config;
	unsigned char payload_length;
	unsigned char payload[44]; // 44 instead of 45 due to UART transport layer limitation of 63 payload bytes... BUG! Fix!
	unsigned char rssi;
	unsigned char lqi;
} RF_DATALINK_PACKET_STRUCT;


volatile RF_DATALINK_PACKET_STRUCT rf_datalink_packet_tx_struct;
volatile RF_DATALINK_PACKET_STRUCT rf_datalink_packet_rx_struct;

void init_radio_faraday(void);
void radio_load_defaults(unsigned char freq2, unsigned char freq1, unsigned char freq0);
void init_rf_fifo(void);
void radio_manual_calibration_idle(void);
void radio_manual_idle(void);
void TransmitOn(void);
void Transmit(unsigned char *buffer, unsigned char length);
void ReceiveOn(void);
void ReceiveOff(void);
void radio_isr(void);
void radio_housekeeping(void);
void radio_tx(unsigned char *buffer, unsigned char buffer_len);

void rf_tx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length);
unsigned char rf_tx_inwait_packet_buffer(void);
unsigned char rf_tx_get_packet_buffer(unsigned char *buffer);
void rf_rx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length);
//unsigned char rf_rx_inwait_packet_buffer(void);
unsigned char rf_rx_get_packet_buffer(unsigned char *buffer);

void rf_get_next_tx_fifo(void);
unsigned char rf_check_tx_fifo(void);
void rf_housekeeping(void);
unsigned char rf_tx_datalink_packet(char *src_callsign, unsigned char src_callsign_len, unsigned char src_callsign_id, char *dest_callsign, unsigned char dest_callsign_len, unsigned char dest_callsign_id, unsigned char packet_type, unsigned char packet_config, unsigned char payload_len, unsigned char *payload);
void rf_send_test_rf_1(void);
void rf_rawpacket_tx(RF_DATALINK_PACKET_STRUCT *packet_data_pointer); // 2/23/2016 - BSALMI - I think this is how we should move to passing structs!
void rf_datalink_parse(unsigned char *packet);
void CC430_Program_Freq(unsigned char freq2, unsigned char freq1, unsigned char freq0);
#endif /* RF_NETWORK_STACK_RF_H_ */
