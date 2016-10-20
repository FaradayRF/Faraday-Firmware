/** @file SRAM.c
 *  @brief SPI SRAM IC Driver
 *
 *  These functions provide basic support to use the onboard SPI SRAM IC. This module
 *  allows a large amount of RAM to be used external to the CC430.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "SRAM.h"

/* faraday hardware allocations */
#include "../REVA_Faraday.h"

/* spi driver*/
#include "../Faraday_HAL/SPI.h"

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

void Faraday_SRAM_Write_Byte(unsigned char byte, unsigned int address){
	unsigned char address_h, address_l;

	//Select the SRAM chip select
	Faraday_SRAM_CS_Enable();
	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Shift the address INTEGER into high and low CHAR bytes
	address_h = (address>>8) & 0xFF;
	address_l = address & 0xFF;

	//Send the WRITE command
	spi_tx(SRAM_WRITE);

	//Send Address to be written to
	spi_tx(address_h);
	spi_tx(address_l);

	//Send byte to be written
	spi_tx(byte);
	__delay_cycles(50);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();
}

unsigned char Faraday_SRAM_Read_Byte(unsigned int address){
	unsigned char address_h, address_l;

	//Select the SRAM chip select
	Faraday_SRAM_CS_Enable();
	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Shift the address INTEGER into high and low CHAR bytes
	address_h = (address>>8) & 0xFF;
	address_l = address & 0xFF;

	//Send the READ command
	spi_tx(SRAM_READ);

	//Send Address to be written to
	spi_tx(address_h);
	spi_tx(address_l);

	//Send dummy byte to shift SPI registers out of SRAM into RX CC430
	spi_tx(0x00); //dummy

	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();

	unsigned char rx_byte;
	rx_byte = UCB0RXBUF;
	return rx_byte;
}

unsigned char Faraday_SRAM_Read_Settings(void){
	// 0 = Byte Mode
	// 1 = Page Mode
	// 2 = Sequential Mode
	// 4 = Reserved (Test?)

	//Select the SRAM chip select
	Faraday_SRAM_CS_Enable();
	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Send the READ command
	spi_tx(SRAM_RDSR);

	//Send dummy byte to shift SPI registers out of SRAM into RX CC430
	spi_tx(0x00); //dummy

	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();

	unsigned char test2;
	test2 = UCB0RXBUF>>6; // Shift mode bytes down from bits 6 & 7 to LSB
	return test2;
}

void Faraday_SRAM_Write_Settings(unsigned char mode){
	// 0 = Byte Mode
	// 1 = Sequential Mode
	// 2 = Page Mode
	// 4 = Reserved (Test?)

	if (mode < 4){
		unsigned char mode2 = mode<<6; //Shift mode bits to bits 6 and 7
		//Select the SRAM chip select

		Faraday_SRAM_CS_Enable();
		__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

		//Send the READ command
		spi_tx(SRAM_WRSR);
		__delay_cycles(50);

		//Send dummy byte to shift SPI registers out of SRAM into RX CC430
		spi_tx(mode2); //dummy

		__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		Faraday_SRAM_CS_Disable();
	}
	else{
		__no_operation(); // ERROR!
	}
}

void Faraday_SRAM_Init_Byte_Mode(void){
	/*
	 * In this mode, the read/
write operations are limited to only one byte. The
Command followed by the 16-bit address is clocked into
the device and the data to/from the device is transferred
on the next 8 clocks (Figure 2-1, Figure 2-2)
	 */
	Faraday_SRAM_Write_Settings(0);
}
void Faraday_SRAM_Init_Sequential_Mode(void){
	/*
	 *  Sequential operation
allows the entire array to be written to and read
from. The internal address counter is automatically
incremented and page boundaries are ignored. When
the internal address counter reaches the end of the
array, the address counter will roll over to 0x0000
(Figure 2-5, Figure 2-6).
	 */
	Faraday_SRAM_Write_Settings(1);
}
void Faraday_SRAM_Init_Page_Mode(void){
	/*
	 *  The 23A256/23K256 has
1024 pages of 32 Bytes. In this mode, the read and write
operations are limited to within the addressed page (the
address is automatically incremented internally). If the
data being read or written reaches the page boundary,
then the internal address counter will increment to the
start of the page (Figure 2-3, Figure 2-4).
	 */
	Faraday_SRAM_Write_Settings(2);
}

void Faraday_SRAM_Write_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	unsigned int i;

	//Faraday_SRAM_Write_Byte(buffer_address[i],sram_address);
	unsigned char address_h, address_l;

	//Select the SRAM chip select
	Faraday_SRAM_CS_Enable();
	__delay_cycles(20); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Shift the address INTEGER into high and low CHAR bytes
	address_h = (sram_address>>8) & 0xFF;
	address_l = sram_address & 0xFF;

	//Send the WRITE command
	spi_tx(SRAM_WRITE);

	//Send Address to be written to
	spi_tx(address_h);
	spi_tx(address_l);

	for(i=0;i<count;i++){
		//Send byte to be written
		spi_tx(buffer_address[i]);
		__delay_cycles(25);

	}
	__delay_cycles(20);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();
}

void Faraday_SRAM_Read_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	// BUG 10/13/2015 - Not fully working! [Brenton Salmi]
	unsigned int i;
		//Faraday_SRAM_Write_Byte(buffer_address[i],sram_address);
		unsigned char address_h, address_l;
		unsigned char test2;

		//Select the SRAM chip select
		Faraday_SRAM_CS_Enable();
		__delay_cycles(10); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

		//Shift the address INTEGER into high and low CHAR bytes
		address_h = (sram_address>>8) & 0xFF;
		address_l = sram_address & 0xFF;

		//Send the WRITE command
		spi_tx(SRAM_READ);

		//Send Address to be written to

		spi_tx(address_h);
		spi_tx(address_l);


		for(i=0;i<count;i++){
			//Send dummy byte to shift SPI registers out of SRAM into RX CC430
			spi_tx(0x00); //dummy

			__delay_cycles(50);
			test2 = UCB0RXBUF;
			buffer_address[i] = test2;//UCB0RXBUF;

		}
		__delay_cycles(50);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		Faraday_SRAM_CS_Disable();

	}
