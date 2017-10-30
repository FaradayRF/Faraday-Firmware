/** @file Faraday_Init.c
 *  @brief Device Initializations
 *
 *  These functions provide a default boot configuration for
 *  the peripheral and software functionallity of Faraday.
 *
 */


/* standard includes */
#include "cc430f6137.h"


/* faraday hardware allocations */
#include "REVA_Faraday.h"
#include "Faraday_Init.h"

/* faraday global variables */
#include "Faraday_Globals.h"

/* hardware abstraction */
#include "Faraday_HAL/Faraday_HAL.h"
#include "Faraday_HAL/SPI.h"
#include "HAL/hal_pmm.h"
#include "HAL/hal_pmm.h"
#include "HAL/hal_UCS.h"
#include "HAL/rtc.h"
#include "HAL/adc.h"
#include "HAL/ref.h"

/*  sram */
#include "SRAM/SRAM.h"

/* fifo - sram */
#include "Ring_Buffers/FIFO_SRAM.h"

/* faraday rf network stack */
#include "RF_Network_Stack/rf.h"

/* faraday uart network stack */
#include "UART/UART_L2.h"

/* faraday device configuration application */
#include "Applications/Device_Config/Device_Config.h"
//#include "Faraday_HAL/cp2120.h"

/* faraday miscellaneous functions */
#include "Faraday_HAL/Misc_Functions.h"

/* CP2120 SPI-I2C module functions */


void faraday_main_intialize(void){
    init_UCS();
    init_GPIO();
    init_ADC();
    init_uart(); //NEEDED FOR UART!
    init_RTCA_Calender_Mode();
    init_usci_A0_UART();
    init_SPI();
    init_REF();
    init_software_uart();
    init_radio_faraday();
    Faraday_SRAM_Write_Settings(1); // Put SRAM into sequence mode (will read bad/0's if wrong)
}

/************************************************************
* Function: init_GPIO(void)
*
* Description: Initialize GPIO ports on the CC430. The GPIO ports
* are used for general I/O, soft uarts, LED's, etc...
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_GPIO(void){

	////////////////////////////////////
	// Hardware IO
	////////////////////////////////////

	// Setup LED's
	P3OUT &= ~LED_1 + ~LED_2; 			// Initialize LED's to off state
	P3DIR |= LED_1 + LED_2; 			// Faraday Rev A LED GPIO's set to output

	// Setup button
	P1REN	|= BUTTON_1; 				// Enable P1.7 internal pull-up resistor
	P1OUT	|= BUTTON_1; 				// Set P1.7 as pull-up resistance
	P1IE	|= BUTTON_1;				// Set P1.7 interrupt enable
	P1IES	|= BUTTON_1;				// Set P1.7 Hi/Lo edge interrupt
	P1IFG	&= ~BUTTON_1;				// Clear P.17 IFG


	// Setup MOSFET Switch
	P5OUT	&= ~MOSFET_CNTL; //Ensure it is OFF on start-up
	P5DIR	|= MOSFET_CNTL;
	//P5REN	|= MOSFET_CNTL; //Pulldown to ensure MOSFET is OFF during boot

	// Setup external GPIO's
	// Default to outputs with zero value

	P3OUT	&= ~GPIO_0;
	P3OUT	&= ~GPIO_1;
	P3OUT	&= ~GPIO_2;
	P4OUT	&= ~GPIO_3;
	P4OUT	&= ~GPIO_4;
	P4OUT	&= ~GPIO_5;
	P4OUT	&= ~GPIO_6;
	P4OUT	&= ~GPIO_7;

	P3DIR   |= GPIO_0 | GPIO_1 | GPIO_2;
	P4DIR	|= GPIO_3 | GPIO_4 | GPIO_5 | GPIO_6 | GPIO_7;


	P5OUT	&= ~DIGITAL_IO_8;
	P5DIR 	|= DIGITAL_IO_8;

	////////////////////////////////////
	// RF Amplifier
	////////////////////////////////////

	//Setup CC1190
	P4DIR |= PA_ENABLE + LNA_ENABLE + HGM_SELECT;
	P4OUT |= PA_ENABLE; //Testing
	P4OUT &= ~LNA_ENABLE | ~HGM_SELECT; //Testing

	// Setup GPS GPIO pins
	P1DIR	&= ~GPS_PPS;				// GPS Pulse Per Second P1.0 as input
	P1IE	|= GPS_PPS;					// P1.0 interrupt enable
	P1IES	&= ~GPS_PPS;				// P1.0 Lo/Hi edge interrupt
	P1IFG	&= ~GPS_PPS;				// P1.0 IFG cleared

	P2DIR	&= ~GPS_UART_TX;			// GPS TX UART P2.0 set as input
	P2IE	|= GPS_UART_TX;				// GPS TX UART interrupt enable
	P2IES	|= GPS_UART_TX;				// GPS TX UART Hi/Lo edge interrupt
	P2IFG	&= ~GPS_UART_TX;			// GPS TX UART IFG cleared

	P3OUT	&= ~GPS_RESET + ~GPS_STANDBY; 	// GPS reset and standby default low
	P3OUT	|= GPS_RESET | GPS_STANDBY; 	// GPS reset and standby default low
	P3DIR	|= GPS_RESET | GPS_STANDBY;		// GPS reset P3.3 and GPS standby P3.4 set as outputs

	////////////////////////////////////
	// SPI
	////////////////////////////////////

	P1SEL 	|= UCB0_SOMI_SCL + UCB0_SIMO_SDA + UCB0CLK;	// Select alternate functions for SPI pins
	P1DIR 	|= UCB0CS1;									// Set UCB0CS1 as output

	// SRAM IC SPI configuration
	//P5OUT	&= ~SRAM_CS + ~SRAM_HOLD;					// Set default SRAM CS and SRAM Hold to 0
	P5OUT	|= SRAM_CS + SRAM_HOLD;						// Set default SRAM CS and SRAM Hold to HIGH
	P5DIR 	|= SRAM_CS + SRAM_HOLD;						// Set SRAm CS and SRAM Hold to output

	//Flash IC SPI Configuration
	P3DIR	|= FLASH_SPI_CS;							// FLASH_SPI_CS set as output
	P5DIR   |= FLASH_HOLD;								// FLASH_HOLD set as output
	P1DIR   &= ~UCB0_SOMI_SCL;							// SPI MISO INPUT
	P1OUT   |= UCB0_SOMI_SCL;							// SPI MISO Pullup
	P1REN   |= UCB0_SOMI_SCL;							// SPI MISO Pullup

//	P2DIR &= ~CP2120_SPI_I2C_INT;						// CP2120 INT Pin P2.5 Input


	////////////////////////////////////
	// UART
	////////////////////////////////////

	P1SEL	|= UCA0TXD + UCA0RXD;						// Select alternate functions for P1.5 and P1.6 for UART
	P1DIR	|= UCA0TXD;									// Set UCA0TXD P1.6 as output
	P1DIR 	&= ~UCA0RXD;								// Set UCA0RXD P1.5 as input
	P1OUT 	&= ~UCA0RXD;								// Set UCA0RXD P1.5 as OUTPUT for Pullup
	P1REN 	&= ~UCA0RXD;								// Set UCA0RXD P1.5 REN as HIGH for pullup

	// CP2120 SPI to I2C Converter Module (External)
//	P1OUT |= CP2120_SPI_CS; // Set P1.1 (external CS2 pin) to HIGH (CS is active LOW)
//	P1DIR |= CP2120_SPI_CS; // Set P1.1 (external CS2 pin) to OUTPUT


}


/************************************************************
* Function: init_UCS(void)
*
* Description: Initialize the universal clock system that sets
* the CC430's main oscillator frequency.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_UCS(void){
	//Set Vcore for intended operating range | VCORE = 2 needed for RF module boot
	SetVCoreUp(2);

	// Initialize LFXT1
	P5SEL |= 0x03;                            // Select XT1
	UCSCTL6 |= XCAP_3;                        // Internal load cap


	__bis_SR_register(SCG0);			// Disable the FLL control loop
	UCSCTL0 = 0x0000;                   // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_7;                // Select DCO range 16MHz operation
	UCSCTL2 = FLLD_1 + 487;             // Set DCO Multiplier for 16MHz
										// (N + 1) * FLLRef = Fdco
										// (487 + 1) * 32768 = 16MHz (15,990.8 MHz) (REFOCLK = internal 32768Hz)
										// Set FLL Div = fDCOCLK/2
	UCSCTL3 |= SELREF_2 + FLLREFDIV_0;  // Set DCO FLL reference = REF0CLK/1

	__bic_SR_register(SCG0);                  // Enable the FLL control loop


	/*
	 * Allow DCO taps and FLL to settle after initialization.
	 * Worst-case MCLK cycles = FLLDIV x 32 x 32 x FLLREFCLK
	 *
	 * Cycles = 1 x 32 x 32 x 32768 = 33554432 cycles
	 */
	__delay_cycles(33554432);

	/*
	 * Set clock sources
	 * ACLK = XT1CLK (32768 Hz)
	 * SMCLK = DCOCLKDIV (8MHz FLL controlled)
	 * MCLK = DCOCLK (16MHz)
	*/
	UCSCTL4 |= SELA__XT1CLK + SELS__DCOCLKDIV + SELM__DCOCLK; // ACLK = LFXTAL1, SMCLK = DCOCLKDIV, MCLK = DCOCLK

  // Loop until XT1,XT2 & DCO stabilizes
  do
  {
	UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
											// Clear XT2,XT1,DCO fault flags
	SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

}


/************************************************************
* Function: init_usci_A0_UART(void)
*
* Description: Initialize the Serial UART hardware transmitter
* and receiver. This allows serial communications between
* Faraday and a host computer.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_usci_A0_UART(void){

	//*********************
	// BSALMI - 8-13-2015
	// OSC FAULT for XT1, DCO default to REF0 and will droop low in frequency!
	//*********************
	__no_operation();
	// **Put state machine in reset**
	UCA0CTL1 |= UCSWRST;
	// SMCLK
	UCA0CTL1 |= UCSSEL_2;
	UCA0BR0 = 134;                              // 1MHz 115200 (see User's Guide)
	UCA0BR1 = 0x00;                              // 1MHz 115200
	UCA0MCTL |= UCBRS_7 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	UCA0IFG &= ~UCTXIFG;					  // Clear TX IFG, will be SET HIGH on init
	UCA0IE |= UCRXIE + UCTXIE;                // Enable USCI_A0 RX interrupt,Enable USCI_A0 TX interrupt
}


void init_DMA(void){
// To be created
}

/************************************************************
* Function: init_timer_A0(void)
*
* Description: Initialize Timer A0 module
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_timer_A0(void){
	//Toggle rate = 32768/(2*TA1CCR0) = Hz
	//ACLK = TACLK = 32768Hz,

	//Setup CCR0 for psuedo watchdog
	TA0CCTL0 = CCIE;
	TA0CCR0 = 65;
	TA0CCTL1 = CCIE;
	TA0CCR1 = 8192;
	TA0CTL = TASSEL_1 + MC_2 + TACLR + TAIE;  // ACLK, contmode, clear TAR
											// enable interrupt
}

/************************************************************
* Function: init_timer_A1(void)
*
* Description: This initializes the Timer A1 module
*
* Inputs: unsigned char enable
*
* Outputs: None
*
* Intended Use(s): This clock source is primarally used for the softare UART. Setup is
* 					performed during initialization but the interrupt enabled only during
* 					program operation as new data arrives.
*
*************************************************************/
void init_timer_A1(void){

		//Initialize timer A1 into a continuous counter using the 32768 Hz LFXT on ACLK
		TA1CTL = TASSEL_2 + MC_2 + TACLR + TAIE;  // SMCLK, contmode, clear TAR, interrupt enable

		//TA1CCR1 interrupt enable
		//TA1CCTL1 = CCIE;

		//TA1CCR2 interrupt enable
		//TA1CCTL2 = CCIE;

}
/************************************************************
* Function: Initialize RTCA Calender Mode
*
* Description:  Initialize the Real Time Clock A to be in calender mode. Enables RTC_A time event interrupts and
* 				RTC_A ready interrupts. Sets initial time to EPOCH zero at Thursday January 1st, 1970 at midnight.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_RTCA_Calender_Mode(void){
	// Real-Time-Clock 0 and 1 control
	// RTC Event interrupt enable, RTC Ready interrupt enable
	// RTC hold (calender stopped)
	// RTC Calender mode enable
	RTCCTL01 |= RTCTEVIE + RTCRDYIE + RTCHOLD + RTCMODE;

	//Setup default
	RTCSEC	= 0x00;
	RTCMIN	= 0x00;
	RTCHOUR	= 0x00;
	RTCDOW	= 0x04;
	RTCDAY	= 0x01;
	RTCMON	= 0x01;
	RTCYEAR	= 0x07B2;

	RTCCTL01 &= ~(RTCHOLD);			// start RTC calender mode

}

/************************************************************
* Function: Initialize RTC_A Counter Mode
*
* Description:  Initialize the Real Time Clock A to bein counter mode, does not set a counter!
* 				ACKLK should be Low Freq 32768 XTAL for proper operation. Sets Prescaler 0 input to ACLK
* 				and prescaler 1 to be Prescaler 0 output. Enableds 8-bit overflow mode. Setup for a
* 				1 second interrupt with RTC_RTCTEVIFG.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_RTCA_Counter_Mode(void){
	//This can be changed to purely div 32768/256/128
	RTCCTL01 = 0;							// Clear RTCCTL01 settings
	RTCPS0CTL = 0;							// Clear RTC Prescaler 0 settings
	RTCPS1CTL = 0;							// Clear RTC Prescaler 0 settings
	Set_RTCA_BCD_Mode();					// Set counter mode
	RTCCTL01 |= RTCSSEL_2;					// Select ACLK source for RTC A
	RTCPS0CTL &= ~RT0SSEL;					// Select Prescaler 0 source ACLK
	RTCPS1CTL |= RT1SSEL_2;					// Select Prescaler 1 source RT0PS (cascade)

	RTCCTL01 |= RTCTEV_0;					// Set 8 bit overflow mode
	Enable_RTCA_Time_Event_Interrupt(1);	// Enable RTC time event interrupts

	//Set 1 second interval counter, ACLK = 32768 Hz
	RTCPS0CTL |= RT0PSDIV_2;				// ACLK/8
	RTCPS1CTL |= RT1PSDIV_3;				// ACLK/16

}

/************************************************************
* Function: init_GPS(void)
*
* Description: Initialize GPS support onboard. Primarally this enables the software UART used to recevie GPS NMEA packets.
* 			   Code begins my creating a roughly 500us reset (LOW) signal to force a clean GPS boot. Then the GPS is
* 			   commanded to leave standby mode.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_GPS(void){
	//Enable GPS on boot
	if(check_bitmask(gps_boot_bitmask, GPS_BOOT_ENABLE)){
		Faraday_GPS_Reset_Enable();
		__delay_cycles(15000);			//MCLK delay 15,000 cycles (about 500us)
		Faraday_GPS_Reset_Disable();
		Faraday_GPS_Standby_Disable();	//Active low, this will allow GPS to leave standby mode
	}
	//Disable GPS boot by default (power save)
	else{
		Faraday_GPS_Reset_Disable();
		Faraday_GPS_Standby_Disable();	//Active low, this will allow GPS to leave standby mode
	}

}

/************************************************************
* Function: init_REF(void)
*
* Description: Initialize the internal reference module of the MSP430
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_REF(void){
	REFCTL0 |= REFMSTR + REFON + REFVSEL_3;	// Enable internal
}

/************************************************************
* Function: init_ADC(void)
*
* Description: Initialize the analog to digital hardware module on the MSP430
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_ADC(void){
	// Clear ADC and reference control registers
	ADC12CTL0 = 0;								// Clear ADC12CTL0
	ADC12CTL1 = 0;								// Clear ADC12CTL1
	ADC12CTL2 = 0;								// Clear ADC12CTL2
	ADC12IE = 0;								// Clear ADC12 Interrupt Enable register
	Clear_ADC12_Memory_Control_Register(0);		// Clear memory control register 0
	Clear_ADC12_Memory_Control_Register(1);		// Clear memory control register 1
	Clear_ADC12_Memory_Control_Register(2);		// Clear memory control register 2
	Clear_ADC12_Memory_Control_Register(3);		// Clear memory control register 3
	Clear_ADC12_Memory_Control_Register(4);		// Clear memory control register 4
	Clear_ADC12_Memory_Control_Register(5);		// Clear memory control register 5
	Clear_ADC12_Memory_Control_Register(6);		// Clear memory control register 6
	Clear_ADC12_Memory_Control_Register(7);		// Clear memory control register 7

	REFCTL0 = 0;	// Clear REFCTL0 register

	// Setup Reference
	REFCTL0 |= REFMSTR;									// Force use of REFCTL0 with REFMASTER bit
	Set_Reference(2);									// Use internal 2.5V reference (2.41v nominal)
	REFCTL0 &= ~REFTCOFF;								// Enable internal temperature sensor
	Enable_Reference(1);								// Enable reference
	__delay_cycles(75);								// allow reference to settle (not optimized simply copied...)

	ADC12CTL0 |= ADC12ON;								// Enable ADC12
	/*
	 * tsample > (RS + RI) × ln(2^(n+1)) × (CI + CS) + 800 ns
	 * tsample > (10K + 1.8K) X ln(2^(12+1)) * (25*10^-12) + 800ns
	 * tsample > 3.46us
	 */

	// Setup ADC12 and sample for at minimum 3.46us for each input
	// Should think about speeding this up with a higher frequency LPF

	/* Setup ADC sample clock
	* 32 oscillator periods at a worst case 5.4MHz = 5.9us worst case which is enough to allow all signals to settle to within 0.5 LSB
	* Total time needed for 8 channels is 61.5us
	*
	* Setup ADC12 for roughly 50Hz operation, will vary widely with MODOSC as clock but OK, we'll likely only send data in big packets at a slower rate.
	* Currently setting sample time to about 2.2ms to slow rate down, way longer than needed but OK.
	*/
	ADC12CTL1 |= ADC12SSEL_0;							// Set ADC12 clock to ADC12OSC (4.8MHz nominal)
	ADC12CTL2 |= ADC12PDIV;								// Pre-Divide ADC12OSC by 4
	ADC12CTL1 |= ADC12DIV_6;							// Divide ADC12OSC by 7
	ADC12CTL1 |= ADC12SHP;								// Set ADC12 to sample from trigger
	ADC12CTL0 |= ADC12MSC;								// Set ADC12 to multiple sample conversions per trigger
	ADC12CTL0 |= ADC12SHT0_9;							// Set ADC12 to sample 394 clock cycles per channel (Memory Channel 0 through 7)
	ADC12CTL0 |= ADC12SHT1_9;							// Set ADC12 to sample 394 clock cycles per channel (Memory Channel 8 through 15)

	// Set ADC Conversion clock
	ADC12CTL1 |= ADC12CONSEQ_3;							// Set ADC12 to repeated sequence of conversions mode
	ADC12CTL1 |= ADC12SHS_0;							// Set ADC12 conversion clock to ADC12OSC
	ADC12CTL1 &= ~ADC12ISSH;							// Do not invert sample and hold timer signal
	ADC12CTL2 |= ADC12RES_2;							// Set ADC12 into 12-bit resolution mode (forced)


	// Setup ADC12 Channels to use internal reference and VSS (Ground) and set associated ADC channels/pins to memory locations
	ADC12MCTL0 |= ADC12SREF_1 + ADC12INCH_7;				// Internal 2.5V Reference, VSS Ground, P2.7 AD12 CHANNEL A7 Faraday ADC0
	ADC12MCTL1 |= ADC12SREF_1 + ADC12INCH_6;				// Internal 2.5V Reference, VSS Ground, P2.6 AD12 CHANNEL A6 Faraday ADC1
	ADC12MCTL2 |= ADC12SREF_1 + ADC12INCH_5;				// Internal 2.5V Reference, VSS Ground, P2.5 AD12 CHANNEL A5 Faraday ADC2
	ADC12MCTL3 |= ADC12SREF_1 + ADC12INCH_4;				// Internal 2.5V Reference, VSS Ground, P2.4 AD12 CHANNEL A4 Faraday ADC3
	ADC12MCTL4 |= ADC12SREF_1 + ADC12INCH_3;				// Internal 2.5V Reference, VSS Ground, P2.3 AD12 CHANNEL A3 Faraday ADC4
	ADC12MCTL5 |= ADC12SREF_1 + ADC12INCH_2;				// Internal 2.5V Reference, VSS Ground, P2.2 AD12 CHANNEL A2 Faraday ADC5
	ADC12MCTL6 |= ADC12SREF_1 + ADC12INCH_1;				// Internal 2.5V Reference, VSS Ground, P2.1 AD12 CHANNEL A1 Faraday ADC6 (VCC)
	ADC12MCTL7 |= ADC12SREF_1 + ADC12INCH_10;				// Internal 2.5V Reference, VSS Ground, CHANNEL A10 CC430 INTERNAL TEMPERATURE
	ADC12MCTL8 |= ADC12SREF_1 + ADC12INCH_11 + ADC12EOS;	// Internal 2.5V Reference, VSS Ground, CHANNEL A11 internal sense on 3.3V (AVCC - AVSS) / 2

	// Enable interrup for memory channel 8 and enable conversions as well as start conversions
	Enable_ADC12_Memory_Channel_Interrupt(8);			// Enable interrupt to trigger following last ADC reading placed into Memory Channel 8
	ADC12CTL0 |= ADC12ENC;								// Enable ADC12 conversions
	ADC12CTL0 |= ADC12SC;								// Start conversions, only need one in multiple samples mode
}

/************************************************************
* Function: init_SPI(void)
*
* Description: Initialize the SPI protocol hardware support on the MSP430
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_SPI(void){
	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 |= UCMODE_0+UCMST+UCSYNC+UCCKPH+UCMSB;    // 3-pin, 8-bit SPI master, MODE 10| +UCCKPL
											  // Clock polarity high, MSB
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	UCB0BR0 = 2;                           // HIGH f/(H+L*256)
	UCB0BR1 = 0x01;                           // LOW  f/(H+L*256)
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	//Disable HOLD (Active LOW)
	Faraday_SRAM_Hold_Disable();

	//Disable Chip Select (CS) (Active Low)
	Faraday_SRAM_CS_Disable();
}

void init_SPI_Clk_00(void){
	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 &= ~UCCKPH;
	UCB0CTL0 &= ~UCCKPL;
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void init_SPI_Clk_01(void){
	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 &= ~UCCKPH;
	UCB0CTL0 |= UCCKPL;
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void init_SPI_Clk_10(void){
	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 |= UCCKPH;
	UCB0CTL0 &= ~UCCKPL;
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void init_SPI_Clk_11(void){
	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 |= UCCKPH;
	UCB0CTL0 |= UCCKPL;
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

/************************************************************
* Function: init_software_uart(void)
*
* Description: Initialize the software UART functionality on the MSP430. This is primarally to start the timer
* 				module used to performed the timing functions to receive the data bits.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void init_software_uart(void){
	//NOTE: This function requires prior initialization of relavent port pins for software UART applications.
	//Initialize software UART timer module. This is used to time each bit after the start bit edge port trigger
	init_timer_A1();
}

/************************************************************
* Function: reset_identification(void)
*
* Description: This functional is used to determine hardware/software reset conditions on boot-up
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void reset_identification(void){
	switch (__even_in_range(SYSRSTIV, SYSRSTIV_PMMKEY))
	   {
	       case SYSRSTIV_NONE:                       // No Interrupt pending
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_BOR:                        // SYSRSTIV : BOR
	    	   app_device_config_device_debug_update(2, 0);
	                               break;
	       case SYSRSTIV_RSTNMI:                     // SYSRSTIV : RST/NMI
	    	   app_device_config_device_debug_update(3, 0);
	                               break;
	       case SYSRSTIV_DOBOR:                      // SYSRSTIV : Do BOR
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_LPM5WU:                     // SYSRSTIV : Port LPM5 Wake Up
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_SECYV:                      // SYSRSTIV : Security violation
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_SVSL:                       // SYSRSTIV : SVSL
	    	   app_device_config_device_debug_update(4, 0);
	                               break;
	       case SYSRSTIV_SVSH:                       // SYSRSTIV : SVSH
	    	   app_device_config_device_debug_update(5, 0);
	                               break;
	       case SYSRSTIV_SVML_OVP:                   // SYSRSTIV : SVML_OVP
	    	   app_device_config_device_debug_update(6, 0);
	                               break;
	       case SYSRSTIV_SVMH_OVP:                   // SYSRSTIV : SVMH_OVP
	    	   app_device_config_device_debug_update(7, 0);
	                               break;
	       case SYSRSTIV_DOPOR:                      // SYSRSTIV : Do POR
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_WDTTO:                      // SYSRSTIV : WDT Time out
	    	   app_device_config_device_debug_update(8, 0);
	                               break;
	       case SYSRSTIV_WDTKEY:                     // SYSRSTIV : WDTKEY violation
	                               //__no_operation();
	                               break;
	       case SYSRSTIV_KEYV:                       // SYSRSTIV : Flash Key violation
	    	   app_device_config_device_debug_update(9, 0);
	                               break;
	       case SYSRSTIV_PLLUL:                      // SYSRSTIV : FLL unlock
	    	   app_device_config_device_debug_update(10, 0);
	                               break;
	       case SYSRSTIV_PERF:                       // SYSRSTIV : peripheral/config area fetch
	    	   app_device_config_device_debug_update(11, 0);
	                               break;
	       case SYSRSTIV_PMMKEY:                     // SYSRSTIV : PMMKEY violation
	                               //__no_operation();
	                               break;
	       default: break;
	   }

}


//************************************************************
//* Function: reset_identification_2(void)
//*
//* Description: This functional is used to determine hardware/software reset conditions on boot-up
//*
//* Inputs: None
//*
//* Outputs: None
//*
//*************************************************************/
	void reset_identification_2(void){
		switch (__even_in_range(SYSUNIV, SYSUNIV_SYSBERRIV))
			{

			   case SYSUNIV_NONE:                       // No Interrupt pending
									   //__no_operation();
									   break;
			   case SYSUNIV_NMIIFG:                       // SYSUNIV : NMIIFG
									   //__no_operation();
									   break;
			   case SYSUNIV_OFIFG:                       // Osc. Fail - OFIFG
									   //__no_operation();
									   break;
			   case SYSUNIV_ACCVIFG:                       // SYSUNIV : Access Violation - ACCVIFG
				   app_device_config_device_debug_update(12, 0);
									   break;
			   case SYSUNIV_SYSBERRIV:                       //SYSUNIV : Bus Error - SYSBERRIV
									   //__no_operation();
									   break;


			   default: break;
			}
	}


//	************************************************************
//	* Function: reset_identification_3(void)
//	*
//	* Description: This functional is used to determine hardware/software reset conditions on boot-up
//	*
//	* Inputs: None
//	*
//	* Outputs: None
//	*
//	*************************************************************/
//	void reset_identification_3(void){
//		switch (__even_in_range(SYSSNIV, SYSSNIV_VLRHIFG))
//			{
//
//			   case SYSSNIV_NONE:                       // No Interrupt pending
//									   __no_operation();
//									   break;
//			   case SYSSNIV_SVMLIFG:                       // SYSSNIV : SVMLIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_SVMHIFG:                       // SYSSNIV : SVMHIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_DLYLIFG:                       // SYSSNIV : DLYLIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_DLYHIFG:                       // SYSSNIV : DLYHIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_VMAIFG:                       // SYSSNIV : VMAIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_JMBINIFG:                       // SYSSNIV : JMBINIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_JMBOUTIFG:                       // SYSSNIV : JMBOUTIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_VLRLIFG:                       // SYSSNIV : VLRLIFG
//									   __no_operation();
//									   break;
//			   case SYSSNIV_VLRHIFG:                       // SYSSNIV : VLRHIFG
//									   __no_operation();
//									   break;
//
//
//
//			   default: break;
//			}
//	}
