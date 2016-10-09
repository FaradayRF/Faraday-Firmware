/*
 * Test_RF.h
 *
 *  Created on: Mar 30, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_TEST_RF_TEST_RF_H_
#define APPLICATIONS_TEST_RF_TEST_RF_H_

typedef struct TEST_RF_PACKET_CONFIG {
	unsigned char RF_L4_service_number;
	char RF_L2_source_callsign[6];
	unsigned char RF_L2_source_callsign_len;
	unsigned char RF_L2_source_indetifier;
	char RF_L2_destination_callsign[6];
	unsigned char RF_L2_destination_callsign_len;
	unsigned char RF_L2_destination_identifier;
	unsigned char RF_L2_packet_type;
	unsigned char RF_L2_packet_config;

} TEST_RF_PACKET_CONFIG_STRUCT;

#define TEST_RF_PAYLOAD_MAX_LEN 42
#define TEST_RF_RF_CONFIG_LEN 19
typedef struct TEST_RF_PACKET {
	unsigned char payload_length;
	unsigned char payload[TEST_RF_PAYLOAD_MAX_LEN];
} TEST_RF_PACKET_STRUCT;


//volatile TEST_RF_PACKET_STRUCT app_test_rf_packet_struct;

void application_test_rf_telemetry_initialize(void);
void init_app_test_rf_fifo(void);
void test_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config);
void test_rf(void);
void app_test_rf_rx_put(unsigned char *packet);
void app_test_rf_housekeeping(void);

#endif /* APPLICATIONS_TEST_RF_TEST_RF_H_ */
