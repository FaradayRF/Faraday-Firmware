/** @file FLASH.c
 *  @brief Hardware abstraction for the onboard Faraday FLASH memory IC.
 *
 *  The functions below provide input/output ability with the onboard
 *  FLASH memory IC using SPI. Read and Write functioanlity is supportted.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"

/* faraday hardware allocations */
#include "../REVA_Faraday.h"
//#include "../Faraday_HAL/SPI.h"



void Faraday_FLASH_CE_Enable(void){
	//Active LOW
	P3OUT &= ~FLASH_SPI_CS;
}

void Faraday_FLASH_CE_Disable(void){
	//Active LOW
	P3OUT |= FLASH_SPI_CS;
}

void Faraday_FLASH_Hold_Enable(void){
	//Active LOW
	P5OUT &= ~FLASH_HOLD;
}

void Faraday_FLASH_Hold_Disable(void){
	//Active LOW
	P5OUT |= FLASH_HOLD;
}
