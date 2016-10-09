#ifndef SRAM_SRAM_H_
#define SRAM_SRAM_H_

typedef struct RingBuffer_SRAM{
	unsigned int data_address;
	unsigned int inwaiting;
	unsigned int length;
	unsigned int head;
	unsigned int tail;
	unsigned char debug;
	unsigned int max_inwait;
} ring_buffer_SRAM;

//Create ring buffer RX
static ring_buffer_SRAM *uart_datalink_rx_ring_buffer_sram_ptr;
static ring_buffer_SRAM uart_datalink_rx_ring_buffer_sram_struct;

void Faraday_SRAM_CS_Enable(void);
void Faraday_SRAM_CS_Disable(void);
void Faraday_SRAM_Hold_Enable(void);
void Faraday_SRAM_Hold_Disable(void);
void Faraday_SRAM_Write_Byte(unsigned char byte, unsigned int address);
unsigned char Faraday_SRAM_Read_Byte(unsigned int address);
void Faraday_SRAM_Read_Multiple_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);
void Faraday_SRAM_Write_Multiple_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);
unsigned char Faraday_SRAM_Read_Settings(void);
void Faraday_SRAM_Write_Settings(unsigned char mode);
void Faraday_SRAM_Init_Byte_Mode(void);
void Faraday_SRAM_Init_Sequential_Mode(void);
void Faraday_SRAM_Init_Page_Mode(void);
void Faraday_SRAM_Write_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);
void Faraday_SRAM_Read_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);

#endif /* SRAM_SRAM_H_ */
