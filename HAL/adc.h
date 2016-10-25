/** @file adc.h
 *  @brief ADC Hardware Abstraction Functions
 *
 *  These funcitons abstract interacts with the ADC peripheral on the
 *  CC430.
 *
 */

#ifndef ADC_H_
#define ADC_H_


/**@brief Clear the ADC12CTL2 memory register passed to the function
 *
 * This function clears the contents of the memory registers for the ADC12 peripheral. Passing
 * the correct number to the function clears the respective register for ADC 12.
 *
 * @param MemoryChannel The ADC 12 memory channel to clear 0-15.
 *
 */
void Clear_ADC12_Memory_Control_Register(unsigned char MemoryChannel);




/**@brief Enable ADC12 channel interrupt
 *
 * The function allows the ADC12 interrupts to be set given the supplied function
 * argument channel number respectively.
 *
 *
 * @param set The ADC 12 memory channel to enable interrupt 0-15.
 *
 */
void Enable_ADC12_Memory_Channel_Interrupt(unsigned char set);


/**@brief Calibrate the ADC temperature sensor
 *
 * This function uses the factory supplied calibration constants saved in Flash memory
 * to calibrate the onboard temperature sensor.
 *
 */
unsigned int adc_corrected_calibration_temp_C_int(int uInt_Raw_Temp);

#endif /* ADC_H_ */
