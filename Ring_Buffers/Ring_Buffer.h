/*
 * Ring_Buffer.h
 *
 *  Created on: Aug 2, 2015
 *      Author: Brent
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#define CHAR_RING_BUFFER_SIZE_16 16
#define CHAR_RING_BUFFER_SIZE_64 64
#define CHAR_RING_BUFFER_SIZE_256 255

#define RING_BUFFER_DEBUG_OVERFLOW_BIT 0x01;

typedef struct RingBuffer_64{
	unsigned char data[CHAR_RING_BUFFER_SIZE_64];
	unsigned char inwaiting;
	unsigned char length;
	unsigned char head;
	unsigned char tail;
	unsigned char debug;
	unsigned char max_inwait;
} ring_buffer_64;

typedef struct RingBuffer_256{
	unsigned char data[CHAR_RING_BUFFER_SIZE_256];
	volatile unsigned char inwaiting;
	unsigned char length;
	unsigned char head;
	unsigned char tail;
	volatile unsigned char debug;
	unsigned char max_inwait;
} ring_buffer_256;


void init_64_char_ring_buffer(ring_buffer_64 *buffer_pointer);
char put_char_ring_buffer_64(ring_buffer_64 *buffer_pointer, unsigned char char_item);
char get_char_ring_buffer_64(ring_buffer_64 *buffer_pointer, unsigned char *item_got);
char ring_buffer_empty_64(ring_buffer_64 *buffer_pointer);
void ring_buffer_64_advance(ring_buffer_64 *buffer_pointer, unsigned char count);
void self_test_ring_buffer_64(void);
unsigned char get_head_ring_buffer_64(ring_buffer_64 *buffer_pointer);
unsigned char ring_buffer_health_check_overflow_bit(ring_buffer_64 *buffer_pointer);
void ring_buffer_health_enable_overflow_bit(ring_buffer_64 *buffer_pointer);
void ring_buffer_health_clear_overflow_bit(ring_buffer_64 *buffer_pointer);
unsigned char ring_buffer_health_check_mac_inwaiting(ring_buffer_64 *buffer_pointer);
void ring_buffer_health_set_max_inwaiting(ring_buffer_64 *buffer_pointer);

//256 byte
void init_256_char_ring_buffer(ring_buffer_256 *buffer_struct);
char put_char_ring_buffer_256(ring_buffer_256 *buffer_struct, unsigned char char_item);
char ring_buffer_empty_256(ring_buffer_256 *buffer_pointer);
char get_char_ring_buffer_256(ring_buffer_256 *buffer_pointer, unsigned char *item_got);
unsigned char get_head_ring_buffer_256(ring_buffer_256 *buffer_pointer);
void ring_buffer_256_advance(ring_buffer_256 *buffer_pointer, unsigned char count);
void self_test_ring_buffer_256(void);
unsigned char ring_buffer_health_check_overflow_bit_256(ring_buffer_256 *buffer_pointer);
void ring_buffer_health_enable_overflow_bit_256(ring_buffer_256 *buffer_pointer);
void ring_buffer_health_clear_overflow_bit_256(ring_buffer_256 *buffer_pointer);
unsigned char ring_buffer_health_check_mac_inwaiting_256(ring_buffer_256 *buffer_pointer);
void ring_buffer_health_set_max_inwaiting_256(ring_buffer_256 *buffer_pointer);


#endif /* RING_BUFFER_H_ */
