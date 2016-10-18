#ifndef INIT_H_
#define INIT_H_


/** @brief The main summary of initialization tasks on boot
*
* 	This function is used to call all the needed boot initializations.
*
*
*/
void faraday_main_intialize(void);



/** @brief General Purpose Input/Output boot configuration
*
*	The function sets up all GPIO pins to their boot states as currently
*	defined for the hardware/software intent.
*
*/
void init_GPIO(void);



/** @brief CC430 Internal Clock Configuration
*
* 	This function initializes the UCS on the CC430. At boot the CC430 is operating
* 	in a "safe" 1MHz clock rate and this is increased to ~16MHz using the on-board
* 	crystal(s). Auxiliary clock(s) are also initialized.
*
* 	@warning Changing the frequency of clocks will may have downstream effects on certain functionallity.
*
*/
void init_UCS(void);



/** @brief Configure the USCI A0 into UART mode
*
* 	This function initializes the USCI A0 hardware peripheral into UART
* 	mode and configures into the intended Faraday settings.
*
*
*/
void init_usci_A0_UART(void);



/** @brief Initalize direct memory access on the CC430
*
* 	This function initializes DMA that allows specific memory tasks to be performed independant
* 	of the CC430 processor. When used this can greatly improve data throughput.
*
**/
void init_DMA(void);

/** @brief Initializes timer A0 for use
*
*	This function initializes timer A0 into the configuration desired to provide interrupt based
*	timing functionality.
*
*	@todo Describe configuration
*
*/
void init_timer_A0(void);



/** @brief Initializes timer A1 for use
*
*	This function initializes timer A1 into the configuration desired to provide interrupt based
*	timing functionality.
*
*	@todo Describe configuration
*
*/
void init_timer_A1(void);



/** @brief Device reset debug checks #10
*
*	This function is used to debug reset events by polling boot runtime registers that contain relavent information.
*	This is the #10 set of checks.
*
*/
void reset_identification(void);



/** @brief Device reset debug checks #2
*
*	This function is used to debug reset events by polling boot runtime registers that contain relavent information.
*	This is the #2 set of checks.
*
*/
void reset_identification_2(void);



/** @brief Device reset debug checks #3
*
*	This function is used to debug reset events by polling boot runtime registers that contain relavent information.
*	This is the #3 set of checks.
*
*/
void reset_identification_3(void);


/** @brief Initialize the on-board GPS to the post boot state
*
*	This function configures the GPS to the intended post boot state. The GPS contains many functions to reduce power
*	and the main use of this setup is to determine if the default state is to enable or "sleep" the GPS for power
*	savings.
*
*/
void init_GPS(void);


/** @brief Intialize the CC430 internal voltage reference peripheral
*
*	Intialize the CC430 internal voltage reference peripheral that is used to provide other peripherals
*	such as the ADC with a precise voltage reference.
*
*/
void init_REF(void);


/** @brief Initialize the analog to digital converter
*
* 	This function initializes the analog to digital converter in the CC430.
*
*/
void init_ADC(void);


/** @brief Initialize the SPI (Serial Peripheral Interface)
*
*	Initialize the SPI (Serial Peripheral Interface) in the CC430 to the intended configuration post
*	boot. This is the default SPI settings that allow communications with critical on-board peripherals
*	such as the SPI SRAM and FLASH.
*
*/
void init_SPI(void);


/** @brief Initialize the software UART for GPS
*
*	This function intializes the onboard software UART used to interface with with the on-board GPS
*	module.
*
*/
void init_software_uart(void);


/** @brief Initialize Real Time Clock A into Calender Mode
*
*	Initialize Real Time Clock A into Calender Mode. This mode performs as advertised by providing
*	an internal incrementing calender to provide both date/time awareness and alarm functionallity.
*
*/
void init_RTCA_Calender_Mode(void);


/** @brief Initialize Real Time Clock A into Counter Mode
*
*	Initialize the Real Time Clock A into Counter Mode which provides a flexible incrementing counter
*	that can be used for interval triggering functionallity.
*
*/
void init_RTCA_Counter_Mode(void);



#endif /* INIT_H_ */
