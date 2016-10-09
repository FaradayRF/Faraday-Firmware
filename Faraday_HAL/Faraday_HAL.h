#ifndef FARADAY_HAL_H_
#define FARADAY_HAL_H_



void hal_uart_set_uctxifg(void);
unsigned char hal_uart_return_tx(void);

//LED's
void Faraday_LED_bitmask_enable(unsigned char ledmask);
void Faraday_LED_bitmask_disable(unsigned char ledmask);
void Faraday_LED_1_Enable(void);
void Faraday_LED_1_Disable(void);
void Faraday_LED_2_Enable(void);
void Faraday_LED_2_Disable(void);
void Faraday_GPIO_Bitmask_Cntl(unsigned char bitmask, unsigned char cntl);
void Faraday_GPIO_On(unsigned char gpio);
void Faraday_GPIO_Off(unsigned char gpio);
void Faraday_MOSFET_On(void);
void Faraday_MOSFET_Off(void);
void Faraday_GPS_Reset_Enable(void);
void Faraday_GPS_Reset_Disable(void);
void Faraday_GPS_Standby_Enable(void);
void Faraday_GPS_Standby_Disable(void);

void Faraday_PA_Enable(void);
void Faraday_PA_Disable(void);
void Faraday_LNA_Enable(void);
void Faraday_LNA_Disable(void);
void Faraday_HGM_Enable(void);
void Faraday_HGM_Disable(void);
void Faraday_LED_1_Toggle(void);
void Faraday_RF_PWR_Change(unsigned ucharPowerSetting);

#endif /* FARADAY_HAL_H_ */
