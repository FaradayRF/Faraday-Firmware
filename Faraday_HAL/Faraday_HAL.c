/** @file Faraday_HAL.c
 *  @brief Hardware abstraction for Faraday
 *
 *  These functions provide basic hardware abstraction for Faraday
 *  and it's onboard peripheral devices.
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "Faraday_HAL.h"

/* hardware abstraction */
#include "../REVA_Faraday.h"

/* cc430 radio hardware abstraction */
#include "../HAL/RF1A.h"


void hal_uart_set_uctxifg(void){
	UCA0IFG |= UCTXIFG; //Manually set the uart transmit buffer ready for next byte flag
}


void Faraday_MOSFET_On(void){
	P5OUT |= MOSFET_CNTL;
}


void Faraday_MOSFET_Off(void){
	P5OUT &= ~MOSFET_CNTL;
}


void Faraday_GPS_Reset_Enable(void){
	//LOW = RESET Enabled (OFF)
	P3OUT &= ~GPS_RESET;
}


void Faraday_GPS_Reset_Disable(void){
	//HIGH = RESET Disabled (ON)
	P3OUT |= GPS_RESET;
}


void Faraday_GPS_Standby_Enable(void){
	//LOW = Stndby Enabled (OFF)
	P3OUT &= ~GPS_STANDBY;
}


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
