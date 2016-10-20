/** @file FIFO_SRAM.h
 *  @brief FIFO circular buffer implementation using SPI SRAM IC
 *
 *  These functions create a FIFO circular buffer using the onboard SPI SRAM IC. The SRAM IC provides significantly
 *  more memory than the onboard RAM of the CC430. The circular buffers defined below are written as generic as
 *  possible to allow varying element lengths, counts, etc...
 *
 */


#ifndef FIFO_SRAM_H_
#define FIFO_SRAM_H_

/** @brief SPI SRAM FIFO structure
 *
 * A structure to hold all the FIFO circular buffer variables needed for operation. Variables
 * contained include buffer sizes, header, footer, etc...
 *
 * @note This structure should be used for each FIFO created. Create a structure using this definition and initialize the configuration information such as memory address and sizes.
 *
 * @warning Be careful when defining memory addresses for the FIFO element! Check with the documentation supplied to ensure you do not overlap pre-assigned memory.
 *
 * @warning Be careful with element and buffer size. The buffer size in bytes should equal a multiple of the element size and thus define an element count
 *
 */
typedef struct FIFO_SRAM_Buffer_State_Machine{
	unsigned int sram_start_address; /**< Address of the FIFO buffer's first byte. All additional bytes will sequentially follow. */
	unsigned int buffer_size; /**< Size of the buffer in bytes */
	unsigned int element_size; /**< Size of each FIFO element in bytes */
	volatile unsigned int inwaiting; /**< Number of elements waiting to be retrived in the FIFO */
	//unsigned int length; /**<  */
	unsigned int head; /**< Location of the FIFO head element byte */
	unsigned int tail; /**< Location of the FIFO tail element byte */
	volatile unsigned char debug; /**< Debug bitmask that holds information such as an overflow flag */
	unsigned int max_inwait; /**< Debug count of the maximum number of elements in wait to be retrieved in the FIFO during operation */
} fifo_sram_state_machine;



/**@brief Initialization routine for a SRAM FIFO
 *
 *	This function is used by an application/program to initialize a fifo_sram_state_machine structure with needed configuration data.
 */
void fifo_sram_init(fifo_sram_state_machine *buffer_struct, const unsigned int sram_address, const unsigned int element_size, const unsigned char element_count);


/**@brief Put a new data element into the FIFO buffer
 *
 *	This function is used to place a new item (element) into the FIFO buffer. Supplying the fifo_sram_state_machine
 *	structure variable of the respective SRAM FIFO is required.
 *
 *	@param buffer_struct A pointer to the fifo_sram_state_machine FIFO structure element containing the configuration data of the SRAM FIFO to place the data element into
 *	@param char_item A pointer to the data byte/element that will be placed into the SRAM FIFO. If the SRAM FIFO element size is larger than a byte the function will automatically retrieve the number of bytes an element is defined in the fifo_sram_state_machine supplied
 *
 * @retval The function returns a status byte indicating a successful put_fifo_sram() operation. Returns 1 if success, 0 if fail (likley an overflow).
 */
unsigned char put_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *char_item);


/**@brief Get a new data element from the FIFO buffer
 *
 *	This function is used to retrieve a waiting item (element) from the FIFO buffer. Supplying the fifo_sram_state_machine
 *	structure variable of the respective SRAM FIFO is required.
 *
 *	@param buffer_struct A pointer to the fifo_sram_state_machine FIFO structure element containing the configuration data of the SRAM FIFO to retrieve data from
 *	@param get_byte A pointer to the data byte/element that the SRAM FIFO will place the retrieved element into. If the SRAM FIFO element size is larger than a byte the function will automatically retrieve the number of bytes an element is defined in the fifo_sram_state_machine supplied
 *
 * @retval The function returns a status byte indicating a successful get_fifo_sram() operation. Returns 1 if success, 0 if fail (likley an overflow).
 */
unsigned char get_fifo_sram(fifo_sram_state_machine *buffer_struct, unsigned char *get_byte);


#endif /* FIFO_SRAM_H_ */
