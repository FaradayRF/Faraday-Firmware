#include "gps.h"
#include <string.h>
#include <stdio.h>
#include <msp430.h>

void initialize_GPS_structs(void){

	memset((void *)GGA.Sync,'0',sizeof(GGA.Sync));
	memset((void *)GGA.Time,'0',sizeof(GGA.Time));
	memset((void *)GGA.Lat,'0',sizeof(GGA.Lat));
	memset((void *)GGA.Lat_Dir,'0',sizeof(GGA.Lat_Dir));
	memset((void *)GGA.Long,'0',sizeof(GGA.Long));
	memset((void *)GGA.Long_Dir,'0',sizeof(GGA.Long_Dir));
	memset((void *)GGA.Fix_Quality,'0',sizeof(GGA.Fix_Quality));
	memset((void *)GGA.Satellites,'0',sizeof(GGA.Satellites));
	memset((void *)GGA.HDOP,'0',sizeof(GGA.HDOP));
	memset((void *)GGA.Altitude,'0',sizeof(GGA.Altitude));
	memset((void *)GGA.Alt_Units,'0',sizeof(GGA.Alt_Units));
	memset((void *)GGA.Geod_Sep,'0',sizeof(GGA.Geod_Sep));
	memset((void *)GGA.Geod_Units,'0',sizeof(GGA.Geod_Units));
	memset((void *)GGA.DGPS_Time,'0',sizeof(GGA.DGPS_Time));
	memset((void *)GGA.DGPS_Station,'0',sizeof(GGA.DGPS_Station));

	memset((void *)RMC.Sync,'0',sizeof(RMC.Sync));
	memset((void *)RMC.Time,'0',sizeof(RMC.Time));
	memset((void *)RMC.Status,'0',sizeof(RMC.Status));
	memset((void *)RMC.Lat,'0',sizeof(RMC.Lat));
	memset((void *)RMC.Lat_Dir,'0',sizeof(RMC.Lat_Dir));
	memset((void *)RMC.Long,'0',sizeof(RMC.Long));
	memset((void *)RMC.Long_Dir,'0',sizeof(RMC.Long_Dir));
	memset((void *)RMC.Speed,'0',sizeof(RMC.Speed));
	memset((void *)RMC.Course,'0',sizeof(RMC.Course));
	memset((void *)RMC.Date,'0',sizeof(RMC.Date));
	memset((void *)RMC.Magnetic,'0',sizeof(RMC.Magnetic));
	memset((void *)RMC.Mag_Dir,'0',sizeof(RMC.Mag_Dir));
	memset((void *)RMC.Mode,'0',sizeof(RMC.Mode));
	memset((void *)RMC.Checksum,'0',sizeof(RMC.Checksum));

}

/************************************************************
* Function: gps_get_nmea_string
*
* Description: Detects the start of a NMEA string and builds a char array with each byte received
*
* Inputs: unsigned char byte
*
* Outputs: Nothing
*
*************************************************************/
void gps_get_nmea_string(volatile unsigned char *byte){
	if(*byte == 0x24){ //("$")
		NMEA.string[0] = *byte;
		NMEA.flags ^= BIT0;		// toggle nmea data flag
		NMEA.byte_cnt = 1;
		NMEA.flags &= ~BIT1;	// set crc flag to False
		NMEA.crc_cnt = 0;
		NMEA.crc = 0;
	}

	//If NMEA string receive in-progress add each suscessive byte to the string buffer
	else if (NMEA.flags & BIT0 == 1){
		NMEA.string[NMEA.byte_cnt] = *byte;

		if (*byte == '*'){
			NMEA.flags ^= BIT1;		// set CRC flag
			NMEA.byte_cnt++;
		}
		else
			NMEA.byte_cnt++;
			if(~NMEA.flags & BIT1){
				NMEA.crc ^= *byte; //XOR each byte to calculate checksum
			}
		if(NMEA.flags & BIT1){
			if(NMEA.crc_cnt > 0){
				NMEA.nmea_crc[NMEA.crc_cnt - 1] = *byte;
			}
			NMEA.crc_cnt++;
		}
		// Check if string capture is complete at end of 2 byte checksum
		if (NMEA.crc_cnt == 3){
			sscanf((const char *)NMEA.nmea_crc,"%x",&(NMEA.nmea_crc_val));
			if((unsigned char *)NMEA.crc == NMEA.nmea_crc_val){
				Save_GPS_string_2(NMEA.string);
			}
			NMEA.byte_cnt = 0;
			NMEA.flags &= ~BIT0;
		}
	}
	// if string buffer full then parse and reset for next string
	// We should never see this if checking for checksum works.
	if (NMEA.byte_cnt > 80){
		NMEA.byte_cnt = 0;
		NMEA.flags &= ~BIT0;
	}
}

/************************************************************
* Function: Parse_GGA
*
* Description: Parses a GGA NMEA string
*
* Inputs: unsigned char string[]
*
* Outputs: Nothing
*
*************************************************************/
void Parse_GGA(volatile unsigned char *string){
	unsigned char i;
	unsigned char j;
	i = 0;
	j = 0;
	while(string[++i] != ','){
		//skips $
		GGA.Sync[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Time[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Lat[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Lat_Dir[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Long[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Long_Dir[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Fix_Quality[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Satellites[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.HDOP[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Altitude[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Alt_Units[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Geod_Sep[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.Geod_Units[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != ','){
		GGA.DGPS_Time[j] = string[i];
		j++;
	}

	j = 0;
	while(string[++i] != '*'){
		GGA.DGPS_Station[j] = string[i];
		j++;
	}
}


/************************************************************
* Function: Parse_RMC
*
* Description: Parses a RMC NMEA string
*
* Inputs: unsigned char string[]
*
* Outputs: Nothing
*
*************************************************************/
void Parse_RMC(volatile unsigned char *string){
	unsigned char i;
	unsigned char j;
	unsigned int safety;
	i = 0;
	j = 0;
	safety=0;

	while(string[++i] != ','){
		//skips $
		RMC.Sync[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Time[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Status[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Lat[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Lat_Dir[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Long[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Long_Dir[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Speed[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Course[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Date[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Magnetic[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != ','){
		RMC.Mag_Dir[j] = string[i];
		j++;
	}
	j = 0;
	while(string[++i] != '*'){
		RMC.Mode[j] = string[i];
		j++;
	}
}

/************************************************************
* Function: Save_GPS_string
*
* Description: Determines what type of NMEA string was received and parses it
*
* Inputs: unsigned char string[]
*
* Outputs: Nothing
*
*************************************************************/
void Save_GPS_string_2(volatile unsigned char *string){
	if(*strstr((char *)string, (char *)"GGA")){
		Parse_GGA(string);
		if(GGA.Fix_Quality[0] == 0x30){
			initialize_GPS_structs();
		}
	}
	else if(*strstr((char *)string, (char *)"RMC")){
		Parse_RMC(string);
	}
}

