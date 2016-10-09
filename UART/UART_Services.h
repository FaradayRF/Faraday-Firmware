/*
 * UART_Services.h
 *
 *  Created on: Apr 2, 2016
 *      Author: Brent
 */

#ifndef APPLICATIONS_COMMAND_UART_SERVICES_H_
#define APPLICATIONS_COMMAND_UART_SERVICES_H_

void uart_send(unsigned char service_number, unsigned char payload_length, unsigned char *payload);
void uart_service_open(unsigned char service_number, void (*func_ptr)());
void uart_service_close(unsigned char service_number);
void uart_service_app_put(unsigned char service_number, unsigned char *data);
void uart_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len);

#endif /* APPLICATIONS_COMMAND_UART_SERVICES_H_ */
