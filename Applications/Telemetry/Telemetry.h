/** @file Telemetry.h
 * 	@brief Faraday telemetry application
 *
 * 	This application provides the telemetry data application functions for Faraday. Sensors and other
 * 	data are gathered, packetized, and transfered to the intended path for telemetry purposes.
 *
 */

#ifndef APPLICATIONS_TELEMETRY_H_
#define APPLICATIONS_TELEMETRY_H_

volatile extern unsigned char app_telem_uart_boot_bits;
volatile extern unsigned char app_telem_rf_boot_bits;

#define CHARSIZE 1

#define APP_TELEM_PACKET_LEN 123
#define APP_TELEM_PACKET_PAYLOAD_LEN 118
#define APP_TELEM_PACKET_TYPE_2_LEN 14
#define APP_TELEM_PACKET_TYPE_3_LEN 91 + 6 //Defining instead of sizeof(struct) due to memory data alignment! // +6 for TEMP HAB DATA
#define APP_TELEM_PACKET_FIFO_COUNT 1

volatile unsigned char manual_telem_status;

typedef struct TELEMETRY {
	unsigned char temp_0[64];
	unsigned char temp_1[64];
	unsigned char GPIO_State;
	unsigned char IO_State;
	unsigned char RF_State;
} TELEMETRYDATA;

typedef struct TELEMETRY_PACKET_DATAGRAM {
	unsigned char packet_type;
	unsigned char rf_source;
	unsigned char data_length;
	unsigned char data[APP_TELEM_PACKET_PAYLOAD_LEN];
	unsigned char error_detection_16[2];
} TELEMETRY_PACKET_DATAGRAM_STRUCT;

typedef struct TELEMETRY_PACKET_1 {
	unsigned char rf_freq2;
	unsigned char rf_freq1;
	unsigned char rf_freq0;
	unsigned char rf_pwr;
} TELEMETRY_PACKET_1_STRUCT;

typedef struct TELEMETRY_PACKET_2 {
	unsigned int boot_cnt;
	unsigned char reset_cnt;
	unsigned char BOR;
	unsigned char RSTNMI;
	unsigned char SVSL;
	unsigned char SVSH;
	unsigned char SVML_OVP;
	unsigned char SVMH_OVP;
	unsigned char WDT_TIMEOUT;
	unsigned char FLASHKEY;
	unsigned char FLL_UNLOCK;
	unsigned char PERIPH_CONFIG;
	unsigned char ACCESS_VIOLATION;
} TELEMETRY_PACKET_2_STRUCT;

typedef struct TELEMETRY_PACKET_3 {
	char source_callsign[9];
	unsigned char source_callsign_length;
	unsigned char source_callsign_id;
	char destination_callsign[9];
	unsigned char destination_callsign_length;
	unsigned char destination_callsign_id;
	unsigned char rtc_second;
	unsigned char rtc_minute;
	unsigned char rtc_hour;
	unsigned char rtc_day;
	unsigned char rtc_dow;
	unsigned char rtc_month;
	unsigned int rtc_year;
	char gps_lattitude[9];
	char gps_lattitude_dir;
	char gps_longitude[10];
	char gps_longitude_dir;
	char gps_altitude[8];
	char gps_altitude_units;
	char gps_speed[5];
	char gps_fix;
	char gps_hdop[4];
	unsigned char gpio_state;
	unsigned char io_state;
	unsigned char rf_state;
	unsigned char adc_0[2];
	unsigned char adc_1[2];
	unsigned char adc_2[2];
	unsigned char adc_3[2];
	unsigned char adc_4[2];
	unsigned char adc_5[2];
	unsigned char adc_6[2];
	unsigned char adc_7[2];
	unsigned char adc_8[2];
	unsigned char HAB_DATA[6];
	//unsigned char error_detection[2];
} TELEMETRY_PACKET_3_STRUCT;


volatile TELEMETRYDATA rftelem;

void manual_telem_led_alert_5hz(void);

typedef struct RF_APP_PACKET {
	unsigned char payload_length;
	unsigned char service_number;
	unsigned char payload[28];
} RF_APP_PACKET_STRUCT;

RF_APP_PACKET_STRUCT test_structrx;
RF_APP_PACKET_STRUCT test_structtx;


// RF Service
void app_telem_rf_rx_command_put(unsigned char *data_pointer, unsigned char length);
// END RF Service

void app_telem_rf_rx_housekeep(void);
void app_telem_rx_remote_telem(unsigned char *data);

void application_telemetry_initialize(void);
void init_app_telem_fifo(void);
void app_telem_housekeeping(void);
void application_send_uart_packet(unsigned char *packet);
void application_load_defaults(void);
void application_send_telemetry_packet_1(void);
void application_send_telemetry_device_debug(void);
void application_send_telemetry_3(char *string, unsigned char callsignlength, unsigned char ID);
void application_telem_create_pkt_1(unsigned char *packet);
void application_telem_create_pkt_2(unsigned char *packet);
void application_telem_create_pkt(unsigned char *packet, char *src_callsign, unsigned char src_callsign_len, unsigned char src_callsign_id, char *dest_callsign, unsigned char dest_callsign_len, unsigned char dest_callsign_id);
void application_adc_gather(void);
void application_gps_gather(void);
void application_adc_send_names_uart(void);
void radio_tx_button(void);
void application_update_RTC_calender_gps(void);
void application_send_rf_telemetry(unsigned char *string,unsigned char callsignlength, unsigned char ID);
void telemetry_rf_transport_rx(void);
void telem_application_rx_rf_parse(void);
void application_telemetry_send_self(void);
void application_telemetry_send_device_debug_telem(void);
void application_telemetry_uart_housekeeping_interval(void);
#endif /* APPLICATIONS_TELEMETRY_TELEMETRY_H_ */
