/*
 * housekeeping.c
 *
 *  Created on: Aug 5, 2015
 *      Author: Brent
 */

#include <msp430.h>
#include "REVA_Faraday.h"
#include "housekeeping.h" //OK to include OWN header? Get declarations issue otherwise due to ordering of functions below...
#include "Faraday_HAL/Faraday_HAL.h"
#include "Faraday_Globals.h"
#include "RF_Network_Stack/rf.h"
#include "RF_Network_Stack/rf_transport.h"
#include "UART/UART_L2.h"
#include "UART/UART_L4.h"
#include "Applications/Telemetry/Telemetry.h"
#include "Applications/Command/command.h"
#include "Applications/Telemetry/Telem_RF.h"
#include "Applications/MSG/MSG.h"
#include "Applications/HAB/App_HAB.h"

void main_housekeeping_routine(void){
	if(housekeeping_bitmask_char & BIT0){
		housekeeping_bitmask_char &= ~BIT0; //Disable general housekeeping bit
		//Check housekeeping functions
		check_housekeeping();

	}
}

/************************************************************
* Function: void check_housekeeping(void)
*
* Description: This function is the high level housekeeping function that is run to perform
*              a housekeeping "check" operation and any resulting actions. This should be kept
*              clean by using function calls to more specific housekeeping sub-routine checks.
*
* Inputs: None
*
* Outputs: None
*
*************************************************************/
void check_housekeeping(void){

	//Check housekeeping Timers
	housekeeping_check_raw();
	housekeeping_check_1hz();






}

void housekeeping_check_raw(){
	//UART
	uart_datalink_tx_housekeep();

	uart_datalink_rx_housekeep();


	//RF
	rf_housekeeping();

	//Applications

	app_telem_housekeeping();
	app_telem_rf_housekeeping();
	app_command_housekeep();
	app_telem_rf_rx_housekeep();
	app_msg_housekeeping();

	if(housekeeping_bitmask_char & BIT1){
		housekeeping_bitmask_char &= ~BIT1; //Disable general housekeeping bit
		//1 second timer bit

		//Increment housekeeping timers
		housekeeping_timer_count_1hz++;

	}


}


void housekeeping_check_1hz(){
	if(housekeeping_timer_count_1hz >= HOUSEKEEPING_TIMER_COUNT_1HZ){
		// Clear housekeeping 1 second timer count
		housekeeping_timer_count_1hz=0;
		//P3OUT ^= LED_2;

		application_telemetry_uart_housekeeping_interval();
		app_telem_rf_housekeeping_interval();

		//HAB Application
		application_hab_housekeeping_interval();
		application_hab_cutdown_event_check_state();

	}


}


void housekeeping_setup(void){
	housekeeping_bitmask_char = 0;
//	housekeeping_timer_count_60sec = 0;
//	housekeeping_timer_count_10sec = 0;
//	housekeeping_timer_count_5sec = 0;
	housekeeping_timer_count_1hz = 0;
//	housekeeping_timer_count_5hz = 0;
}

