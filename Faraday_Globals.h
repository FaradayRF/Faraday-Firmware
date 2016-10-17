#ifndef FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_
#define FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_

/** @name ADC Global Variables
* 	@brief Global variables that are used to support the ADC functionallity
*
* 	This byte array is used to hold the saved "current" values of the ADC during an ADC query.
*
* 	@todo This should be moved into a specific ADC header file
*
@{**/
volatile unsigned int ADC_Data[9]; // Global for ADC, maybe remove?
/** @}*/

/** @name Real Time Clock Structure
* 	@brief RTC structure definition
*
* 	This structure is used to hold the current real time clock information as queried.
*
* 	@todo This should be moved into a specific RTC header file
*
@{**/
typedef struct RTC_A {
	char second;
	char minute;
	char hour;
	char day;
	char dow;
	char month;
	int year;
	unsigned char alarm[4];
} RTC_A;
/** @}*/


/** @name RTC_A global structure
* 	@brief Initialize RTC_A global structure
*
* 	This global variable is used by other program/routines to query the latest real time clock
* 	information.
*
* 	@todo This should be moved into a specific RTC header file
*
@{**/
volatile struct RTC_A RTC;
/** @}*/


/** @name Software UART Definitions
* 	@brief Definitions that define the configuration/timing of bits expected to decode a UART bitstream from a GPIO pin
*
* 	Definitions that define the configuration/timing of bits expected to decode a UART bitstream from a GPIO pin. This is primarally
* 	used to decode the GPS module UART data.
*
* 	@todo This should be moved into a specific software uart header file
*
@{**/
#define SOFTWARE_UART_BIT_TIME 1667 /**< (Clock frequency/baud) - i.e. 16MHZ/9600 baud */
#define SOFTWARE_UART_HALF_BIT_TIME 833 /**< (Clock frequency/baud)/2 - i.e. (16MHZ/9600)/2 baud */
#define SOFTWARE_UART_BIT_COUNT 9 /**<  Software UART bit count (including framing bit(s)*/
#define SOFTWARE_UART_STOPBIT_MASK 0x200 /**<  Software UART STOPBIT bitmask */
#define SOFTWARE_UART_STARTBIT_MASK 0x01 /**<  Software UART STARTBIT bitmask */
/** @}*/

/** @name Software UART global variables
* 	@brief Global variables used by the software UART
*
* 	Global variables used by the software UART.
*
* 	@todo This should be moved into a specific software uart header file
*
@{**/
volatile unsigned int software_uart_int_buffer_rx; //**<  Buffer for storing current received bit frame (start/stop bits create a bit frame larger than 1 byte) */
volatile unsigned char software_uart_char_buffer_rx;       //**<  Buffer for storing current received byte */
volatile char software_uart_char_bit_count;  //**<  bit counter for receive */
/** @}*/


#endif /* FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_ */
