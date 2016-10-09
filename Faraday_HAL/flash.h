#ifndef FARADAY_HAL_FLASH_H_
#define FARADAY_HAL_FLASH_H_

#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_A 0x1A80
#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_A 0x1A00
#define FLASH_MEM_ADR_DEVICE_DESCRIPTOR_SEGMENT_SIZE 128
#define FLASH_MEM_ADR_INFO_A 0x1980
#define FLASH_MEM_ADR_INFO_B 0x1900
#define FLASH_MEM_ADR_INFO_C 0x1880
#define FLASH_MEM_ADR_INFO_D 0x1800
#define FLASH_MEM_INFO_SEGMENT_SIZE 128
#define FLASH_MEM_MAIN_SEGMENT_SIZE 512
#define FLASH_MEM_ADR_MAIN_START 0x8000
#define FLASH_MEM_ADR_MAIN_STOP 0xFF7F
#define FLASH_MEM_ADR_MAIN_INTERRUPT_VECTOR_START 0xFF809
#define FLASH_MEM_ADR_MAIN_INTERRUPT_VECTOR_STOP 0xFFFF
#define FLASH_MEM_ADR_PERIPHERAL_START 0x0000
#define FLASH_MEM_ADR_PERIPHERAL_STOP 0x0FFF

void flash_erase_segment(long memory_loc);
void flash_write_char(unsigned int address, unsigned char byte);
void flash_write_info_c_segment_char(unsigned char offset, unsigned char byte);
void flash_write_info_c_segment_int(unsigned char offset, unsigned int integer);
void flash_write_buffer(unsigned int address, unsigned char *buff, unsigned int len);

#endif /* FARADAY_HAL_FLASH_H_ */
