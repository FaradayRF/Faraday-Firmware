/*
 * ring.c
 *
 *  Created on: Mar 8, 2016
 *      Author: Brent
 */

#include "FIFO.h"
#include "msp430.h"



unsigned char put_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *data, unsigned char *char_item){
	__no_operation();
	//Check if buffer is full!
	if((buffer_struct->inwaiting*buffer_struct->element_size) >= buffer_struct->buffer_size){
		//Set debut overflow bit
		buffer_struct->debug |= BIT0;
		//Return 0 to indicate failure (buffer full!)
		return 0;
	}
	//Buffer ready to accept new item
	else{
		unsigned char i;
		for(i=0;i<buffer_struct->element_size;i++){
			//Insert value into the FIFO ring buffer in next avaliable location (head)
			data[buffer_struct->head+i] = char_item[i];
		}

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

unsigned char get_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *data, unsigned char *get_byte_addr){
	__no_operation();
	//Check if buffer is empty!
	if(buffer_struct->inwaiting == 0){
		//Set debut overflow bit
		//buffer_struct->debug |= BIT0;
		//Return 0 to indicate failure (buffer full!)
		return 0; //Failure (nothing to get)
	}
	//Buffer ready to accept new item
	else{
		unsigned char i;
		for(i=0;i<buffer_struct->element_size;i++){
			//Copy value of the FIFO ring buffer tail into the get_byte pointer
			get_byte_addr[i]= data[buffer_struct->tail+i];
		}

		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->tail = (buffer_struct->tail+buffer_struct->element_size)%buffer_struct->buffer_size;
		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting--; //Decrement the inwaiting count
		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		return 1; //Success

	}
}

unsigned char fifo_empty(fifo_state_machine *buffer_struct){
	if(buffer_struct->inwaiting==0){
		return 1;
	}
	else{
		return 0;
	}
}
/*
char ring_buffer_empty_256(ring_buffer_256 *buffer_pointer){
	if((buffer_pointer->inwaiting) == 0){
		//Return 1 to indicate buffer is empty
		return 1;
	}
	else if(buffer_pointer->inwaiting!=0){
		//Return 0 to indicate buffer is NOT empty
		return 0;
	}
	else{
		return 0;
	}
}

char get_char_ring_buffer_256(ring_buffer_256 *buffer_pointer, unsigned char *item_got){
	if(ring_buffer_empty_256(buffer_pointer)){
		//Return 0 to indicate failure, no new FIFO (ring buffer) items to be read!
		return 0;
	}
	else{
		//Get the next FIFO item available and update char variable passed by reference
		*item_got = buffer_pointer->data[buffer_pointer->tail];
		//Increment the tail of the ring buffer, modulus allows easy wrapping (circle)
		buffer_pointer->tail = (buffer_pointer->tail+1)%CHAR_RING_BUFFER_SIZE_256;
		//Decrement the inwaiting variable to account for removed FIFO item
		buffer_pointer->inwaiting--;
		//Return 1 to indicate success (item read from FIFO)
		return 1;
	}
}
*/
