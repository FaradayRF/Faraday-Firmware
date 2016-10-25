/** @file GPIO.h
 * 	@brief Hardware abstraction for the GPIO
 *
 * 	These functions provide a hardware abstraction for the general purpose
 * 	input/output peripheral on the CC430.
 *
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_


/**@brief Update a GPIO Port using a command bitmask
 *
 *  Update a GPIO Port using a command bitmask supplied to indicated pins and a command to indicate action. This function
 *  is primarly used to verify allowed actions on GPIO ports and call teh gpio_command_update() routine to perform
 *  updates as needed.
 *
 *  Ports Supported:
 *  - Ports 3, 4, 5
 *
 *  Commands
 *  - 0 = Bitmasked HIGH pins OFF
 *  - 1 = Bitmasked HIGH pins ON
 *
 *  @param port The GPIO port
 *  @param pins Bitmask for the port pins intended to be updated
 *  @param command to supply the gpio_command_update() function that determines if the pins bitmasked are enabled or disabled
 *
 */
void gpio_update(unsigned char port, unsigned char pins, unsigned char command);


/**@brief Update GPIO port and pins
 *
 * Using a supplied port number and supplied pins bitmask GPIO pins can be updated to enabled or disabled.
 *
 *
 *  @param port A pointer to the GPIO port number
 *  @param pins Bitmask for the port pins intended to be updated
 *  @param command to supply the gpio_command_update() function that determines if the pins bitmasked are enabled or disabled
 *
 *	@bug Does port variable really need to be a pointer?
 *
 */
void gpio_command_update(unsigned char *port, unsigned char channel, unsigned char command);


/**@brief Enable the CC1190 RF power amplifier
 *
 * Enable the CC1190 RF power amplifier GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_PA_Enable(void);


/**@brief Disable the CC1190 RF power amplifier
 *
 * Disable the CC1190 RF power amplifier GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_PA_Disable(void);


/**@brief Enable the CC1190 RF low noise amplifier
 *
 * Enable the CC1190 RF low noise amplifier GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_LNA_Enable(void);


/**@brief Disable the CC1190 RF low noise amplifier
 *
 * Disable the CC1190 RF low noise amplifier GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_LNA_Disable(void);


/**@brief Enable the CC1190 High Gain Mode (HGM)
 *
 * Enable the CC1190 High Gain Mode (HGM) GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_HGM_Enable(void);


/**@brief Disable the CC1190 High Gain Mode (HGM)
 *
 * Disable the CC1190 High Gain Mode (HGM) GPIO.
 *
 * @todo This should be moved into Faraday_HAL.c
 *
 */
void CC1190_HGM_Disable(void);

#endif /* HAL_GPIO_H_ */
