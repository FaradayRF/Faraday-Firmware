#ifndef APPLICATIONS_HAB_APP_HAB_H_
#define APPLICATIONS_HAB_APP_HAB_H_

#define HAB_AUTO_CUTDOWN_STATE_0 0 //Idle
#define HAB_AUTO_CUTDOWN_STATE_1 1 //Start Timer
#define HAB_AUTO_CUTDOWN_STATE_2 2 //Count
#define HAB_AUTO_CUTDOWN_STATE_3 3 //Cutdown Action

#define HAB_CUTDOWN_TIMER_COUNT_SECONDS 7200 //Cutdown timer in seconds to trigger automatic MO // 7200 Seconds is 2 hours

typedef struct HAB_AUTO_CUTDOWN_TIMER_SM {
	unsigned char uChar_state;
	unsigned int uInt_app_hab_timer;
} HAB_AUTO_CUTDOWN_TIMER_SM_STRUCT;


#define HAB_CUTDOWN_EVENT_STATE_0 0 //Idle
#define HAB_CUTDOWN_EVENT_STATE_1 1 //Start Timer
#define HAB_CUTDOWN_EVENT_STATE_2 2 //Iterate cutdown actions duration
#define HAB_CUTDOWN_EVENT_STATE_3 3 //Post cutdown actions
#define HAB_CUTDOWN_EVENT_STATE_255 255 //Post cutdown IDLE (Indicates HAS FIRED)

#define HAB_CUTDOWN_EVENT_TIMER_COUNT_SECONDS 5 //Cutdown timer in seconds to trigger automatic MO


typedef struct HAB_CUTDOWN_EVENT_TIMER_SM {
	unsigned char uChar_state;
	unsigned int uInt_app_hab_timer;
} HAB_CUTDOWN_EVENT_TIMER_SM_STRUCT;

typedef struct HAB_TELEMETRY_PACKET {
	unsigned char uChar_auto_cutdown_timer_state_status;
	unsigned char uChar_cutdown_event_state_status;
	unsigned char uInt_timer_set[2];
	unsigned char uInt_timer_current[2];
} HAB_TELEMETRY_PACKET_STRUCT;

void application_hab_housekeeping_interval(void);

//Auto-Cutdown
void application_hab_auto_timer_set_state(unsigned char state);
void application_hab_auto_timer_check_state(void);
void application_hab_auto_timer_state_0(void);
void application_hab_auto_timer_state_1(void);
void application_hab_auto_timer_state_2(void);
void application_hab_auto_timer_state_3(void);

//Cutdown Event
void application_hab_cutdown_event_set_state(unsigned char state);
void application_hab_cutdown_event_check_state(void);
void application_hab_cutdown_event_state_0(void);
void application_hab_cutdown_event_state_1(void);
void application_hab_cutdown_event_state_2(void);
void application_hab_cutdown_event_state_3(void);
void application_hab_cutdown_event_state_255(void);
unsigned char application_hab_create_telem_3_pkt(unsigned char *packet);



#endif /* APPLICATIONS_HAB_APP_HAB_H_ */
