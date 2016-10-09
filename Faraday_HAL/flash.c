#include <msp430.h>
#include "flash.h"
#include "string.h"

/*
 * NOTES:
 * Information segments are 128 bytes long
 * Main memory segments are 512 bytes long
 *
 * Locations:
 * Information segments:
 * A-
 * B-
 * C-
 * D-
 *
 * Main Memory:
 * Note - Program code lives here...

 */




/************************************************************
* Function: flash_erase_info_seg(long memory_loc)
*
* Description: This function is intended to erase a memory locations
* segment in FLASH, specifically the info segments.
* NOTE: Interrupts must be disabled when writing to FLASH. If
* they are not and an interrupt occurs the interrupt will not
* return correctly and will lock the CC430 until it is power cycled.
*
* Inputs: long memory_loc
*
* Outputs: None
*
*************************************************************/
void flash_erase_segment(long memory_loc){
	//INFO segments are defined as 128 Bytes
	unsigned int i;
	char * Flash_ptr;                         // Initialize Flash pointer
	Flash_ptr = (char *) memory_loc;
	__disable_interrupt();                    // 5xx Workaround: Disable global
											// interrupt while erasing. Re-Enable
											// GIE if needed
	FCTL3 = FWKEY;                            // Clear Lock bit
	FCTL1 = FWKEY+ERASE;                      // Set Erase bit
	*Flash_ptr = 0;                           // Dummy write to erase Flash seg
	FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

	//Re-initialize the interrupts
	__bis_SR_register(GIE);       //Interrupts enabled BUG: This should be a higher level call otherwise it'll be a pain to update to LPM
	}

void flash_write_char(unsigned int address, unsigned char byte){
	unsigned char * Flash_ptr;                         // Initialize Flash pointer
	Flash_ptr = (unsigned char *) address;

	__disable_interrupt();                    // 5xx Workaround: Disable global
											// interrupt while erasing. Re-Enable
											// GIE if needed
	FCTL3 = FWKEY;                            // Clear Lock bit
	FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

	*Flash_ptr = byte;

	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

	//Re-initialize the interrupts
	__bis_SR_register(GIE);       //Interrupts enabled BUG: This should be a higher level call otherwise it'll be a pain to update to LPM
}


void flash_write_info_c_segment_char(unsigned char offset, unsigned char byte){
	if(offset<=128){
		unsigned char * Flash_ptr;                         // Initialize Flash pointer
		Flash_ptr = (unsigned char *) FLASH_MEM_ADR_INFO_C;
		unsigned char buffer[128];

		memcpy(&buffer, Flash_ptr, 128);

		buffer[offset] = byte;

		//Erase flash info C to prepare for buffer write
		flash_erase_segment(FLASH_MEM_ADR_INFO_C);

		__disable_interrupt();                    // 5xx Workaround: Disable global
												// interrupt while erasing. Re-Enable
												// GIE if needed
		FCTL3 = FWKEY;                            // Clear Lock bit
		FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

		//*Flash_ptr = byte;
		flash_write_buffer(FLASH_MEM_ADR_INFO_C, buffer, 128);

		FCTL1 = FWKEY;                            // Clear WRT bit
		FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

		//Re-initialize the interrupts
		__bis_SR_register(GIE);       //Interrupts enabled BUG: This should be a higher level call otherwise it'll be a pain to update to LPM
	}
	else{
		//Invalid offset, ignore
	}
}

void flash_write_info_c_segment_int(unsigned char offset, unsigned int integer){
	if(offset<=128){
		unsigned char * Flash_ptr;                         // Initialize Flash pointer
		Flash_ptr = (unsigned char *) FLASH_MEM_ADR_INFO_C;
		unsigned char buffer[128];

		//Little Endian! (This may differ from other Faraday implementation but should be moved to standard)
		unsigned char int_buf[2];
		int_buf[1] = integer>>8;
		int_buf[0] = integer;

		memcpy(&buffer, Flash_ptr, 128);

		buffer[offset] = int_buf[0]; //Little Endian, LSB first
		buffer[offset+1] = int_buf[1];

		//Erase flash info C to prepare for buffer write
		flash_erase_segment(FLASH_MEM_ADR_INFO_C);

		__disable_interrupt();                    // 5xx Workaround: Disable global
												// interrupt while erasing. Re-Enable
												// GIE if needed
		FCTL3 = FWKEY;                            // Clear Lock bit
		FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

		//*Flash_ptr = byte;
		flash_write_buffer(FLASH_MEM_ADR_INFO_C, buffer, 128);

		FCTL1 = FWKEY;                            // Clear WRT bit
		FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

		//Re-initialize the interrupts
		__bis_SR_register(GIE);       //Interrupts enabled BUG: This should be a higher level call otherwise it'll be a pain to update to LPM
	}
	else{
		//Invalid offset, ignore
	}
}

void flash_write_buffer(unsigned int address, unsigned char *buff, unsigned int len){
	unsigned char * Flash_ptr;                         // Initialize Flash pointer
	unsigned int i;
	Flash_ptr = (unsigned char *) address;

	__disable_interrupt();                    // 5xx Workaround: Disable global
											// interrupt while erasing. Re-Enable
											// GIE if needed
	FCTL3 = FWKEY;                            // Clear Lock bit
	FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

	for(i=0; i<len; i++){
		*Flash_ptr = buff[i];
		Flash_ptr++;
	}



	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

	//Re-initialize the interrupts
	__bis_SR_register(GIE);       //Interrupts enabled BUG: This should be a higher level call otherwise it'll be a pain to update to LPM
}
