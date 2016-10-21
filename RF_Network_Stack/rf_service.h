/** @file rf_service.h
 * 	@brief Services for the layer 4 RF experimental protocol
 *
 * 	These functions provide services for the RF layer 4 (transport) protocol.
 *
 *
 */


#ifndef RF_NETWORK_STACK_RF_SERVICE_H_
#define RF_NETWORK_STACK_RF_SERVICE_H_

/** @name Automatic Cutdown Event State Machine Definitions
* 	@brief Definitions for the state machine based function that performs automatic timed based cutdown of a HAB used the Faraday MOSFET as control.
@{**/
#define RF_SERVICE_ELEMENT_COUNT 8 /**< The number of allowable service ports. This determines the number of function pointers in the function pointer array*/
/** @}*/


/** @brief Register an application receive FIFO
 *
 * This function creates a function pointer to an application function refering to a specific RF "service port" when used and allows the RF layer 4 recevie protocol to place received
 * data packets into the application FIFO without the RF layer 4 service having to include or know about the application!
 *
 *	@warning Be sure that the function pointed to in the application adheres to the defined function expected per documentation. Unreliable operation may occure if this is not followed.
 *
 *	@param service_number The service port number of the layer 4 protocol packet
 *	@param (*func_ptr)(void) A function pointer to the external program's FIFO "Put()" function
 *	@param broadcast_rx_allowed 1 if this port and program registration is allowed to receive MAC layer packets addressed to broadcast, 0 if not allowed.
 *
 *
 * //expected function example:
 * //	void command_put(unsigned char *data_pointer, unsigned char length){
 * //		put_fifo(&command_state_machine, &command_fifo_buffer, data_pointer);
 * //		__no_operation();
 * //	}
 *
 */
void rf_rx_service_open(unsigned char service_number, void (*func_ptr)(void), unsigned char broadcast_rx_allowed);


/** @brief Unregister an application receive FIFO
 *
 *	This function removes an application receive FIFO from the assigned RF "service port" as assigned in rf_rx_service_open().
 *
 *	@param service_number The service port number of the layer 4 protocol packet
 *
 */
void rf_rx_service_close(unsigned char service_number);


/** @brief Place data into an application receive FIFO
 *
 *	This is the main RF layer 4 service function that queries the registered applications in the function pointer array and if the RF "service port" has
 *	an assigned application the supplied data is placed into the applications FIFO.
 *
 *	@param service_number The service port number of the layer 4 protocol packet
 *	@param data A pointer to the data packet to be placed into the appropriate program FIFO
 *	@param payload_len The length of the data that is to be placed into the appropriate program FIFO
 *
 *	@warning Be sure that the function pointed to in the application adheres to the defined function expected per documentation. Unreliable operation may occure if this is not followed.
 *
 */
void rf_rx_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len);


/** @brief Register a service port to allow a "broadcast" address packet (at MAC layer) to be parsed
 *
 *	Broadcast packets are addressed to all device in the local area. This functionality allows the protocol to allow/disallow
 *	broadcast addressed packets from executing on the local device since this may be dangerous. Example: A command sent with
 *	the broadcast address that could execute on ALL devices in the area instead of a specifically address device.
 *
 *@param service_number The service port number of the layer 4 protocol packet
 *
 *	@todo Placing this functionallity at the layer 4 service is convientient but breaks the OSI layer isolation. This should probably get moved to layer 2 where MAC is handled.
 *
 */
void rf_rx_service_broadcast_rule_open(service_number);


/** @brief Check if a service port is allows to receive broadcast addressed packets (at MAC layer)
 *
 *	This is a simple function that returns a value indicating the service port is or is not allowed to parse
 *	a broadcast (at MAC layer) packet. Broadcast is an address that all units will receive and parse as if it
 *	was address to the local device unless otherwise programed. This allows programs like broadcast telemetry
 *	and directed commands to exist together.
 *
 *	@param service_number The service port number of the layer 4 protocol packet
 *
 *	@retval Returns rx_service_port_broadcast_rule_array[service_number] which is 1 if allowed to parse a broadcast address MAC layer packet, 0 if not.
 *
 *	@todo Placing this functionallity at the layer 4 service is convientient but breaks the OSI layer isolation. This should probably get moved to layer 2 where MAC is handled.
 *
 */
unsigned char rf_rx_service_broadcast_rule_get(service_number);

#endif /* RF_NETWORK_STACK_RF_SERVICE_H_ */
