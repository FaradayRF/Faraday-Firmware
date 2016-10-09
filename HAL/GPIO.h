/*
 * GPIO.h
 *
 *  Created on: Oct 26, 2015
 *      Author: Brent
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_


#define GPIO_UCB0CS1 0
#define GPIO_PORT_UCB0CS1 P1OUT
#define GPIO_UCB0_SIMO_SDA 0x01 //0b0000000000000001
#define GPIO_PORT_SIMO_SDA P1OUT
#define GPIO_UCB0CLK 0x02 //0b0000000000000010
#define GPIO_PORT_UCB0CLK P1OUT
#define GPIO_UCA0TXD  0x04//0b0000000000000100
#define GPIO_PORT_UCA0TXD P1OUT
#define GPIO_PA_ENABLE 0x08 //0b0000000000001000
#define GPIO_PORT_PA_ENABLE P3OUT
#define GPIO_LNA_ENABLE 0x10 //b0000000000010000
#define GPIO_PORT_LNA_ENABLE P3OUT
#define GPIO_HGM_SELECT 0x20 //0b0000000000100000
#define GPIO_PORT_HGM_SELECT P3OUT
#define GPIO_GPS_RESET 0x40 //0b0000000001000000
#define GPIO_PORT_GPS_RESET P3OUT
#define GPIO_GPS_STANDBY 0x80 //0b0000000010000000
#define GPIO_PORT_GPS_STANDBY P3OUT
#define GPIO_LED_1 0x100 //0b0000000100000000
#define GPIO_PORT_LED_1 P3OUT
#define GPIO_LED_2 0x200 //b0000001000000000
#define GPIO_PORT_LED_2 P3OUT
#define GPIO_MOSFET_CNTL 0x400 //0b000001000000000
#define GPIO_PORT_MOSFET_CNTL P5OUT
#define GPIO_SRAM_CS 0x800 //0b000010000000000
#define GPIO_PORT_SRAM_CS P5OUT
#define GPIO_SRAM_HOLD 0x1000 //0b000100000000000
#define GPIO_PORT_SRAM_HOLD P5OUT

//unsigned char gpio_ctnl_p3, gpio_p3_bitmask;


//void gpio_update_p3(unsigned char update);
//void gpio_bitmask_modify(unsigned char bitmask, unsigned char guard_mask);
void gpio_update(unsigned char port, unsigned char pins, unsigned char command);
void gpio_command_update(unsigned char *port, unsigned char channel, unsigned char command);

void CC1190_PA_Enable(void);
void CC1190_PA_Disable(void);
void CC1190_LNA_Enable(void);
void CC1190_LNA_Disable(void);
void CC1190_HGM_Enable(void);
void CC1190_HGM_Disable(void);

#endif /* HAL_GPIO_H_ */
