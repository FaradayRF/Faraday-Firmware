#ifndef RING_BUFFERS_FIFO_H_
#define RING_BUFFERS_FIFO_H_



typedef struct FIFO_Buffer_State_Machine{
	unsigned int buffer_size;
	unsigned int element_size;
	volatile unsigned int inwaiting;
	unsigned int length;
	unsigned int head;
	unsigned int tail;
	volatile unsigned char debug;
	unsigned int max_inwait;
} volatile fifo_state_machine;




void uart_init(void);
unsigned char put_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *data, unsigned char *char_item);
unsigned char get_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *data, unsigned char *get_byte);
unsigned char fifo_empty(fifo_state_machine *buffer_struct);

#endif /* RING_BUFFERS_FIFO_H_ */
