/** @file command.h
 * 	@brief Firmware application that performs command and control
 *
 * 	This program performs general command and control for Faraday. Toggling GPIO and
 * 	initiating specific program/functions are some of the use-cases of this program.
 * 	The command program has its own defined packet protocol that resides at Layer 7
 * 	(Application) that is used to filter and parse commands and respective data.
 *
 * 	@todo Update MAX_CONFIGURATION_UPDATE_PACKET_LEN to implement Device_Configuration application
 * 	or layer 4 UART transport MTU definitions.
 *
 * 	@todo Update APP_COMMAND_PAYLOAD_MAX_LEN to implement RF network stack definitions instead of implementing
 * 	a seperate definition.
 *
 */

#ifndef APPLICATIONS_COMMAND_COMMAND_H_
#define APPLICATIONS_COMMAND_COMMAND_H_

/** @name Device Configuration Definitions
* 	@brief Definitions that govern the operations of the device configuration application command interface
@{**/
#define MAX_CONFIGURATION_UPDATE_PACKET_LEN 124 /**< Maximum allowable length of the device configuration update command payload */
/** @}*/


/** @name Read Device Memory Location Definitions
* 	@brief Definitions used to operate the CC430 Flash memory read commands
@{**/
#define CMD_READ_MEMORY_MAX_LENGTH 121 /**< Maximum allowable length in bytes of the memory to be read in a single packet */
#define CMD_READ_MEMORY_UART_PORT 2 /**< Layer 4 UART protocol "Service Port" to send device memory contents over */
/** @}*/


/** @name RF Command Definitions
* 	@brief Definitions used to govern the operation of the RF commands
@{**/
#define APP_COMMAND_PAYLOAD_MAX_LEN 42 /**< Maximum allowable length in bytes of the RF command packets. This is directly determined by the MTU of the RF network stack */
#define APP_COMMAND_RF_CONFIG_LEN 19 /**< Length in bytes of the RF configuration (for all layers in the network stack) information */
/** @}*/


/** @brief This is the main command packet definition structure
 *
 *	This is the main command packet definition structure and is used to transfer commands to Faraday. If commands themselves
 *	define additional packet structures they will be carried as payload in this main packet.
 *
 */
typedef struct COMMAND_PACKET {
	unsigned char command; /**< Command number */
	char payload_len; /**< Length of the payload in bytes */
	unsigned char payload[119]; /**< Payload bytearray */
	unsigned char error_detection_16[2]; /**< Error detection - 16-bit to allow verification of the command packet */
} COMMAND_PACKET_STRUCT;


/** @brief CC430 Flash memory read command command packet
 *
 *	This is the packet definition structure that defines the command packet associated with the command to
 *	read CC430 memory locations.
 *
 */
typedef struct COMMAND_PACKET_READ_MEMORY_SEND {
	unsigned char memory_address_h; /**< High byte of the 16 bit memory address */
	unsigned char memory_address_l; /**< Low byte of the 16 bit memory address */
	unsigned char payload[121]; /**< Payload that contains the memory contents of the respective memory address */
} COMMAND_PACKET_READ_MEMORY_SEND_STRUCT;


/** @brief GPIO command command packet definition
 *
 *	This is the GPIO command packet that contains bitmasks of the GPIO ports supports that call the GPIO control
 *	HAL function(s). This GPIO command invokes the gpio_update() routine.
 *
 */
typedef struct GPIO_COMMAND_PACKET {
	unsigned char port_3_on; /**< Bitmask for port 3 pins (bits) to toggle HIGH */
	unsigned char port_4_on; /**< Bitmask for port 4 pins (bits) to toggle HIGH */
	unsigned char port_5_on; /**< Bitmask for port 5 pins (bits) to toggle HIGH */
	unsigned char port_3_off; /**< Bitmask for port 3 pins (bits) to toggle LOW */
	unsigned char port_4_off; /**< Bitmask for port 4 pins (bits) to toggle LOW */
	unsigned char port_5_off; /**< Bitmask for port 5 pins (bits) to toggle LOW */
} GPIO_COMMAND_PACKET_STRUCT;


/** @brief RF command command packet definition structure
 *
 *	This packet structure defines the packet used to perform RF commands to a remote Faraday device. Remote Farady
 *	device commands essentially encapsulate a normal "local" command inside of a special "RF" command. The remote
 *	device exectutes the local command as if it originated locally.
 *
 */
typedef struct RF_COMMAND_PACKET {
	char dest_callsign[9]; /**< Callsign of remote device to be commanded */
	unsigned char dest_callsign_len; /**< Length of the callsign of the remote device to be commanded  */
	unsigned char dest_device_id; /**< Callsign ID number of the remote device to be commanded */
	unsigned char cmd_app_datagram_remote[29]; /**< Bytearray that holds the "local" command to be executed on the remote device */
	unsigned char checksum_16[2]; /**< 16 bit error detection bytearray */
} RF_COMMAND_PACKET_STRUCT;


/** @brief RF command configuration structure
 *
 *	This structure is used to hold the RF network stack information needed to properly transmit the command
 *	to the remote device.
 *
 */
typedef struct APP_COMMAND_RF_CONFIG {
	unsigned char RF_L4_service_number; /**< RF network stack layer 4 service number */
	char RF_L2_source_callsign[6]; /**< RF network stack layer 2 local callsign */
	unsigned char RF_L2_source_callsign_len; /**< RF network stack layer 2 local callsign length in bytes */
	unsigned char RF_L2_source_indetifier; /**< RF network stack layer 2 local callsign ID number */
	char RF_L2_destination_callsign[6]; /**< RF network stack layer 2 destination device callsign */
	unsigned char RF_L2_destination_callsign_len; /**< RF network stack layer 2 destination device callsign length in bytes */
	unsigned char RF_L2_destination_identifier; /**< RF network stack layer 2 destination device callsign ID number */
	unsigned char RF_L2_packet_type; /**< RF network stack layer 2 packet type number */
	unsigned char RF_L2_packet_config; /**< RF network stack layer 2 packet configuration bitmask */
} APP_COMMAND_RF_CONFIG_STRUCT;



/** @brief RF command packet (final)
 *
 *	This is the structure used to hold the final RF command packet prior to placing into the RF transmit FIFO.
 *
 *
 */
typedef struct APP_COMMAND_RF_PACKET {
	unsigned char payload_length; /**< Length in bytes of the payload */
	unsigned char payload[APP_COMMAND_PAYLOAD_MAX_LEN]; /**< Bytearray that holds the final RF command packet */
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
