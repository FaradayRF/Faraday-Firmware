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

/** @name UART Layer 4 Service Definitions
* 	@brief Definitions that control the services of the UART layer 4 protocol. Specifically defined here
* 	are buffer and other counts that are used throughout the source file.
@{**/
#define UART_SERVICE_ELEMENT_COUNT 8
/** @}*/


/** @brief Service used to send a payload over the UART layer 4 protocol
 *
 *	A generic service used to send data over UART layer 4 protocol. This should be used as the main
 *	interface for the UART layer 4 protocol to send data.
 *
 *	@warning Adhere to maximum transmissible unit limits
 *
 */
void uart_send(unsigned char service_number, unsigned char payload_length, unsigned char *payload);


/** @brief Register an application receive FIFO
 *
 * This function creates a function pointer to an application function refering to a specific UART "service port" when used and allows the UART layer 4 to place received
 * data packets into the application FIFO without the UART layer 4 service having to include or know about the application!
 *
 *	@warning Be sure that the function pointed to in the application adheres to the defined function expected per documentation. Unreliable operation may occure if this is not followed.
 *
 *
 * //expected function example:
 * //	void command_put(unsigned char *data_pointer, unsigned char length){
 * //		put_fifo(&command_state_machine, &command_fifo_buffer, data_pointer);
 * //		__no_operation();
 * //	}
 *
 */
void uart_service_open(unsigned char service_number, void (*func_ptr)(void));


/** @brief Unregister an application receive FIFO
 *
 *	This function removes an application receive FIFO from the assigned UART "service port" as assigned in uart_service_open().
 *
 */
void uart_service_close(unsigned char service_number);


/** @brief Place data into an application receive FIFO
 *
 *	This is the main UART layer 4 service function that queries the registered applications in the function pointer array and if the UART "service port" has
 *	an assigned application the supplied data is placed into the applications FIFO.
 *
 *	@warning Be sure that the function pointed to in the application adheres to the defined function expected per documentation. Unreliable operation may occure if this is not followed.
 *
 */
void uart_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len);

#endif /* APPLICATIONS_COMMAND_UART_SERVICES_H_ */
