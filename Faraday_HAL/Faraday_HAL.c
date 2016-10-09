#include <msp430.h>
#include "../REVA_Faraday.h"
#include "Faraday_HAL.h"
#include "../HAL/RF1A.h"

/************************************************************
*
* UART Hardware Abstraction
*
*************************************************************/
/************************************************************
* Function: void hal_uart_set_uctxifg(void)
*
* Description: This function manually sets teh UCA0IFG transmitter "UCTXIFG" flag.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void hal_uart_set_uctxifg(void){
	UCA0IFG |= UCTXIFG; //Manually set the uart transmit buffer ready for next byte flag
}

/************************************************************
* Function: unsigned char hal_uart_return_tx(void)
*
* Description: This function returns the current value of the uart transmitter byte buffer.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
unsigned char hal_uart_return_tx(void){
	return UCA0TXBUF;
}

/************************************************************
* Function: Faraday_LED_bitmask_enable(unsigned char ledmask)
*
* Description: This function accepts a bitmasked unsigned char byte and parses it to determine if the onboard LED
* 			   should be ON/OFF. Bitmasking is used so that a single command can perform multiple actions. Actions
* 			   are split between ON and OFF so a single command can only turn items ON and another must be issued
* 			   to turn devices OFF. This function enables LED's
*
* Inputs: unsigned char ledmask
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_bitmask_enable(unsigned char ledmask){
	if(ledmask & BIT0){
		P3OUT |= LED_1;
	}
	if(ledmask & BIT1){
		P3OUT |= LED_2;
	}
}

/************************************************************
* Function: Faraday_LED_bitmask_disable(unsigned char ledmask)
*
* Description: This function accepts a bitmasked unsigned char byte and parses it to determine if the onboard LED
* 			   should be ON/OFF. Bitmasking is used so that a single command can perform multiple actions. This
* 			   function disables LED's.
*
* Inputs: unsigned char ledmask
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_bitmask_disable(unsigned char ledmask){
	if(ledmask & BIT0){
		P3OUT &= ~LED_1;
	}
	if(ledmask & BIT1){
		P3OUT &= ~LED_2;
	}
}

/************************************************************
* Function: Faraday_LED_1_Enable(void)
*
* Description: This function is a direct LED_1 enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_1_Enable(void){
	P3OUT |= LED_1;
}

/************************************************************
* Function: Faraday_LED_1_Disable(void)
*
* Description: This function is a direct LED_1 disable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_1_Disable(void){
	P3OUT &= ~LED_1;
}

/************************************************************
* Function: Faraday_LED_2_Enable(void)
*
* Description: This function is a direct LED_2 enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_2_Enable(void){
	P3OUT |= LED_2;
}

/************************************************************
* Function: Faraday_LED_2_Disable(void)
*
* Description: This function is a direct LED_2 disable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_LED_2_Disable(void){
	P3OUT &= ~LED_2;
}

/************************************************************
* Function: Faraday_GPIO_On(unsigned char gpio)
*
* Description: This function is a a basic GPIO (port 4) bitmasked and direct enable function. This should only be used for debugging
* 			   as proper methods should apply bitmask to a global variable so that current status can be easily read.
*
* Inputs: gpio - a bitmask byte where a single bit represents a GPIO pin.
*
* Outputs: None
*
*************************************************************/
void Faraday_GPIO_On(unsigned char gpio){
	P4OUT |= gpio;
}

/************************************************************
* Function: Faraday_GPIO_Off(unsigned char gpio)
*
* Description: This function is a a basic GPIO (port 4) bitmasked and direct disable function. This should only be used for debugging
* 			   as proper methods should apply bitmask to a global variable so that current status can be easily read.
*
* Inputs: gpio - a bitmask byte where a single bit represents a GPIO pin.
*
* Outputs: None
*
*************************************************************/
void Faraday_GPIO_Off(unsigned char gpio){
	P4OUT &= ~gpio;
}

/************************************************************
* Function: Faraday_GPIO_Bitmask_Cntl(unsigned char bitmask, unsigned char cntl)
*
* Description: This function is a direct LED_1 enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: unsigned char bitmask - Bitmask byte where each bit represents a port pin for GPIO (port 4)
* 		  unsigned char cntl - Control byte that determines if the action with Enable/Disable GPIO from the bitmask
*
* Outputs: None
*
*************************************************************/
//SOMETHING IS BUGGY BELOW
void Faraday_GPIO_Bitmask_Cntl(unsigned char bitmask, unsigned char cntl){
	//Bitmask for all port IO
	//cntl char to perform ON (1) or OFF (0)
	if(cntl == 0x01){
		P4OUT &= ~bitmask;
	}
	else if(cntl == 0x01){
		P4OUT |= bitmask;
	}
	else{
		//Error
		__no_operation();
	}
}

/************************************************************
* Function: Faraday_MOSFET_On(void)
*
* Description: This function is a direct Faraday MOSFET enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_MOSFET_On(void){
	P5OUT |= MOSFET_CNTL;
}

/************************************************************
* Function: Faraday_MOSFET_Off(void)
*
* Description: This function is a direct Faraday MOSFET disable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_MOSFET_Off(void){
	P5OUT &= ~MOSFET_CNTL;
}

/************************************************************
* Function: Faraday_GPS_Reset_Enable(void)
*
* Description: This function is a direct Faraday GPS RESET enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_GPS_Reset_Enable(void){
	//LOW = RESET Enabled (OFF)
	P3OUT &= ~GPS_RESET;
}

/************************************************************
* Function: Faraday_GPS_Reset_Disable(void)
*
* Description: This function is a direct Faraday GPS RESET disable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_GPS_Reset_Disable(void){
	//HIGH = RESET Disabled (ON)
	P3OUT |= GPS_RESET;
}

/************************************************************
* Function: Faraday_GPS_Standby_Enable(void)
*
* Description: This function is a direct Faraday GPS STANDBY enable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_GPS_Standby_Enable(void){
	//LOW = Stndby Enabled (OFF)
	P3OUT &= ~GPS_STANDBY;
}

/************************************************************
* Function: Faraday_GPS_Stanby_Disable(void)
*
* Description: This function is a direct Faraday GPS STANDBY disable. This should only be used for DEBUG and be replaced with appropriate GPIO
* 			   bitmasking function techniques.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void Faraday_GPS_Standby_Disable(void){
	//HIGH = Stanby Disabled (ON)
	P3OUT |= GPS_STANDBY;
}



void Faraday_PA_Enable(void){
	//LOW = Stndby Enabled (OFF)
	P3OUT |= PA_ENABLE;
}


void Faraday_PA_Disable(void){
	//HIGH = Stanby Disabled (ON)
	P3OUT &= ~PA_ENABLE;
}

void Faraday_LNA_Enable(void){
	//LOW = Stndby Enabled (OFF)
	P3OUT |= LNA_ENABLE;
}


void Faraday_LNA_Disable(void){
	//HIGH = Stanby Disabled (ON)
	P3OUT &= ~LNA_ENABLE;
}

void Faraday_HGM_Enable(void){
	//LOW = Stndby Enabled (OFF)
	P3OUT |= HGM_SELECT;
}


void Faraday_HGM_Disable(void){
	//HIGH = Stanby Disabled (ON)
	P3OUT &= ~HGM_SELECT;
}

void Faraday_LED_1_Toggle(void){
	P3OUT ^= LED_1;
}

/************************************************************
* Function: Faraday_RF_PWR_Change()
*
* Description: This function allows the updating of the CC430 PA Table setting to update the RF output power. Note that this changes the setting in the default PA
* Table pointer and is not a function that changes the table pointer (for amplitude shift keying).
*
* Inputs: ucharPowerSetting
*
* Outputs: None
*
*************************************************************/
void Faraday_RF_PWR_Change(unsigned ucharPowerSetting){
	//Update PATable using RF1A HAL library function
	WriteSinglePATable(ucharPowerSetting);
}
