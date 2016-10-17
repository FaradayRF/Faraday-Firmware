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
#include "FLASH.h"

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
}

void Faraday_FLASH_SPI_Disable(void){
	Faraday_FLASH_CE_Disable();
}

void Faraday_FLASH_Get_ID(unsigned char * id_data){
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

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
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

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
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

	//Send the WLEN command
	spi_tx(0x06);
	__delay_cycles(50); //Delay for IC to process
}


void Faraday_FLASH_Write_Disable(void){
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

	//Send the WLEN command
	spi_tx(0x04);
	__delay_cycles(50); //Delay for IC to process
}

void Faraday_FLASH_Toggle_Chip_Enable(void){
	Faraday_FLASH_CE_Disable();
	__delay_cycles(50);
	//spi_tx(0x00);
	Faraday_FLASH_CE_Enable();
	__delay_cycles(50);
}

void Faraday_FLASH_Read_Data(unsigned char address_2, unsigned char address_1, unsigned char address_0, unsigned int length, unsigned char * ptr_receive_data){
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

	//Send the READ command
	spi_tx(0x03);

	//Send 3 address bytes
	spi_tx(address_2);
	spi_tx(address_1);
	spi_tx(address_0);

	//Read bytes at address and place into supplied pointer
	unsigned int i;
	for(i=0; i<length; i++){
		spi_tx(0x00); // Send dummy byte to shift read byte out
		__delay_cycles(50); // Delay for CC430 to poll RX buffer when data ready
		ptr_receive_data[i] = UCB0RXBUF;

	}
}


void Faraday_FLASH_Sector_Erase(unsigned char address_2, unsigned char address_1, unsigned char address_0){
	//Toggle Chip Enable
	Faraday_FLASH_Toggle_Chip_Enable();

	//Send the SECTOR_ER command
	spi_tx(0xD7);

	//Send 3 address bytes
	spi_tx(address_2);
	spi_tx(address_1);
	spi_tx(address_0);

	unsigned char status;

	//check status until device is done erasing
	status = Faraday_FLASH_Get_Status();
	while(status&BIT0){
			__delay_cycles(5000);
			status = Faraday_FLASH_Get_Status();
		}

}
