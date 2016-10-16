#include "cc430f6137.h"
#include "RTC.h"
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
/************************************************************
* Function: Enable RTC_A Ready Interrupt
*
* Description: Enables RTCCTL01 RTC Ready interrupt enable bit
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Enable_RTCA_Ready_Interrupt(void){
	RTCCTL01 |= RTCRDYIE;		// RTC Ready interrupt enabled
}

/************************************************************
* Function: Disable RTC_A Ready Interrupt
*
* Description: Disables RTCCTL01 RTC Ready interrupt enable bit
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Disable_RTCA_Ready_Interrupt(void){
	RTCCTL01 &= ~RTCRDYIE;		// RTC Ready interrupt disabled
}

/************************************************************
* Function: Set RTC_A Binary Coded Decimal Mode
*
* Description: Sets RTCCLT01 register bit RTCBCD to enable Binary Coded Decimal mode for RTC_A calender
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_BCD_Mode(void){
	RTCCTL01 |= RTCBCD;		// RTC Calender set to BCD mode
}

/************************************************************
* Function: Set RTC_A Hexadecimal Mode
*
* Description: Sets RTCCLT01 register bit RTCBCD to enable hexadecimal mode for RTC_A calender
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_Hexadecimal_Mode(void){
	RTCCTL01 &= ~RTCBCD;	// RTC Calender set to Hexadecimal mode
}

/************************************************************
* Function: Set RTC_A Calender Time
*
* Description:	Sets RTC_A time in Binary Coded Decimal format while in calender mode (second, minute, hour, day of week, day of month, month, year).
*
* Inputs: unsigned char *DateArray
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Set RTC_A Calender Alarm Time
*
* Description: Sets the RTC_A alarm time when in calender mode (minute, hour, day, day of week)
*
* Inputs: unsigned char *DateArrayAlarm
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Enable RTC_A Calender Alarm time Interrupts
*
* Description: Enables RTC_A alarm interrupts while in calender mode. Sets the 7th bit of each alarm time to enable the respective alarm value to be enabled.
*
* Inputs: unsigned char MinEnable, unsigned char HourEnable, unsigned char DayEnable, unsigned char, DOWEnable
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Read RTC_A Calender
*
* Description: Reads the time values when RTC_A is in calender mode and RTCRDY is valid ensuring values are not obtained during a time transition.
* 			   Waits for RTCRDY (up to 4ms) if not ready which is slow and can be improved. Places values into DateArray passed to it.
*
* Inputs: unsigned char *DateArray
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Set RTC_A Prescaler 0 Source ACLK
*
* Description: Sources clock signals from ACLK for the RTC_A prescaler
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_Prescaler_0_Source_ACLK(void){
	RTCPS0CTL &= ~RT0SSEL;		// RTC Prescaler Source From ACLK
}

/************************************************************
* Function: Set RTC_A Prescaler 0 Source SMCLK
*
* Description: Sources clock signals from SMCLK for the RTC_A prescaler
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_Prescaler_0_Source_SMCLK(void){
	RTCPS0CTL |= RT0SSEL;		// RTC Prescaler Source From SMCLK
}

/************************************************************
* Function: Enable RTC_A Prescaler 0 Interrupt
*
* Description: Enables RTC_A Prescaler 0 interrupt bit in the RTCPS0CTL register
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Enable RTC_A Prescaler 1 Interrupt
*
* Description: Enables RTC_A Prescaler 1 interrupt bit in the RTCPS1CTL register
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
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



/************************************************************
* Function: Enable RTC_A Prescaler 0
*
* Description: Enable RTC_A prescaler 0 to divide the clock value
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
void Enable_RTCA_Prescaler_0(unsigned char set){
	switch(set)
		{
	case 0:
			RTCPS0CTL |= RT0PSHOLD;		// Disable RTC 0 Prescaler
			break;
		case 1:
			RTCPS0CTL &= ~RT0PSHOLD;		// Enable RTC 0 Prescaler
			break;
		default:
			__no_operation();
			break;
		}
}

/************************************************************
* Function: Enable RTC_A Alarm interrupt
*
* Description: Enables RTC_A alarm interrupts by setting the RTCAIE in the RTCCTL01 register
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
void Enable_RTCA_Alarm_Interrupt(unsigned char set){
	switch(set)
		{
	case 0:
			RTCCTL01 &= ~RTCAIE;
			break;
		case 1:
			RTCCTL01 |= RTCAIE;
			break;
		default:
			__no_operation();
			break;
		}
}

/************************************************************
* Function: Enabled RTC_A Time Event Interrupt
*
* Description: Enables RTC_A Time Event (TEV) interrupt by setting RTCTEVIE in the RTCCTL01 register
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Set RTC_A Time Event Mode
*
* Description: Sets the RTC_A Time Event Mode corresponding to an 8-bit, 16-bit, 24-bit, or 32-bit overflow triggering a time event interrupt
*
* Inputs: unsigned char set
*
* Outputs: Nothing
*
*************************************************************/
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

/************************************************************
* Function: Set RTC_A Counter Mode
*
* Description: Sets Real Time Clock A to counter mode
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_Counter_Mode(void){
	RTCCTL01 &= ~RTCMODE;		// RTC A Counter Mode
}
/************************************************************
* Function: Set RTC_A Calender Mode
*
* Description: Sets Real Time Clock A to Calender mode
*
* Inputs: Nothing
*
* Outputs: Nothing
*
*************************************************************/
void Set_RTCA_Calender_Mode(void){
	RTCCTL01 |= RTCMODE;		// RTC A Calender Mode
}

