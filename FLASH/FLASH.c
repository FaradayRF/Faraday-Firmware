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

/* faraday SPI library */
#include "../Faraday_HAL/SPI.h"



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

void Faraday_FLASH_SPI_Enable(void){
	Faraday_FLASH_CE_Enable();
	Faraday_FLASH_Hold_Disable();
	__delay_cycles(50);
}

void Faraday_FLASH_SPI_Disable(void){
	Faraday_FLASH_CE_Disable();
}

void Faraday_FLASH_Get_ID(unsigned char * id_data){
	Faraday_FLASH_SPI_Enable();

	//Send the READ command
	spi_tx(0x90);

	//Send 3 dummy bytes
	spi_tx(0x00);
	spi_tx(0x00);
	spi_tx(0x00);

	//4 read bytes
	unsigned char i;
	for(i=0;i<4;i++){
		spi_tx(0x00);
		__delay_cycles(50); //  This delay should be optimized out
		id_data[i] = UCB0RXBUF;
	}

	//Release the device chip SPI select/enable
	Faraday_FLASH_SPI_Disable();
}
