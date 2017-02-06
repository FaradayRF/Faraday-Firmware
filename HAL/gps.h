/** @file gps.h
 *  @brief Hardware abstraction for the Faraday GPS module
 *
 *  These functions provide hardware abstraction for the onboard
 *  GPS.
 *
 */

#ifndef HAL_GPS_H_
#define HAL_GPS_H_

/** @brief General structure used to hold a GPS string recevied
 *
 *  General structure used to hold a GPS string recevied and contain basic validity information
 *  regarding the received string.
 *
 * GPS String Flags
 *
 * - BIT0 = nmea string flag
 * - BIT1 = CRC valid flag
 *
 * @todo Are all these structure fields really needed / used? Bryce?
 *
 */
typedef struct GPS_string {
	unsigned char string[80]; /**< Byte array used to hold the raw received GPS packet */
	char byte_cnt; /**< Byte count of the recevied packet */
	char flags; /**< GPS flag bitmask */
	unsigned char crc; /**< Packet CRC */
	unsigned char nmea_crc[2]; /**< NMEA CRC bytes */
	unsigned char *calc_crc; /**< Calculated CRC byte pointer */
	unsigned int crc_cnt; /**< Calculated CRC integer */
	unsigned char *nmea_crc_val; /**< Pointer to NMEA CRC value */
	unsigned char GPSFixValid; /**< GPS valid fix byte to indicate if the received packet is from a valid GPS lock */
}GPSNMEA;


/** @brief Structure defining the expected NMEA "GGA" string packet type
 *
 *	Structure defining the expected NMEA "GGA" string packet type. This structure is used to
 *	hold the parsed information from the received GGA packet.
 *
 */
typedef struct GGA_Data {
	char Sync[5]; /**< GGA sentence sync header */
	char Time[10]; /**< GGA sentence time*/
	char Lat[9]; /**< GGA sentence lattitude */
	char Lat_Dir[1]; /**< GGA sentence lattitude direction */
	char Long[10]; /**< GGA sentence longitude */
	char Long_Dir[1]; /**< GGA sentence longitude direction */
	char Fix_Quality[1]; /**< GGA sentence fix quality */
	char Satellites[2]; /**< GGA sentence number of sattelites received */
	char HDOP[4]; /**< GGA sentence horizontal relative accuracy */
	char Altitude[8];  /**< GGA sentence altitude in meteres (up to 99999.99 meters) */
	char Alt_Units[1]; /**< GGA sentence altitude units */
	char Geod_Sep[8];  /**< GGA sentence height about WGS84 ellipsoid in meters (up to 99999.99 meters) */
	char Geod_Units[1]; /**< GGA sentence WGS84 ellipsoid altitude units */
	char DGPS_Time[5]; /**< GGA sentence DGPS time */
	char DGPS_Station[4]; /**< GGA sentence DGPS reference station ID */ //Was 3 moved to 4 due to causing buffer overflow
	//char Checksum[3];  /**< GGA sentence checksum */ //Why is this commented Bryce?
} GPSGGA;


/** @brief Structure defining the expected NMEA "RMC" string packet type
 *
 *	Structure defining the expected NMEA "RMC" string packet type. This structure is used to
 *	hold the parsed information from the received RMC packet.
 *
 */
typedef struct RMC_Data {
	char Sync[5]; /**< RMC Sentence sync header */
	char Time[10]; /**< RMC Sentence time */
	char Status[1]; /**< RMC Sentence status */
	char Lat[9]; /**< RMC Sentence latitude */
	char Lat_Dir[1]; /**< RMC Sentence latitude direction */
	char Long[10]; /**< RMC Sentence longitude */
	char Long_Dir[1]; /**< RMC Sentence longitude direction */
	char Speed[5]; /**< RMC Sentence speed in knots */
	char Course[5]; /**< RMC Sentence course (degrees) */
	char Date[6]; /**< RMC Sentence date stamp */
	char Magnetic[5]; /**< RMC Sentence magnetic bearing */
	char Mag_Dir[1]; /**< RMC Sentence magnetic bearing direction */
	char Mode[1]; /**< RMC Sentence mode */
	char Checksum[2]; /**< RMC Sentence checksum */
} GPSRMC;


/** @name GPS Structures
* 	@brief structures that are used to parse GPS sentences
*
* 	These structures are global and allow the GPS parsing routines a common location to parse GPS sentences into
* 	thier respective fields.
*
@{**/
volatile GPSGGA GGA;
volatile GPSRMC RMC;
volatile GPSNMEA NMEA;
/** @}*/


/**@brief Initialize all needed GPS structures
 *
 *	Initialize needed GPS structures for proper default operation.
 *
 */
void initialize_GPS_structs(void);


/**@brief Parse GPS NMEA bytestream
 *
 * Detects the start of a NMEA string and builds a char array with each byte received until a full sentence is received.
 *
 * @param byte A pointer to the byte from the GPS NMEA bytestream to be parsed (framing)
 *
 */
void gps_get_nmea_string(volatile unsigned char *byte);


/**@brief Parses GPS sentence
 *
 *  Determines what type of NMEA string was received and parses it using the expected packet fields.
 *
 *  @param string A pointer to the GPS NMEA string sentence to be parsed
 *
 *  @warning Only a select few GPS sentences are supported!
 *
 */
void Save_GPS_string_2(volatile unsigned char *string);


/**@brief Parse NMEA GGA sentence
 *
 *	This function parses the NMEA GGA sentence into the GPS global structure that is used to hold the parsed GGA fields.
 *
 *	@param string A pointer to the GPS NMEA string sentence to be parsed
 *
 */
void Parse_GGA(volatile unsigned char *string);


/**@brief Parse NMEA RMC sentence
 *
 *	This function parses the NMEA RMC sentence into the GPS global structure that is used to hold the parsed RMC fields.
 *
 *	@param string A pointer to the GPS NMEA string sentence to be parsed
 *
 */
void Parse_RMC(volatile unsigned char *string);


volatile unsigned char gpsTest; //GPS Testing, DEBUG

#endif /* FARADAY_REVA_RF_MERGE_HAL_GPS_H_ */
