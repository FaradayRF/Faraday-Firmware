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

	//GPS Test
	Faraday_GPS_Reset_Disable();

	//Debugger Placeholder
	__no_operation();

}


