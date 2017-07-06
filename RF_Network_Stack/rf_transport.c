/** @file rf_transport.c
 * 	@brief The layer 4 RF experimental protocol
 *
 * 	These functions create the experimental RF layer 4 (transport) protocol. The protocol is a fixed length protocol and provides
 * 	no error detection. Packet fragmentation is not supported and therefor the layer 4 protocol packets much be equal to or smaller
 * 	than the maximum transmissible unit of the lower layers.
 *
 * 	@todo Are all of these headers actually used?
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "rf_transport.h"

/* faraday rf layer 2 include */
#include "rf.h"

/* faraday rf layer 4 service include */
#include "rf_service.h"

/* faraday fifo include */
#include "../Ring_Buffers/FIFO.h"

/* faraday hardware allocation include */
#include "../REVA_Faraday.h"

/* faraday gpio hardware abstraction functions */
#include "../HAL/GPIO.h"

/* faraday device configuration application include */
#include "../Applications/Device_Config/Device_Config.h"


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
		unsigned char L2_packet_config){
			RF_TRANSPORT_PACKET_STRUCT rf_transport_packet_tx_struct;
			rf_transport_tx_create_packet((unsigned char *)L4_payload_buffer, L4_payload_len, L4_service_number, &rf_transport_packet_tx_struct);
			__no_operation();
			rf_tx_datalink_packet(L2_src_callsign, L2_src_callsign_len,	L2_src_callsign_id, L2_dest_callsign, L2_dest_callsign_len, L2_dest_callsign_id, L2_packet_type, L2_packet_config, RF_TRANPORT_PACKET_LEN, &rf_transport_packet_tx_struct);
			__no_operation();
			}


unsigned char rf_transport_tx_create_packet(unsigned char *payload_buffer, unsigned char payload_len, unsigned char service_number, RF_TRANSPORT_PACKET_STRUCT *packet_struct){
	packet_struct->payload_length = payload_len;
	packet_struct->service_number = service_number;

	if( packet_struct->payload_length<=RF_TRANPORT_PAYLOAD_MAX_LEN){
		unsigned char i;
		//Place payload into packet struct
		for(i=0; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
			packet_struct->payload[i] = payload_buffer[i];
		}

		//Pad payload (if needed)
		for(i=payload_len; i<RF_TRANPORT_PAYLOAD_MAX_LEN; i++){
			packet_struct->payload[i] = 0xFF; //Padding
		}
		return 1;
	}
	else{
		//Payload too long!
		return 0;
	}

}

void rf_transport_parse(unsigned char *packet, unsigned char broadcast_status){
	RF_TRANSPORT_PACKET_STRUCT rf_transport_packet_rx_struct;

	//Parse received RX Transport datagram
	unsigned char i;
	rf_transport_packet_rx_struct.payload_length = packet[RF_TRANPORT_PACKET_PAYLOAD_LEN_LOC];
	rf_transport_packet_rx_struct.service_number = packet[RF_TRANPORT_PACKET_SERVICE_NUMBER_LOC];

	//Check if transport payload is larger than valid to avoid overflow
	if(rf_transport_packet_rx_struct.payload_length<=RF_TRANPORT_PAYLOAD_MAX_LEN){
		for(i=0;i<RF_TRANPORT_PAYLOAD_MAX_LEN;i++){ // BUG: Using just RF_TRANPORT_PAYLOAD_MAX_LEN is probably not a long term good idea
			rf_transport_packet_rx_struct.payload[i] = packet[(RF_TRANPORT_PACKET_PAYLOAD_LOC + RF_TRANPORT_PACKET_PAYLOAD_LEN_LOC)+i];
		}
		//Check if receive port is safe for broadcast reception
		if((rf_rx_service_broadcast_rule_get(rf_transport_packet_rx_struct.service_number) != 0) && (broadcast_status == 1)){
			//Turn on receive LED indicator if configuration allows
			if(config_bitmask & RX_GREEN_INDICATOR){
				gpio_update(3, LED_1, 1);
			}

			//Broadcast reception safe
			rf_rx_stack_rx(rf_transport_packet_rx_struct.service_number, rf_transport_packet_rx_struct.payload, rf_transport_packet_rx_struct.payload_length);
			__no_operation();

			//Turn off receive LED indicator if configuration allows
			if(config_bitmask & RX_GREEN_INDICATOR){
				gpio_update(3, LED_1, 0);
			}
		}
		else if(broadcast_status != 1){
			//Turn on receive LED indicator if configuration allows
			if(config_bitmask & RX_GREEN_INDICATOR){
				gpio_update(3, LED_1, 1);
			}

			//Not a broadcast packet
			rf_rx_stack_rx(rf_transport_packet_rx_struct.service_number, rf_transport_packet_rx_struct.payload, rf_transport_packet_rx_struct.payload_length);
			__no_operation();

			//Turn off receive LED indicator if configuration allows
			if(config_bitmask & RX_GREEN_INDICATOR){
				gpio_update(3, LED_1, 0);
			}
		}
		else{
			//Transport layer port not allowed with broadcast packet callsign! Discard packet.
			__no_operation();
		}
	}
	else{
		//Payload is too long, corrupted packet! Drop.
	}

}

