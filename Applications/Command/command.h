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

/** @name Command FIFO Definitions
* 	@brief FIFO definitions
*
* 	Constants used to configure the command application FIFO's.
*
@{**/
#define CMD_FIFO_SIZE 123 /**< Command application FIFO element size*/
#define CMD_FIFO_ELEMENT_CNT 1 /**< Number of elements in the the command application FIFO */
/** @}*/

/** @name RF Command Definitions
* 	@brief Definitions used to govern the operation of the RF commands
@{**/
#define APP_COMMAND_PAYLOAD_MAX_LEN 42 /**< Maximum allowable length in bytes of the RF command packets. This is directly determined by the MTU of the RF network stack */
#define APP_COMMAND_RF_CONFIG_LEN 19 /**< Length in bytes of the RF configuration (for all layers in the network stack) information */
/** @}*/

/** @name RF Command Application Definitions
* 	@brief constants used in the RF command application functionality
*
*	Constants used in the RF command application functionality.
*
*	@todo APP_COMMAND_RF_PACKET_PAYLOAD_LEN should be updated to an RF network stack constant to consilidate.
*
@{**/
#define APP_RF_PACKET_PAYLOAD_LEN 42 /**< Maximum RF packet length to determine maximum RF command command payload FIFO element size*/
#define APP_COMMAND_RF_PACKET_FIFO_COUNT 2 /**< RF command packet FIFO element count */
/** @}*/

/** @name Command Application Source Identifier Constants
* 	@brief Identifiers for the source of the command
*
*	Used to determine if a packet being parsed is remote of local origin.
*
@{**/
#define APP_CMD_SOURCE_LOCAL 0 /**< Identifier for locally sourced command packet */
#define APP_CMD_SOURCE_RF 1 /**< Identifier for remotely sourced command packet */
/** @}*/

/** @name Command Application Packet Constants
* 	@brief Constants used to define information about the command application packet
*
*	Constants used to define information about the command application packet.
*
@{**/
#define CMD_DATAGRAM_COMMAND_PKT_LEN 123 /**< Maximum command packet length in bytes */
#define CMD_DATAGRAM_COMMAND_LEN 1 /**< Maximum command number length in bytes */
#define CMD_DATAGRAM_COMMAND_LOC 0 /**< Command byte packet index location */



#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LEN 1 /**< Command packet payload length field length in bytes */
#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC 1 /**< Command application payload length field packet index location */
#define CMD_DATAGRAM_PAYLOAD_LEN 119 /**< Command packet payload field length in bytes */
#define CMD_DATAGRAM_PAYLOAD_LOC 2 /**< Command packet payload */
#define CMD_DATAGRAM_ERRORDETECTION_LEN 2 /**< Command packet error detection field length in bytes */
#define CMD_DATAGRAM_ERRORDETECTION_LOC 121 /**< Command packet error detection packet index location */

#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN 9 /**< Command packet callsign field length in bytes */
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LOC 0 /**<  Command packet callsign field packet index location*/
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LEN 1 /**< Command application callsign length field length in bytes */
#define CMD_DATAGRAM_COMMAND_CALLSIGN_LEN_LOC 9 /**< Command application callsign length packet index location */
#define CMD_DATAGRAM_COMMAND_DEVICE_ID_LEN 1 /**< Command application packet device callsign ID field length in bytes */
#define CMD_DATAGRAM_COMMAND_DEVICE_ID_LOC 10 /**< Command application packet device callsign ID packet index location */
#define CMD_DATAGRAM_COMMAND_DATAGRAM_LEN 32 /**< Command application packet "local" command for remote device field length in bytes */
#define CMD_DATAGRAM_COMMAND_DATAGRAM_LOC 11 /**< Command application packet "local" command for remote device packet index location */
#define CMD_DATAGRAM_COMMAND_CHK16_LEN 2 /**< Command application error detection (16 bit) field length in bytes */
#define CMD_DATAGRAM_COMMAND_CHK16_LOC 40 /**< Command application error detection (16 bit) packet index location */

#define CMD_DATAGRAM_COMMAND_PKT_RF_LEN 29 /**< RF command maximum length*/
#define CMD_DATAGRAM_COMMAND_LOC_RF 0 /**< RF command command packet index location */
#define CMD_DATAGRAM_COMMAND_PAYLOAD_LEN_LOC_RF 1 /**< RF command payload length field packet index location */
#define CMD_DATAGRAM_PAYLOAD_LOC_RF 2 /**< RF command payload packet index location */
#define CMD_DATAGRAM_ERRORDETECTION_LOC_RF 27 /**< RF command application error detection (16 bit) packet index location */
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
 */
typedef struct APP_COMMAND_RF_PACKET {
	unsigned char payload_length; /**< Length in bytes of the payload */
	unsigned char payload[APP_COMMAND_PAYLOAD_MAX_LEN]; /**< Bytearray that holds the final RF command packet */
} APP_COMMAND_RF_PACKET_STRUCT;


/**@brief Initialization routine for the command application
 *
 *	Initialization routine for the command application. This includes initializing FIFO's and other needed
 *	functions.
 *
 */
void app_init_command(void);


/**@brief Function pointer "PUT()" routine for UART
 *
 * This is the standard FIFO put() command required by the function pointer architecture of the FIFO inteface to devices
 * UART network stack. This funciton is called by those service routines when needing to interact with the application.
 *
 * @param data_pointer A pointer to the data to be placed into the command application FIFO
 * @param length The length in bytes of the data being placed into the command application FIFO
 *
 */
void app_command_put(unsigned char *data_pointer, unsigned char length);


/**@brief Command application housekeeping routing
 *
 *	The housekeeping routine is called regularly (in the housekeeping module) to perform actions
 *	needed on a reoccuring basis for nominal operation. Actions such as checking FIFO's and operating
 *	on data provided by them.
 *
 */
void app_command_housekeep(void);


/**@brief Parse command application packet
 *
 *	This function is used to parse a recieved command application packet from the device FIFO.
 *
 *	@param packet A pointer to the packet data to be parsed
 *	@param source An indication of whether the source of the command application packet was local or remote. use APP_CMD_SOURCE_LOCAL and APP_CMD_SOURCE_RF.
 *
 */
void app_command_parse(unsigned char *packet, unsigned char source);


/**@brief GPIO command function
 *
 *	This function executes a supplied GPIO command packet.
 *
 *	@param cmd_gpio_packet A pointer to the GPIO command packet to be parsed and executed
 *
 */
void app_cmd_gpio(unsigned char *cmd_gpio_packet);


/**@brief Experimental RF packet forwarding command
 *
 *	This command function forwards payload data (could be encapsulated packets!) over a single RF packet.
 *	The remote device will receive the packet and parse it through the command application respectively.
 *	This is useful to perform basic RF data transfer without creating a dedicated program to do so.
 *
 *	@note This is easy and quick but not efficient at all!
 *
 *	@param packet A pointer to the packet payload to forward over RF to a remove device
 *
 */
void app_cmd_rf_single_pkt(unsigned char *packet);


/**@brief Initialization routine for RF command functionality
 *
 *	Initialization routine for RF command functionality. This includes mainly FIFO's for handling the
 *	incoming and outgoing RF commands between the RF network stack.
 *
 */
void init_app_rf_packet_fifo(void);


/**@brief Housekeeping routine for RF commanding
 *
 *	This is the housekeeping routine for RF command functionallity. This function should be run on a reoccuring
 *	basis to perform FIFO checking and executing data retrived from FIFO's for the RF command functionality.
 *
 */
void app_command_rf_housekeeping(void);


/**@brief Function pointer "PUT()" routine for RF commanding
 *
 * This is the standard FIFO put() command required by the function pointer architecture of the FIFO inteface to devices
 * to the RF network stack. This funciton is called by those service routines when needing to interact with the application.
 *
 * @param packet A pointer to the data to be placed into the RF command application FIFO
 *
 */
void app_command_rf_rx_put(unsigned char *packet);

#endif /* APPLICATIONS_COMMAND_COMMAND_H_ */
