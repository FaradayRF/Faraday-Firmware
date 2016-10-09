/*
 * command.h
 *
 *  Created on: Apr 2, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_COMMAND_COMMAND_H_
#define APPLICATIONS_COMMAND_COMMAND_H_

//Configuration Update Definitions
#define MAX_CONFIGURATION_UPDATE_PACKET_LEN 124

//Read Memory definitions
#define CMD_READ_MEMORY_MAX_LENGTH 121
#define CMD_READ_MEMORY_UART_PORT 2

typedef struct COMMAND_PACKET {
	unsigned char command;
	char payload_len;
	unsigned char payload[119];
	unsigned char error_detection_16[2];
} COMMAND_PACKET_STRUCT;

typedef struct COMMAND_PACKET_ECHO {
	unsigned char payload[124];
} COMMAND_PACKET_ECHO_STRUCT;

typedef struct COMMAND_PACKET_READ_MEMORY_GET {
	unsigned char memory_address_h;
	unsigned char memory_address_l;
	unsigned char length;
} COMMAND_PACKET_READ_MEMORY_GET_STRUCT;

typedef struct COMMAND_PACKET_READ_MEMORY_SEND {
	unsigned char memory_address_h;
	unsigned char memory_address_l;
	unsigned char payload[121];
} COMMAND_PACKET_READ_MEMORY_SEND_STRUCT;

typedef struct GPIO_COMMAND_PACKET {
	unsigned char port_3_on;
	unsigned char port_4_on;
	unsigned char port_5_on;
	unsigned char port_3_off;
	unsigned char port_4_off;
	unsigned char port_5_off;
} GPIO_COMMAND_PACKET_STRUCT;

typedef struct RF_COMMAND_PACKET {
	char dest_callsign[9];
	unsigned char dest_callsign_len;
	unsigned char dest_device_id;
	unsigned char cmd_app_datagram_remote[29];
	unsigned char checksum_16[2]
} RF_COMMAND_PACKET_STRUCT;


typedef struct APP_COMMAND_PACKET_CONFIG {
	unsigned char RF_L4_service_number;
	char RF_L2_source_callsign[6];
	unsigned char RF_L2_source_callsign_len;
	unsigned char RF_L2_source_indetifier;
	char RF_L2_destination_callsign[6];
	unsigned char RF_L2_destination_callsign_len;
	unsigned char RF_L2_destination_identifier;
	unsigned char RF_L2_packet_type;
	unsigned char RF_L2_packet_config;

} APP_COMMAND_PACKET_CONFIG_STRUCT;

#define APP_COMMAND_PAYLOAD_MAX_LEN 42
#define APP_COMMAND_RF_CONFIG_LEN 19
typedef struct APP_COMMAND_RF_PACKET {
	unsigned char payload_length;
	unsigned char payload[APP_COMMAND_PAYLOAD_MAX_LEN];
} APP_COMMAND_RF_PACKET_STRUCT;

void app_init_command(void);
void app_command_put(unsigned char *data_pointer, unsigned char length);
void app_command_housekeep(void);
void app_command_parse(unsigned char *packet, unsigned char source);
void app_cmd_gpio(unsigned char *cmd_gpio_packet);
void app_command_led_toggle_test(void);
void app_cmd_rf_single_pkt(unsigned char *packet);

void init_app_command_rf_fifo(void);
void app_command_send_rf_packet(unsigned char *payload_buffer,	unsigned char payload_len,	unsigned char RF_L4_service_number,	char RF_L2_source_callsign[6], unsigned char RF_L2_source_callsign_len,	unsigned char RF_L2_source_indetifier,	char RF_L2_destination_callsign[6],unsigned char RF_L2_destination_callsign_len,	unsigned char RF_L2_destination_identifier,	unsigned char RF_L2_packet_type,	unsigned char RF_L2_packet_config);
void app_command_rf_housekeeping(void);
void app_command_rf_rx_put(unsigned char *packet);

#endif /* APPLICATIONS_COMMAND_COMMAND_H_ */
