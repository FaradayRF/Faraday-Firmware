/** @file Misc_Functions.c
 * 	@brief Miscellaneous faraday functions
 *
 *	The functions are miscellaneous functions used to perform common functions.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "Misc_Functions.h"

unsigned char check_bitmask(unsigned char bitmask_byte, unsigned char bit_location){
	return bitmask_byte & bit_location;
}

//Bit shift an integer into a 2 byte array. Bit shifting ensures portability between platforms.
void int_to_byte_array(unsigned char *byte_array, int integer){
	byte_array[0] = (integer >>8) & 0xFF;
	byte_array[1] = (integer) & 0xFF;
}


unsigned int compute_checksum_16(int buffer_size, unsigned char *buffer){
	unsigned int i;
	unsigned int checksum_16 = 0;
	checksum_16 = 0;
	for(i=0; i<buffer_size; i++){
		checksum_16 = checksum_16 +buffer[i];
		__no_operation();
	}
	return checksum_16;
}
