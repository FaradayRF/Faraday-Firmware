#ifndef FARADAY_HAL_MISC_FUNCTIONS_H_
#define FARADAY_HAL_MISC_FUNCTIONS_H_

void Basic_Delay(unsigned long count);
unsigned char check_bitmask(unsigned char bitmask_byte, unsigned char bit_location);
void int_to_byte_array(unsigned char *byte_array, int integer);
unsigned int compute_checksum_16(int buffer_size, unsigned char *buffer);

#endif /* FARADAY_HAL_MISC_FUNCTIONS_H_ */
