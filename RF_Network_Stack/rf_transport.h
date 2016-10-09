/*
 * rf_transport.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Brent
 */

#ifndef RF_NETWORK_STACK_RF_TRANSPORT_H_
#define RF_NETWORK_STACK_RF_TRANSPORT_H_

//#include "../Ring_Buffers/Packet_Ring_Buffer.h"

#define RF_TRANPORT_PACKET_LEN 44
#define RF_TRANPORT_PAYLOAD_MAX_LEN 42
#define RF_TRANPORT_PACKET_PAYLOAD_LEN_LOC 0
#define RF_TRANPORT_PACKET_PAYLOAD_LOC 1
#define RF_TRANPORT_PACKET_SERVICE_NUMBER_LOC 43

typedef struct RF_TRANSPORT_PACKET {
	unsigned char payload_length;
	unsigned char payload[RF_TRANPORT_PAYLOAD_MAX_LEN];
	unsigned char service_number;

} RF_TRANSPORT_PACKET_STRUCT;

#define TX_STATE_IDLE 0
#define TX_STATE_PREPARE 1
#define TX_STATE_TRANSMIT_MAIN 2
#define TX_STATE_TRANSMIT_FINAL 3
#define TX_STATE_END 4
#define TX_DATALINK_LAYER_PAYLOAD_MTU 44 //Maximum transmitable unit for datalink layer

#define RX_STATE_RECEIVE_IDLE 0
#define RX_STATE_RECEIVE_START 1
#define RX_STATE_RECEIVE_RECEIVE 2
#define RX_STATE_RECEIVE_END 3
#define RX_DATALINK_LAYER_PAYLOAD_MTU 44 //Maximum transmitable unit for datalink layer

typedef struct RF_TRANSPORT_TX_STATE_MACHINE {
	unsigned char state;
	unsigned char fragment_count;
	unsigned char padding_byte_count;
	unsigned char count;

} RF_TRANSPORT_TRANSMIT_STATE_MACHINE;

//Packet Ring Buffer
//volatile RF_TRANSPORT_PACKET_STRUCT rf_transport_packet_rx_struct;

//Transmit state machine
//volatile RF_TRANSPORT_TRANSMIT_STATE_MACHINE rf_transport_transmit_state_machine_struct;
//volatile RF_TRANSPORT_TRANSMIT_STATE_MACHINE rf_transport_receive_state_machine_struct;

//Packet Ring Buffer
//volatile packet_ring_buffer_64 rf_transport_fragment_test_struct;

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

unsigned char rf_transport_tx_create_packet(unsigned char *payload_buffer, unsigned char payload_len, unsigned char service_number, RF_TRANSPORT_PACKET_STRUCT *packet_struct);
void rf_transport_parse(unsigned char *packet, unsigned char broadcast_status);
void rf_transport_rx_action(void);

#endif /* RF_NETWORK_STACK_RF_TRANSPORT_H_ */
