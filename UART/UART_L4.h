#ifndef UART_UART_L4_H_
#define UART_UART_L4_H_

#define UART_L4_TX_BUFFER_SIZE 125
#define UART_L4_PACKET_LENGTH 125
#define UART_L4_PAYLOAD_LENGTH 123
typedef struct UART_L4_PACKET {
	unsigned char service_number;
	unsigned char payload_length;
	unsigned char payload[UART_L4_PAYLOAD_LENGTH]; // 44 instead of 45 due to UART transport layer limitation of 63 payload bytes... BUG! Fix!
} UART_TRANSPORT_PACKET_STRUCT;

void uart_transport_create_packet(volatile UART_TRANSPORT_PACKET_STRUCT *buffer_struct, unsigned char service_number, unsigned char payload_length, unsigned char *payload); //Change from void!
unsigned char uart_transport_tx_packet(unsigned char service_number, unsigned char payload_length, unsigned char *payload);
void uart_transport_tx_housekeep();
unsigned char uart_transport_rx_packet(unsigned char datagram_len, unsigned char *datagram);

#endif /* UART_UART_L4_H_ */
