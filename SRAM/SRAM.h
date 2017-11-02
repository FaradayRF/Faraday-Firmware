/** @file SRAM.h
 *  @brief SPI SRAM IC Driver
 *
 *  These functions provide basic support to use the onboard SPI SRAM IC. This module
 *  allows a large amount of RAM to be used external to the CC430.
 *
 */

#ifndef SRAM_SRAM_H_
#define SRAM_SRAM_H_





/** @brief Write a byte to an SRAM address
 *
 *	This function allows a byte to be written to a SRAM memory location.
 *
 *	@param byte The byte of data to be written to the supplied memory address
 *	@param address The 2-byte address location where the data byte will be written to
 */
void Faraday_SRAM_Write_Byte(unsigned char byte, unsigned int address);


/** @brief Read a byte from a SRAM memory location
 *
 *	This function allows a data byte to be read from a memory location on the SRAM IC. The function
 *	returns the byte that is read.
 *
 *	@param address The 2-byte address on the SRAM IC where the data byte to be retrieved is located
 *
 *	@retval rx_byte The function returns the retrieved data byte from the SRAM memory location.
 *
 */
//unsigned char Faraday_SRAM_Read_Byte(unsigned int address);


/** @brief Retrieve SRAM IC settings
 *
 *	This function retrieves the current SRAM device settings register byte and returns it.
 *
 *	@retval The function returns the retrieved SRAM IC settings register byte
 */
unsigned char Faraday_SRAM_Read_Settings(void);


/** @brief Update the SRAM IC settings register
 *
 *  This function updates the SRAM IC settings register with the supplied byte. This is mainly used
 *  to place the SRAM device into different operation modes.
 *
 *  -  0 = Byte Mode
 *  -  1 = Sequential Mode
 *  -  2 = Page Mode
 *  -  4 = Reserved (Test?)
 *
 *  @param mode A coded byte that indicates what SRAM IC operation mode to enter.
 *
 *
 */
void Faraday_SRAM_Write_Settings(unsigned char mode);


/** @brief A shortcut function to initiate BYTE mode of the SRAM IC
 *
 * A shortcut function to initiate BYTE mode of the SRAM IC.
 *
 *
 */
void Faraday_SRAM_Init_Byte_Mode(void);


/** @brief A shortcut function to initiate SEQUENTIAL mode of the SRAM IC
 *
 * A shortcut function to initiate SEQUENTIAL mode of the SRAM IC.
 *
 */
void Faraday_SRAM_Init_Sequential_Mode(void);


/** @brief A shortcut function to initiate PAGE mode of the SRAM IC
 *
 * A shortcut function to initiate PAGE mode of the SRAM IC.
 *
 */
void Faraday_SRAM_Init_Page_Mode(void);


/** @brief Write multiple bytes to SRAM while operating in SEQUENTIAL mode in a single function call
 *
 *  Write multiple bytes to SRAM while operating in SEQUENTIAL mode in a single function call. The function
 *  requires a memory address which indicates where to place the first byte, all bytes will follow sequentially.
 *
 *  @param count The length in bytes of the data to be written to SRAM memory
 *  @param sram_address The 2-byte SRAM address where the first byte is to be written
 *  @param buffer_address A pointer to the byte/bytes where the data is to be read from sequentially and placed into SRAM memory
 *
 */
void Faraday_SRAM_Write_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);


/** @brief Read multiple bytes from SRAM while operating in SEQUENTIAL mode in a single function call
 *
 *  Read multiple bytes from SRAM while operating in SEQUENTIAL mode in a single function call. The function
 *  requires a memory address which indicates where to read the first byte from, all bytes will follow sequentially.
 *
 *  @param count The length in bytes of the data to be read from SRAM memory
 *  @param sram_address The 2-byte SRAM address where the first byte is to be read from
 *  @param buffer_address A pointer to the byte/bytes on the CC430 where retrieved data bytes is to be written to sequentially
 *
 */
void Faraday_SRAM_Read_Sequential_Bytes(unsigned int count, unsigned int sram_address, unsigned char *buffer_address);

void Faraday_SRAM_Send_Address(unsigned int sram_address);

void Faraday_SRAM_Toggle_CS(void);

#endif /* SRAM_SRAM_H_ */
