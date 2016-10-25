/** @file RTC.h
 *  @brief CC430 real time clock hardware abstraction
 *
 *  These functions provide CC430 real time clock hardware abstraction
 *  functionality.
 *
 */


#ifndef RTC_H_
#define RTC_H_


/**@brief Enables RTCCTL01 RTC Ready interrupt enable bit
 *
 *  Enables RTCCTL01 RTC Ready interrupt enable bit.
 *
 */
void Enable_RTCA_Ready_Interrupt(void);


/**@brief Disables RTCCTL01 RTC Ready interrupt enable bit
 *
 *  Disables RTCCTL01 RTC Ready interrupt enable bit.
 *
 */
void Disable_RTCA_Ready_Interrupt(void);


/**@brief Enable the RTCCTL0 RTC_A calender alarm interrupt enable bit
 *
 *  Enable the RTCCTL0 RTC_A calender alarm interrupt enable bit.
 *
 */
void Enable_RTCA_Calender_Alarm(void);


/**@brief Disable the RTCCTL0 RTC_A calender alarm interrupt enable bit
 *
 *  Disable the RTCCTL0 RTC_A calender alarm interrupt enable bit.
 *
 */
void Disable_RTCA_Calender_Alarm(void);


/**@brief Enable the RTCA
 *
 *  Enable the RTCA (RTCHOLD)
 *
 */
void Enable_RTCA(void);


/**@brief Disable the RTCA
 *
 *  Disable the RTCA (RTCHOLD)
 *
 */
void Disable_RTCA(void);


/**@brief Enables RTC_A Prescaler 0 interrupt bit in the RTCPS0CTL register
 *
 *  Enables RTC_A Prescaler 0 interrupt bit in the RTCPS0CTL register.
 *
 *  @param set Enabled = 1, Disabled = 0
 *
 */
void Enable_RTCA_Prescaler_0_Interrupt(unsigned char set);


/**@brief Enables RTC_A Prescaler 1 interrupt bit in the RTCPS1CTL register
 *
 *  Enables RTC_A Prescaler 1 interrupt bit in the RTCPS1CTL register
 *
 *  @param set Enabled = 1, Disabled = 0
 *
 */
void Enable_RTCA_Prescaler_1_Interrupt(unsigned char set);


/**@brief Enable RTC_A Time Event (TEV) interrupt by setting RTCTEVIE in the RTCCTL01 register
 *
 *  Enable RTC_A Time Event (TEV) interrupt by setting RTCTEVIE in the RTCCTL01 register.
 *
 *  @param set Enabled = 1, Disabled = 0
 *
 */
void Enable_RTCA_Time_Event_Interrupt(unsigned char set);


/**@brief Enables RTC_A alarm interrupts while in calender mode
 *
 *  Enables RTC_A alarm interrupts while in calender mode. Sets the 7th bit of each alarm time to enable the respective alarm value to be enabled.
 *
 *  @param MinEnable Set to 1 if minute alarm enable, 0 to disable
 *  @param HourEnable Set to 1 if Hour alarm enable, 0 to disable
 *  @param DayEnable Set to 1 if Day alarm enable, 0 to disable
 *  @param DOWEnable Set to 1 if Day Of Week alarm enable, 0 to disable
 *
 *
 */
void Enable_RTCA_Calender_Alarm_Time_Interrupts(unsigned char MinEnable, unsigned char HourEnable, unsigned char DayEnable, unsigned char DOWEnable);


/**@brief Sets RTCCLT01 register bit RTCBCD to enable Binary Coded Decimal mode for RTC_A calender
 *
 *  Sets RTCCLT01 register bit RTCBCD to enable Binary Coded Decimal mode for RTC_A calender.
 *
 */

void Set_RTCA_BCD_Mode(void);


/**@brief Sets RTCCLT01 register bit RTCBCD to enable hexadecimal mode for RTC_A calender
 *
 *  Sets RTCCLT01 register bit RTCBCD to enable hexadecimal mode for RTC_A calender.
 *
 */
void Set_RTCA_Hexadecimal_Mode(void);


/**@brief Sets RTC_A time in Binary Coded Decimal format while in calender mode (second, minute, hour, day of week, day of month, month, year).
 *
 *  Sets RTC_A time in Binary Coded Decimal format while in calender mode (second, minute, hour, day of week, day of month, month, year)..
 *
 *  @note DateArray should be in format: [second, minute, hour, day of week, day of month, month, year]
 *
 *  @param DateArray A pointer to a bytearray containing the date array RTC calendar time to update to
 *
 */
void Set_RTCA_Calender_Time(unsigned char *DateArray);


/**@brief Sets the RTC_A alarm time when in calender mode (minute, hour, day, day of week)
 *
 *  Sets the RTC_A alarm time when in calender mode (minute, hour, day, day of week).
 *
 *  @note DateArrayAlarm should be in format: [minute, hour, day, day of week]
 *
 *  @param DateArrayAlarm A pointer to a bytearray containing the date array RTC calendar alarm time to update to
 *
 */
void Set_RTCA_Calender_Alarm_Time(unsigned char *DateArrayAlarm);


/**@brief Sets the RTC_A Time Event Mode
 *
 *  Sets the RTC_A Time Event Mode corresponding to an 8-bit, 16-bit, 24-bit, or 32-bit overflow triggering a time event interrupt.
 *
 *	Modes:
 *	- 0 = 8-bit
 *	- 1 = 16-bit
 *	- 2 = 24-bit
 *	- 3 = 32-bit
 *
 *	@param set Mode number
 *
 */
void Set_RTCA_Time_Event_Mode(unsigned char set);


/**@brief Sets Real Time Clock A to counter mode
 *
 *  Sets Real Time Clock A to counter mode
 *
 */
void Set_RTCA_Counter_Mode(void);


/**@brief Sets Real Time Clock A to Calender mode
 *
 *  Sets Real Time Clock A to Calender mode
 *
 */
void Set_RTCA_Calender_Mode(void);


/**@brief Sets teh sources clock signals from ACLK for the RTC_A prescaler
 *
 *  Sets the sources clock signals from ACLK for the RTC_A prescaler
 *
 */
void Set_RTCA_Prescaler_0_Source_ACLK(void);


/**@brief Sets the sources clock signals from SMCLK for the RTC_A prescaler
 *
 *  Sets the sources clock signals from SMCLK for the RTC_A prescaler.
 *
 */
void Set_RTCA_Prescaler_0_Source_SMCLK(void);


/**@brief Read the RTCA Calender
 *
 *  Reads the time values when RTC_A is in calender mode and RTCRDY is valid ensuring values are not obtained during a time transition.
 *  Waits for RTCRDY (up to 4ms) if not ready which is slow and can be improved. Places values into DateArray passed to it.
 *
 *  @param DateArray A pointer to a byte array that is filled with the read date array values. Expected 8 bytes in size.
 *
 */
void Read_RTCA_Calender(unsigned char *DateArray);

#endif /* RTC_H_ */
