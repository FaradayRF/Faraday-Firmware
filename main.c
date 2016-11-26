#include "Faraday_Globals.h"
#include "cc430f6137.h"
#include "Faraday_Init.h"
#include "REVA_Faraday.h"
#include "housekeeping.h"
#include "HAL/hal_pmm.h"
#include "HAL/adc.h"
#include "HAL/rtc.h"
#include "Scratch/bryce.h"
#include "HAL/gps.h"
#include "RF_Network_Stack/rf.h"
#include "RF_Network_Stack/rf_service.h"
#include "UART/UART_L2.h"
#include "Applications/Telemetry/Telemetry.h"
#include "Applications/Telemetry/Telem_RF.h"

#include "Applications/Command/command.h"
#include "UART/UART_Services.h"
#include "Faraday_HAL/flash.h"
#include "Applications/Device_Config/Device_Config.h"
#include "Applications/MSG/MSG.h"
#include "Scratch/scratch_sram.h"
#include "Faraday_HAL/Faraday_HAL.h"
#include "Applications/HAB/App_HAB.h"

//DELETE ME
#include "scratch_flash.h"

#define TIMER_HOUSEKEEP_CCR0 65 //Housekeeping timer raw interrupt count value. 65 with 32768 clock is ~1.98ms
#define TIMER_HOUSEKEEP_CCR1 8192
unsigned char buttonPressed;


int main(void) {
	/*
	 * Watchdog Timer
	 */
 	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	housekeeping_setup();

	SetVCoreUp(2); // Increase PMMCOREV level to 2 for proper radio operation
	app_device_config_load_default(); //Load defaults from flash
	faraday_main_intialize();
	init_GPS();
	initialize_GPS_structs();
	init_timer_A0(); //Enable main housekeeping timer


    //Applications
	application_telemetry_initialize();
	app_init_command();
	init_app_msg();
	init_app_telem_rf_fifo();
	application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_0); //0 IDLE - This should get updated for flash memory integration control
	application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_0); //Set cutdown event duration timer to IDLE

	//Update boot count
	app_device_config_device_debug_update(0, 0);

	//Open RX UART service ports (Transport Layer)
	uart_service_open(2, app_command_put); //UART Command Link
	uart_service_open(3, app_msg_put); //UART MSG App Link

	//Open RX RF service ports (Transport Layer)
	rf_rx_service_open(2, app_command_rf_rx_put, 0); // RF Command Link, not safe for broadcast reception
	rf_rx_service_open(5, app_telem_rf_rx_put, 1); //RF Telemetry RX, safe for broadcast reception
	rf_rx_service_open(3, app_msg_rf_rx_put, 0); //RF MSG RX, not safe for broadcast reception


	radio_manual_idle(); // Goto IDLE first to force self calibration
	ReceiveOn();
	RTC.alarm[0] = 1;
	RTC.alarm[1] = 0;
	RTC.alarm[2] = 0;
	RTC.alarm[3] = 0;
	Set_RTCA_Calender_Alarm_Time((unsigned char *)RTC.alarm);
	Enable_RTCA_Calender_Alarm();

	Faraday_GPS_Reset_Enable();
	Faraday_GPS_Standby_Enable();

	//Check for RESET Faults on boot (Leave commented by default)
    //reset_identification();
    //reset_identification_2();


    //Enable interrupts
    __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled

    ///////////////////////////////////////////
	//MAIN() While(1) Loop
    //
    //Used because debugging in LPM contains PC corruption bug
    //
    //Also, should I do the housekeeping in the housekeeping timer ISR
    //Or enable Housekeeping flag, disable LPM, run through while(1) loop
    //and then reenable LPM?
	///////////////////////////////////////////


    //Scratch testing
    //flash_test(); // FLASH

    //Note: Per Errata bug the LPM iterrupt return will corrupt the PC, disable LPM when debugging and let the loop loose!
     while(1){
    	//__no_operation();                         // For debugger
    	//__bis_SR_register(LPM0_bits + GIE);
    	main_housekeeping_routine();

    	if (buttonPressed)                      // Process a button press->transmit
			{
				//Test the radio during manual push button operation
				buttonPressed = 0;                    // Re-enable button press
				test_tx_constant ^= BIT1;
			}
    	if(test_tx_constant && BIT1){
    		__no_operation();
    		unsigned char testbuf[62] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    		//memcpy(&testbuf, local_callsign, local_callsign_len);
    		memcpy(&testbuf, local_callsign, local_callsign_len);
    		rf_tx_put_packet_buffer(testbuf, 62);
    	}
    	if(test_tx_constant){
    		P3OUT |= LED_2;
    	}
    	else{
    		P3OUT &= ~LED_2;
    	}

    	//Read RSSI
    	//volatile unsigned char rssi_value;
    	//rssi_value = ReadSingleReg(RSSI);
    	//__no_operation();
    }

}//END MAIN


//AES_VECTOR
#pragma vector=AES_VECTOR
__interrupt void AES_ISR(void)
{
}

//RTC_VECTOR
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
	switch(__even_in_range(RTCIV,16))
	{
	case RTC_NONE:				// No interrupts
		break;
	case RTC_RTCRDYIFG:			// RTCRDYIFG

		// Interrupt called when RTCRDY set indicating it is OK to copy RTC time
		RTC.second = RTCSEC;
		RTC.minute = RTCMIN;
		RTC.hour = RTCHOUR;
		RTC.day = RTCDAY;
		RTC.month = RTCMON;
		RTC.dow = RTCDOW;
		RTC.year = RTCYEAR;
		break;
	case RTC_RTCTEVIFG:			//RTCTEVIFG
		break;
	case RTC_RTCAIFG:			//RTCAIFG
		application_update_RTC_calender_gps();			// Once per hour one minute after the hour set the RTC calender to GPS time
		break;
	case RTC_RT0PSIFG:			// RT0PSIFG
		break;
	case RTC_RT1PSIFG:			// RT1PSIFG
		break;
    case 12: break;                         // Reserved
    case 14: break;                         // Reserved
    case 16: break;                         // Reserved
    default: break;
	}
}
//LCD_B_VECTOR
#pragma vector=LCD_B_VECTOR
__interrupt void LCD_B_ISR(void)
{
	__no_operation();
}
//PORT2_VECTOR
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	//GPS UART TX
	  switch(__even_in_range(P2IV,16))
	  {
	    case 0:  break;                 // No Interrupt
	    case 2:							// P2.0 (GPS TX From UART)
	    //Clear the P1.5 interrupt flag for GPIO (Software UART) and disable P2 GPS TX interrupts
		P2IFG &= ~GPS_UART_TX;
		P2IE &= ~GPS_UART_TX;

		//Enable TimerA1 CCR1 and trigger on edge of start bit, count until center of expected bit
		TA1CCTL1 = CCIE;
		TA1CCR1 = TA1R + SOFTWARE_UART_HALF_BIT_TIME;

		//Reset the buffer byte/arrays as needed for software UART to ensure clean start
		software_uart_char_buffer_rx = 0;	// clear the Rx buffer
		software_uart_int_buffer_rx = 0;
		software_uart_char_bit_count = SOFTWARE_UART_BIT_COUNT; // Expect 10 bits for every RX byte
	    	break;

	    case 4:  break;                 // P2.1
	    case 6:  break;                 // P2.2
	    case 8:  break;                 // P2.3
	    case 10: break;                 // P2.4
	    case 12: break;                 // P2.5
	    case 14: break;                 // P2.6
	    case 16: break;                 // P2.7
	    default: break;
	 }
}
//PORT1_VECTOR
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	//P1IFG &= ~BIT7;                          // P1.4 IFG cleared
	  switch(__even_in_range(P1IV,16))
	  {
	    case 0:  break;                 // No Interrupt
	    case 2: 				        // P1.0
	    	break;
	    case 4:  break;                 // P1.1
	    case 6:  break;                 // P1.2
	    case 8:  break;                 // P1.3
	    case 10: break;                 // P1.4
	    case 12: 						// P1.5
	    	break;
	    case 14: break;                 // P1.6
	    case 16:	                    // P1.7 (BUTTON_1)
	    buttonPressed = 1;
	    	//scratch_app_adc_get();
	    break;
	    default: break;
	 }
}
//TIMER1_A1_VECTOR
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{

  switch(__even_in_range(TA1IV,14))
  {
    case 0: break;
    case 2:										//TA1CCR1
    	/* This interrupt timer is used to receive GPS data from a software UART */
    	//Add UART bit-time (time duration of 1 bit) to the trigger
		TA1CCR1 += SOFTWARE_UART_BIT_TIME;

		//Still parsing a new UART byte "frame"
		if(software_uart_char_bit_count>0){
			--software_uart_char_bit_count;

			if (P2IN & GPS_UART_TX){
				// Recieved bit is HIGH (1)
				software_uart_int_buffer_rx |= 0x400;
				software_uart_int_buffer_rx = software_uart_int_buffer_rx >> 1;
			}
			else{
				// Recieved bit is LOW (0)
				software_uart_int_buffer_rx = software_uart_int_buffer_rx >> 1;			// otherwise just shift.
			}
		}

		//Frame complete, save last bit and byte
		else{
			// Recieved bit is HIGH (1)
			if (P2IN & GPS_UART_TX){
				software_uart_int_buffer_rx |= 0x400;
				software_uart_int_buffer_rx = software_uart_int_buffer_rx >> 1;
			}
			// Recieved bit is LOW (0)
			else{
				software_uart_int_buffer_rx = software_uart_int_buffer_rx >> 1;			// otherwise just shift.
			}

			//Disable TimerA1 - No longer needed
			TA1CCTL1 &= ~CCIE;
			//Check start and stop bit for correctness (start -> LSB=0 stop -> MSB=1)
			if((software_uart_int_buffer_rx & SOFTWARE_UART_STOPBIT_MASK) && (~software_uart_int_buffer_rx & SOFTWARE_UART_STARTBIT_MASK)){
				//Remove start bit with right shift and stop bit by copying only a byte of data
				software_uart_int_buffer_rx = (software_uart_int_buffer_rx >> 1);	// extract received byte
				software_uart_char_buffer_rx = software_uart_int_buffer_rx;

				//Send received byte to GPS NMEA string parsing function(s)
				gps_get_nmea_string(&software_uart_char_buffer_rx);
			}
			//Start and Stop bits incorrect
			else{
				//Ignore, data is corrupt.
				__no_operation();
			}

			//Clear P2 interrupt flags and enabled interrupts for next byte
			P2IFG &= ~GPS_UART_TX; // Should this be complete port on just this ISR case? Bug?
			P2IE |= GPS_UART_TX;
			//P1IE = UCB0CS1;		// for Faraday Rev 1 units
		}
             break;
    case 4:  //TA1CCR2 += 100;                // Add Offset to CCR2
             break;
    case 6:  break;                         // CCR3 not used
    case 8:  break;                         // CCR4 not used
    case 10: break;                         // CCR5 not used
    case 12: break;                         // Reserved not used
    case 14: //P1OUT ^= 0x01;                 // overflow
             break;
    default: break;
 }
}

/************************************************************
* Function: TIMER0 A0 INTERRUPT VECTOR
*
* Description: Highest priority Timer0 interrup vector. Performed when CCR0 of Timer 0 reached. Used for housekeeping task triggering
*
*************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	housekeeping_bitmask_char |= BIT0;		// Set bitmask for housekeeping check
	TA0CCR0 += TIMER_HOUSEKEEP_CCR0;//65;							// add offset to CCR0 for ~1.98ms trigger at 32768 KHz ACLK
}

/************************************************************
* Function: TIMER0 A5 INTERRUPT VECTOR
*
* Description:
*
*************************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
  switch(__even_in_range(TA0IV,14))
  {
    case 0:
    	break;
    case 2:  //TA1CCR1 += 16;                 // Add Offset to CCR1
    	housekeeping_bitmask_char |= BIT1; //BIT 1 for 1 second timer
    	TA0CCR1 += TIMER_HOUSEKEEP_CCR1;
             break;
    case 4:  //TA1CCR2 += 100;                // Add Offset to CCR2
             break;
    case 6:
    		break;                         // CCR3 not used
    case 8:
    		break;                         // CCR4 not used
    case 10:
    		break;                         // CCR5 not used
    case 12:
    		break;                         // Reserved not used
    case 14: //P1OUT ^= 0x01;                 // overflow
    		break;
    default:
    		break;
 }
}
//DMA_VECTOR
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void)
{
}
//CC1101_VECTOR
#pragma vector=CC1101_VECTOR
__interrupt void CC1101_ISR(void)
{
  switch(__even_in_range(RF1AIV,32))        // Prioritizing Radio Core Interrupt
  {
    case  0: break;                         // No RF core interrupt pending
    case  2: break;                         // RFIFG0
    case  4: break;                         // RFIFG1
    case  6: break;                         // RFIFG2
    case  8: break;                         // RFIFG3
    case 10: break;                         // RFIFG4
    case 12: break;                         // RFIFG5
    case 14: break;                         // RFIFG6
    case 16: break;                         // RFIFG7
    case 18: break;                         // RFIFG8
    case 20:								// RFIFG9
			radio_isr();
    break;
    case 22: break;                         // RFIFG10
    case 24: break;                         // RFIFG11
    case 26: break;                         // RFIFG12
    case 28: break;                         // RFIFG13
    case 30: break;                         // RFIFG14
    case 32: break;                         // RFIFG15
  }
}



//ADC12_VECTOR
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	//__no_operation();
	switch(__even_in_range(ADC12IV,34))
	  {
	  case  ADC12IV_NONE:					// No Interrupt Pending
		  break;
	  case  ADC12IV_ADC12OVIFG:				// ADC Memory Overflow flag
		  break;
	  case  ADC12IV_ADC12TOVIFG:			// ADC Conversion Timeout flag
		  break;
	  case  ADC12IV_ADC12IFG0:				// ADC Memory Channel 0 Flag
		  break;
	  case  ADC12IV_ADC12IFG1:				// ADC Memory Channel 1 Flag
		  break;
	  case ADC12IV_ADC12IFG2:				// ADC Memory Channel 2 Flag
		  break;
	  case ADC12IV_ADC12IFG3:				// ADC Memory Channel 3 Flag
		  break;
	  case ADC12IV_ADC12IFG4:				// ADC Memory Channel 4 Flag
		  break;
	  case ADC12IV_ADC12IFG5:				// ADC Memory Channel 5 Flag
		  break;
	  case ADC12IV_ADC12IFG6:				// ADC Memory Channel 6 Flag
		  break;
	  case ADC12IV_ADC12IFG7:				// ADC Memory Channel 7 Flag
		  break;
	  case ADC12IV_ADC12IFG8:				// ADC Memory Channel 8 Flag
		  // Move ADC data into a global array so it can be accessed by any other code
		  // this might change in the future to a non-global array.

		  ADC_Data[0] = ADC12MEM0;          // ADC0, Move results, IFG is cleared
		  ADC_Data[1] = ADC12MEM1;          // ADC1, Move results, IFG is cleared
		  ADC_Data[2] = ADC12MEM2;          // ADC2, Move results, IFG is cleared
		  ADC_Data[3] = ADC12MEM3;          // ADC3, Move results, IFG is cleared
		  ADC_Data[4] = ADC12MEM4;          // ADC4, Move results, IFG is cleared
		  ADC_Data[5] = ADC12MEM5;          // ADC5, Move results, IFG is cleared
		  ADC_Data[6] = ADC12MEM6;          // ADC6 (VCC), Move results, IFG is cleared
		  ADC_Data[7] = ADC12MEM7;          // CC430 Internal Temperature, Move results, IFG is cleared
		  ADC_Data[8] = ADC12MEM8;			// CC430 internal 3.3V measurment (VCC - VSS)/2, IFG is cleared
		  ADC12IV &= ~ADC12IV_ADC12IFG8;	// Clear the flag manually
		  break;
	  case ADC12IV_ADC12IFG9:				// ADC Memory Channel 9 Flag
		  break;
	  case ADC12IV_ADC12IFG10:				// ADC Memory Channel 10 Flag
		  break;
	  case ADC12IV_ADC12IFG11:				// ADC Memory Channel 11 Flag
		  break;
	  case ADC12IV_ADC12IFG12:				// ADC Memory Channel 12 Flag
		  break;
	  case ADC12IV_ADC12IFG13:				// ADC Memory Channel 13 Flag
		  break;
	  case ADC12IV_ADC12IFG14:				// ADC Memory Channel 14 Flag
		  break;
	  case ADC12IV_ADC12IFG15:				// ADC Memory Channel 15 Flag
		  break;
	  default:								// Default Flag
		  break;
	  }
}

//USCI_B0_VECTOR
/************************************************************
* Function: #pragma vector=USCI_A0_VECTOR  USCI_A0 interrupt vector handler
*
* Description: This is the interrupt service routine that
* the CC430 jumps to when a the USCI A0 interrupt is triggered
* For Farday this is triggered during by the UART connection
* to the host computer.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
	switch(__even_in_range(UCB0IV,4))
	{
	case 0: break;                          // Vector 0 - no interrupt
	case 2:                                 // Vector 2 - RXIFG
	  while (!(UCB0IFG&UCTXIFG));           // USCI_A0 TX buffer ready?
	  UCB0TXBUF = 0xAA;                 // Send next value

	  __delay_cycles(40);                   // Add time between transmissions to
											// make sure slave can process information
	  break;
	case 4: break;                          // Vector 4 - TXIFG
	default: break;
	}
}

//USCI_A0_VECTOR
/************************************************************
* Function: #pragma vector=USCI_A0_VECTOR  USCI_A0 interrupt vector handler
*
* Description: This is the interrupt service routine that
* the CC430 jumps to when a the USCI A0 interrupt is triggered
* For Farday this is triggered during by the UART connection
* to the host computer.
*
* 0Inputs: None
*
* Outputs: None
*
*************************************************************/
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:// Vector 0 - no interrupt
	  break;
  case 2:// Vector 2 - RXIFG
	  uart_datalink_rx_put_byte((volatile unsigned char)UCA0RXBUF);
	  break;
  case 4:// Vector 4 - TXIFG
	  uart_tx_datalink_isr();
	  break;

  default: break;
  }
}
//WDT_VECTOR
//------------------------------------------------------------------------------
// Trigger WatchDog Timer - WDT or Interval Timer
//------------------------------------------------------------------------------
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
}


//COMP_B_VECTOR
#pragma vector=COMP_B_VECTOR
__interrupt void COMP_B_ISR(void)
{
}
//UNMI_VECTOR
#pragma vector=UNMI_VECTOR
__interrupt void UNMI_ISR(void)
{
}
//SYSNMI_VECTOR
#pragma vector=SYSNMI_VECTOR
__interrupt void SYSNMI_ISR(void)
{
}
//RESET_VECTOR
#pragma vector=RESET_VECTOR
__interrupt void RESET_ISR(void)
{
}
