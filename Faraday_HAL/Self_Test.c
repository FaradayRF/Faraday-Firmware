/*
 * Self_Test.c
 *
 *  Created on: Oct 4, 2015
 *      Author: Brent
 */
#include <msp430.h>
#include "Self_Test.h"
#include "../REVA_Faraday.h"
#include "../SRAM/SRAM.h"

void Faraday_External_IO_Test(void){
	//Blink LED's
	Faraday_LED_1_Enable();
	Basic_Delay(400000);
	Faraday_LED_1_Disable();
	Faraday_LED_2_Enable();
	Basic_Delay(400000);
	Faraday_LED_2_Disable();

	//Test GPIO
	//P4OUT |= GPIO_7;
	//Seems like SN1 translator has some control issues, MSP430 IO looks good but output level converter does not
	__no_operation();
	Faraday_GPIO_On(GPIO_0); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_0); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_1); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_1); //Can't put a breakpoint here but still works?
	//__no_operation();
	//__no_operation();
	Faraday_GPIO_On(GPIO_2); //Can't put a breakpoint here but still works?
	//__no_operation();
	//araday_GPIO_Off(GPIO_2); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_3); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_3); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_4); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_4); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_5); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_5); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_6); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_6); //Can't put a breakpoint here but still works?
	//__no_operation();
	Faraday_GPIO_On(GPIO_7); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Off(GPIO_7); //Can't put a breakpoint here but still works?
	//__no_operation();
	//__no_operation();
	//Faraday_GPIO_Bitmask_Cntl(GPIO_0, 1); //Can't put a breakpoint here but still works?
	//__no_operation();
	//Faraday_GPIO_Bitmask_Cntl(GPIO_0, 0); //Can't put a breakpoint here but still works?
	//__no_operation();

	//Mosfet testing
	Faraday_MOSFET_On();
	Faraday_MOSFET_Off();

	Faraday_GPS_Reset_Disable();



	//Debugger Placeholder
	__no_operation();

}

/*void Faraday_SRAM_Test(void){
	//Faraday_SRAM_Write_Byte(0xde,  0x0202);
	//Faraday_SRAM_Read_Byte(0x202);
	//Faraday_SRAM_Write_Byte(0xad, 0x0203);
	//Faraday_SRAM_Read_Byte(0x203);
	//Faraday_SRAM_Write_Byte(0xbe, 0x0204);
	//Faraday_SRAM_Read_Byte(0x204);
	//Faraday_SRAM_Write_Byte(0xef, 0x0205);
	//Faraday_SRAM_Read_Byte(0x205);
	unsigned char buf[74];
	unsigned char buf2[10]={0,1,2,3,4,253,6,7,8,251};
	//Faraday_SRAM_Read_Multiple_Bytes(6, 0x200, buf);
	//Faraday_SRAM_Write_Multiple_Bytes(10, 0, buf2);
	//Faraday_SRAM_Read_Multiple_Bytes(10, 0x0000, buf);
	unsigned char mode_rx;
	//Faraday_SRAM_Read_Settings();
	//Faraday_SRAM_Write_Settings(1);
	//Faraday_SRAM_Init_Page_Mode();
	//mode_rx = Faraday_SRAM_Read_Settings();
	//Faraday_SRAM_Write_Settings(2);
	//Faraday_SRAM_Init_Byte_Mode();
	//mode_rx = Faraday_SRAM_Read_Settings();
	//Faraday_SRAM_Write_Settings(0);
	//Faraday_SRAM_Init_Sequential_Mode();
	//mode_rx = Faraday_SRAM_Read_Settings();
	//Faraday_SRAM_Init_Sequential_Mode();
	//Faraday_SRAM_Write_Sequential_Bytes(10, 50, buf2);
	//Faraday_SRAM_Init_Byte_Mode();
	//Faraday_SRAM_Read_Sequential_Bytes(5, 50, buf);
	//Faraday_SRAM_Read_Multiple_Bytes(10, 50, buf);

	//SRAM RING

	//create_sram_ring_buffer();
	////init_sram_ring_buffer(uart_datalink_rx_ring_buffer_sram_ptr, 100, 64);
	//put_char_ring_buffer_sram(uart_datalink_rx_ring_buffer_sram_ptr, 0xAB);
	//Faraday_SRAM_Read_Multiple_Bytes(74, 90, buf);



	if(mode_rx == 0){
		__no_operation();
	}
}
*/

