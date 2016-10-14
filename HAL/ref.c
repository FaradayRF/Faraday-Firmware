#include "cc430f6137.h"

void Enable_Reference(unsigned char set){
	switch(set)
	{
	case 0:
		REFCTL0 &= ~REFON;	// Disable Reference regardless of need
		break;
	case 1:
		REFCTL0 |= REFON;	// Enable Reference regardless of need
		break;
	default:
		__no_operation();
		break;
	}
}

void Enable_Reference_External_Output(unsigned char set){
	switch(set)
	{
	case 0:
		REFCTL0 &= ~REFOUT;	// Disable Reference external output buffer
		break;
	case 1:
		REFCTL0 |= REFOUT;	// Enable Reference external output buffer
		break;
	default:
		__no_operation();
		break;
	}
}


void Set_Reference(unsigned char set){
	switch(set)
	{
	case 0:
		REFCTL0 |= REFVSEL_0;	// Use internal 1.5V Reference
		break;
	case 1:
		REFCTL0 |= REFVSEL_1;	// Use internal 2.0V Reference
		break;
	case 2:
		REFCTL0 |= REFVSEL_2;	// Use internal 2.5V Reference
		break;
	case 3:
		REFCTL0 |= REFVSEL_3;	// Use internal 2.5V Reference
		break;
	default:
		__no_operation();
		break;
	}
}
