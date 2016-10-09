#ifndef APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_
#define APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_

#define CONFIG_PACKET_LEN 116
#define MAX_CALLSIGN_LENGTH 9

#define CONFIG_BASIC_FLASH_CONFIG_BITMASK_ADDR 6144
#define CONFIG_BASIC_FLASH_CONFIG_BITMASK_INDEX 0

#define CONFIG_BASIC_LOCAL_CALLSIGN_ADDR 6145
#define CONFIG_BASIC_LOCAL_CALLSIGN_INDEX 1
#define CONFIG_BASIC_LOCAL_CALLSIGN_LEN_ADDR 6154
#define CONFIG_BASIC_LOCAL_CALLSIGN_LEN_INDEX 10
#define CONFIG_BASIC_LOCAL_CALLSIGN_ID_ADDR 6155
#define CONFIG_BASIC_LOCAL_CALLSIGN_ID_INDEX 11

#define CONFIG_BASIC_P3_GPIO_ADDR 6156
#define CONFIG_BASIC_P3_GPIO_INDEX 12
#define CONFIG_BASIC_P4_GPIO_ADDR 6157
#define CONFIG_BASIC_P4_GPIO_INDEX 13
#define CONFIG_BASIC_P5_GPIO_ADDR 6158
#define CONFIG_BASIC_P5_GPIO_INDEX 14

#define CONFIG_RF_DEFAULT_FREQ_ADDR 6168
#define CONFIG_RF_DEFAULT_FREQ_INDEX 24
#define CONFIG_RF_DEFAULT_PATABLE_ADDR 6171
#define CONFIG_RF_DEFAULT_PATABLE_INDEX 27

#define CONFIG_GPS_DEFAULT_LATTITUDE_ADDR 6193
#define CONFIG_GPS_DEFAULT_LATTITUDE_INDEX 49
#define CONFIG_GPS_DEFAULT_LATTITUDE_DIR_ADDR 6202
#define CONFIG_GPS_DEFAULT_LATTITUDE_DIR_INDEX 58
#define CONFIG_GPS_DEFAULT_LONGITUDE_ADDR 6203
#define CONFIG_GPS_DEFAULT_LONGITUDE_INDEX 59
#define CONFIG_GPS_DEFAULT_LONGITYUDE_DIR_ADDR 6213
#define CONFIG_GPS_DEFAULT_LONGITYUDE_DIR_INDEX 59
#define CONFIG_GPS_DEFAULT_ALTITUDE_ADDR 6214
#define CONFIG_GPS_DEFAULT_ALTITUDE_INDEX 70
#define CONFIG_GPS_DEFAULT_ALTITUDE_UNITS_ADDR 6222
#define CONFIG_GPS_DEFAULT_ALTITUDE_UNITS_INDEX 78
#define CONFIG_GPS_DEFAULT_BOOT_BITMASK_ADDR 6223
#define CONFIG_GPS_DEFAULT_BOOT_BITMASK_INDEX 79

#define CONFIG_TELEMETRY_BOOT_BITMASK_ADDR 6245
#define CONFIG_TELEMETRY_BOOT_BITMASK_INDEX 101
#define CONFIG_TELEMETRY_UART_INTERVAL_ADDR 6246
#define CONFIG_TELEMETRY_UART_INTERVAL_INDEX 102
#define CONFIG_TELEMETRY_RF_INTERVAL_ADDR 6248
#define CONFIG_TELEMETRY_RF_INTERVAL_INDEX 104


#define RF_FREQ_LEN 3
#define GPS_LATTITUDE_LEN 9
#define GPS_LONGITUDE_LEN 10
#define GPS_ALTITUDE_LEN 8


/*
 * Device Debug definitions
 */
#define CONFIG_DEBUG_BOOT_COUNT_INDEX 0
#define CONFIG_DEBUG_RESET_COUNT_INDEX 2
#define CONFIG_DEBUG_BOOT_SYSRSTIV_BOR_INDEX 3
#define CONFIG_DEBUG_BOOT_SYSRSTIV_RSTNMI_INDEX 4
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVSL_INDEX 5
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVSH_INDEX 6
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVML_OVP_INDEX 7
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SVMH_OVP_INDEX 8
#define CONFIG_DEBUG_BOOT_SYSRSTIV_WDT_TIMEOUT_INDEX 9
#define CONFIG_DEBUG_BOOT_SYSRSTIV_FLASHKEY_INDEX 10
#define CONFIG_DEBUG_BOOT_SYSRSTIV_FLL_UNLOCK_INDEX 11
#define CONFIG_DEBUG_BOOT_SYSRSTIV_PERIPH_CONFIG_INDEX 12
#define CONFIG_DEBUG_BOOT_SYSRSTIV_SYSUNIV_ACCVIFG_INDEX 13


//GPIO P3 Bitmask

//GPIO P3 Bitmask

//Flash Config Bitmask
#define UNIT_PROGRAMMED BIT0

//GPS Boot Bitmask
#define GPS_BOOT_ENABLE BIT0

//Telemetry Boot Bitmask
#define UART_BEACON_BOOT_ENABLE BIT0
#define RF_BEACON_BOOT_ENABLE BIT1

extern volatile unsigned char config_bitmask;
extern volatile unsigned char local_callsign_len;
extern volatile char local_callsign[MAX_CALLSIGN_LENGTH];
extern volatile unsigned char local_device_id;
extern volatile unsigned char default_gpio_p3_bitmask;
extern volatile unsigned char default_gpio_p4_bitmask;

//RF
extern volatile unsigned char boot_freq[RF_FREQ_LEN];
extern volatile unsigned char boot_rf_PATABLE;

//GPS
extern volatile char default_lattitde[GPS_LATTITUDE_LEN];
extern volatile char default_lattitude_dir;
extern volatile char default_longitude[GPS_LONGITUDE_LEN];
extern volatile char default_longitude_dir;
extern volatile char default_altitude[GPS_ALTITUDE_LEN];
extern volatile char default_altitude_units;
extern volatile unsigned char gps_boot_bitmask;

//Telemetry
extern volatile unsigned char telem_boot_bitmask;
extern volatile unsigned int telem_default_uart_interval;
extern volatile unsigned int telem_default_rf_interval;

typedef struct default_config{
			unsigned char flash_config_bitmask;
			char local_callsign [9];
			unsigned char local_callsign_len;
			unsigned char local_device_id;
			unsigned char default_gpio_p3_bitmask;
			unsigned char default_gpio_p4_bitmask;
			unsigned char default_gpio_p5_bitmask;
			unsigned char padding_basic[9];
			unsigned char boot_freq[3];
			unsigned char PATable;
			unsigned char padding_rf[21];
			char default_lattitde[9];
			char default_lattitude_dir;
			char default_longitude[10];
			char default_longitude_dir;
			char default_altitude[8];
			char default_altitude_units;
			unsigned char gps_boot_bitmask;
			unsigned char padding_gps[21];
			unsigned char telem_boot_bitmask;
			unsigned int telem_default_uart_interval;
			unsigned int telem_default_rf_interval;
			unsigned char padding_telemetry[10];
		} default_flash_config_struct;

void app_device_config_write(void);
void app_device_config_write_callsign(unsigned char *callsign);
void app_device_config_write_buffer(unsigned char *data, unsigned char len);
void app_device_config_load_default(void);
void app_device_config_read_defaults(void);
void app_device_config_update_ram_parameter(unsigned char parameter, unsigned char *payload);
void app_device_config_device_debug_reset(void);
void app_device_config_device_debug_update(unsigned char param, unsigned char command);
void app_device_config_device_debug_increment_char(unsigned char offset);

#endif /* APPLICATIONS_DEVICE_CONFIG_DEVICE_CONFIG_H_ */
