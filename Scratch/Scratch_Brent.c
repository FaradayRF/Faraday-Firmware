/*
 * Scratch_Brent.c
 *
 *  Created on: Oct 27, 2015
 *      Author: Brent
 */

#include "Scratch_Brent.h"
#include <msp430.h>

#include "../Applications/Telemetry/Telemetry.h"
#include "../HAL/GPIO.h"
#include "../Faraday_Init.h"
#include "../Ring_Buffers/FIFO.h"
#include "../SRAM/SRAM.h"
//#include "../Ring_Buffers/Packet_Ring_Buffer.h"
#include "../UART/UART_L2.h"
#include "../UART/UART_L4.h"

volatile unsigned char test[64];
volatile unsigned char test2[64];

void scratch_init_main(void){
	//RF INIT
	InitRadio();
	// Internal timer output (10.5 kHz) to Radio TX
	// NOTE: SMARTF_CC430 IOCFG0 should = 0x2E. When IOCFG0 = 0x2D,
	// asynchronous data into the radio is taken from GDO0 and not the timer.
	init_timer_A0();
	/*
	TA0CCR0 = 50;
	TA0CCR1 = 50;

	TA0CCTL0 = OUTMOD_4 +CCIE;
	TA0CCTL1 = OUTMOD_4;
	TA0CTL = TASSEL__SMCLK + MC_1 + TACLR;
	*/
	// END RF INIT


    //GPIO_Output_Bitmask_HAL_Update(&gpio_bitmask_struct_struct, GPIO_LED_1, 1);
    //GPIO_Output_Bitmask_HAL_Update(&gpio_bitmask_struct_struct, GPIO_MOSFET_CNTL, 1);
    //GPIO_Bitmask_HAL_Update_Single(&gpio_bitmask_struct_struct, GPIO_LED_1, 0);
    //GPIO_Bitmask_HAL_housekeep(&gpio_bitmask_struct_struct);
    //GPIO_Output_Bitmask_HAL_Update(&gpio_bitmask_struct_struct, GPIO_LED_2, 0);
    //GPIO_Output_Bitmask_HAL_Update(&gpio_bitmask_struct_struct, GPIO_MOSFET_CNTL, 0);
    //GPIO_Output_Bitmask_HAL_Update(&gpio_bitmask_struct_struct, GPIO_LED_1 + GPIO_LED_2, 1);
    //GPIO_Bitmask_HAL_housekeep(&gpio_bitmask_struct_struct);

    //ADC
        //application_adc_set_names_default();
}

void scratch_app_adc_get(void){
	__no_operation();
}

void scratch_sram_packets(void){
	Faraday_SRAM_Write_Settings(0);
	Faraday_SRAM_Write_Byte(0x01, 0);
	Faraday_SRAM_Write_Byte(0x02, 1);
	Faraday_SRAM_Write_Byte(0x03, 2);

}

void scratch_sram_read(void){
	volatile unsigned char test_sram_read[64];
	test_sram_read[0] = Faraday_SRAM_Read_Byte(0);
	test_sram_read[1] = Faraday_SRAM_Read_Byte(1);
	test_sram_read[2] = Faraday_SRAM_Read_Byte(2);
	__no_operation();

}

/*void main_packet_buffer(void){
	init_packet_buffers();

	test[0]= 0x09;
	test[1]= 0x08;
	test[2]= 0x07;
	test[3]= 0x06;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,4);
	test[4]= 0x07;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,5);
	test[5]= 0x08;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,6);
	test[6]= 0x04;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,7);
	test[7]= 0x03;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,8);
	test[2]= 0x02;
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,9);
	put_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test,9);
	unsigned char i;
	for(i=0;i<8;i++){
		if(isempty_packet_ring_buffer_64(packet_ring_buffer_64_ptr)==1){
			get_char_packet_ring_buffer_64(packet_ring_buffer_64_ptr, test2);
		}
		else{
			__no_operation();
		}
	}


	__no_operation();
}
*/

void scratch_uart_tx_bytes(void){

	init_uart();
	volatile unsigned char test2, test3;
	volatile unsigned char gettest[64];
	volatile unsigned char status_final;

	unsigned char test[5] = {0,1,0x7b,3,0x7c};
//	//uart_transport_create_packet(&uart_tx_transport_pkt_struct, 0x33, 5, test);
//	status_final = uart_transport_tx_packet(0x31, 5, test);
//	status_final = uart_transport_tx_packet(0x32, 5, test);
//	status_final = uart_transport_tx_packet(0x33, 5, test);
//	status_final = uart_transport_tx_packet(0x34, 5, test);
//	status_final = uart_transport_tx_packet(0x35, 5, test);

	//put_rx();


}

