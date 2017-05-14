/** @file rf_packet.h
 * 	@brief Firmware application provides a generic data interface to RF
 *
 * 	This program provides an interface for data to be received and transmitted over
 * 	RF.
 *
 *
 *
 */


#ifndef APPLICATIONS_RF_PACKET_RF_PACKET_H_
#define APPLICATIONS_RF_PACKET_RF_PACKET_H_

void app_init_app_rf_packet(void);
void app_rf_packet_uart_rx_put(unsigned char *data_pointer, unsigned char length);
void app_rf_packet_housekeeping(void);
void app_rf_packet_rf_tx(unsigned char *packet);


#endif /* APPLICATIONS_RF_PACKET_RF_PACKET_H_ */
