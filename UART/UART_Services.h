/** @file UART_Services.h
 *  @brief Faraday UART Network Stack - Layer 4 Services
 *
 *  This header file provides the layer 4 (TRANSPORT) layer protocol services. Providing service functions
 *  allows the protocol to be interacted with in an abstracted method that better suites layer isolation
 *  and layer modularity.
 *
 */

#ifndef APPLICATIONS_COMMAND_UART_SERVICES_H_
#define APPLICATIONS_COMMAND_UART_SERVICES_H_

/** @name Automatic Cutdown Event State Machine Definitions
* 	@brief Definitions for the state machine based function that performs automatic timed based cutdown of a HAB used the Faraday MOSFET as control.
@{**/
#define UART_SERVICE_ELEMENT_COUNT 8
/** @}*/

void uart_send(unsigned char service_number, unsigned char payload_length, unsigned char *payload);
void uart_service_open(unsigned char service_number, void (*func_ptr)());
void uart_service_close(unsigned char service_number);
void uart_service_app_put(unsigned char service_number, unsigned char *data);
void uart_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len);

#endif /* APPLICATIONS_COMMAND_UART_SERVICES_H_ */
