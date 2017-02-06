/** @file housekeeping.c
 *  @brief General Faraday housekeeping routines
 *
 *  These functions provide basic "housekeeping" functions that
 *  allow the gathering, processing, and general use of data input
 *  and output to operate.
 *
 */

/* standard includes */
#include "cc430f6137.h"
#include "Applications/HAB/App_HAB.h"
#include "housekeeping.h"

/* faraday hardware allocations */
#include "REVA_Faraday.h"
#include "Faraday_HAL/Faraday_HAL.h"

/* faraday global variables */
#include "Faraday_Globals.h"

/* faraday rf network stack */
#include "RF_Network_Stack/rf.h"
#include "RF_Network_Stack/rf_transport.h"

/* faraday uart network stack*/
#include "UART/UART_L2.h"
#include "UART/UART_L4.h"

/* faraday application - telemetry */
#include "Applications/Telemetry/Telemetry.h"

/* faraday application - command */
#include "Applications/Command/command.h"
#include "Applications/Telemetry/Telem_RF.h"

/* faraday application - message */
#include "Applications/MSG/MSG.h"

/* faraday application - high altitude balloon */
#include "Applications/HAB/App_HAB.h"

#include "HAL/gps.h"

void main_housekeeping_routine(void){
	if(housekeeping_bitmask_char & BIT0){
		housekeeping_bitmask_char &= ~BIT0; //Disable general housekeeping bit
		//Check housekeeping functions
		check_housekeeping();

	}
}


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
	app_msg_housekeeping();

	if(housekeeping_bitmask_char & BIT1){
		housekeeping_bitmask_char &= ~BIT1; //Disable general housekeeping bit
		//1 second timer bit
		//Increment housekeeping timers
		housekeeping_timer_count_1hz++;
	}

//	if(CC430_Check_Transmitting_Flag()){
//		P3OUT |= LED_2;
//	}
//	else{
//		P3OUT &= ~LED_2;
//	}
}


void housekeeping_check_1hz(){
	if(housekeeping_timer_count_1hz >= HOUSEKEEPING_TIMER_COUNT_1HZ){
		// Clear housekeeping 1 second timer count
		housekeeping_timer_count_1hz=0;

		application_telemetry_uart_housekeeping_1hz_interval();
		app_telem_rf_housekeeping_interval();

		//HAB Application
		application_hab_housekeeping_interval();
		application_hab_cutdown_event_check_state();
	}
}
void housekeeping_setup(void){
	housekeeping_bitmask_char = 0;
	housekeeping_timer_count_1hz = 0;
}

