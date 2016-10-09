/*
 * scratch_sram.c
 *
 *  Created on: Apr 11, 2016
 *      Author: Brent
 */


#include "scratch_sram.h"
#include "../SRAM/SRAM.h"
#include "../Ring_Buffers/FIFO_SRAM.h"

//Application FIFO Packet Buffers
volatile fifo_sram_state_machine sram_test_fifo_state_machine;
//volatile unsigned char sram_test_fifo_buffer[8*3];

void test_1(void){
	/*Faraday_SRAM_Write_Byte(0xAA, 0xAA);
	Faraday_SRAM_Write_Byte(0xAB, 0xAB);
	Faraday_SRAM_Write_Byte(0xAC, 0xAC);
	Faraday_SRAM_Write_Byte(0xAD, 0xAD);
	volatile unsigned char test_sram;
	test_sram = Faraday_SRAM_Read_Byte(0xAA);
	__no_operation();
	test_sram = Faraday_SRAM_Read_Byte(0xAB);
	__no_operation();
	test_sram = Faraday_SRAM_Read_Byte(0xAC);
	__no_operation();
	test_sram = Faraday_SRAM_Read_Byte(0xAD);
	__no_operation();
	unsigned char test_2[4];
	Faraday_SRAM_Read_Multiple_Bytes(4, 0xAA, &test_2);
	__no_operation();
	*/

	fifo_sram_init(&sram_test_fifo_state_machine,0x0000, 8, 4);

//	sram_test_fifo_state_machine.sram_start_address = 0x100;
//	sram_test_fifo_state_machine.debug = 0;
//	sram_test_fifo_state_machine.element_size = 8;
//	sram_test_fifo_state_machine.head = 0;
//	sram_test_fifo_state_machine.inwaiting = 0;
//	sram_test_fifo_state_machine.length = 0;
//	sram_test_fifo_state_machine.max_inwait = 0;
//	sram_test_fifo_state_machine.tail = 0;
//	sram_test_fifo_state_machine.buffer_size = 8*3;

	Faraday_SRAM_Write_Settings(1);
	volatile unsigned char mode_sram;
	mode_sram = Faraday_SRAM_Read_Settings();
	__no_operation();
	volatile unsigned char test_3[20], test_32[20];
	volatile unsigned char test_4[8] = {'t','e','s','t',0x0A, 0x0B, 0x0C, 0};
	//Faraday_SRAM_Write_Sequential_Bytes(4, 0x0010, &test_4);
	//Faraday_SRAM_Read_Sequential_Bytes(10, 0x0010, &test_3);

	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 1;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 2;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 3;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 4;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 5;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);

	//Faraday_SRAM_Read_Sequential_Bytes(8, 0x0100, &test_3);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	test_4[7] = 0xCD;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	test_4[7] = 0xEF;
	put_fifo_sram(&sram_test_fifo_state_machine, &test_4);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);
	get_fifo_sram(&sram_test_fifo_state_machine, &test_32);

	__no_operation();


}
