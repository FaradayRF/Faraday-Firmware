/*
 * Ring_Buffer.c
 *
 *  Created on: Aug 2, 2015
 *      Author: Brent
 */
#include <msp430.h>
#include "Ring_Buffer.h"






/************************************************************
* Function: init_64_char_ring_buffer(ring_buffer_64 *buffer_struct)
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
void init_64_char_ring_buffer(ring_buffer_64 *buffer_struct){
	int i;
	//Reset all values to default
	buffer_struct->head = 0;
	buffer_struct->tail = 0;
	buffer_struct->inwaiting = 0;
	for(i=0; i<CHAR_RING_BUFFER_SIZE_64; i++){
		buffer_struct->data[i] = 0;
	}

	//return 1;


}



/************************************************************
* Function: put_char_ring_buffer(ring_buffer_64 *buffer_struct, char char_item)
*
* Description: This function inserts a char byte value into
* 			   a Struct object ring buffer (64 byte version)
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
char put_char_ring_buffer_64(ring_buffer_64 *buffer_struct, unsigned char char_item){
	//Check if buffer is full!
	if(buffer_struct->inwaiting >= CHAR_RING_BUFFER_SIZE_64){
		//Set debut overflow bit
		ring_buffer_health_enable_overflow_bit(buffer_struct);
		//buffer_struct->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
		//Return 0 to indicate failure (buffer full!)
		//DEBUG - MAX INWAIT
		ring_buffer_health_set_max_inwaiting(buffer_struct);
		return 0;
	}
	//Buffer ready to accept new item
	else{
		//Insert value into the FIFO ring buffer in next avaliable location (head)
		buffer_struct->data[buffer_struct->head] = char_item;
		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->head = (buffer_struct->head+1)%CHAR_RING_BUFFER_SIZE_64;
		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting++; //Increment the inwaiting count
		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		ring_buffer_health_set_max_inwaiting(buffer_struct);
		return 1;

	}
}


/************************************************************
* Function: ring_buffer_empty(ring_buffer_64 *buffer_pointer)
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
char ring_buffer_empty_64(ring_buffer_64 *buffer_pointer){
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

/************************************************************
* Function: get_char_ring_buffer(ring_buffer_64 *buffer_pointer, char *item_got)
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
char get_char_ring_buffer_64(ring_buffer_64 *buffer_pointer, unsigned char *item_got){
	if(ring_buffer_empty_64(buffer_pointer)){
		//Return 0 to indicate failure, no new FIFO (ring buffer) items to be read!
		return 0;
	}
	else{
		//Get the next FIFO item available and update char variable passed by reference
		*item_got = buffer_pointer->data[buffer_pointer->tail];
		//Increment the tail of the ring buffer, modulus allows easy wrapping (circle)
		buffer_pointer->tail = (buffer_pointer->tail+1)%CHAR_RING_BUFFER_SIZE_64;
		//Decrement the inwaiting variable to account for removed FIFO item
		buffer_pointer->inwaiting--;
		//Return 1 to indicate success (item read from FIFO)
		return 1;
	}
}

unsigned char get_head_ring_buffer_64(ring_buffer_64 *buffer_pointer){
	return buffer_pointer->head;
}

void ring_buffer_64_advance(ring_buffer_64 *buffer_pointer, unsigned char count){
	unsigned char i;
	unsigned char dummy;
	for(i=0;i<count;i++){
		get_char_ring_buffer_64(buffer_pointer, &dummy);
	}
}


/************************************************************
* Function: self_test_ring_buffer(void)
*
* Description: This function is a simple test case function for debugging
* 			   purposes. This also serves as an example of proper usage.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void self_test_ring_buffer_64(void){
	//Create ring buffer #1
	ring_buffer_64 *ringbuf;
	ring_buffer_64 ringbuf_struct;
	ringbuf = &ringbuf_struct;

	//Create ring buffer #2
	ring_buffer_64 *ringbuf2;
	ring_buffer_64 ringbuf_struct2;
	ringbuf2 = &ringbuf_struct2;


	init_64_char_ring_buffer(ringbuf);
	init_64_char_ring_buffer(ringbuf2);
	unsigned char chkbuf = 0;
	unsigned char chkbuf2 = 0;
	//Test if empty, returns 1 if true
	chkbuf = ring_buffer_empty_64(ringbuf);
	//Fill buffer to 60 bytes in waiting
	unsigned char i;
	for(i=0; i<60; i++){
		put_char_ring_buffer_64(ringbuf,i);
	}
	//Fill buffer #2 to 60 bytes in waiting
	for(i=0; i<60; i++){
		put_char_ring_buffer_64(ringbuf2,i);
	}
	//Test if empty, returns 1 if true
	chkbuf = ring_buffer_empty_64(ringbuf);
	//Check reading
	for(i=0; i<60; i++){
		get_char_ring_buffer_64(ringbuf,&chkbuf);
	}
	//Test buffer for wrap around
	for(i=0; i<10; i++){
		put_char_ring_buffer_64(ringbuf,i);
	}
	//Check reading
	for(i=0; i<10; i++){
	get_char_ring_buffer_64(ringbuf,&chkbuf);
	}
	//Check for read when empty
	get_char_ring_buffer_64(ringbuf,&chkbuf);
	//Check overflow
	for(i=0; i<66; i++){
		put_char_ring_buffer_64(ringbuf,i);
	}

	//Read buffer #2 until empty
	while(!ring_buffer_empty_64(ringbuf2)){
		get_char_ring_buffer_64(ringbuf2,&chkbuf2);
	}
}


/************************************************************
* Function: unsigned char ring_buffer_health_check_overflow_bit(ring_buffer_64 *buffer_pointer)
*
* Description: This function checks the status of the circular buffer debug
*              bit flag for an overflow event.
*
* Inputs:
*              ring_buffer_64 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/

unsigned char ring_buffer_health_check_overflow_bit(ring_buffer_64 *buffer_pointer){
	return buffer_pointer->debug & RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: void ring_buffer_health_enable_overflow_bit(ring_buffer_64 *buffer_pointer)
*
* Description: This function checks the status of the circular buffer debug
*              bit flag for an overflow event to 0.
*
* Inputs:
*              ring_buffer_64 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/
void ring_buffer_health_enable_overflow_bit(ring_buffer_64 *buffer_pointer){
	buffer_pointer->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: void ring_buffer_health_clear_overflow_bit(ring_buffer_64 *buffer_pointer)
*
* Description: This function sets the status of the circular buffer debug
*              bit flag for an overflow event to 1.
*
* Inputs:
*              ring_buffer_64 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/
void ring_buffer_health_clear_overflow_bit(ring_buffer_64 *buffer_pointer){
	buffer_pointer->debug &= ~RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: unsigned char ring_buffer_health_check_mac_inwaiting(ring_buffer_64 *buffer_pointer)
*
* Description: This function returns the value of the "max_inwait" variable in a circular buffer.
*              This value holds the maximum value of the "in_waiting" counter so that performance
*              of circular buffer utilization can be measured.
*
* Inputs:
*              ring_buffer_64 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/

unsigned char ring_buffer_health_check_mac_inwaiting(ring_buffer_64 *buffer_pointer){
	return buffer_pointer->max_inwait;
}

/************************************************************
* Function: void ring_buffer_health_set_max_inwaiting(ring_buffer_64 *buffer_pointer)
*
* Description: This function sets the status of the circular buffer debug
*              bit flag for an overflow event to 1.
*
* Inputs:
*              ring_buffer_64 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/
void ring_buffer_health_set_max_inwaiting(ring_buffer_64 *buffer_pointer){
	//Check if current value of in_waiting is larger than the current max hold value.
	if(buffer_pointer->inwaiting > buffer_pointer->max_inwait){
		buffer_pointer->max_inwait = buffer_pointer->inwaiting;
	}
}




///////////////////////////////////////////////////////////////////////////
//
//
// 256 byte
//
///////////////////////////////////////////////////////////////////////////


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
void init_256_char_ring_buffer(ring_buffer_256 *buffer_struct){
	int i;
	//Reset all values to default
	buffer_struct->head = 0;
	buffer_struct->tail = 0;
	buffer_struct->inwaiting = 0;
	for(i=0; i<CHAR_RING_BUFFER_SIZE_256; i++){
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
char put_char_ring_buffer_256(ring_buffer_256 *buffer_struct, unsigned char char_item){
	//Check if buffer is full!
	if(buffer_struct->inwaiting >= CHAR_RING_BUFFER_SIZE_256){
		//Set debut overflow bit
		ring_buffer_health_enable_overflow_bit_256(buffer_struct);
		//buffer_struct->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
		//Return 0 to indicate failure (buffer full!)
		//DEBUG - MAX INWAIT
		ring_buffer_health_set_max_inwaiting_256(buffer_struct);
		return 0;
	}
	//Buffer ready to accept new item
	else{
		//Insert value into the FIFO ring buffer in next avaliable location (head)
		buffer_struct->data[buffer_struct->head] = char_item;
		//Increment head location of ring buffer, modulus allows easy "wrapping" (circle)
		buffer_struct->head = (buffer_struct->head+1)%CHAR_RING_BUFFER_SIZE_256;
		//Increment the inwaiting variable to account for the new item in the FIFO
		buffer_struct->inwaiting++; //Increment the inwaiting count
		//Return 1 to indicate success
		//DEBUG - MAX INWAIT
		ring_buffer_health_set_max_inwaiting_256(buffer_struct);
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

unsigned char get_head_ring_buffer_256(ring_buffer_256 *buffer_pointer){
	return buffer_pointer->head;
}

void ring_buffer_256_advance(ring_buffer_256 *buffer_pointer, unsigned char count){
	unsigned char i;
	unsigned char dummy;
	for(i=0;i<count;i++){
		get_char_ring_buffer_256(buffer_pointer, &dummy);
	}
}


/************************************************************
* Function: self_test_ring_buffer(void)
*
* Description: This function is a simple test case function for debugging
* 			   purposes. This also serves as an example of proper usage.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void self_test_ring_buffer_256(void){
	//Create ring buffer #1
	ring_buffer_256 *ringbuf;
	ring_buffer_256 ringbuf_struct;
	ringbuf = &ringbuf_struct;

	//Create ring buffer #2
	ring_buffer_256 *ringbuf2;
	ring_buffer_256 ringbuf_struct2;
	ringbuf2 = &ringbuf_struct2;


	init_256_char_ring_buffer(ringbuf);
	init_256_char_ring_buffer(ringbuf2);
	unsigned char chkbuf = 0;
	unsigned char chkbuf2 = 0;
	//Test if empty, returns 1 if true
	chkbuf = ring_buffer_empty_256(ringbuf);
	//Fill buffer to 60 bytes in waiting
	unsigned char i;
	for(i=0; i<60; i++){
		put_char_ring_buffer_256(ringbuf,i);
	}
	//Fill buffer #2 to 60 bytes in waiting
	for(i=0; i<60; i++){
		put_char_ring_buffer_256(ringbuf2,i);
	}
	//Test if empty, returns 1 if true
	chkbuf = ring_buffer_empty_256(ringbuf);
	//Check reading
	for(i=0; i<60; i++){
		get_char_ring_buffer_256(ringbuf,&chkbuf);
	}
	//Test buffer for wrap around
	for(i=0; i<10; i++){
		put_char_ring_buffer_256(ringbuf,i);
	}
	//Check reading
	for(i=0; i<10; i++){
	get_char_ring_buffer_256(ringbuf,&chkbuf);
	}
	//Check for read when empty
	get_char_ring_buffer_256(ringbuf,&chkbuf);
	//Check overflow
	for(i=0; i<66; i++){
		put_char_ring_buffer_256(ringbuf,i);
	}

	//Read buffer #2 until empty
	while(!ring_buffer_empty_256(ringbuf2)){
		get_char_ring_buffer_256(ringbuf2,&chkbuf2);
	}
}


/************************************************************
* Function: unsigned char ring_buffer_health_check_overflow_bit(ring_buffer_256 *buffer_pointer)
*
* Description: This function checks the status of the circular buffer debug
*              bit flag for an overflow event.
*
* Inputs:
*              ring_buffer_256 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/

unsigned char ring_buffer_health_check_overflow_bit_256(ring_buffer_256 *buffer_pointer){
	return buffer_pointer->debug & RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: void ring_buffer_health_enable_overflow_bit(ring_buffer_256 *buffer_pointer)
*
* Description: This function checks the status of the circular buffer debug
*              bit flag for an overflow event to 0.
*
* Inputs:
*              ring_buffer_256 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/
void ring_buffer_health_enable_overflow_bit_256(ring_buffer_256 *buffer_pointer){
	buffer_pointer->debug |= RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: void ring_buffer_health_clear_overflow_bit(ring_buffer_256 *buffer_pointer)
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
void ring_buffer_health_clear_overflow_bit_256(ring_buffer_256 *buffer_pointer){
	buffer_pointer->debug &= ~RING_BUFFER_DEBUG_OVERFLOW_BIT;
}

/************************************************************
* Function: unsigned char ring_buffer_health_check_mac_inwaiting(ring_buffer_256 *buffer_pointer)
*
* Description: This function returns the value of the "max_inwait" variable in a circular buffer.
*              This value holds the maximum value of the "in_waiting" counter so that performance
*              of circular buffer utilization can be measured.
*
* Inputs:
*              ring_buffer_256 *buffer_pointer - Passed by reference pointer to circular buffer
*
* Outputs: None
*
*************************************************************/

unsigned char ring_buffer_health_check_mac_inwaiting_256(ring_buffer_256 *buffer_pointer){
	return buffer_pointer->max_inwait;
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
void ring_buffer_health_set_max_inwaiting_256(ring_buffer_256 *buffer_pointer){
	//Check if current value of in_waiting is larger than the current max hold value.
	if(buffer_pointer->inwaiting > buffer_pointer->max_inwait){
		buffer_pointer->max_inwait = buffer_pointer->inwaiting;
	}
}
