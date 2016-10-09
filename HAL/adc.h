#ifndef ADC_H_
#define ADC_H_

void Clear_ADC12_Memory_Control_Register(unsigned char MemoryChannel);
void Enable_ADC12_Channel_Interrupt(unsigned char set);
void Enable_ADC12_Memory_Channel_Interrupt(unsigned char set);
unsigned int adc_corrected_calibration_temp_C_int(int uInt_Raw_Temp);

#endif /* ADC_H_ */
