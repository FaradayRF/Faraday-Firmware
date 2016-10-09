/*
 * Packet_Ring_Buffer.c
 *
 *  Created on: Jan 13, 2016
 *      Author: Brent
 */
#include "Packet_Ring_Buffer.h"

/*void init_packet_buffers(void){
	//Create ring buffer RX
	packet_ring_buffer_64_ptr = &packet_ring_buffer_64_struct;
	init_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr);
}
*/

/************************************************************
* Function: init_256_char_ring_buffer(ring_buffer_256 *buffer_struct)
*
* Description: This function is used to initialize a ring buffer
* 			   Struct object. All struct values will be reset to
* 			   values. The Struct is passed by reference.
*
* Inputs: *buffer_struct
*
* Outputs: Returns 1 afer completion.
*
*************************************************************/
void init_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_struct){
	int i;
	//Reset all values to default
	buffer_struct->head_pkt = 0;
	buffer_struct->tail_pkt = 0;
	buffer_struct->inwaiting = 0;
	for(i=0; i<(CHAR_PACKET_RING_BUFFER_PACKET_SIZE_64*CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64); i++){
		buffer_struct->data[i] = 0;
	}

	//return 1;


}


/************************************************************
* Function: put_char_ring_buffer(ring_buffer_256 *buffer_struct, char char_item)
*
* Description: This function inserts a char byte value into
* 			   a Struct object ring buffer (256 byte version)
* 			   at the current HEAD position. The HEAD position
* 			   value and the "inwaiting" values are updated
* 			   accordingly. If the buffer is full the new item
* 			   will NOT be inserted into the buffer.
*
* Inputs: *buffer_struct, char_item
*
* Outputs: Returns 1 afer sucessful insert into buffer. Returns 0 if buffer
* 		   is full and item is NOT inserted.
*
*************************************************************/
char put_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_struct, unsigned char *packet_data_pointer, unsigned char length){
	//Check if buffer is full!
	if(buffer_struct->inwaiting >= (CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64)){
		//Set debut overflow bit
		//ring_buffer_health_enable_overflow_bit_256(buffer_struct);
		//buffer_struct->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
		//Return 0 to indicate failure (buffer full!)
		//DEBUG - MAX INWAIT
		update_max_inwaiting_packet_ring_buffer_64(buffer_struct);
		return 0;
	}
	//Buffer ready to accept new item
	else{
		unsigned char i;

		//Place packet into buffer byte by byte
		for(i=0;i<length;i++){
			//Insert value into the FIFO ring buffer in next avaliable location (head)
					buffer_struct->data[((buffer_struct->head_pkt*CHAR_PACKET_RING_BUFFER_PACKET_SIZE_64)+i)] = packet_data_pointer[i];
		}

		//Save packet buffer location length
		buffer_struct->length_pkt[buffer_struct->head_pkt] = length;

		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->head_pkt = (buffer_struct->head_pkt+1)%CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64;
		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting++; //Increment the inwaiting count
		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		update_max_inwaiting_packet_ring_buffer_64(buffer_struct);
		return 1;

	}
}


/************************************************************
* Function: ring_buffer_empty(ring_buffer_256 *buffer_pointer)
*
* Description: This function checks the struct ring buffer
* 			   object that was passed by reference and
* 			   returns 1 if the ring buffer has NO items
* 			   left to "get" and is "empty." The function
* 			   returns 0 if there are items in the buffer
* 			   waiting to be read by "get."
*
* Inputs: *buffer_pointer
*
* Outputs: Returns 1 if buffer is empty (no waiting bytes to read).
* 		   Returns 0 if buffer contains items waiting to be read.
*
*************************************************************/
/*char ring_buffer_empty_256(ring_buffer_256 *buffer_pointer){
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
*/

/************************************************************
* Function: get_char_ring_buffer(ring_buffer_256 *buffer_pointer, char *item_got)
*
* Description: This function updates a char variable that is passed by reference to
* 			   the next item (FIFO) to be read in the ring buffer passed by reference.
* 			   The respective TAIL and inwaiting struct object values are updated
* 			   accordingly. If there are no items waiting to be read then the
* 			   function returns 0.
*
* Inputs: *buffer_pointer, char *item_got
*
* Outputs: Returns 1 afer sucessful READ of the buffer. Returns 0 if buffer
* 		   is contains no items waiting to be read (empty).
*
*************************************************************/
unsigned char get_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer, unsigned char *packet_got_ptr){
	if(buffer_pointer->inwaiting <= 0){
		//Return 0 to indicate failure, no new FIFO (ring buffer) items to be read!
		return 0;
	}
	else{
		//Get the next FIFO item available and update char variable passed by reference
		unsigned char i;

		for(i=0;i<64;i++){
			packet_got_ptr[i] = buffer_pointer->data[(buffer_pointer->tail_pkt*CHAR_PACKET_RING_BUFFER_PACKET_SIZE_64)+i];
		}

		//Increment the tail of the ring buffer, modulus allows easy wrapping (circle)
		buffer_pointer->tail_pkt = (buffer_pointer->tail_pkt+1)%CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64;



		//Decrement the inwaiting variable to account for removed FIFO item
		buffer_pointer->inwaiting--;
		//Return 1 to indicate success (item read from FIFO)
		return 1;
	}
}


unsigned char isempty_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer){
	if(buffer_pointer->inwaiting != 0){
		return 1;
	}
	else{
		return 0;
	}
}

/************************************************************
* Function: void ring_buffer_health_set_max_inwaiting(ring_buffer_256 *buffer_pointer)
*
* Description: This function sets the status of the circular buffer debug
*              bit flag for an overflow event to 1.
*
* Inputs:
*              ring_buffer_256 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/
void update_max_inwaiting_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer){
	//Check if current value of in_waiting is larger than the current max hold value.
	if(buffer_pointer->inwaiting > buffer_pointer->max_inwait){
		buffer_pointer->max_inwait = buffer_pointer->inwaiting;
	}
}

