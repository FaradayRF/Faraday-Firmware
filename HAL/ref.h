/** @file ref.h
 * 	@brief Hardware abstraction for the CC430 internal voltage reference
 *
 * 	Hardware abstraction for the CC430 internal voltage reference peripheral. This voltage reference
 * 	is used by primarally the ADC. This HAL also allows for enabling the internal reference to be provided
 * 	externally through a GPIO pin.
 *
 */


#ifndef REF_H_
#define REF_H_


/**@brief Enable/Disable the internal voltage reference
 *
 * Enable/Disable the CC430 internal voltage reference peripheral.
 *
 * @param set If 0 then REFON is OFF and if 1 then REFON is ON
 *
 * @todo This is a confusing function name. It should be split in the future to a specific enable/disable function with no function argument.
 *
 */
void Enable_Reference(unsigned char set);


/**@brief Enable/Disable the provision of the internal voltage reference to an external pin
 *
 *  Enable/Disable the provision of the internal voltage reference to an external pin
 *
 *	@param set If 0 then REFOUT is OFF and if 1 then REFOUT is ON
 *
 *	@todo This is a confusing function name. It should be split in the future to a specific enable/disable function with no function argument.
 *
 */
void Enable_Reference_External_Output(unsigned char set);


/**@brief Sets the internal voltage reference voltage
 *
 *  This function is used to set the internal voltage reference operating voltage. This is used to determine ADC full scale voltage.
 *
 *	Set Modes
 *	- 0 = 1.5V
 *	- 1 = 2.0V
 *	- 2 = 2.5V
 *
 *	@param set The mode number which determines the voltage reference voltage
 *
 */
void Set_Reference(unsigned char set);

#endif /* REF_H_ */
