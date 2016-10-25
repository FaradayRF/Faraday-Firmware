/** @file Faraday_HAL.h
 *  @brief Hardware abstraction for Faraday
 *
 *  These functions provide basic hardware abstraction for Faraday
 *  and it's onboard peripheral devices.
 */

#ifndef FARADAY_HAL_H_
#define FARADAY_HAL_H_


/**@brief Enable the UART UCA0IFG transmitter "UCTXIFG" flag
 *
 *  This function manually enable the UART UCA0IFG transmitter "UCTXIFG" flag.
 *
 */
void hal_uart_set_uctxifg(void);


/**@brief Turn external MOSFET ON
 *
 *	Enables the external MOSFET GPIO that turns the MOSFET ON.
 *
 */
void Faraday_MOSFET_On(void);


/**@brief Turn external MOSFET OFF
 *
 *	Disables the external MOSFET GPIO that turns the MOSFET OFF.
 *
 */
void Faraday_MOSFET_Off(void);


/**@brief Enable the GPS RESET GPIO
 *
 *  Enable the GPS RESET GPIO.
 *
 */
void Faraday_GPS_Reset_Enable(void);


/**@brief Disable the GPS RESET GPIO
 *
 *  Disable the GPS RESET GPIO.
 *
 */
void Faraday_GPS_Reset_Disable(void);


/**@brief Enable the GPS Standby GPIO
 *
 *  Enable the GPS Standby GPIO.
 *
 */
void Faraday_GPS_Standby_Enable(void);


/**@brief Disable the GPS Standby GPIO
 *
 *  Disable the GPS Standby GPIO.
 *
 */
void Faraday_GPS_Standby_Disable(void);


/**@brief Enable the CC1190 RF Amplifier
 *
 *	Enable the CC1190 RF Amplifier
 *
 */
void Faraday_PA_Enable(void);


/**@brief Disable the CC1190 RF Amplifier
 *
 *	Disable the CC1190 RF Amplifier
 *
 */
void Faraday_PA_Disable(void);


/**@brief Enable the CC1190 Lower Noise Amplifier
 *
 *	Enable the CC1190 Low Noise Amplifier
 *
 */
void Faraday_LNA_Enable(void);


/**@brief Disable the CC1190 Lower Noise Amplifier
 *
 *	Disable the CC1190 Low Noise Amplifier
 *
 */
void Faraday_LNA_Disable(void);


/**@brief Enable the CC1190 High Gain Mode (HGM)
 *
 *	Enable the CC1190 High Gain Mode (HGM)
 *
 */
void Faraday_HGM_Enable(void);


/**@brief Enable the CC1190 High Gain Mode (HGM)
 *
 *	Enable the CC1190 High Gain Mode (HGM)
 *
 */
void Faraday_HGM_Disable(void);


/**@brief Change the CC430 RF power setting
 *
 *	This is a hardware abstraction function that allows modifying the value of the CC430
 *	RF power setting. This function uses the RF1A HAL library function to update the PATable
 *	value.
 *
 *	@note See the CC430 Family Users Guide for additional information and settings.
 *
 *	@param ucharPowerSetting RF Power setting that updates PATable.
 *
 */
void Faraday_RF_PWR_Change(unsigned ucharPowerSetting);

#endif /* FARADAY_HAL_H_ */
