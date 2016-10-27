/** @file Device_Config.h
 * 	@brief Application that controls the non-volatile device configuration
 *
 *	This application provides Faraday with a device configuration functionality. Device
 *	configuration allows non-volatile device information to be kept on the Faraday
 *	digital radio.
 *
 */


#ifndef APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_
#define APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_


/** @name
* 	@brief
*
*
*
@{**/
#define CONFIG_PACKET_LEN 116 /**<  */
#define MAX_CALLSIGN_LENGTH 9 /**<  */
/** @}*/


/** @name Device Configuration Memory Address Constants
* 	@brief Constants that define locatoin and size of configuration data
*
*	Constants that define locatoin and size of configuration data for the Faraday device.
*
@{**/
//Configuration
#define CONFIG_BASIC_FLASH_CONFIG_BITMASK_ADDR 6144 /**< Configuration status bitmask memory address location */
#define CONFIG_BASIC_FLASH_CONFIG_BITMASK_INDEX 0 /**< Configuration status bitmask packet index location */
//Device Information
#define CONFIG_BASIC_LOCAL_CALLSIGN_ADDR 6145 /**< Device callsign memory address location */
#define CONFIG_BASIC_LOCAL_CALLSIGN_INDEX 1 /**< Device callsign packet index location */
#define CONFIG_BASIC_LOCAL_CALLSIGN_LEN_ADDR 6154 /**< Device callsign length in  bytes memory address location */
#define CONFIG_BASIC_LOCAL_CALLSIGN_LEN_INDEX 10 /**< Device callsign length in bytes packet index location */
#define CONFIG_BASIC_LOCAL_CALLSIGN_ID_ADDR 6155 /**< Device callsign ID number memory address location */
#define CONFIG_BASIC_LOCAL_CALLSIGN_ID_INDEX 11 /**< Device callsign ID number packet index location */
//GPIO Defaults
#define CONFIG_BASIC_P3_GPIO_ADDR 6156 /**< GPIO port 3 default PxOUT status memory address location */
#define CONFIG_BASIC_P3_GPIO_INDEX 12 /**< GPIO port 3 default PxOUT status packet index location */
#define CONFIG_BASIC_P4_GPIO_ADDR 6157 /**< GPIO port 4 default PxOUT status memory address location */
#define CONFIG_BASIC_P4_GPIO_INDEX 13 /**< GPIO port 4 default PxOUT status packet index location */
#define CONFIG_BASIC_P5_GPIO_ADDR 6158 /**< GPIO port 5 default PxOUT status memory address location */
#define CONFIG_BASIC_P5_GPIO_INDEX 14 /**< GPIO port 5 default PxOUT status packet index location */
//Radio
#define CONFIG_RF_DEFAULT_FREQ_ADDR 6168 /**< Default radio frequency memory address location */
#define CONFIG_RF_DEFAULT_FREQ_INDEX 24 /**< Default radio frequency packet index location */
#define CONFIG_RF_DEFAULT_PATABLE_ADDR 6171 /**< Default CC430 RF power setting memory address location */
#define CONFIG_RF_DEFAULT_PATABLE_INDEX 27 /**< Default CC430 RF power setting packet index location */
//GPS
#define CONFIG_GPS_DEFAULT_LATTITUDE_ADDR 6193 /**< Default GPS Lattitude memory address location */
#define CONFIG_GPS_DEFAULT_LATTITUDE_INDEX 49 /**< Default GPS Lattitude packet index location */
#define CONFIG_GPS_DEFAULT_LATTITUDE_DIR_ADDR 6202 /**< Default GPS Lattitude direction memory address location */
#define CONFIG_GPS_DEFAULT_LATTITUDE_DIR_INDEX 58 /**< Default GPS Lattitude direction packet index location */
#define CONFIG_GPS_DEFAULT_LONGITUDE_ADDR 6203 /**< Default GPS Longitude memory address location */
#define CONFIG_GPS_DEFAULT_LONGITUDE_INDEX 59 /**< Default GPS Longitude packet index location */
#define CONFIG_GPS_DEFAULT_LONGITYUDE_DIR_ADDR 6213 /**< Default GPS Longitude  direction memory address location */
#define CONFIG_GPS_DEFAULT_LONGITYUDE_DIR_INDEX 59 /**< Default GPS Longitude direction packet index location */
#define CONFIG_GPS_DEFAULT_ALTITUDE_ADDR 6214 /**< Default altitude memory address location */
#define CONFIG_GPS_DEFAULT_ALTITUDE_INDEX 70 /**< Default altitude packet index location */
#define CONFIG_GPS_DEFAULT_ALTITUDE_UNITS_ADDR 6222 /**< Default altitude units memory address location */
#define CONFIG_GPS_DEFAULT_ALTITUDE_UNITS_INDEX 78 /**< Default altitude units packet index location */
#define CONFIG_GPS_DEFAULT_BOOT_BITMASK_ADDR 6223 /**< Default GPS boot bitmask memory address location */
#define CONFIG_GPS_DEFAULT_BOOT_BITMASK_INDEX 79 /**< Default GPS boot bitmask packet index location */
//Telemetry Application
#define CONFIG_TELEMETRY_BOOT_BITMASK_ADDR 6245 /**< Default telemetry application configuration bitmask memory address location */
#define CONFIG_TELEMETRY_BOOT_BITMASK_INDEX 101 /**< Default telemetry application configuration bitmask packet index location */
#define CONFIG_TELEMETRY_UART_INTERVAL_ADDR 6246 /**< Default UART telemetry interval memory address location */
#define CONFIG_TELEMETRY_UART_INTERVAL_INDEX 102 /**< Default UART telemetry interval packet index location */
#define CONFIG_TELEMETRY_RF_INTERVAL_ADDR 6248 /**< Default RF telemetry interval memory address location */
#define CONFIG_TELEMETRY_RF_INTERVAL_INDEX 104 /**< Default RF telemetry interval packet index location */

//Bitmask locations
#define UNIT_PROGRAMMED BIT0 /**< Flash programmed configuration bitmask location */
#define GPS_BOOT_ENABLE BIT0 /**< GPS boot enabled GPS boot bitmask location */
#define UART_BEACON_BOOT_ENABLE BIT0 /**< UART beacon telemetry enabled telemetry boot bitmask location */
#define RF_BEACON_BOOT_ENABLE BIT1 /**< RF beacon telemetry enabled telemetry boot bitmask */
/** @}*/


/** @name Device Configuration Allowable Field Lengths
* 	@brief Constants that define the maximum lengths of device configuration settings
*
*	Constants that define the maximum lengths of device configuration settings. Some values
*	define the nomnimal (which is equal to the max) and others define a maximum size.
*
@{**/
#define RF_FREQ_LEN 3 /**< Length in bytes of the default RF frequency register settings */
#define GPS_LATTITUDE_LEN 9 /**< Length in bytes of the default GPS lattitude */
#define GPS_LONGITUDE_LEN 10 /**< Length in bytes of the default GPS longitude */
#define GPS_ALTITUDE_LEN 8 /**< Length in bytes of the default GPS altitude */
/** @}*/


/** @name Device Debug Flash Memory
* 	@brief Constants that define the device debug information
*
*	Constants that define the device debug information saved in non-volatile memory. Device
*	debug info saves statistics such as boot count, reset count, and other information useful
*	for device debugging.
*
@{**/
#define CONFIG_DEBUG_BOOT_COUNT_INDEX 0 /**< Device boot counter device debug packet index location */
#define CONFIG_DEBUG_RESET_COUNT_INDEX 2 /**< Device reset counter device debug packet index location*/
#define CONFIG_DEBUG_BOOT_SYSRSTIV_BOR_INDEX 3 /**< Device brown out reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_RSTNMI_INDEX 4 /**< Device non-maskable interrupt counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVSL_INDEX 5 /**< Device power supervisor low voltage bound reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVSH_INDEX 6 /**< Device power supervisor high voltage bound reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVML_OVP_INDEX 7 /**< Device power supervisor low-side monitor reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVMH_OVP_INDEX 8 /**< Device power supervisor high-side monitor reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_WDT_TIMEOUT_INDEX 9 /**< Device watch-dog timer timout reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_FLASHKEY_INDEX 10 /**< Device Flashkey violation reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_FLL_UNLOCK_INDEX 11 /**< Device frequency lock loop reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_PERIPH_CONFIG_INDEX 12 /**< Device peripheral reset counter device debug packet index location */
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SYSUNIV_ACCVIFG_INDEX 13 /**< Device access violation interupt flag reset counter device debug packet index location */
/** @}*/


/** @name Device Configuration RAM Variables
* 	@brief RAM variables to hold the current state of configuration
*
*	RAM variables to hold the current state of configuration of the Faraday device. At boot
*	these are equal to the device configuration flash memory values but during runtime they
*	can be updated. This allows easy modification of values during runtime as needed.
*
@{**/
extern volatile unsigned char config_bitmask; /**< Configuration bitmask RAM variable */
extern volatile unsigned char local_callsign_len; /**< Device callsign length RAM variable */
extern volatile char local_callsign[MAX_CALLSIGN_LENGTH]; /**< Device callsign RAM variable */
extern volatile unsigned char local_device_id; /**< Device callsign ID number RAM variable */
extern volatile unsigned char default_gpio_p3_bitmask; /**< Default GPIO port 3 settings RAM variable */
extern volatile unsigned char default_gpio_p4_bitmask; /**< Default GPIO port 4 settings RAM variable */

//RF
extern volatile unsigned char boot_freq[RF_FREQ_LEN]; /**< RF boot frequency RAM variable */
extern volatile unsigned char boot_rf_PATABLE; /**< RF power amplifier RAM variable*/

//GPS
extern volatile char default_lattitde[GPS_LATTITUDE_LEN]; /**< Default GPS lattitude RAM variable */
extern volatile char default_lattitude_dir; /**< Default GPS lattitude direction RAM variable */
extern volatile char default_longitude[GPS_LONGITUDE_LEN]; /**< Default GPS longitude RAM variable */
extern volatile char default_longitude_dir; /**< Default GPS longitude direction RAM variable */
extern volatile char default_altitude[GPS_ALTITUDE_LEN]; /**< Default GPS altitude RAM variable */
extern volatile char default_altitude_units; /**< Default GPS altitude units RAM variable */
extern volatile unsigned char gps_boot_bitmask; /**< Default GPS boot bitmask RAM variable */

//Telemetry
extern volatile unsigned char telem_boot_bitmask; /**< Telemetry application boot bitmask RAM variable */
extern volatile unsigned int telem_default_uart_interval; /**< Telemetry application default UART beacon interval RAM variable */
extern volatile unsigned int telem_default_rf_interval; /**< Telemetry application default RF beacon interval RAM variable */
/** @}*/


/** @brief Default configuration structure
 *
 * 	This structure defines the default device configuration packet as held in non-volatile
 * 	memory.
 *
 */
typedef struct default_config{
			unsigned char flash_config_bitmask;
			char local_callsign [9];
			unsigned char local_callsign_len;
			unsigned char local_device_id;
			unsigned char default_gpio_p3_bitmask;
			unsigned char default_gpio_p4_bitmask;
			unsigned char default_gpio_p5_bitmask;
			unsigned char padding_basic[9];
			unsigned char boot_freq[3];
			unsigned char PATable;
			unsigned char padding_rf[21];
			char default_lattitde[9];
			char default_lattitude_dir;
			char default_longitude[10];
			char default_longitude_dir;
			char default_altitude[8];
			char default_altitude_units;
			unsigned char gps_boot_bitmask;
			unsigned char padding_gps[21];
			unsigned char telem_boot_bitmask;
			unsigned int telem_default_uart_interval;
			unsigned int telem_default_rf_interval;
			unsigned char padding_telemetry[10];
		} default_flash_config_struct;




/**@brief Device configuration non-volatile memory buffer write
 *
 *	This function allows the device configuration (Information Segment D) to be written to
 *	with a bytearray input. This function always writes from the start of the information
 *	segment and expects a full device configuration packet.
 *
 *	@param data A pointer to the bytearray that contains the data to write to device configuration
 *	@param len Length in bytes of the bytearray to be written to device configuration
 */
void app_device_config_write_buffer(unsigned char *data, unsigned char len);


/**@brief Write factory default device configuration
 *
 *	This is a factory default device configuration that is written when the Faraday device is either
 *	booting for the first time or has had it's device configuration erased. These are standard "safe"
 *	values.
 *
 */
void app_device_config_load_default(void);


/**@brief Read default device configuration values into RAM
 *
 *	This function reads default device configuration values into RAM variables that are accessible to
 *	external programs.
 *
 */
void app_device_config_read_defaults(void);


/**@brief Factory reset device configuration
 *
 *	This function invokes a factory reset of the local Faraday device configuration.
 *
 */
void app_device_config_device_debug_reset(void);


/**@brief Update a device debug value
 *
 *	This function updates a device debug value with the supplied command.
 *
 *	@note See engineering documentation for more information.
 *
 *	@param param A parameter number indication what value to update
 *	@param command The command intended for the parameter update
 *
 */
void app_device_config_device_debug_update(unsigned char param, unsigned char command);


/**@brief Increment a device debug integer value
 *
 *	This is a quick function that increments an integer counter in the device debug memory location
 *	of the respective parameter whos memory offest is supplied as a function argument.
 *
 *	@param offset The memory location offset from the beginning of the device debug memory location
 *
 */
void app_device_config_device_debug_increment_int(unsigned char offset);


/**@brief Increment a device debug byte value
 *
 *	This is a quick function that increments a byte counter in the device debug memory location
 *	of the respective parameter whos memory offest is supplied as a function argument.
 *
 *	@param offset The memory location offset from the beginning of the device debug memory location
 *
 */
void app_device_config_device_debug_increment_char(unsigned char offset);

#endif /* APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_ */
