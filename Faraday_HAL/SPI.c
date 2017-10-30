/** @file SPI.c
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "SPI.h"
#include "../REVA_Faraday.h"
//#include "cp2120.h"





/** @name SPI HAL Variables
*
* 	These variables are used for the SPI hardware abstraction layer.
*
@{**/
//volatile unsigned char chip_select_active; /**< A byte that indicates whether any chip select is active OR if none are active */
volatile unsigned char chip_select_bitmask; /**< This bitmask holds 8 bits that indicate which peripheral chip selects to manipulate and function as a set and hold configuration */
/** @}*/



void spi_tx(unsigned char tx){
	  while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	  UCB0TXBUF = tx;                     // Transmit first character
	  //__delay_cycles(2300);
}

unsigned char spi_rx_byte(unsigned char delay_cycles){
	unsigned char rx_byte;
	rx_byte = UCB0RXBUF;
	return rx_byte;
}

unsigned char spi_enable_chip_select(unsigned char SPI_HAL_CS){
	// This function is meant as a central control for chip select functionality between multiple devices

	if (chip_select_bitmask == 0){
		// No chip selects currently active - OK to activate a chip select output.

		// Set chip select bitmask global variable to new value to hold current state (mostly for debugging, at this time)
		chip_select_bitmask = SPI_HAL_CS;

		switch(chip_select_bitmask){
		case SPI_HAL_CS_SRAM: // SRAM device
			Faraday_SRAM_CS_Enable();
			break;
		case SPI_HAL_CS_I2C: // SPI to I2C
			Faraday_CP2120_CS_Enable();
			break;
		default: //Default - Should NEVER get here
			__no_operation();
			break;
		}
		return 1;
	}
	else{
		// A chip select is still active! This should never happen and will potentially cause race condition errors.
		__no_operation();
		return 0;
	}
}

unsigned char spi_disable_chip_select(unsigned char SPI_HAL_CS){
	// This function is meant as a central control for chip select functionality between multiple devices

	if (chip_select_bitmask != 0){
		// No chip selects currently active - OK to activate a chip select output.
		switch(chip_select_bitmask){
		case SPI_HAL_CS_SRAM: // SRAM device
			Faraday_SRAM_CS_Disable();
			break;
		case SPI_HAL_CS_I2C: // SPI to I2C
//			Faraday_CP2120_CS_Disable();
			break;
		default: //Default - Should NEVER get here
			__no_operation();
			break;
		}

		// Set chip select bitmask global variable to default state (0x00) (mostly for debugging, at this time)
		chip_select_bitmask = 0x00;

		return 1;
	}
	else{
		// A chip select is still active! This should never happen and will potentially cause race condition errors.
		__no_operation();
		return 0;
	}
}

void Faraday_SRAM_CS_Enable(void){
	//Active LOW
	P5OUT &= ~SRAM_CS;
}

void Faraday_SRAM_CS_Disable(void){
	//Active LOW
	P5OUT |= SRAM_CS;
}

void Faraday_SRAM_Hold_Enable(void){
	//Active LOW
	P5OUT &= ~SRAM_HOLD;
}

void Faraday_SRAM_Hold_Disable(void){
	//Active LOW
	P5OUT |= SRAM_HOLD;
}

//void Faraday_CP2120_CS_Enable(void){
//	//Active LOW
//	P1OUT &= ~CP2120_SPI_CS;
//}
//
//void Faraday_CP2120_CS_Disable(void){
//	//Active LOW
//	P1OUT |= CP2120_SPI_CS;
//}
