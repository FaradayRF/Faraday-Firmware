#ifndef FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_
#define FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_

volatile unsigned int ADC_Data[9]; // Global for ADC, maybe remove?


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

// Initialize RTC_A global structure
volatile struct RTC_A RTC;


// Software UART
#define SOFTWARE_UART_BIT_TIME 1667 //(Clock frequency/baud) - i.e. 16MHZ/9600 baud
#define SOFTWARE_UART_HALF_BIT_TIME 833 //(Clock frequency/baud)/2 - i.e. (16MHZ/9600)/2 baud
#define SOFTWARE_UART_BIT_COUNT 9
#define SOFTWARE_UART_STOPBIT_MASK 0x200
#define SOFTWARE_UART_STARTBIT_MASK 0x01
volatile unsigned char software_uart_char_buffer_rx;       // Buffer for storing current received byte
volatile char software_uart_char_bit_count;  // bit counter for receive
volatile unsigned int software_uart_int_buffer_rx;


#endif /* FARADAY_REVA_RF_MERGE_FARADAY_GLOBALS_H_ */
