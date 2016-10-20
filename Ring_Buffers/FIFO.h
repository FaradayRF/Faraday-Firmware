/** @file FIFO.h
 *  @brief FIFO circular buffer implementation using CC430 RAM
 *
 *  These functions create a FIFO circular buffer using the onboard CC430 RAM. The circular buffers defined below are written as generic as
 *  possible to allow varying element lengths, counts, etc...
 *
 */


#ifndef RING_BUFFERS_FIFO_H_
#define RING_BUFFERS_FIFO_H_



typedef struct FIFO_Buffer_State_Machine{
	unsigned int buffer_size; /**< Size of the buffer in bytes */
	unsigned int element_size; /**< Size of each FIFO element in bytes */
	volatile unsigned int inwaiting; /**< Number of elements waiting to be retrived in the FIFO */
	//unsigned int length;
	unsigned int head; /**< Location of the FIFO head element byte */
	unsigned int tail; /**< Location of the FIFO tail element byte */
	volatile unsigned char debug; /**< Debug bitmask that holds information such as an overflow flag */
	unsigned int max_inwait; /**< Debug count of the maximum number of elements in wait to be retrieved in the FIFO during operation */
} volatile fifo_state_machine;

///**@brief Initialization routine for a CC430 RAM FIFO
// *
// *	This function is used by an application/program to initialize a fifo_state_machine structure with needed configuration data
// */
//void uart_init(void);


/**@brief Put a new data element into the CC430 RAM FIFO buffer
 *
 *	This function is used to place a new item (element) into the CC430 RAM FIFO buffer. Supplying the fifo_state_machine
 *	structure variable of the respective FIFO is required.
 *
 *	@param buffer_struct A pointer to the fifo_sram_state_machine FIFO structure element containing the configuration data of the SRAM FIFO to place the data byte into
 *	@param buffer A pointer to the buffer byte array used by the RAM CC430 FIFO
 *	@param char_item A pointer to the data byte/element that will be placed into the CC430 RAM FIFO.
 *
 * @retval The function returns a status byte indicating a successful put_fifo() operation. Returns 1 if success, 0 if fail (likley an overflow).
 */
unsigned char put_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *buffer, unsigned char *char_item);


/**@brief Get a new data element from the CC430 RAM FIFO buffer
 *
 *	This function is used to retrieve a new item (element) from the CC430 RAM FIFO buffer. Supplying the fifo_state_machine
 *	structure variable of the respective FIFO is required.
 *
 *	@param buffer_struct A pointer to the fifo_sram_state_machine FIFO structure element containing the configuration data of the SRAM FIFO to retrieve the FIFO item from
 *	@param buffer A pointer to the buffer byte array used by the CC430 RAM FIFO
 *	@param char_item A pointer to the data byte/element that will be placed into the CC430 RAM FIFO.
 *
 * @retval The function returns a status byte indicating a successful get_fifo() operation. Returns 1 if success, 0 if fail (likley an overflow).
 */
unsigned char get_fifo(fifo_state_machine *buffer_struct, volatile unsigned char *buffer, unsigned char *char_item);


/**@brief Check if FIFO is empty
 *
 *	This function is a simple method to check if the FIFO contains a waiting item to be retrieved.
 *
 *	@param buffer_struct A pointer to the fifo_sram_state_machine FIFO structure element containing the configuration data of the SRAM FIFO to check for a waiting FIFO item to retrieve
 *
 * @retval The function returns a status byte indicating if the CC430 RAM FIFO supplied contains a waiting item to retrieve. Returns 1 if empty, 0 if item(s) waiting in FIFO.
 */
unsigned char fifo_empty(fifo_state_machine *buffer_struct);

#endif /* RING_BUFFERS_FIFO_H_ */
