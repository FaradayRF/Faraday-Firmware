/** @file adc.c
 *  @brief ADC Hardware Abstraction Functions
 *
 *  These funcitons abstract interacts with the ADC peripheral on the
 *  CC430.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "adc.h"

/* hardware abstraction/allocation */
#include "../REVA_Faraday.h"

/* faraday global variables */
#include "../Faraday_Globals.h"


void Clear_ADC12_Memory_Control_Register(unsigned char MemoryChannel){
switch(MemoryChannel)
	{
	case 0:
		ADC12MCTL0 = 0;		// Clear ADC12 Memory Channel 0 control register
		break;
	case 1:
		ADC12MCTL1 = 0;		// Clear ADC12 Memory Channel 1 control register
		break;
	case 2:
		ADC12MCTL2 = 0;		// Clear ADC12 Memory Channel 2 control register
		break;
	case 3:
		ADC12MCTL3 = 0;		// Clear ADC12 Memory Channel 3 control register
		break;
	case 4:
		ADC12MCTL4 = 0;		// Clear ADC12 Memory Channel 4 control register
		break;
	case 5:
		ADC12MCTL5 = 0;		// Clear ADC12 Memory Channel 5 control register
		break;
	case 6:
		ADC12MCTL6 = 0;		// Clear ADC12 Memory Channel 6 control register
		break;
	case 7:
		ADC12MCTL7 = 0;		// Clear ADC12 Memory Channel 7 control register
		break;
	case 8:
		ADC12MCTL8 = 0;		// Clear ADC12 Memory Channel 8 control register
		break;
	case 9:
		ADC12MCTL9 = 0;		// Clear ADC12 Memory Channel 9 control register
		break;
	case 10:
		ADC12MCTL10 = 0;	// Clear ADC12 Memory Channel 10 control register
		break;
	case 11:
		ADC12MCTL11 = 0;	// Clear ADC12 Memory Channel 11 control register
		break;
	case 12:
		ADC12MCTL12 = 0;		// Clear ADC12 Memory Channel 12 control register
		break;
	case 13:
		ADC12MCTL13 = 0;	// Clear ADC12 Memory Channel 13 control register
		break;
	case 14:
		ADC12MCTL14 = 0;	// Clear ADC12 Memory Channel 14 control register
		break;
	case 15:
		ADC12MCTL15 = 0;	// Clear ADC12 Memory Channel 15 control register
		break;
	default:
		__no_operation();
		break;
	}
}


void Enable_ADC12_Memory_Channel_Interrupt(unsigned char set){
	switch(set)
	{
	case 0:
		ADC12IE |= ADC12IE0;	// ADC12 memory channel 0 interrupt enable
		break;
	case 1:
		ADC12IE |= ADC12IE1;	// ADC12 memory channel 1 interrupt enable
		break;
	case 2:
		ADC12IE |= ADC12IE2;	// ADC12 memory channel 2 interrupt enable
		break;
	case 3:
		ADC12IE |= ADC12IE3;	// ADC12 memory channel 3 interrupt enable
		break;
	case 4:
		ADC12IE |= ADC12IE4;	// ADC12 memory channel 4 interrupt enable
		break;
	case 5:
		ADC12IE |= ADC12IE5;	// ADC12 memory channel 5 interrupt enable
		break;
	case 6:
		ADC12IE |= ADC12IE6;	// ADC12 memory channel 6 interrupt enable
		break;
	case 7:
		ADC12IE |= ADC12IE7;	// ADC12 memory channel 7 interrupt enable
		break;
	case 8:
		ADC12IE |= ADC12IE8;	// ADC12 memory channel 8 interrupt enable
		break;
	case 9:
		ADC12IE |= ADC12IE9;	// ADC12 memory channel 9 interrupt enable
		break;
	case 10:
		ADC12IE |= ADC12IE10;	// ADC12 memory channel 10 interrupt enable
		break;
	case 11:
		ADC12IE |= ADC12IE11;	// ADC12 memory channel 11 interrupt enable
		break;
	case 12:
		ADC12IE |= ADC12IE12;	// ADC12 memory channel 12 interrupt enable
		break;
	case 13:
		ADC12IE |= ADC12IE13;	// ADC12 memory channel 13 interrupt enable
		break;
	case 14:
		ADC12IE |= ADC12IE14;	// ADC12 memory channel 14 interrupt enable
		break;
	case 15:
		ADC12IE |= ADC12IE15;	// ADC12 memory channel 15 interrupt enable
		break;
	default:
		__no_operation();
		break;
	}
}


unsigned int adc_corrected_calibration_temp_C_int(int uInt_Raw_Temp){
	//Get the TI supplied flash calibration values from Faraday definitions
	//Use TI supplied 2 point calibration temperature convertion equation (Note that this is JUNCTION temperature on the MSP430 itself
	int uInt_30C_Cal, uInt_85C_Cal;
	int Int_Temp_C_Calibration = 0; // Long or INT because the multiplication steps could be larger than INT? Will just go on stack those so not needed?

	//Copy calibration constants for device. I could probable make this more efficient using just an INT pointer
	memcpy(&uInt_30C_Cal, ADC12_2_5_V_TEMP_CAL_30C, 2);
	memcpy(&uInt_85C_Cal, ADC12_2_5_V_TEMP_CAL_85C, 2);

	//Perform temperature (C) convertion using calibration line
	Int_Temp_C_Calibration = ((uInt_Raw_Temp-uInt_30C_Cal)*(85-30))/(uInt_85C_Cal-uInt_30C_Cal)+30;


	//Return calibration temperature in C as Int (Note that this is a Scaled INT)
	return Int_Temp_C_Calibration;
}
