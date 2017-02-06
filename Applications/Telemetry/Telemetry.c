/** @file Telemetry.c
 * 	@brief Faraday telemetry application
 *
 * 	This application provides the telemetry data application functions for Faraday. Sensors and other
 * 	data are gathered, packetized, and transfered to the intended path for telemetry purposes.
 *
 */


#ifndef APPLICATIONS_APPLICATIONS_C_
#define APPLICATIONS_APPLICATIONS_C_

/* -- Includes -- */

/* standard includes */
#include "Telemetry.h"
#include "cc430f6137.h"
#include <time.h> //Needed?
#include <stdlib.h> // Needed?

/* faraday glocal variable includes */
#include "../../Faraday_Globals.h"

/* faraday hardware abstraction includes */
#include "../../Faraday_HAL/Faraday_HAL.h"
#include "../../HAL/gps.h"
#include "../../REVA_Faraday.h"
#include "../../Faraday_HAL/Misc_Functions.h"
#include "../../Faraday_HAL/flash.h"
#include "../../HAL/RF1A.h"
#include "../HAB/App_HAB.h"
#include "../../HAL/adc.h"

/* faraday rf network stack includes */
#include "../../RF_Network_Stack/rf.h"
#include "../../RF_Network_Stack/rf_transport.h"

/* fifo buffer includes */
#include "../../Ring_Buffers/FIFO_SRAM.h"

/* faraday uart network stack includes */
#include "../../UART/UART_Services.h"

/* device configuration application includes */
#include "../Device_Config/Device_Config.h"


/** @name Telemetry Application FIFO Variables
*
* 	These variables define the FIFO buffers to be used to enable the telemetry application
* 	functionality. 
*
*
@{**/
volatile fifo_sram_state_machine app_telem_uart_flow_buffer_state_machine; /**< FIFO buffer used to flow control the applications access to the UART network stack transmit FIFO */
volatile fifo_sram_state_machine app_telem_uart_state_machine; /**< FIFO buffer used to place telemetry application packets into the UART transmit FIFO buffer */
/** @}*/


//UART Beacon interval timer counter
volatile unsigned int telemetry_interval_counter_int = 0; /**< Telemetry application beacon interval counter in seconds */


void app_telem_housekeeping(void){
	/*
	 * Move APPLICATION packets into the APPLICATION UART FIFO
	 */
	if((app_telem_uart_flow_buffer_state_machine.inwaiting>0) && (app_telem_uart_state_machine.inwaiting == 0)){
		//Create temporary array to store packet from APPLICATION
		volatile unsigned char app_packet_buf[APP_TELEM_PACKET_LEN];

		//GET() APPLICATION packet from FIFO
		get_fifo_sram(&app_telem_uart_flow_buffer_state_machine, app_packet_buf);

		//PUT() APPLICATION packet into APPLICATION UART FIFO
		put_fifo_sram(&app_telem_uart_state_machine, app_packet_buf);
	}
	else{
		//Nothing in FIFO
	}

	/*
	 * Move APPLICATION UART FIFO packet(s) into the UART stack and transmit
	 */
	if(app_telem_uart_state_machine.inwaiting>0){
		//Create temporary array to store packet from APPLICATION
		unsigned char telem_tx_uart_buf[APP_TELEM_PACKET_LEN];

		//GET() APPLICATION packet from APPLICATION UART FIFO
		get_fifo_sram(&app_telem_uart_state_machine, &telem_tx_uart_buf);

		//Transmit APPLICATOIN UART FIFO packet into UART stack
		uart_send(TELEM_UART_SERVICE_NUMBER, APP_TELEM_PACKET_LEN, telem_tx_uart_buf);
	}
	else{
		//Nothing in FIFO
	}
}

void application_telem_create_pkt_1(unsigned char *packet){
	//Create temporary structs for packets
	TELEMETRY_PACKET_DATAGRAM_STRUCT telem_datagram;
	TELEMETRY_PACKET_1_STRUCT telem_pkt_1;

	//Fill telemetry packet payload with data
	telem_pkt_1.rf_freq2 = ReadSingleReg(FREQ2);
	telem_pkt_1.rf_freq1 = ReadSingleReg(FREQ1);
	telem_pkt_1.rf_freq0 = ReadSingleReg(FREQ0);
	telem_pkt_1.rf_pwr = ReadSingleReg(PATABLE);

	//Copy telemetry packet payload into telemetry datagram
	memcpy(&telem_datagram.data, &telem_pkt_1, 4);

	//Set datagram settings correctly for packet type #1
	telem_datagram.packet_type = 1;
	telem_datagram.rf_source = 0;
	telem_datagram.data_length = 4;

	//Error detection 16 bit calculation
	int_to_byte_array(&telem_datagram.error_detection_16, compute_checksum_16(9-2, &telem_datagram));

	//Copy full packet into pointer buffer
	unsigned char sizetelem = sizeof(telem_datagram);
	memcpy(&packet[0], &telem_datagram, sizetelem);
}


void application_telem_create_pkt_2(unsigned char *packet){
	//Create temporary structs for packets
	TELEMETRY_PACKET_DATAGRAM_STRUCT telem_datagram;

	//Copy device config memory into buffer
	memcpy(&telem_datagram.data, FLASH_MEM_ADR_INFO_C, APP_TELEM_PACKET_TYPE_2_LEN);


	unsigned char telem_packet_length = APP_TELEM_PACKET_TYPE_2_LEN;//sizeof(telem_packet_3_struct)-1; //-1 for end of struct character (off by one due to data alignmet in memory!)
	telem_datagram.packet_type = 2;
	telem_datagram.rf_source = 0;
	telem_datagram.data_length = APP_TELEM_PACKET_TYPE_2_LEN;

	//Error detection 16 bit calculation
	int_to_byte_array(&telem_datagram.error_detection_16, compute_checksum_16(APP_TELEM_PACKET_LEN-2, &telem_datagram));

	//Copy full packet into pointer buffer
	unsigned char sizetelem = sizeof(telem_datagram);
	memcpy(&packet[0], &telem_datagram, sizetelem);
}


void application_telem_create_rf_pkt(unsigned char *packet, char *src_callsign, unsigned char src_callsign_len, unsigned char src_callsign_id, char *dest_callsign, unsigned char dest_callsign_len, unsigned char dest_callsign_id){
	//Create temporary structs for packets
		TELEMETRYDATA telem;
		TELEMETRY_PACKET_DATAGRAM_STRUCT telem_datagram;
		TELEMETRY_PACKET_3_STRUCT telem_packet_3_struct;

		if(src_callsign_len < 10){
			memcpy(telem_packet_3_struct.source_callsign,(char *)src_callsign, src_callsign_len);
			telem_packet_3_struct.source_callsign_length = src_callsign_len;
			telem_packet_3_struct.source_callsign_id = src_callsign_id;
		}else{
			_no_operation();
		}

		if(dest_callsign_len < 10){
			memcpy(telem_packet_3_struct.destination_callsign,(char *)dest_callsign, dest_callsign_len);
			telem_packet_3_struct.destination_callsign_length = dest_callsign_len;
			telem_packet_3_struct.destination_callsign_id = dest_callsign_id;
		}else{
			_no_operation();
		}

		// Obtains safely read time from RTCRDYIFG interrupt structure
		telem_packet_3_struct.rtc_second = RTC.second;
		telem_packet_3_struct.rtc_minute = RTC.minute;
		telem_packet_3_struct.rtc_hour = RTC.hour;
		telem_packet_3_struct.rtc_day = RTC.day;
		telem_packet_3_struct.rtc_dow = RTC.dow;
		telem_packet_3_struct.rtc_month = RTC.month;
		telem_packet_3_struct.rtc_year = RTC.year;

		//Obtain GPS information
		if(check_bitmask(gps_boot_bitmask, GPS_PRESENT_BIT)){
			//GPS is present per FLASH configuration
			memcpy(&telem_packet_3_struct.gps_lattitude,(char *)GGA.Lat,9);
			memcpy(&telem_packet_3_struct.gps_lattitude_dir,(char *)GGA.Lat_Dir,1);
			memcpy(&telem_packet_3_struct.gps_longitude,(char *)GGA.Long,10);
			memcpy(&telem_packet_3_struct.gps_longitude_dir,(char *)GGA.Long_Dir,1);
			memcpy(&telem_packet_3_struct.gps_altitude,(char *)GGA.Altitude,8);
			memcpy(&telem_packet_3_struct.gps_altitude_units,(char *)GGA.Alt_Units,1);
			memcpy(&telem_packet_3_struct.gps_speed,(char *)RMC.Speed,5);
			memcpy(&telem_packet_3_struct.gps_fix,(char *)GGA.Fix_Quality,1);
			memcpy(&telem_packet_3_struct.gps_hdop,(char *)GGA.HDOP,4);
		}
		else{
			//GPS is NOT present per FLASH configuration
			memcpy(&telem_packet_3_struct.gps_lattitude,(char *)default_lattitde,9);
			memcpy(&telem_packet_3_struct.gps_lattitude_dir,(char *)&default_lattitude_dir,1);
			memcpy(&telem_packet_3_struct.gps_longitude,(char *)default_longitude,10);
			memcpy(&telem_packet_3_struct.gps_longitude_dir,(char *)&default_longitude_dir,1);
			memcpy(&telem_packet_3_struct.gps_altitude,(char *)default_altitude,8);
			memcpy(&telem_packet_3_struct.gps_altitude_units,(char *)&default_altitude_units,1);
			unsigned char speed[5] = {0,0,0,0,0};
			memcpy(&telem_packet_3_struct.gps_speed,speed,5);
			unsigned char fix_quality[1] = {30}; //30 is ASCII '0' which matches a GPS NO FIX
			memcpy(&telem_packet_3_struct.gps_fix,(char *)&fix_quality,1);
			unsigned char hdop[4] = {0,0,0,0};
			memcpy(&telem_packet_3_struct.gps_hdop,(char *)hdop,4);
		}


		//GPIO and System State
		telem.IO_State	= 0x00;
		telem.IO_State 	|= (P5IN & ARDUINO_IO_8) << 5;		// Grab IO 8 and shift left 5 to put into BIT 8 of IO_State
		telem.IO_State 	|= (P5IN & ARDUINO_IO_9) << 3;		// Grab IO 9 and shift left 3 to put into BIT 7 of IO_State
		telem.IO_State	|= (P5IN & MOSFET_CNTL) << 1;		// Grab MOSFET CNTL value and shift left 1 bit to put into BIT 6 of IO_State
		telem.IO_State	|= (P3IN & LED_1) >> 2;				// Grab LED_1 value and shift right 2 bits to put into BIT 5 of IO_State
		telem.IO_State	|= (P3IN & LED_2) >> 4;				// Grab LED_2 value and shift right 4 bits to put into BIT 4 of IO_State
		telem.IO_State	|= (P3IN & GPS_RESET) >> 1;			// Grab GPS_RESET value and shift right 1 bits to put into BIT 3 of IO_State
		telem.IO_State	|= (P3IN & GPS_STANDBY) >> 3;		// Grab GPS_STANDBY value and shift right 3 bits to put into BIT 2 of IO_State
		telem.IO_State	|= (P1IN & BUTTON_1) >> 7;			// Grab BUTTON_1 value and shift right 7 bits to put into BIT 1 of IO_State

		telem.RF_State	= 0x00;
		telem.RF_State	|= (P3IN & PA_ENABLE) << 7;			// Grab PA_ENABLE value and shift left 7 bits to put into BIT 8 of RF_State
		telem.RF_State	|= (P3IN & LNA_ENABLE) << 5;		// Grab LNA_ENABLE value and shift left 5 bits to put into BIT 7 of RF_State
		telem.RF_State	|= (P3IN & HGM_SELECT) << 3;		// Grab HGM_SELECT value and shift left 3 bits to put into BIT 6 of RF_State

		telem_packet_3_struct.gpio_state = P4IN;
		telem_packet_3_struct.io_state = telem.IO_State;
		telem_packet_3_struct.rf_state = telem.RF_State;

		//ADC Data
		int_to_byte_array(&telem_packet_3_struct.adc_0, ADC_Data[0]);
		int_to_byte_array(&telem_packet_3_struct.adc_1, ADC_Data[1]);
		int_to_byte_array(&telem_packet_3_struct.adc_2, ADC_Data[2]);
		int_to_byte_array(&telem_packet_3_struct.adc_3, ADC_Data[3]);
		int_to_byte_array(&telem_packet_3_struct.adc_4, ADC_Data[4]);
		int_to_byte_array(&telem_packet_3_struct.adc_5, ADC_Data[5]);
		int_to_byte_array(&telem_packet_3_struct.adc_6, ADC_Data[6]);
		int_to_byte_array(&telem_packet_3_struct.adc_7, adc_corrected_calibration_temp_C_int(ADC_Data[7]));
		int_to_byte_array(&telem_packet_3_struct.adc_8, ADC_Data[8]);



		unsigned char telem_packet_length = APP_TELEM_PACKET_TYPE_3_LEN;//sizeof(telem_packet_3_struct)-1; //-1 for end of struct character (off by one due to data alignmet in memory!)
		telem_datagram.packet_type = 3;
		telem_datagram.rf_source = 0;
		telem_datagram.data_length = telem_packet_length;

		//TEMPORARY HAB APPLICATION DATA
		//unsigned char uChar_HAB_Data[7];
		unsigned char uChar_HAB_Packet_Status;
		uChar_HAB_Packet_Status = application_hab_create_telem_3_pkt(&telem_packet_3_struct.HAB_DATA);

		//Copy packet Type 1 into packet datagram
		memcpy(&telem_datagram.data, &telem_packet_3_struct,telem_packet_length);

		//Error detection 16 bit calculation
		int_to_byte_array(&telem_datagram.error_detection_16, compute_checksum_16(APP_TELEM_PACKET_LEN-2, &telem_datagram));

		//Copy full packet into pointer buffer
		volatile unsigned char sizetelem = sizeof(telem_datagram);
		memcpy(&packet[0], &telem_datagram, sizetelem);
}

void application_send_telemetry_packet_1(void){
	unsigned char telem_packet_buffer[123]; //It is very important that this is the correct size, if too small the buffer write will overflow and be upredicatable to system performance
	application_telem_create_pkt_1(telem_packet_buffer);
	application_send_uart_packet(&telem_packet_buffer);
}

void application_send_telemetry_device_debug(void){
	unsigned char telem_packet_buffer[123]; //It is very important that this is the correct size, if too small the buffer write will overflow and be upredicatable to system performance
	application_telem_create_pkt_2(telem_packet_buffer);
	application_send_uart_packet(&telem_packet_buffer);
}

void application_send_telemetry_3(void){
	unsigned char telem_packet_buffer[123]; //It is very important that this is the correct size, if too small the buffer write will overflow and be upredicatable to system performance
	application_telem_create_rf_pkt(telem_packet_buffer, local_callsign, local_callsign_len, local_device_id, local_callsign, local_callsign_len, local_device_id);
	application_send_uart_packet(&telem_packet_buffer);
}


void application_update_RTC_calender_gps(void){

	char buff[2];
	int year,month,day,hour,min,sec;

	memcpy(buff,(const char*)RMC.Date + 4 * CHARSIZE, 2 * CHARSIZE);
	year = 2000 + atoi(buff);
	RTCYEAR = year;
	memcpy(buff,(const char*)RMC.Date + 2 * CHARSIZE, 2 * CHARSIZE);
	month = atoi(buff);
	RTCMON = month;
	memcpy(buff,(const char*)RMC.Date, 2 * CHARSIZE);
	day = atoi(buff);
	RTCDAY = day;
	memcpy(buff,(const char*)GGA.Time, 2 * CHARSIZE);
	hour = atoi(buff);
	RTCHOUR = hour;
	memcpy(buff,(const char*)GGA.Time + 2 * CHARSIZE, 2 * CHARSIZE);
	min = atoi(buff);
	RTCMIN = min;
	memcpy(buff,(const char*)GGA.Time + 4 * CHARSIZE, 2 * CHARSIZE);
	sec = atoi(buff);
	RTCSEC = sec;

	struct tm timeinfo;

	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = day;
	timeinfo.tm_hour = hour;
	timeinfo.tm_min = min;
	timeinfo.tm_sec = sec;
	timeinfo.tm_isdst = -1;
	mktime(&timeinfo);

	RTCDOW = timeinfo.tm_wday;
}


void application_telemetry_initialize(void){
	//initialize FIFO's
	init_app_telem_fifo();
}


void init_app_telem_fifo(void){
	fifo_sram_init(&app_telem_uart_flow_buffer_state_machine, 0, APP_TELEM_PACKET_LEN, APP_TELEM_PACKET_FIFO_COUNT);
	fifo_sram_init(&app_telem_uart_state_machine, 126, APP_TELEM_PACKET_LEN, 1);
}


void application_send_uart_packet(unsigned char *packet){
	put_fifo_sram(&app_telem_uart_flow_buffer_state_machine, packet);
}


void application_telemetry_send_self(void){
	application_send_telemetry_3();
}


void application_telemetry_send_device_debug_telem(void){
	application_send_telemetry_device_debug();
}


void application_telemetry_uart_housekeeping_1hz_interval(void){
	//Check if bitmask allows UART telemetry OR if telemetry interval == 0 (if 0 then disable telemetry UART actions)
	if(check_bitmask(telem_boot_bitmask,UART_BEACON_BOOT_ENABLE) && (telem_default_uart_interval != 0)){

		//Check if interval counter reached
		if((telemetry_interval_counter_int>=telem_default_uart_interval) || (telem_default_uart_interval == 1)){
			//Reset counter
			telemetry_interval_counter_int = 0;

			//send uart local telemetry
			application_telemetry_send_self();
		}
		else{
			telemetry_interval_counter_int++;
		}
	}

	else{
		//Nothing
	}

}

#endif /* APPLICATIONS_APPLICATIONS_C_ */
