/** @file App_HAB.h
 * 	@brief Function prototypes for the HAB application.
 *
 * 	This contains the functions, statemachines, and definitions
 * 	that allow the HAB program to operate. The functionality
 * 	provided include:
 *
 * 	- Automatic timed cutdown event
 * 	- Time controlled "Cutdown" event
 *
 * 	@bug application_hab_create_telem_3_pkt() function doesn't actually return anything!
 *
 */

#ifndef APPLICATIONS_HAB_APP_HAB_H_
#define APPLICATIONS_HAB_APP_HAB_H_

/** @name Automatic Cutdown Event State Machine Definitions
* 	@brief Definitions for the state machine based function that performs automatic timed based cutdown of a HAB used the Faraday MOSFET as control.
@{**/
#define HAB_AUTO_CUTDOWN_STATE_0 0 /**< Idle*/
#define HAB_AUTO_CUTDOWN_STATE_1 1 /**< Start Timer */
#define HAB_AUTO_CUTDOWN_STATE_2 2 /**< Active Count*/
#define HAB_AUTO_CUTDOWN_STATE_3 3 /**< Cutdown Action*/
#define HAB_CUTDOWN_TIMER_COUNT_SECONDS 7200 /**< Cutdown timer in seconds to trigger automatic cutdown. (7200 Seconds is 2 hours) */
/** @}*/


/** @brief Automatic HAB cutdown event state machine structure
 *
 * A structure to hold all the state machine variables needed to perform an automatically
 * timed cutdown event for safety to avoid a "floating" payload.
 *
 */
typedef struct HAB_AUTO_CUTDOWN_TIMER_SM {
	unsigned char uChar_state; /**< current state.*/
	unsigned int uInt_app_hab_timer; /**< current timer value in seconds.*/
} HAB_AUTO_CUTDOWN_TIMER_SM_STRUCT;


/** @name Cutdown Action Event State Machine Definitions
* 	@brief Definitions for the state machine based function that controls the actual cutdown event sequence and timing.
@{**/
#define HAB_CUTDOWN_EVENT_STATE_0 0 /**< Idle*/
#define HAB_CUTDOWN_EVENT_STATE_1 1 /**< Start Timer*/
#define HAB_CUTDOWN_EVENT_STATE_2 2 /**< Iterate cutdown actions duration*/
#define HAB_CUTDOWN_EVENT_STATE_3 3 /**< Post cutdown actions*/
#define HAB_CUTDOWN_EVENT_STATE_255 255 /**< Post cutdown IDLE (Indicates HAS FIRED)*/
#define HAB_CUTDOWN_EVENT_TIMER_COUNT_SECONDS 5 /**< Duration of active cutdown in seconds*/
/** @}*/


/** @brief Cutdown Action Event State Machine structure
 *
 * A structure to hold all the state machine variables needed to perform a controlled
 * cutdown event that has predefined actions and timing.
 *
 */
typedef struct HAB_CUTDOWN_EVENT_TIMER_SM {
	unsigned char uChar_state;
	unsigned int uInt_app_hab_timer;
} HAB_CUTDOWN_EVENT_TIMER_SM_STRUCT;

/** @brief A packet structure that contains information about the HAB programs for inclusion into the telemetry stream(s)
 *
 * HAB application telemetry data structure. This packet contains:
 * - Automatic cutdown timer state
 * - Current cutdown (active) event state
 * - Automatic timed cutdown trigger count (seconds)
 * - Current automatic timed cutdown count (seconds)
 */
typedef struct HAB_TELEMETRY_PACKET {
	unsigned char uChar_auto_cutdown_timer_state_status;
	unsigned char uChar_cutdown_event_state_status;
	unsigned char uInt_timer_set[2];
	unsigned char uInt_timer_current[2];
} HAB_TELEMETRY_PACKET_STRUCT;


/**@brief HAB application housekeeping actions routine
 *
 * This function defines the actions that need to be perfomed or states checked
 * during each housekeeping cycle. This is the main function that allows for
 * continuously updating timers/states/etc...
 *
 * @warning This function expects a 1 second housekeeping cycle!
 *
 */
void application_hab_housekeeping_interval(void);

//Auto-Cutdown
/**@brief Automatic timed cutdown state machine state update function
 *
 * This function is used to update the current state of the automatic
 * timed cutdown sequence state machine. The possible states are predefined.
 *
 * \b States
 * - 0 = IDLE
 * - 1 = Start Timer
 * - 2 = Active Counting
 * - 3 = Cutdown Active
 *
 * @param state The state the update the state machine to.
 *
 */
void application_hab_auto_timer_set_state(unsigned char state);

/**@brief Check automatic timed cutdown state state and perform defined actions
 *
 * This function is used to perform the predefined actions for a given state. This
 * check should be performed during each housekeeping function and the defined actions
 * are performed once per cycle.
 */
void application_hab_auto_timer_check_state(void);

/**@brief Pre-defined actions for automatic timed cutdown state 0
 *
 * Actions to be performed each cycle of the state 0 (IDLE)
 *
 */
void application_hab_auto_timer_state_0(void);

/**@brief Pre-defined actions for automatic timed cutdown state 1
 *
 * Actions to be performed each cycle of the state 1 (Start Timer)
 *
 * - Start the timer
 * - Initialize any variables needing initialization
 *
 */
void application_hab_auto_timer_state_1(void);

/**@brief Pre-defined actions for automatic timed cutdown state 2
 *
 * Actions to be performed each cycle of the state 2 (Active Count)
 *
 * - Increment counter(s)
 *
 */
void application_hab_auto_timer_state_2(void);

/**@brief Pre-defined actions for automatic timed cutdown state 3
 *
 * Actions to be performed each cycle of the state 3 (Cutdown Active)
 *
 * - Initiate cutdown action
 *
 */
void application_hab_auto_timer_state_3(void);

//Cutdown Event
/**@brief Cutdown event state machine state update function
 *
 * This function is used to update the current state of the timed cutdown
 * event sequence state machine. This state machine controls the ACTUAL cutdown
 * actions, timing, and sequence.
 *
 * \attention The purpose of two seperate IDLE states is to indicate the
 * 		occurance of a prior cutdown in the event of telemetry loss during
 * 		the cutdown event itself.
 *
 * The possible states are predefined:
 *
 * \b States
 * - 0 = IDLE
 * - 1 = Start Timer
 * - 2 = Cutdown Actions
 * - 3 = Post Cutdown
 * - 255 = POST Cutdown IDLE
 *
 * @param state The state the update the state machine to.
 *
 */
void application_hab_cutdown_event_set_state(unsigned char state);

/**@brief Check the cutdown event state and perform defined actions
 *
 * This function is used to perform the predefined actions for a given state. This
 * check should be performed during each housekeeping function and the defined actions
 * are performed once per cycle.
 */
void application_hab_cutdown_event_check_state(void);

/**@brief Pre-defined actions for automatic timed cutdown state 0
 *
 * Actions to be performed each cycle of the state 0 (IDLE)
 *
 */
void application_hab_cutdown_event_state_0(void);

/**@brief Pre-defined actions for automatic timed cutdown state 1
 *
 * Actions to be performed each cycle of the state 1 (Start Timer)
 *
 * \note This IDLE state should only be used after a reset of the device or manual commanding
 * 		to IDLE 0 as to ensure knowledge of cutdown event occuring if telemetry is lost.
 *
 */
void application_hab_cutdown_event_state_1(void);

/**@brief Pre-defined actions for automatic timed cutdown state 2
 *
 * Actions to be performed each cycle of the state 2 (Cutdown Actions)
 *
 * - Perform actions needed to cutdown the HAB payload
 *
 */
void application_hab_cutdown_event_state_2(void);

/**@brief Pre-defined actions for automatic timed cutdown state 3
 *
 * Actions to be performed each cycle of the state 3 (Post Cutdown)
 *
 * - Safe the HAB cutdown system
 *
 */
void application_hab_cutdown_event_state_3(void);

/**@brief Pre-defined actions for automatic timed cutdown state 255
 *
 * Actions to be performed each cycle of the state 255 (Post Cutdown IDLE)
 *
 * - Wait in IDLE until commanded to execute cutdown again
 *
 */
void application_hab_cutdown_event_state_255(void);

/**@brief Gather information about the HAB functions for telemetry
 *
 * This function creates a string of bytes (data packet) for inclusion in Faraday telemetry
 * to broadcast the current HAB system status.
 *
 * @param packet Pointer to char array to save packet data too
 *
 * \note The char array that is pointed to should be the same size as the packet structure in bytes.
 *
 * @return Nothing
 */
unsigned char application_hab_create_telem_3_pkt(unsigned char *packet);



#endif /* APPLICATIONS_HAB_APP_HAB_H_ */
