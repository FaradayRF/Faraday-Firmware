#include <msp430.h>
#include "GPIO.h"
#include "../REVA_Faraday.h"

volatile unsigned char gpio_p3_guard = GPS_RESET + GPS_STANDBY + LED_1 + LED_2;
volatile unsigned char gpio_p4_guard = GPIO_0 + GPIO_1 + GPIO_2 + GPIO_3 + GPIO_4 + GPIO_5 + GPIO_6 + GPIO_7;
volatile unsigned char gpio_p5_guard = ARDUINO_IO_8 + ARDUINO_IO_9 + P5_7_UNUSED; //Don't allow MOSFET_CNTL to be manually toggled due to nicrowire fire risk


//GPIO Commanding
void gpio_update(unsigned char port, unsigned char pins, unsigned char command){
	switch(port){
	case 3:
		//Check intended GPIO bits against the allowed GPIO bits through commanding and only allowed changable bits to change!
		pins = pins & gpio_p3_guard;

		//Perform GPIO action only if a port pin (channel) actually
		if(pins!=0){
			gpio_command_update(&P3OUT, pins, command);
		}
		break;
	case 4:
		//Check intended GPIO bits against the allowed GPIO bits through commanding and only allowed changable bits to change!
		pins = pins & gpio_p4_guard;

		//Perform GPIO action only if a port pin (channel) actually
		if(pins!=0){
			gpio_command_update(&P4OUT, pins, command);
		}
		break;
	case 5:
		//Check intended GPIO bits against the allowed GPIO bits through commanding and only allowed changable bits to change!
		pins = pins & gpio_p5_guard;

		//Perform GPIO action only if a port pin (channel) actually
		if(pins!=0){
			gpio_command_update(&P5OUT, pins, command);
		}
		break;
	}
	__no_operation();
}

void gpio_command_update(unsigned char *port, unsigned char channel, unsigned char command){
	switch(command){
	case 0:
		*port &= ~channel;
		break;
	case 1:
		*port |= channel;
		break;
	}
}

//////
// These should be absorded into the FARADAY HAL functions already written!!! BUG
//////
void CC1190_PA_Enable(void){
	P3OUT |= PA_ENABLE;
}

void CC1190_PA_Disable(void){
	P3OUT &= ~PA_ENABLE;
}

void CC1190_LNA_Enable(void){
	P3OUT |= LNA_ENABLE;
}

void CC1190_LNA_Disable(void){
	P3OUT &= ~LNA_ENABLE;
}

void CC1190_HGM_Enable(void){
	P3OUT |= HGM_SELECT;
}

void CC1190_HGM_Disable(void){
	P3OUT &= ~HGM_SELECT;
}
