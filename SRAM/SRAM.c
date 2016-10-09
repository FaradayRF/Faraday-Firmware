/*
 * SRAM.c
 *
 *  Created on: Oct 13, 2015
 *      Author: Brent
 */

#include <msp430.h>
#include "../REVA_Faraday.h"
#include "SRAM.h"
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
	//while (!(UCB0IFG & UCRXIFG)); // USCI_A0 RX Received?
	//__delay_cycles(10);
	__delay_cycles(50); //Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();

	unsigned char test2;
	test2 = UCB0RXBUF;
	return test2;
}

void Faraday_SRAM_Read_Multiple_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	unsigned int i;

	for(i=0;i<count;i++){
		buffer_address[i] = Faraday_SRAM_Read_Byte(sram_address);
		sram_address++;
	}
}

void Faraday_SRAM_Write_Multiple_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	unsigned int i;

	for(i=0;i<count;i++){
		Faraday_SRAM_Write_Byte(buffer_address[i],sram_address);
		sram_address++;
	}
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
	//__delay_cycles(10);
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
		//__delay_cycles(10);
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
	//static unsigned char test;
	//test = Faraday_SRAM_Read_Settings();

	//Check if in sequential mode (BUG!!! 10-13-15 BRENTSALMI)
	/*
	if(test == 0x01){
		__no_operation();
	}
	else{
		__no_operation();
	}*/

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
	//__delay_cycles(25);
	for(i=0;i<count;i++){
		//Send byte to be written
		//__delay_cycles(3);//Per datasheet at 3.0V CS delay is 1ns = @16MHz is ~1 clock cycle
		spi_tx(buffer_address[i]);
		__delay_cycles(25);

	}
	__delay_cycles(20);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
	Faraday_SRAM_CS_Disable();
}

void Faraday_SRAM_Read_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address){
	// BUG 10/13/2015 - Not fully working! [Brenton Salmi]
	unsigned int i;
		//static unsigned char test;
		//Faraday_SRAM_Read_Settings();

		//Check if in sequential mode (BUG!!! 10-13-15 BRENTSALMI)
		/*
		if(test == 0x01){
			__no_operation();
		}
		else{
			__no_operation();
		}*/

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
		//__delay_cycles(50);

		for(i=0;i<count;i++){
			//Send byte to be written
			//__delay_cycles(3);//Per datasheet at 3.0V CS delay is 1ns = @16MHz is ~1 clock cycle
			//spi_tx(buffer_address[i]);
			//Send dummy byte to shift SPI registers out of SRAM into RX CC430
			spi_tx(0x00); //dummy
			//while (!(UCB0IFG&UCRXIFG) && !(UCB0IFG&UCTXIFG));
			__delay_cycles(50);
			test2 = UCB0RXBUF;
			buffer_address[i] = test2;//UCB0RXBUF;

		}
		__delay_cycles(50);//Per datasheet at 3.0V CS delay is 25ns = @16MHz is 2.5 clock cycles
		Faraday_SRAM_CS_Disable();

	}

/*
void init_sram_ring_buffer(ring_buffer_SRAM *buffer_struct, unsigned int start, unsigned int length){
	int i;
	buffer_struct->data_address = start;
	buffer_struct->length = length;
	//Reset all values to default
	buffer_struct->head = 0;
	buffer_struct->tail = 0;
	buffer_struct->inwaiting = 0;
	for(i=0; i<buffer_struct->length; i++){
		Faraday_SRAM_Write_Byte(0x00, buffer_struct->data_address+i);
	}
}



void create_sram_ring_buffer(void){
	//Link the struct pointer to struct, for some reason this needs to happen for proper declaration and not globably...?
	uart_datalink_rx_ring_buffer_sram_ptr = &uart_datalink_rx_ring_buffer_sram_struct;
	//init_sram_ring_buffer(uart_datalink_rx_ring_buffer_sram_ptr, 100, 64);
}

unsigned char put_char_ring_buffer_sram(ring_buffer_SRAM *buffer_struct, unsigned char char_item){
	//Check if buffer is full!
	if(buffer_struct->inwaiting >= buffer_struct->length){
		//Set debut overflow bit
		//ring_buffer_health_enable_overflow_bit(buffer_struct);
		//buffer_struct->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
		//Return 0 to indicate failure (buffer full!)
		//DEBUG - MAX INWAIT
		//ring_buffer_health_set_max_inwaiting(buffer_struct);
		return 0;
	}
	//Buffer ready to accept new item
	else{
		//Insert value into the FIFO ring buffer in next avaliable location (head)
		////buffer_struct->data[buffer_struct->head] = char_item;
		Faraday_SRAM_Write_Byte(char_item, buffer_struct->data_address + buffer_struct->head);
		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->head = (buffer_struct->head+1)%buffer_struct->length;
		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting++; //Increment the inwaiting count
		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		//ring_buffer_health_set_max_inwaiting(buffer_struct);
		return 1;

	}
}
*/
