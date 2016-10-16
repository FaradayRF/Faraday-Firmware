/** @file housekeeping.h
 *  @brief General Faraday housekeeping routines
 *
 *  These functions provide basic "housekeeping" functions that
 *  allow the gathering, processing, and general use of data input
 *  and output to operate.
 *
 */


#ifndef HOUSEKEEPING_H_
#define HOUSEKEEPING_H_

/** @name Housekeeping Timing Definitions
* 	@brief Definitions for the timing of the housekeeping loop routines.
@{**/
#define HOUSEKEEPING_TIMER_COUNT_5HZ 101		// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_1HZ 4		// Timer A0 ACLK = 32.768KHz with CCR1 8192 = 4Hz = 250ms/clock
#define HOUSEKEEPING_TIMER_COUNT_60SEC 30303	// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_10SEC 5051		// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_5SEC 2525		// Timer A0 ACLK = 32.768KHz = 1.98ms
/** @}*/


/** @name Create housekeeping bitmask
* 	@brief Bitmasks that control the housekeeping function(s)
@{**/
unsigned char housekeeping_bitmask_char; /**< housekeeping bitmask that contains configuration and status information*/
unsigned int housekeeping_timer_count_1hz; /**< cycle count that prescales the housekeeping timer RAW to count 1hz*/


/**@brief Main Housekeeping Routine
 *
 *	This routine is the main loop that is performed during each cycle. From
 *	this routine all housekeeping sub-tasks and sub-housekeeping routines
 *	are performed.
 *
 *
 */
void main_housekeeping_routine(void);


/**@brief Housekeeping Setup
 *
 *	Initialization of the housekeeping variables
 *
 */
void housekeeping_setup(void);


/**@brief Check Housekeeping
 *
 *	This function is the high level housekeeping function that is run to perform
 *  a housekeeping "check" operation during each housekeeping cycle. This should be kept
 *  clean by using function calls to more specific housekeeping sub-routine checks. Actions
 *  that need to be performed during each cycle or higher level checks (i.e. 1hz) are to be
 *
 */
void check_housekeeping(void);


/**@brief Housekeeping Raw Routine
 *
 *	This routine is the fastest housekeeping routine that is acted on
 *	during every housekeeping cycle.
 *
 */
void housekeeping_check_raw(void);


/**@brief Housekeeping 1hz
 *
 *	This routine is operated once after each second. The RAW routine increaments a
 *	counter that counts and initiates the 1hz routine.
 *
 */
void housekeeping_check_1hz(void);


/**@brief Housekeeping Routine - UART
 *
 *	This is a function that holds the routine/function calls that are
 *	to be operated on a regular basis. This contains checking for new
 *	data to be transmitted/received.
 *
 */
void housekeeping_routine_UART(void);


/**@brief Housekeeping Routine - Applications
 *
 *	This is a function that holds the routine/function calls that are
 *	to be operated on a regular basis for Faraday applications.
 *
 */
void housekeeping_routine_applications(void);

#endif /* HOUSEKEEPING_H_ */
