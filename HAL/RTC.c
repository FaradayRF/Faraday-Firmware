/** @file RTC.c
 *  @brief CC430 real time clock hardware abstraction
 *
 *  These functions provide CC430 real time clock hardware abstraction
 *  functionality.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "RTC.h"

/* gps include */
#include "GPS.h"

/************************************************************
* Function: Enable RTCA Calender Alarm
*
* Description: Enables the RTCCTL0 RTC_A calender alarm interrupt enable bit
*
* Inputs: Nothing
*
* Outputs: nothing
*
*************************************************************/
void Enable_RTCA_Calender_Alarm(void){
	RTCCTL0 |= RTCAIE;		// Enable RTCA alarm
}

/************************************************************
* Function: Disable RTCA Calender Alarm
*
* Description: Disables the RTCCTL0 RTC_A calender alarm interrupt enable bit
*
* Inputs: Nothing
*
* Outputs: nothing
*
*************************************************************/
void Disable_RTCA_Calender_Alarm(void){
	RTCCTL0 &= ~RTCAIE;		// Disable RTCA alarm
}


void Enable_RTCA_Ready_Interrupt(void){
	RTCCTL01 |= RTCRDYIE;		// RTC Ready interrupt enabled
}


void Disable_RTCA_Ready_Interrupt(void){
	RTCCTL01 &= ~RTCRDYIE;		// RTC Ready interrupt disabled
}


void Set_RTCA_BCD_Mode(void){
	RTCCTL01 |= RTCBCD;		// RTC Calender set to BCD mode
}


void Set_RTCA_Hexadecimal_Mode(void){
	RTCCTL01 &= ~RTCBCD;	// RTC Calender set to Hexadecimal mode
}


void Set_RTCA_Calender_Time(unsigned char *DateArray)
		{
		unsigned int year;
		unsigned char yearH, yearL;

		// create unsigned int year from two unsigned chars
		yearH = DateArray[6];
		yearL = DateArray[7];
		year = yearH;
		year <<= 8;
		year |= yearL;

		RTCCTL01 |= RTCHOLD; 	// Stop RTC

		RTCSEC = DateArray[0];	// Set seconds value
		RTCMIN = DateArray[1];	// Set minutes value
		RTCHOUR = DateArray[2];	// Set hours value
		RTCDAY = DateArray[3];	// Set day value
		RTCDOW = DateArray[4];	// Set day of the week value (0x00 = Sunday)
		RTCMON = DateArray[5];	// Set month value
		RTCYEAR = year;			// Set year value (year = yearH + yearL)

		RTCCTL01 &= ~(RTCHOLD);	// Start RTC calender mode
	}


void Set_RTCA_Calender_Alarm_Time(unsigned char *DateArrayAlarm)
	{
		RTCIV &= ~RTCAIFG;								// Clear interrupt flags
		RTCCTL0 &= ~RTCAIE;								// Disable RTCA interrupts

		RTCAMIN &= ~RTCAE;  							// disable interrupt bit
		RTCAHOUR &= ~RTCAE;  							// disable interrupt bit
		RTCADAY &= ~RTCAE;  							// disable interrupt bit
		RTCADOW &= ~RTCAE;  							// disable interrupt bit

		RTCAMIN = DateArrayAlarm[0];  					// Set alarm minute, disable interrupt bit
		RTCAHOUR = DateArrayAlarm[1];  					// Set alarm hour, disable interrupt bit
		RTCADAY = DateArrayAlarm[2];  					// Set alarm day, disable interrupt bit
		RTCADOW = DateArrayAlarm[3];  					// Set alarm day of week, disable interrupt bit

		// Uncomment alarm interrupt enable signals as needed
		RTCAMIN |= RTCAE;  							// disable interrupt bit
//		RTCAHOUR |= RTCAE;  							// disable interrupt bit
//		RTCADAY |= RTCAE;  							// disable interrupt bit
//		RTCADOW |= RTCAE;  							// disable interrupt bit
		RTCCTL01	|= RTCAIE;
	}


void Enable_RTCA_Calender_Alarm_Time_Interrupts(unsigned char MinEnable, unsigned char HourEnable, unsigned char DayEnable, unsigned char DOWEnable)
	{
		RTCIV &= ~RTCAIFG;						// Clear all RTC interrupt flags

		if(MinEnable)
			RTCAMIN |= RTCAE;  					// Set alarm minute interrupt enable
		if(HourEnable)
			RTCAHOUR |= RTCAE;  				// Set alarm hour interrupt enable
		if(DayEnable)
			RTCADAY |= RTCAE;  					// Set alarm day interrupt enable
		if(DOWEnable)
			RTCADOW |= RTCAE;  					// Set alarm day of week interrupt enable
	}


void Read_RTCA_Calender(unsigned char *DateArray){
	//Can be slow, should optimize
	unsigned int wait = 0;
	if(!RTCRDY){
		while(!RTCRDY)
			wait++;
			if(wait > 40000)		// wait 5ms at 8MHz system clock, this is slow...
			{
				DateArray[0] = RTCSEC;
				DateArray[1] = RTCMIN;
				DateArray[2] = RTCHOUR;
				DateArray[3] = RTCDAY;
				DateArray[4] = RTCDOW;
				DateArray[5] = RTCMON;
				DateArray[6] = RTCYEARH;
				DateArray[7] = RTCYEARL;
			}
	}
	else if(RTCRDY){
		DateArray[0] = RTCSEC;
		DateArray[1] = RTCMIN;
		DateArray[2] = RTCHOUR;
		DateArray[3] = RTCDAY;
		DateArray[4] = RTCDOW;
		DateArray[5] = RTCMON;
		DateArray[6] = RTCYEARH;
		DateArray[7] = RTCYEARL;
	}
}


void Set_RTCA_Prescaler_0_Source_ACLK(void){
	RTCPS0CTL &= ~RT0SSEL;		// RTC Prescaler Source From ACLK
}


void Set_RTCA_Prescaler_0_Source_SMCLK(void){
	RTCPS0CTL |= RT0SSEL;		// RTC Prescaler Source From SMCLK
}


void Enable_RTCA_Prescaler_0_Interrupt(unsigned char set){
	switch(set)
		{
	case 0:
			RTCPS0CTL &= ~RT0PSIE;
			break;
		case 1:
			RTCPS0CTL |= RT0PSIE;
			break;
		default:
			__no_operation();
			break;
		}
}


void Enable_RTCA_Prescaler_1_Interrupt(unsigned char set){
	switch(set)
		{
	case 0:
			RTCPS1CTL &= ~RT1PSIE;
			break;
		case 1:
			RTCPS1CTL |= RT1PSIE;
			break;
		default:
			__no_operation();
			break;
		}
}


void Enable_RTCA(void){
	RTCCTL01 &= ~RTCHOLD;		// Enable RTC
}

void Disable_RTCA(void){
	RTCCTL01 |= RTCHOLD;		// Disable RTC
}


void Enable_RTCA_Time_Event_Interrupt(unsigned char set){
	switch(set)
		{
	case 0:
			RTCCTL01 &= ~RTCTEVIE;
			break;
		case 1:
			RTCCTL01 |= RTCTEVIE;
			break;
		default:
			__no_operation();
			break;
		}
}


void Set_RTCA_Time_Event_Mode(unsigned char set){
	switch(set)
	{
	case 0:
		RTCCTL01 |= RTCTEV_0;		// RTC A 8-Bit Overflow (Minute Changed)
		break;
	case 1:
		RTCCTL01 |= RTCTEV_1;		// RTC A 16-Bit Overflow (Hour Changed)
		break;
	case 2:
		RTCCTL01 |= RTCTEV_2;		// RTC A 24-Bit Overflow (Midnight 00:00)
		break;
	case 3:
		RTCCTL01 |= RTCTEV_3;		// RTC A 32-Bit Overflow (Noon 12:00)
		break;
	default:
		__no_operation();
		break;
	}
}


void Set_RTCA_Counter_Mode(void){
	RTCCTL01 &= ~RTCMODE;		// RTC A Counter Mode
}


void Set_RTCA_Calender_Mode(void){
	RTCCTL01 |= RTCMODE;		// RTC A Calender Mode
}

