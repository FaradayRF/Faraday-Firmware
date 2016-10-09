/*
 * init.h
 *
 *  Created on: Jul 10, 2015
 *      Author: Brent
 */

#ifndef INIT_H_
#define INIT_H_


void faraday_main_intialize(void);
void init_GPIO(void);
void init_UCS(void);
void init_usci_A0_UART(void);
void init_DMA(void);
void init_timer_A0(void);
void init_timer_A1(void);
void reset_identification(void);
void reset_identification_2(void);
void reset_identification_3(void);
void init_GPS(void);
void init_REF(void);
void init_ADC(void);
void init_SPI(void);
void init_software_uart(void);
void init_RTCA_Calender_Mode(void);
void init_RTCA_Counter_Mode(void);
void InitTimer_0A1(void);
void InitRadio(void);
#endif /* INIT_H_ */
