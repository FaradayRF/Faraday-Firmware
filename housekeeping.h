/*
 * housekeeping.h
 *
 *  Created on: Aug 5, 2015
 *      Author: Brent
 */

#ifndef HOUSEKEEPING_H_
#define HOUSEKEEPING_H_


#define HOUSEKEEPING_TIMER_COUNT_5HZ 101		// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_1HZ 4		// Timer A0 ACLK = 32.768KHz with CCR1 8192 = 4Hz = 250ms/clock
#define HOUSEKEEPING_TIMER_COUNT_60SEC 30303	// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_10SEC 5051		// Timer A0 ACLK = 32.768KHz = 1.98ms
#define HOUSEKEEPING_TIMER_COUNT_5SEC 2525		// Timer A0 ACLK = 32.768KHz = 1.98ms




//Create housekeeping bitmask
unsigned char housekeeping_bitmask_char;
unsigned int housekeeping_timer_count_5hz;
unsigned int housekeeping_timer_count_1hz;
unsigned int housekeeping_timer_count_60sec;
unsigned int housekeeping_timer_count_10sec;
unsigned int housekeeping_timer_count_5sec;

void main_housekeeping_routine(void);
void housekeeping_setup(void);
void check_housekeeping(void);
void housekeeping_check_raw();
void housekeeping_check_5hz();
void housekeeping_check_1hz();
void housekeeping_check_5sec();
void housekeeping_check_10sec();
void housekeeping_check_60sec();
void housekeeping_routine_UART(void);
void housekeeping_routine_applications(void);





#endif /* HOUSEKEEPING_H_ */
