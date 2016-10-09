/*
 * FIFO_SRAM.h
 *
 *  Created on: Mar 8, 2016
 *      Author: Brent
 */

#ifndef FIFO_SRAM_H_
#define FIFO_SRAM_H_

typedef struct FIFO_SRAM_Buffer_State_Machine{
	unsigned int sram_start_address;
	unsigned int buffer_size;
	unsigned int element_size;
	volatile unsigned int inwaiting;
	unsigned int length;
	unsigned int head;
	unsigned int tail;
	volatile unsigned char debug;
	unsigned int max_inwait;
} fifo_sram_state_machine;




void fifo_sram_init(fifo_sram_state_machine *buffer_struct, const unsigned int sram_address, const unsigned int element_size, const unsigned char element_count);
unsigned char put_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *char_item);
unsigned char get_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *get_byte);
//unsigned char fifo_empty_sram(fifo_sram_state_machine *buffer_struct);
//char put_char_ring_buffer(fifo_state_machine *buffer_struct, unsigned char char_item);

#endif /* FIFO_SRAM_H_ */
