/** @file GPIO.c
 * 	@brief Hardware abstraction for the GPIO
 *
 * 	These functions provide a hardware abstraction for the general purpose
 * 	input/output peripheral on the CC430.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "GPIO.h"

/* faraday hardware allocations */
#include "../REVA_Faraday.h"


/** @name GPIO Guard Bitmask
* 	@brief The bitmask bytes defined in this group determine if a GPIO state is allowed to be updated using this GPIO hardware abstraction. Certain GPIO's
* 	may be dangerous to change such as hardware peripheral (GPS/LNA) and especially the MOSFET high current GPIO. GPIO's are "opt-in" to be updated and
* 	if the bitmask for that port is a HIGH bit then the corresponding pin for that port is alloed to be updated using this HAL.
*
*
@{**/
volatile unsigned char gpio_p3_guard = GPS_RESET + GPS_STANDBY + LED_1 + LED_2; /**< Guard bitmask for Port 3 */
volatile unsigned char gpio_p4_guard = GPIO_0 + GPIO_1 + GPIO_2 + GPIO_3 + GPIO_4 + GPIO_5 + GPIO_6 + GPIO_7; /**< Guard bitmask for Port 4 */
volatile unsigned char gpio_p5_guard = ARDUINO_IO_8 + ARDUINO_IO_9; /**< Guard bitmask for Port 3 */
/** @}*/


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
