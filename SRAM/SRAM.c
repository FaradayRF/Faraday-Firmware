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


void Faraday_SRAM_Write_Byte(unsigned char byte, unsigned int address){
	unsigned char address_h, address_l;

	//Select the SRAM chip select
	spi_enable_chip_select(SPI_HAL_CS_SRAM);
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
	spi_disable_chip_select(SPI_HAL_CS_SRAM);
}

unsigned char Faraday_SRAM_Read_Settings(void){
	// 0 = Byte Mode
	// 1 = Page Mode
	// 2 = Sequential Mode
	// 4 = Reserved (Test?)

	//Select the SRAM chip select
	spi_enable_chip_select(SPI_HAL_CS_SRAM);
	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Send the READ command
	spi_tx(SRAM_RDSR);

	//Send dummy byte to shift SPI registers out of SRAM into RX CC430
	spi_tx(0x00); //dummy

	__delay_cycles(SPI_BYTE_CYCLES*2); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	spi_disable_chip_select(SPI_HAL_CS_SRAM);

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

		spi_enable_chip_select(SPI_HAL_CS_SRAM);
		__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

		//Send the READ command
		spi_tx(SRAM_WRSR);
		//__delay_cycles(50);

		//Send dummy byte to shift SPI registers out of SRAM into RX CC430
		spi_tx(mode2); //dummy

		__delay_cycles(SPI_BYTE_CYCLES*2); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		spi_disable_chip_select(SPI_HAL_CS_SRAM);
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
	//Faraday_SRAM_CS_Enable();
	spi_enable_chip_select(SPI_HAL_CS_SRAM);

	//Delay post transmission
	__delay_cycles(20); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Send the WRITE command
	spi_tx(SRAM_WRITE);

	//Send Address to be written to
	Faraday_SRAM_Send_Address(sram_address);
	__delay_cycles(SPI_BYTE_CYCLES*3);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	for(i=0;i<count;i++){
		//Send byte to be written
		spi_tx(buffer_address[i]);

		//Delay post transmission
		//__delay_cycles(25);
	}
	for(i=0;i<count;i++){
		//Delay post transmission
		__delay_cycles(SPI_BYTE_CYCLES);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	}
	//Faraday_SRAM_CS_Disable();
	spi_disable_chip_select(SPI_HAL_CS_SRAM);
}

void Faraday_SRAM_Read_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	//Initialize variables
	unsigned int i;

	//Select the SRAM chip select
	spi_enable_chip_select(SPI_HAL_CS_SRAM);

	//Delay post transmission
	__delay_cycles(10); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles

	//Send the WRITE command
	spi_tx(SRAM_READ);

	Faraday_SRAM_Send_Address(sram_address);
	__delay_cycles(SPI_BYTE_CYCLES*3);

	for(i=0;i<count;i++){
		spi_tx(SPI_DUMMY_BYTE);
		__delay_cycles(SPI_BYTE_CYCLES*2); // Delay for each byte RX to allow CC430 to catch up (Not sure why x2...)
		buffer_address[i] = spi_rx_byte(50);
	}
	spi_disable_chip_select(SPI_HAL_CS_SRAM);
	}


void Faraday_SRAM_Send_Address(unsigned int sram_address){
	//Faraday_SRAM_Write_Byte(buffer_address[i],sram_address);
	unsigned char address_h, address_l;

	//Shift the address INTEGER into high and low CHAR bytes
	address_h = (sram_address>>8) & 0xFF;
	address_l = sram_address & 0xFF;

	//Send Address to be written to
	spi_tx(address_h);
	spi_tx(address_l);
}

void Faraday_SRAM_Toggle_CS(void){
	//This function simply turns the SRAM CS pin enabled and disabled which when used on bootup prevents the low impedance issue noted in firmware issue #80
	spi_enable_chip_select(SPI_HAL_CS_SRAM);
	__delay_cycles(SPI_BYTE_CYCLES); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	spi_disable_chip_select(SPI_HAL_CS_SRAM);
}
