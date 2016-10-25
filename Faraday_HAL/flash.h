/** @file flash.h
 * 	@brief CC430 flash memory functionallity
 *
 * 	These functions provide access to the internal CC430 flash memory modification.
 *
 * 	Memory Segments:
 * 	- Information segments are 128 bytes long
 *  - Main memory segments are 512 bytes long
 *
 */

#ifndef FARADAY_HAL_FLASH_H_
#define FARADAY_HAL_FLASH_H_


/** @name CC430 Flash Memory Definitions
* 	@brief Definitions for the CC430 Flash memory routines
@{**/
#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_A 0x1A80 /**< Flash memory device descriptor address */
//#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_A 0x1A00
#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_SEGMENT_SIZE 128 /**< Flash memory device descriptor segment size */
#define FLASH_MEM_ADR_INFO_A 0x1980 /**< Flash memory Information segment A address */
#define FLASH_MEM_ADR_INFO_B 0x1900 /**< Flash memory Information segment B address */
#define FLASH_MEM_ADR_INFO_C 0x1880 /**< Flash memory Information segment C address */
#define FLASH_MEM_ADR_INFO_D 0x1800 /**< Flash memory Information segment D address */
#define FLASH_MEM_INFO_SEGMENT_SIZE 128 /**< Size in bytes of Information segments */
#define FLASH_MEM_MAIN_SEGMENT_SIZE 512 /**< Size in bytes of main flash memory segments */
#define FLASH_MEM_ADR_MAIN_START 0x8000 /**< Memory address of the start of the main flash memory */
#define FLASH_MEM_ADR_MAIN_STOP 0xFF7F /**< Memory address of the end of the main flash memory */
#define FLASH_MEM_ADR_MAIN_INTERRUPT_VECTOR_START 0xFF809 /**< Memory address of the start of the interrupt vector tables */
#define FLASH_MEM_ADR_MAIN_INTERRUPT_VECTOR_STOP 0xFFFF /**< Memory address of the end of the interrupt vector tables */
#define FLASH_MEM_ADR_PERIPHERAL_START 0x0000 /**< Memory address of the start of the peripheral registers */
#define FLASH_MEM_ADR_PERIPHERAL_STOP 0x0FFF /**< Memory address of the end of the peripheral registers */
/** @}*/


/**@brief Erase Flash memory segment
 *
 * Description: This function is intended to erase a memory locations
 * segment in FLASH, specifically the info segments.
 *
 * @warning Interrupts must be disabled when writing to FLASH. If they are not and an interrupt occurs the interrupt will not return correctly and will lock the CC430 until it is power cycled.
 *
 * @warning This function will erase the entire segment that the memory location is located within!
 *
 * @param memory_loc Memory address location to erase.
 *
 */
void flash_erase_segment(long memory_loc);


/**@brief Write byte into a Flash memory location
 *
 *	This function allows a single byte to be written into a memory location in the CC430 Flash.
 *
 *	@warning The location being written too must be erased prior.
 *
 */
void flash_write_char(unsigned int address, unsigned char byte);


/**@brief Write a byte to the Info C segment memory location
 *
 * This is a quick abstraction that allows quick access to flash memory segment C. The intended byte
 * to be written along with an offset from the start of Flash memory segment C is to be provided.
 *
 * @param offset Offset in bytes from the beginning of the Flash memory information segment C
 * @param byte The byte to be written to the Flash memory location addressed
 *
 */
void flash_write_info_c_segment_char(unsigned char offset, unsigned char byte);


/**@brief Write an integer to the Info C segment memory location
 *
 * This is a quick abstraction that allows quick access to flash memory segment C. The intended integer
 * to be written along with an offset from the start of Flash memory segment C is to be provided.
 *
 * @param offset Offset in bytes from the beginning of the Flash memory information segment C
 * @param integer The integer to be written to the Flash memory location addressed
 *
 */
void flash_write_info_c_segment_int(unsigned char offset, unsigned int integer);


/**@brief Write multiple bytes into Flash memory
 *
 *	This function allows the writing of multiple bytes in a single command to be written
 *	to the Flash memory location provided.
 *
 *	@param address The integer address of the flash memory location that the first byte of the multiple bytes will be written too
 *	@param buff A pointer to the bytearray location (first byte) to be written into the Flash memory location provided
 *	@param len The length of the byte array to be written to Flash memory in bytes
 *
 */
void flash_write_buffer(unsigned int address, unsigned char *buff, unsigned int len);

#endif /* FARADAY_HAL_FLASH_H_ */
