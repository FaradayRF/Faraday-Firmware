/*
 * gps.h
 *
 *  Created on: Nov 8, 2015
 *      Author: Brent
 */

#ifndef HAL_GPS_H_
#define HAL_GPS_H_
/*
 *
 * Declare GPS structs
 */

typedef struct GPS_string {
	/*
	 * GPS String Flags
	 * BIT0 = nmea string flag
	 * BIT1 = CRC valid flag
	 */
	unsigned char string[80];
	char byte_cnt;
	char flags; //byte for bit flags
	unsigned char crc;
	unsigned char nmea_crc[2];
	unsigned char *calc_crc;
	unsigned int crc_cnt;
	unsigned char *nmea_crc_val;
	unsigned char GPSFixValid;
}GPSNMEA;

typedef struct GGA_Data {
	char Sync[5];
	char Time[10];
	char Lat[9];
	char Lat_Dir[1];
	char Long[10];
	char Long_Dir[1];
	char Fix_Quality[1];
	char Satellites[2];
	char HDOP[4];
	char Altitude[8]; // allows for 99999.99 meters
	char Alt_Units[1];
	char Geod_Sep[8]; // allows for 99999.99 meters
	char Geod_Units[1];
	char DGPS_Time[5];
	char DGPS_Station[4]; //Was 3 moved to 4 due to causing buffer overflow
	//char Checksum[3];
} GPSGGA;

typedef struct RMC_Data {
	char Sync[5];
	char Time[10];
	char Status[1];
	char Lat[9];
	char Lat_Dir[1];
	char Long[10];
	char Long_Dir[1];
	char Speed[5];
	char Course[5];
	char Date[6];
	char Magnetic[5];
	char Mag_Dir[1];
	char Mode[1];
	char Checksum[2];
} GPSRMC;

/* Make GPS structs */
volatile GPSGGA GGA;
volatile GPSRMC RMC;
volatile GPSNMEA NMEA;

/* Declare GPS functions */
void initialize_GPS_structs(void);
void gps_get_nmea_string(volatile unsigned char *byte);
//void Save_GPS_string(volatile unsigned char *string);
void Save_GPS_string_2(volatile unsigned char *string);
void Parse_GGA(volatile unsigned char *string);
void Parse_RMC(volatile unsigned char *string);

#endif /* FARADAY_REVA_RF_MERGE_HAL_GPS_H_ */
