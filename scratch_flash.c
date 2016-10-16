/*
 * scratch_flash.c
 *
 *  Created on: Oct 11, 2016
 *      Author: Brent
 */




#include "scratch_flash.h"
#include "FLASH/FLASH.h"
#include "Faraday_HAL/SPI.h"
#include "cc430f6137.h"

void flash_test(void){

	UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB0CTL0 |= UCMST+UCSYNC+UCCKPH+UCMSB;    // 3-pin, 8-bit SPI master +UCCKPL
	//UCB0CTL0 |= UCMST+UCSYNC+UCMSB;    // 3-pin, 8-bit SPI master +UCCKPL
											  // Clock polarity high, MSB
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	UCB0BR0 = 0x02;                           // /2
	UCB0BR1 = 0;                              //
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	//Device and manufacture ID
	//volatile unsigned char flashID[4];
	//Faraday_FLASH_Get_ID(flashID);

	//Enable device SPI
	//Faraday_FLASH_Hold_Disable();
	Faraday_FLASH_Hold_Enable();
	Faraday_FLASH_SPI_Enable();
	__delay_cycles(50);

	//Device Status
	volatile unsigned char status;
	status = Faraday_FLASH_Get_Status();
	__delay_cycles(50);

	//Faraday_FLASH_SPI_Disable();

	__no_operation();

	//Write Enable
	//Faraday_FLASH_SPI_Enable();
	__delay_cycles(50);
	Faraday_FLASH_Write_Enable();
	__delay_cycles(50);
	//Faraday_FLASH_SPI_Disable();
	//Faraday_FLASH_SPI_Enable();
	__delay_cycles(50);
	status = Faraday_FLASH_Get_Status();
	__delay_cycles(50);

	__no_operation();

	//Release the device chip SPI select/enable
	Faraday_FLASH_SPI_Disable();


//
//	///////// Read Status Register
//
//	Faraday_FLASH_CE_Enable();
//	Faraday_FLASH_Hold_Disable();
//	__delay_cycles(50);
//
//	//Send the Read Status Byte command
//	spi_tx(0x05);
//	__delay_cycles(50); //Seem to need some delay at least
//	spi_tx(0x00);
//	__delay_cycles(50);
//
//	volatile unsigned char status_byte;
//	status_byte = UCB0RXBUF;
//
//	__delay_cycles(50);
//
//	Faraday_FLASH_CE_Disable();
//
//
//	/////////Write Enable
//
//	Faraday_FLASH_CE_Enable();
//	Faraday_FLASH_Hold_Disable();
//	__delay_cycles(50);
//
//	//Send the WRITE ENABLE command
//	spi_tx(0x06);
//
//
//	__delay_cycles(50);
//
//	//Faraday_FLASH_CE_Disable();
//	__delay_cycles(50);
//
//	///////// Read Status Register
//
//	Faraday_FLASH_CE_Enable();
//	Faraday_FLASH_Hold_Disable();
//	__delay_cycles(50);
//
//	//Send the Read Status Byte command
//	spi_tx(0x05);
//	__delay_cycles(50); //Seem to need some delay at least
//	spi_tx(0x00);
//	__delay_cycles(50);
//	volatile unsigned char status_byte2;
//	status_byte2 = UCB0RXBUF;
//
//	__delay_cycles(50);
//
//	Faraday_FLASH_CE_Disable();
//
//	/////////Write Data
//
//	Faraday_FLASH_CE_Enable();
//	Faraday_FLASH_Hold_Disable();
//	__delay_cycles(50);
//
//	//Send the PAGE WRITE command
//	spi_tx(0x02);
//
//	//Send 3 address bytes MSB
//	spi_tx(0x00);
//	spi_tx(0x00);
//	spi_tx(0x00);
//
//	//Send 4 DATA bytes
//	spi_tx(0x00);
//	spi_tx(0x01);
//	spi_tx(0x02);
//	spi_tx(0x03);
//
//
//	Faraday_FLASH_CE_Disable();
//	__delay_cycles(50);
//
//	__no_operation();
//
//	///////////Read Memory Address (Device ID?)
//	volatile unsigned char databytes2[4];
//
//	Faraday_FLASH_CE_Enable();
//	Faraday_FLASH_Hold_Disable();
//	__delay_cycles(50);
//
//	//Send the READ command
//	spi_tx(0x03);
//
//	//Send 3 address bytes MSB
//	spi_tx(0x00);
//	spi_tx(0x00);
//	spi_tx(0x00);
//
//	//4 read bytes
//	for(i=0;i<4;i++){
//		spi_tx(0x00);
//		__delay_cycles(50);
//		databytes2[i] = UCB0RXBUF;
//	}
//
//	Faraday_FLASH_CE_Disable();
//	__delay_cycles(50);
//
//	__no_operation();


}
