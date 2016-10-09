#ifndef RTC_H_
#define RTC_H_

void Enable_RTCA_Ready_Interrupt(void);
void Disable_RTCA_Ready_Interrupt(void);
void Enable_RTCA_Calender_Alarm(void);
void Disable_RTCA_Calender_Alarm(void);
void Enable_RTCA(void);
void Disable_RTCA(void);
void Enable_RTCA_Prescaler_0_Interrupt(unsigned char set);
void Enable_RTCA_Prescaler_1_Interrupt(unsigned char set);
void Enable_RTCA_Time_Event_Interrupt(unsigned char set);
void Enable_RTCA_Calender_Alarm_Time_Interrupts(unsigned char MinEnable, unsigned char HourEnable, unsigned char DayEnable, unsigned char DOWEnable);

void Set_RTCA_BCD_Mode(void);
void Set_RTCA_Hexadecimal_Mode(void);
void Set_RTCA_Calender_Time(unsigned char *DateArray);
void Set_RTCA_Calender_Alarm_Time(unsigned char *DateArrayAlarm);
void Set_RTCA_Time_Event_Mode(unsigned char set);
void Set_RTCA_Counter_Mode(void);
void Set_RTCA_Calender_Mode(void);
void Set_RTCA_Prescaler_0_Source_ACLK(void);
void Set_RTCA_Prescaler_0_Source_SMCLK(void);
void GPS_Update_Calender_Time(void);

void Read_RTCA_Calender(unsigned char *DateArray);

#endif /* RTC_H_ */
