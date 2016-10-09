/*
 * uart_bridge.h
 *
 *  Created on: Apr 1, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_TEST_RF_UART_BRIDGE_H_
#define APPLICATIONS_TEST_RF_UART_BRIDGE_H_

#include "../../Ring_Buffers/FIFO.h"

void uart_bridge_send(fifo_state_machine *state_machine, unsigned char *fifo_buffer, unsigned char *packet);

void uart_bridge_init(fifo_state_machine *state_machine, unsigned char bufsize, unsigned char elem_size);
unsigned char uart_bridge_receive(fifo_state_machine *state_machine, unsigned char *fifo_buffer, unsigned char *packet);
#endif /* APPLICATIONS_TEST_RF_UART_BRIDGE_H_ */
