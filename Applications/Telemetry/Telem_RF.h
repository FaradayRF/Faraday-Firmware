#ifndef APPLICATIONS_telem_rf_telem_rf_H_
#define APPLICATIONS_telem_rf_telem_rf_H_

#define TELEM_RF_PACKET_PACKET_ID_LOC 0
#define TELEM_RF_PACKET_1_LEN 123 //123 to match telemetry fixed packet LENGTH
#define TELEM_RF_PACKET_1_FRAG_END_LEN 6 //Hardcoded to avoid packet overruns in noisy environments due to simple stack design
#define TELEM_RF_FRAGMENT_MAX_LEN 39

#define TELEM_RF_PACKET_PAYLOAD_LEN 42
#define TELEM_RF_PACKET_FIFO_COUNT 8


typedef struct telem_rf_PACKET_CONFIG {
	unsigned char RF_L4_service_number;
	char RF_L2_source_callsign[6];
	unsigned char RF_L2_source_callsign_len;
	unsigned char RF_L2_source_indetifier;
	char RF_L2_destination_callsign[6];
	unsigned char RF_L2_destination_callsign_len;
	unsigned char RF_L2_destination_identifier;
	unsigned char RF_L2_packet_type;
	unsigned char RF_L2_packet_config;

} telem_rf_PACKET_CONFIG_STRUCT;

#define telem_rf_PAYLOAD_MAX_LEN 42
#define telem_rf_RF_CONFIG_LEN 19
typedef struct telem_rf_PACKET {
	unsigned char payload_length;
	unsigned char payload[telem_rf_PAYLOAD_MAX_LEN];
} telem_rf_PACKET_STRUCT;

typedef struct RF_TELEMETRY_PACKET_DATAGRAM {
	unsigned char packet_type;
	unsigned char data[41];
} RF_TELEMETRY_PACKET_DATAGRAM_STRUCT;

typedef struct RF_TELEMETRY_PACKET_1 {
	char callsign[9];
	unsigned char callsign_id;
	unsigned char callsign_length;
	char gps_lattitude[9];
	char gps_lattitude_dir;
	char gps_longitude[10];
	char gps_longitude_dir;
} RF_TELEMETRY_PACKET_1_STRUCT;

typedef struct RF_TELEMETRY_PACKET_2 {
	char callsign[9];
	unsigned char callsign_id;
	unsigned char callsign_length;
	char gps_altitude[8];
	char gps_speed[5];
	unsigned int adc_0;
	unsigned int adc_1;
	unsigned int adc_2;
	unsigned int adc_3;
	unsigned int adc_4;
	unsigned int adc_5;
	unsigned int adc_6;
} RF_TELEMETRY_PACKET_2_STRUCT;

typedef struct RF_TELEMETRY_PACKET_3 {
	char callsign[9];
	unsigned char callsign_id;
	unsigned char callsign_length;
	unsigned int adc_7;
	unsigned int adc_8;
} RF_TELEMETRY_PACKET_3_STRUCT;

typedef struct TELEMETRY_RF_PACKET_DATAGRAM {
	unsigned char packet_type;
	unsigned char sequence;
	unsigned char data_length;
	unsigned char data[39];
} TELEMETRY_RF_PACKET_DATAGRAM_STRUCT;


//volatile telem_rf_PACKET_STRUCT app_telem_rf_packet_struct;

#define STATE_START 0
#define STATE_STOP 255
typedef struct TELEMETRY_RF_PACKET_STATE_MACHINE {
	unsigned char state;
	unsigned char data_length;
	unsigned char data[128];
} TELEMETRY_RF_PACKET_STATE_MACHINE_STRUCT;

void application_telem_rf_telemetry_initialize(void);
void init_app_telem_rf_fifo(void);
void telem_rf_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config);
void telem_rf(void);
void telem_rf_create_pkt_1(unsigned char *packet);
void telem_rf_create_pkt_2(unsigned char *packet);
void telem_rf_create_pkt_3(unsigned char *packet);
void app_telem_rf_rx_put(unsigned char *packet);
void app_telem_rf_housekeeping(void);
void app_telem_rf_pkt_1_state_machine(unsigned char *packet);

#endif /* APPLICATIONS_telem_rf_telem_rf_H_ */
