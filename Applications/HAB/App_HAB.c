/** @file App_HAB.c
 *  @brief High altitude balloon program(s) for Faraday
 *
 *  These functions provide basic support to use Faraday
 *  as a platform for high altitude balloon (HAB) telemetry,
 *  commanding, and computing.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "App_HAB.h"

/* faraday hardware allocations */
#include "../../REVA_Faraday.h"

/** @name State Machine Structure Variables
* 	@brief structures that contain the needed members that operate the state machine operations
*
* 	These structures are global and allow the high altitude balloon state machine functionality.
*
*
@{**/
volatile HAB_AUTO_CUTDOWN_TIMER_SM_STRUCT struct_hab_auto_cutdown_state; /**< High altitude balloon application automatic timer cutdown state machine structure */
volatile HAB_CUTDOWN_EVENT_TIMER_SM_STRUCT struct_hab_cutdown_event_state; /**< High altitude balloon application cutdown event state machine strucuture */
/** @}*/

void application_hab_housekeeping_interval(void){
	//Auto-cutdown timer
	application_hab_auto_timer_check_state();
}


void application_hab_auto_timer_set_state(unsigned char state){
	struct_hab_auto_cutdown_state.uChar_state = state;
}


void application_hab_auto_timer_check_state(void){
	switch(struct_hab_auto_cutdown_state.uChar_state){
	case 0:
		//State 0 - IDLE
		application_hab_auto_timer_state_0();
		break;

	case 1:
		//State 1 - Set Timer
		application_hab_auto_timer_state_1();
		break;

	case 2:
		//State 2 - Count
		application_hab_auto_timer_state_2();
		break;

	case 3:
		//State 3 - Initiate Cutdown
		application_hab_auto_timer_state_3();
		break;
	}
}


void application_hab_auto_timer_state_0(void){
	//Idle
	__no_operation(); //Trap here until code or command sets the state to start timer
}


void application_hab_auto_timer_state_1(void){
	//Start timer
	struct_hab_auto_cutdown_state.uInt_app_hab_timer = 0;
	//Set state to increment timer
	application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_2);
}


void application_hab_auto_timer_state_2(void){
	//Increment timer
	if(struct_hab_auto_cutdown_state.uInt_app_hab_timer >= HAB_CUTDOWN_TIMER_COUNT_SECONDS){
		//Set state to cutdown
		application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_3);
	}
	else{
		//Increment timer
		struct_hab_auto_cutdown_state.uInt_app_hab_timer++;
	}
}


void application_hab_auto_timer_state_3(void){
	//Cutdown event
	//Active cutdown event action state machine
	application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_1);

	//Reset state to IDLE
	application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_0);
}


void application_hab_cutdown_event_set_state(unsigned char state){
	struct_hab_cutdown_event_state.uChar_state = state;
}


void application_hab_cutdown_event_check_state(void){
	__no_operation();
	switch(struct_hab_cutdown_event_state.uChar_state){
	case 0:
		//State 0 - IDLE
		application_hab_cutdown_event_state_0();
		break;

	case 1:
		//State 1 - Set Timer
		application_hab_cutdown_event_state_1();
		break;

	case 2:
		//State 2 - Perform iteration of cutdown actions
		application_hab_cutdown_event_state_2();
		break;

	case 3:
		//State 3 - Post cutdown actions
		application_hab_cutdown_event_state_3();
		break;

	}
}


void application_hab_cutdown_event_state_0(void){
	//Idle trap until commanded
	//Continuously assert MOSFET OFF
	P5OUT &= ~MOSFET_CNTL;
}


void application_hab_cutdown_event_state_1(void){
	//Reset Timer
	struct_hab_cutdown_event_state.uInt_app_hab_timer = 0;

	//Set state cutdown actions
	application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_2);
}


void application_hab_cutdown_event_state_2(void){
	//Cutdown action iterations
	if(struct_hab_cutdown_event_state.uInt_app_hab_timer >= HAB_CUTDOWN_EVENT_TIMER_COUNT_SECONDS){
		//Perform imediate cutdown END actions
		P5OUT &= ~MOSFET_CNTL;

		//Set state to post cutdown
		application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_3);
	}
	else{
		//gpio_update(5, MOSFET_CNTL, 1); //FIRE MOSFET
		P5OUT |= MOSFET_CNTL;
		struct_hab_cutdown_event_state.uInt_app_hab_timer++;
	}
}


void application_hab_cutdown_event_state_3(void){
	//Post cutdown actions
	//Try turning MOSFET OFF again, just because.
	P5OUT &= ~MOSFET_CNTL;

	//Cancel current auto-cutdown timer (this avoids firing cutdown burn after commanded cutdown to avoid damage/fire)
	application_hab_auto_timer_set_state(HAB_AUTO_CUTDOWN_STATE_0); //Set auto-timer to IDLE to stop active auto-cutdown. Can be reset if needed.

	//Set state to IDLE
	application_hab_cutdown_event_set_state(HAB_CUTDOWN_EVENT_STATE_255);
}


void application_hab_cutdown_event_state_255(void){
	//This is an IDLE for post cutdown to show in telemetry the HAS FIRED state
	//Idle trap until commanded
	__no_operation();
}


unsigned char application_hab_create_telem_3_pkt(unsigned char *packet){
	//Create temporary structs for packets
	volatile HAB_TELEMETRY_PACKET_STRUCT struct_telem_pkt;

	//Clear old data

	struct_telem_pkt.uChar_auto_cutdown_timer_state_status = struct_hab_auto_cutdown_state.uChar_state;
	struct_telem_pkt.uChar_cutdown_event_state_status = struct_hab_cutdown_event_state.uChar_state;
	int_to_byte_array(&struct_telem_pkt.uInt_timer_current, struct_hab_auto_cutdown_state.uInt_app_hab_timer);
	int_to_byte_array(&struct_telem_pkt.uInt_timer_set, HAB_CUTDOWN_TIMER_COUNT_SECONDS);

	//Copy full packet into pointer buffer
	unsigned char sizetelem = sizeof(struct_telem_pkt);
	memcpy(&packet[0], &struct_telem_pkt, sizetelem);
}
