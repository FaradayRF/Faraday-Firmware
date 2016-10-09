#ifndef RF_NETWORK_STACK_RF_SERVICE_H_
#define RF_NETWORK_STACK_RF_SERVICE_H_

void rf_rx_service_open(unsigned char service_number, void (*func_ptr)(), unsigned char broadcast_rx_allowed);
void rf_rx_service_close(unsigned char service_number);
void rf_rx_service_app_put(unsigned char service_number, unsigned char *data);
void rf_rx_stack_rx(unsigned char service_number, unsigned char *data, unsigned char payload_len);
void rf_rx_service_broadcast_rule_open(service_number);
unsigned char rf_rx_service_broadcast_rule_get(service_number);

#endif /* RF_NETWORK_STACK_RF_SERVICE_H_ */
