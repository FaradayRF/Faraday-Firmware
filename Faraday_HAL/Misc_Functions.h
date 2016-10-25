/** @file Misc_Functions.h
 * 	@brief Miscellaneous faraday functions
 *
 *	The functions are miscellaneous functions used to perform common functions.
 *
 */


#ifndef FARADAY_HAL_MISC_FUNCTIONS_H_
#define FARADAY_HAL_MISC_FUNCTIONS_H_


/**@brief Check a bitmask for current bit state
 *
 *	This function accepts a bitmask byte and a bit location in the byte and returns a value
 *	based on whether the bit in the bitmask is HIGH.
 *
 *	@param bitmask_byte The bitmask byte to check
 *	@param bit_location The bit location in the bitmask to check
 *
 *	@retval Returns the result of (bitmask_byte & bit_location)
 *
 */
unsigned char check_bitmask(unsigned char bitmask_byte, unsigned char bit_location);


/**@brief Integer to byte array function
 *
 *	This function accepts an integer and shifts the integer into a byte array. This function is useful
 *	for converting integers such as ADC values into 2-byte unsigned char array values.
 *
 *	@param byte_array A pointer to the byte array that the integer supplied will be shifted into (expect size of 2 bytes)
 *	@param integer The integer to be shifted in to the byte array
 *
 */
void int_to_byte_array(unsigned char *byte_array, int integer);


/**@brief Compute 16 bit checksum
 *
 *	This function computes the supplied byte(s) 16 bit checksum value. This is used around Faraday for error detection.
 *
 *	@param buffer_size Size in bytes of the byte/bytearray that will be computed
 *	@param buffer A pointer to the data (byte/bytearray) that the 16 bit checksum will be computed from
 *
 *	@retval Returns the 16 bit checksum as an integer
 *
 */
unsigned int compute_checksum_16(int buffer_size, unsigned char *buffer);

#endif /* FARADAY_HAL_MISC_FUNCTIONS_H_ */
