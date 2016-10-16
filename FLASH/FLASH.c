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
	//Faraday_FLASH_Hold_Disable();
	__delay_cycles(5000);
}

void Faraday_FLASH_SPI_Disable(void){
	Faraday_FLASH_CE_Disable();
}

void Faraday_FLASH_Get_ID(unsigned char * id_data){

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
}


unsigned char Faraday_FLASH_Get_Status(void){
	//Create function variables
	unsigned char uChar_status;

	//Send the RDSR command
	spi_tx(0x05);

	//Send 1 dummy byte
	spi_tx(0x00);

	__delay_cycles(500);

	//Get status byte
	uChar_status = UCB0RXBUF;

	//Return status byte
	return uChar_status;
}


void Faraday_FLASH_Write_Enable(void){
	//Send the WLEN command
	spi_tx(0x06);
}


void Faraday_FLASH_Write_Disable(void){
	//Send the WLEN command
	spi_tx(0x04);
}
