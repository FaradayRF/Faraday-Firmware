/** @file REVA_Faraday.h
 * 	@brief Hardware GPIO Allocations
 *
 * 	This file contains definitions that allocate GPIO pins to Faraday
 * 	functionality.
 *
 *
 */


#ifndef FARADAY_PORT_MAPPING_H_
#define FARADAY_PORT_MAPPING_H_

/////////////////////////////////
//Define Faraday port connections
/////////////////////////////////


/** @name PORT 1
* 	@brief Definitions for the CC430 PORT 1
*
* 	- P1.0	GPS_PPS	GPS	Interrupt Enabled	GPS PPS
*   - P1.1	UCB0CS1	SPI	Interrupt Enabled	3V3 to 5V
*   - P1.2	UCB0_SOMI_SCL	SPI	Interrupt Enabled	3V3 to 5V
*   - P1.3	UCB0_SIMO_SDA	SPI	Interrupt Enabled	3V3 to 5V
*   - P1.4	UCB0CLK	SPI	Interrupt Enabled	3V3 to 5V
*   - P1.5	UCA0RXD	UART	Interrupt Enabled
*   - P1.6	UCA0TXD	UART	Interrupt Enabled
*   - P1.7	BUTTON_1	IO/BTN	Interrupt Enabled
@{**/
#define GPS_PPS BIT0
#define UCB0CS1 BIT1
#define UCB0_SOMI_SCL BIT2
#define UCB0_SIMO_SDA BIT3
#define UCB0CLK BIT4
#define UCA0RXD BIT5
#define UCA0TXD BIT6
#define BUTTON_1 BIT7
/** @}*/


/** @name PORT 2
* 	@brief Definitions for the CC430 PORT 2
*
*   - P2.0	GPS_UART_TX	GPS	Interrupt Enabled	GPS TX
*   - P2.1	ADC_6	CC430_ADC	Interrupt Enabled	VCC Monitor
*   - P2.2	ADC_5	CC430_ADC/GPS	Interrupt Enabled	GPS_UART_RX
*   - P2.3	ADC_4	CC430_ADC	Interrupt Enabled
*   - P2.4	ADC_3	CC430_ADC	Interrupt Enabled
*   - P2.5	ADC_2	CC430_ADC	Interrupt Enabled
*   - P2.6	ADC_1	CC430_ADC	Interrupt Enabled
*   - P2.7	ADC_0	CC430_ADC	Interrupt Enabled
@{**/
#define ADC_0 BIT7
#define ADC_1 BIT6
#define ADC_2 BIT5
#define ADC_3 BIT4
#define ADC_4 BIT3
#define ADC_5 BIT2
#define ADC_6 BIT1 //Not wired to external header!
#define GPS_UART_TX BIT0 //Not wired to external header!
/** @}*/


/** @name PORT 3
* 	@brief Definitions for the CC430 PORT 3
*
*   - P3.0	GPIO_2	IO
*   - P3.1	GPIO_1	IO
*   - P3.2	GPIO_0	IO
*   - P3.3	GPS_RESET	GPS
*   - P3.4	GPS_STANDBY	GPS
*   - P3.5	FLASH_SPI_CS FLASH
*   - P3.6	LED_1	Indicator
*   - P3.7	LED_2	Indicator
@{**/
#define GPIO_2 BIT0
#define GPIO_1 BIT1
#define GPIO_0 BIT2
#define GPS_RESET BIT3
#define GPS_STANDBY BIT4
#define FLASH_SPI_CS BIT5
#define LED_1 BIT6
#define LED_2 BIT7
/** @}*/


/** @name PORT 4
* 	@brief Definitions for the CC430 PORT 4
*
*   - P4.0	GPIO_7	IO
*   - P4.1	GPIO_6	IO
*   - P4.2	GPIO_5	IO
*   - P4.3	GPIO_4	IO
*   - P4.4	GPIO_3	IO
*   - P4.5	PA_ENABLE	RF
*   - P4.6	LNA_ENABLE	RF
*   - P4.7	HGM_SELECT	RF
@{**/
#define GPIO_7 BIT0
#define GPIO_6 BIT1
#define GPIO_5 BIT2
#define GPIO_4 BIT3
#define GPIO_3 BIT4
#define PA_ENABLE BIT5
#define LNA_ENABLE BIT6
#define HGM_SELECT BIT7
/** @}*/



/** @name PORT 5
* 	@brief Definitions for the CC430 PORT 5
*
*   - P5.0	CC430_WATCH_XTAL_0	XTAL	32.768KHz	XIN
*   - P5.1	CC430_WATCH_XTAL_1	XTAL	32.768KHz	XOUT
*   - P5.2	ARDUINO_IO_8	IO	5V Conversion	3V3 to 5V
*   - P5.3	ARDUINO_IO_9	IO	5V Conversion	3V3 to 5V
*   - P5.4	MOSFET_CNTL	Actuation
*   - P5.5	SRAM_CS	SRAM
*   - P5.6	SRAM_HOLD	SRAM
*   - P5.7	FLASH_HOLD	FLASH
@{**/
#define CC430_WATCH_XTAL_0 BIT0
#define CC430_WATCH_XTAL_1 BIT1
#define DIGITAL_IO_8 BIT2
#define GPS_RX BIT3
#define MOSFET_CNTL BIT4
#define SRAM_CS BIT5
#define SRAM_HOLD BIT6
#define FLASH_HOLD BIT7
/** @}*/





/** @name SPI SRAM Definitions
* 	@brief Definitions for the SPI SRAM IC
*
@{**/
#define SRAM_READ 0x03
#define SRAM_WRITE 0x02
#define SRAM_RDSR 0x05
#define SRAM_WRSR 0x01
/** @}*/


//
/** @name CC430 Flash Factory Calibration/Information
* 	@brief Definitions for the CC430 Flash Factory Calibration/Information stored on the device
*
@{**/
#define INFO_LEN 0x01A00
#define DEVICE_ID_A 0x01A04
#define DEVICE_ID_B 0x01A05
#define DEVICE_HARDWARE_REV 0x01A06
#define DEVICE_FIRMWARE_REV 0x01A07
#define ADC12_CALIBRATION_TAG 0x01A14
#define ADC12_CALIBRATION_LEN 0x01A15
#define ADC12_GAIN_FACTOR 0x01A16 //2 BYTES
#define ADC12_OFFSET 0x01A18 //2 BYTES
#define ADC12_2_5_V_TEMP_CAL_30C 0x01A22 // 2 BYTES
#define ADC12_2_5_V_TEMP_CAL_85C 0x01A24 // 2 BYTES
#define REF_CAL_TAG 0x01A26
#define REF_CAL_LENGTH 0x01A27
#define REF_CAL_2_5_V_FACTOR 0x01A2C
/** @}*/





#endif /* FARADAY_PORT_MAPPING_H_ */
