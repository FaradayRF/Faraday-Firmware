#include "FIFO_SRAM.h"
#include "msp430.h"
#include "../SRAM/SRAM.h"

void fifo_sram_init(fifo_sram_state_machine *buffer_struct, const unsigned int sram_address, const unsigned int element_size, const unsigned char element_count){
	buffer_struct->sram_start_address = sram_address;
	buffer_struct->debug = 0;
	buffer_struct->element_size = element_size;
	buffer_struct->head = 0;
	buffer_struct->inwaiting = 0;
	buffer_struct->length = 0;
	buffer_struct->max_inwait = 0;
	buffer_struct->tail = 0;
	buffer_struct->buffer_size = element_size*element_count;
}

unsigned char put_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *char_item){
	//Check if buffer is full!
	if((buffer_struct->inwaiting*buffer_struct->element_size) >= buffer_struct->buffer_size){
		//Set debut overflow bit
		buffer_struct->debug |= BIT0;

		//Return 0 to indicate failure (buffer full!)
		return 0;
	}

	//Buffer ready to accept new item
	else{
		unsigned int address;
		address = (buffer_struct->sram_start_address)+(buffer_struct->head);
		Faraday_SRAM_Write_Sequential_Bytes(buffer_struct->element_size, address, char_item);

		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->head = (buffer_struct->head+buffer_struct->element_size)%buffer_struct->buffer_size;

		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting++; //Increment the inwaiting count

		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		if(buffer_struct->inwaiting > buffer_struct->max_inwait){
			buffer_struct->max_inwait = buffer_struct->inwaiting;
		}

		return 1;
	}
}

unsigned char get_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *get_byte_addr){
	//Check if buffer is empty!
	if(buffer_struct->inwaiting == 0){
		//Set debut overflow bit
		//buffer_struct->debug |= BIT0;
		//Return 0 to indicate failure (buffer full!)
		return 0; //Failure (nothing to get)
	}
	//Buffer ready to accept new item
	else{
		unsigned int address;
		address = (buffer_struct->sram_start_address)+(buffer_struct->tail);
		Faraday_SRAM_Read_Sequential_Bytes(buffer_struct->element_size, address, (unsigned char *)get_byte_addr);

		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->tail = (buffer_struct->tail+buffer_struct->element_size)%buffer_struct->buffer_size;

		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting--; //Decrement the inwaiting count

		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		return 1; //Success

	}
}
