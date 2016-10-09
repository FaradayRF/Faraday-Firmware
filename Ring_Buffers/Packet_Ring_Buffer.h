#ifndef RING_BUFFERS_PACKET_RING_BUFFER_H_
#define RING_BUFFERS_PACKET_RING_BUFFER_H_

#define CHAR_PACKET_RING_BUFFER_PACKET_SIZE_64 64
#define CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64 5

typedef struct Packet_RingBuffer_64{
	unsigned char data[CHAR_PACKET_RING_BUFFER_PACKET_SIZE_64*CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64];
	unsigned char inwaiting;
	unsigned char length_pkt[CHAR_PACKET_RING_BUFFER_BUFFER_SIZE_64];
	unsigned char head_pkt;
	unsigned char tail_pkt;
	unsigned char debug;
	unsigned char max_inwait;
} packet_ring_buffer_64;

void init_packet_buffers(void);
void init_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_struct);
char put_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_struct, unsigned char *packet_data_pointer, unsigned char length);
unsigned char get_char_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer, unsigned char *packet_got_ptr);
unsigned char isempty_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer);
void update_max_inwaiting_packet_ring_buffer_64(packet_ring_buffer_64 *buffer_pointer);

#endif /* RING_BUFFERS_PACKET_RING_BUFFER_H_ */
