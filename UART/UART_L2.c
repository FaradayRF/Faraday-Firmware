/*
 * UART_L2.c
 *
 *  Created on: Mar 8, 2016
 *      Author: Brent
 */


#include "UART_L2.h"
#include "UART_L4.h"
#include "../Faraday_HAL/Faraday_HAL.h"
#include <msp430.h>
#include "UART_Services.h"
#include "../Ring_Buffers/FIFO.h"
#include "../REVA_Faraday.h"



//Packet Ring Buffer
volatile fifo_state_machine uart_tx_bytes_state_machine;
volatile unsigned char uart_data_tx_bytes_256[UART_TX_BUFFER_SIZE];
volatile fifo_state_machine uart_rx_raw_bytes_state_machine;
volatile unsigned char uart_data_rx_raw_bytes[64];

//Packet Struct
//volatile UART_DATALINK_PACKET_STRUCT uart_tx_datalink_pkt_struct;

//ISR
volatile UART_DATALINK_PACKET_MSP430_BUFFER_STRUCT uart_tx_bytes_isr_buffer_struct;

//RX Frame State Machine
volatile unsigned char uart_datalink_frame_rx_state = UART_DATALINK_RX_STATE_IDLE;
volatile unsigned char rx_datalink_packet[128];
volatile unsigned char rx_datalink_byte_cnt;


void init_uart(void){
	//UART TX FIFO
	uart_tx_bytes_state_machine.debug = 0;
	uart_tx_bytes_state_machine.element_size = 128;
	uart_tx_bytes_state_machine.head = 0;
	uart_tx_bytes_state_machine.inwaiting = 0;
	uart_tx_bytes_state_machine.length = 0;
	uart_tx_bytes_state_machine.max_inwait = 0;
	uart_tx_bytes_state_machine.tail = 0;
	uart_tx_bytes_state_machine.buffer_size = UART_TX_BUFFER_SIZE;

	//UART RX FIFO
	uart_rx_raw_bytes_state_machine.debug = 0;
	uart_rx_raw_bytes_state_machine.element_size = 1;
	uart_rx_raw_bytes_state_machine.head = 0;
	uart_rx_raw_bytes_state_machine.inwaiting = 0;
	uart_rx_raw_bytes_state_machine.length = 0;
	uart_rx_raw_bytes_state_machine.max_inwait = 0;
	uart_rx_raw_bytes_state_machine.tail = 0;
	uart_rx_raw_bytes_state_machine.buffer_size = 64;
}

void uart_datalink_create_packet(volatile UART_DATALINK_PACKET_STRUCT *buffer_struct, unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload){

	buffer_struct->packet_type = packet_type;
	buffer_struct->packet_config = packet_config;
	buffer_struct->payload_length = payload_length;

	unsigned char i;
	//Place destination callsign into packet struct
	for(i=0; i<payload_length; i++){
		buffer_struct->payload[i] = payload[i];
	}

	//Pad destination callsign
	for(i=payload_length; i<UART_L2_PAYLOAD_LENGTH; i++){
		buffer_struct->payload[i] = 0xFF; //Padding
	}
}

unsigned char uart_datalink_put_tx(unsigned char packet_type, unsigned char packet_config, unsigned char payload_length, unsigned char *payload){
	UART_DATALINK_PACKET_STRUCT uart_tx_datalink_pkt_struct;
	//Create packet
	uart_datalink_create_packet(&uart_tx_datalink_pkt_struct, packet_type, packet_config, payload_length, payload);
	unsigned char status;
	//Place into buffer queue
	status = put_fifo(&uart_tx_bytes_state_machine, &uart_data_tx_bytes_256, &uart_tx_datalink_pkt_struct);
	return status;

}

unsigned char uart_datalink_get_tx(unsigned char *get_buffer_ptr){
	unsigned char result;
	result = get_fifo(&uart_tx_bytes_state_machine, uart_data_tx_bytes_256, get_buffer_ptr);
	return result;
}

unsigned char uart_datalink_isempty_tx(void){
	if(uart_tx_bytes_state_machine.inwaiting>0){
		return 1;
	}
	else{
		return 0;
	}
}

void uart_datalink_tx_housekeep(void){
	//Datalink TX
	if((uart_tx_bytes_state_machine.inwaiting>0) && (uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_rdy_flag == 0)){
		__no_operation();
		//__delay_cycles(500000); //Race condition? BUG - YES THERE IS A RACE CONDITION = 500000
		uart_datalink_get_tx((unsigned char *)uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_tx_pkt_buffer);
		uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_rdy_flag = 1;
		hal_uart_set_uctxifg(); // Manually set interrupt TX flag to cause TX UART ISR to trigger if not already trigger.



	}
}

void uart_datalink_rx_housekeep(void){
	//Datalink RX
	if(uart_rx_raw_bytes_state_machine.inwaiting > 0){
		while(uart_rx_raw_bytes_state_machine.inwaiting > 0){
			__no_operation();
			unsigned char rx_byte;
			get_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &rx_byte);
			uart_datalink_rx_framer_parser_parse_byte(rx_byte);
		}
	}
}

//unsigned char uart_datlink_tx_startbyte_flag;
//unsigned char uart_datlink_tx_stopbyte_flag;
//unsigned char uart_datlink_tx_escape_flag;
//unsigned char uart_datlink_tx_escape_buffer;

void uart_tx_datalink_isr(void){
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//Check if byte waiting to be transmitted, if so get it and move it into the UART TX buffer register
	// - Transmitting is done through a simple framing escape state machine. The first byte gets prepended with an escape "START" byte.
	// - The last byte gets appended with a STOP byte. All Start, Stop, and Escape bytes get escaped with an escape byte.
	// - Note that the simple system uses flags and choosing to increment the counter cleverly to perform these actions.
	// - Only in the case of the escaped data bytes NOT at start or end does actual buffering of a byte get performed.
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	  if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current<UART_L2_PACKET_LENGTH){
			/////////////////////////////////////
			//Next byte is post startbyte flag
			/////////////////////////////////////
		  if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_startbyte_flag == 1){
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_startbyte_flag = 0; //Reset startbyte framing flag to 0
			  //Place first (start) data byte into uart TX buffer register
			  UCA0TXBUF = uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_tx_pkt_buffer[uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current];
			  //Increment byte counter
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current++;
		  }
			/////////////////////////////////////
			//Next byte is post stopbyte flag
			/////////////////////////////////////
		  else if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_stopbyte_flag == 1){
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_stopbyte_flag = 0; //Reset startbyte framing flag to 0
			  //Place stop byte into uart TX buffer register
			  UCA0TXBUF = UART_DATALINK_FRAMING_STOP_BYTE;
			  //Increment byte counter
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current++;
		  }
			/////////////////////////////////////
			//Next byte is post escape flag
			/////////////////////////////////////
		  else if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_flag == 1){
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_flag = 0; //Reset startbyte framing flag to 0
			  //Place escaped data byte into uart TX buffer register
			  UCA0TXBUF = uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer;
			  //Increment byte counter
			  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current++;
		  }
			///////////////////////////
			//Next byte is normal data
			///////////////////////////
		  else{
			  //Frame - Insert start byte
			  if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current == 0){
				  //First byte
				  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_startbyte_flag = 1; //Set startbyte flag
				  UCA0TXBUF = UART_DATALINK_FRAMING_START_BYTE;
				  __no_operation();
			  }
			  //Frame - Insert stop byte
			  else if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current == 127){
				  //Last byte
				  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_stopbyte_flag = 1; //Set startbyte flag
				  //Place last databyte into UART tx buffer register, stopbyte will be sent after this last byte
				  UCA0TXBUF = uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_tx_pkt_buffer[uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current];
				  __no_operation();
			  }
			  //Frame - Not START or STOP byte, check for data bytes needing escape character prepended
			  else{
				  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer = uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_tx_pkt_buffer[uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current];
				  // If databyte is an escape character escape the databyte!
				  // Databyte is escape byte, escape it.
				  if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer == UART_DATALINK_FRAMING_ESC_BYTE){
					  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_flag = 1; //Set startbyte flag
					  UCA0TXBUF = UART_DATALINK_FRAMING_ESC_BYTE;
				  }
				  // Databyte is start byte, escape it.
				  else if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer == UART_DATALINK_FRAMING_START_BYTE){
					  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_flag = 1; //Set startbyte flag
					  UCA0TXBUF = UART_DATALINK_FRAMING_ESC_BYTE;
				  }
				  // Databyte is stop byte, escape it.
				  else if(uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer == UART_DATALINK_FRAMING_STOP_BYTE){
					  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_flag = 1; //Set startbyte flag
					  UCA0TXBUF = UART_DATALINK_FRAMING_ESC_BYTE;
				  }
				  // Databyte doesn't need escaping.
				  else{
					  UCA0TXBUF = uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_escape_buffer;
					  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current++;
				  }

			  }
		  }
	  }
	  else{
		  uart_tx_bytes_isr_buffer_struct.uart_datlink_tx_byte_current = 0;
		  uart_tx_bytes_isr_buffer_struct.uart_datalink_tx_rdy_flag = 0;
	  }
}


/*
 * Receiver
 */


//status = put_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &uart_tx_datalink_pkt_struct);
//result = get_fifo(&uart_rx_raw_bytes_state_machine, uart_data_rx_raw_bytes, get_buffer_ptr);


unsigned char uart_datalink_byte_isempty_rx(void){
	if(uart_rx_raw_bytes_state_machine.inwaiting>0){
		return 1;
	}
	else{
		return 0;
	}
}

void uart_datalink_rx_put_byte(volatile unsigned char *data_byte){

	//rx_byte = 0;
	//data = 0x31;
	//Place into buffer queue
	//volatile unsigned char status;//,data,rx_byte;
	put_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &data_byte);
	//status = get_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &rx_byte);
	//status = get_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &rx_byte);
	//status = get_fifo(&uart_rx_raw_bytes_state_machine, &uart_data_rx_raw_bytes, &rx_byte);
}

//
//#define UART_DATALINK_TX_START_BYTE 0x7b
//#define UART_DATALINK_TX_STOP_BYTE 0x7c
//#define UART_DATALINK_TX_ESC_BYTE 0x7d

///*
// * UART Receive Byte Escaping
// */
//
///************************************************************
//* Function: unsigned char uart_datalink_rx_frame_parser_check_state(void)
//*
//* Description: This function returns the value of the datalink layer frame
//*              parser's current state variable. Current state indicates the
//*              state machines current status.
//*              - Idle   - Waiting for start byte, no frame parsing in progress
//*              - Start  - Frame parsing currently in progress
//*              - Stop   - Stop byte received, frame is completed, will perform actions and return to idle
//*              - Escape - Escape byte received, next databyte should be a Start, Stop, or Escape byte in data.
//*
//* Inputs: None
//*
//* Outputs: Returns the current value of the uart datalink layer
//*          frame parser state variable.
//*
//*************************************************************/
unsigned char uart_datalink_rx_frame_parser_check_state(void){
	return uart_datalink_frame_rx_state;
}

///************************************************************
//* Function: void uart_datalink_rx_frame_parser_change_state(unsigned char state)
//*
//* Description: This function is used to set a char value to the uart datalink
//*              layer frame parser's current state machine status variable.
//*
//* Inputs:
//*              unsigned char state - State to place the frame parser state machine into
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_frame_parser_change_state(unsigned char state){
	uart_datalink_frame_rx_state = state;
}
//
///************************************************************
//* Function: void uart_datalink_rx_frame_parser_state_idle(unsigned char new_byte)
//*
//* Description: This function is the IDLE state machine to parse new bytes. The IDLE
//*              state is entered when no frame is currently being parsed and the parsing
//*              algorithm is waiting for a new frame's START byte.
//*
//* Inputs:
//               unsigned char new_byte - Pass by reference the new byte to parse.
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_frame_parser_state_idle(unsigned char new_byte){
	switch (new_byte){
	case UART_DATALINK_RX_START_BYTE:
		//Clear for new frame parse
		rx_datalink_byte_cnt = 0;
		//New packet detected, advance state to "START"
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_START);
		//valid_start_buf = get_head_ring_buffer_64(&uart_datalink_rx_frame_ring_buffer_64_struct);
		break;
	case UART_DATALINK_RX_STOP_BYTE:
		//Invalid data byte for IDLE, ignore
		break;
	case UART_DATALINK_RX_ESC_BYTE:
		//Invalid data byte for IDLE, ignore
		break;
	default:
		//Invalid data byte for IDLE, ignore
		break;
	}
}

///************************************************************
//* Function: void uart_datalink_rx_frame_parser_state_start(unsigned char new_byte)
//*
//* Description: This function is the START state machine to parse new bytes. The START
//*              state is entered when the parser has found the START byte and begins
//*              parsing the new frame. If noise presents the START byte the parser will attempt
//*              to parse but will reset to a new packet if another START byte is received
//*              without a preceding ESC byte.
//*
//* Inputs:
//*              unsigned char new_byte - Pass by reference the new byte to parse.
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_frame_parser_state_start(unsigned char new_byte){
	switch (new_byte){
	case UART_DATALINK_RX_START_BYTE:
		//Clear for new framer parse
		rx_datalink_byte_cnt = 0;
		//New packet detected, advance state to "START" - Prior packet corrupted / not escaped properly
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_START);
		break;
	case UART_DATALINK_RX_STOP_BYTE:
		//END of frame found, packet parse completed
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_STOP);
		break;
	case UART_DATALINK_RX_ESC_BYTE:
		//Escape byte found
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_ESC);
		break;
	default:
		//Databyte recevied, save databyte to buffer
		if(rx_datalink_byte_cnt<128){
			rx_datalink_packet[rx_datalink_byte_cnt] = new_byte;
			rx_datalink_byte_cnt++;
		}
		break;
	}
}

///************************************************************
//* Function: void uart_datalink_rx_frame_parser_state_stop(void)
//*
//* Description: This function is the STOP state machine. The STOP
//*              state is entered when the parser has found the STOP byte has been recieved
//*              only during a framer parsing state (i.e. not during IDLE). This indicates the
//*              end of a frame and the final actions need to be completed to handle the frame
//*              accordingly and place into the frame fragmentation assembly parser.
//*
//* Inputs:
//*              unsigned char new_byte - Pass by reference the new byte to parse.
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_frame_parser_state_stop(void){
	//Full packet parsed, finalize and move to buffer
	//Reset state to IDLE after actions completed
	uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_IDLE);

}
//
///************************************************************
//* Function: void uart_datalink_rx_frame_parser_state_esc(unsigned char new_byte)
//*
//* Description: This function is the ESCAPE state machine state. This state is
//*              entered when a new frame is being parsed (not in IDLE) and an
//*              ESC byte is received. The ESC byte indicates the next byte will
//*              be a START, STOP, or ESC byte that should be treat as payload data
//*              and not a framing byte.
//*
//* Inputs:
//*              unsigned char new_byte - Pass by reference the new byte to parse.
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_frame_parser_state_esc(unsigned char new_byte){
	switch (new_byte){
	case UART_DATALINK_RX_START_BYTE:
		//ESCAPED START databyte recevied, save databyte to buffer
		if(rx_datalink_byte_cnt<128){
			rx_datalink_packet[rx_datalink_byte_cnt] = new_byte;
			rx_datalink_byte_cnt++;
		}
		//Return state to START
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_START);
		break;
	case UART_DATALINK_RX_STOP_BYTE:
		//ESCAPED STOP databyte recevied, save databyte to buffer
		if(rx_datalink_byte_cnt<128){
			rx_datalink_packet[rx_datalink_byte_cnt] = new_byte;
			rx_datalink_byte_cnt++;
		}
		//Return state to START
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_START);
		break;
	case UART_DATALINK_RX_ESC_BYTE:
		//ESCAPED ESCAPE databyte recevied, save databyte to buffer
		if(rx_datalink_byte_cnt<128){
			rx_datalink_packet[rx_datalink_byte_cnt] = new_byte;
			rx_datalink_byte_cnt++;
		}
		//Return state to START
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_START);
		break;
	default:
		//INVALID, data likely corrupt but return state to START to keep moving.
		break;
	}
}
//
///************************************************************
//* Function: void uart_datalink_rx_framer_parser_parse_byte(unsigned char new_byte)
//*
//* Description: This function is the uart datalink layer framing byte parse state machine parser.
//*              A new byte to be parsed is determined to be a framing byte or data byte and actions
//*              accordingly are performed. Depending on the byte value the actions might change the
//*              state machine current state.
//*
//* Inputs:
//*              unsigned char new_byte - Pass by reference the new byte to parse.
//*
//* Outputs: None
//*
//*************************************************************/
void uart_datalink_rx_framer_parser_parse_byte(unsigned char new_byte){
	switch (uart_datalink_frame_rx_state){
	case UART_DATALINK_RX_STATE_IDLE:
		uart_datalink_rx_frame_parser_state_idle(new_byte);
		break;
	case UART_DATALINK_RX_STATE_START:
		uart_datalink_rx_frame_parser_state_start(new_byte);
		break;
	case UART_DATALINK_RX_STATE_STOP:
		//THIS IS NOT A STATE TO ACCEPT A BYTE IN! UPDATE!!!
		uart_datalink_rx_frame_parser_state_stop();
		break;
	case UART_DATALINK_RX_STATE_ESC:
		uart_datalink_rx_frame_parser_state_esc(new_byte);
		break;
	default:
		//STATE should never be here, reset to IDLE
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_IDLE);


	}

	//Check if a packet is completed (STATE = STOP)
	if(uart_datalink_rx_frame_parser_check_state() == UART_DATALINK_RX_STATE_STOP){
		//Perform final packet actions
		//Return to IDLE state
		uart_datalink_rx_frame_parser_change_state(UART_DATALINK_RX_STATE_IDLE);

		//Parse Datalink Packet
		// [Packet type, Packet config, payload length, payload...]
		//MAKE struct!
		unsigned char packet_type;
		unsigned char packet_config;
		unsigned char payload_length;
		unsigned char payload[UART_L2_PAYLOAD_LENGTH];


		packet_type = rx_datalink_packet[UART_L2_PKT_TYPE_LOC];
		packet_config = rx_datalink_packet[UART_L2_PKT_CONFIG_LOC];
		payload_length = rx_datalink_packet[UART_L2_PKT_PAYLOAD_LEN_LOC];

		unsigned char i;
		if(payload_length<=125){//MAKE CONSTANT
			for(i=3; i<payload_length + UART_L2_PKT_HEADER_LEN_OFFSET; i++){
				payload[i-3] = rx_datalink_packet[i];
			}
		}
		else{
			__no_operation(); //Shouldn't get here. Bad packet length, caught to avoid overflow.
		}

		__no_operation();

		//Pass to higher layer
		uart_datalink_rx_pass_higher_layer(payload_length, &payload);

	}


}

void uart_datalink_rx_pass_higher_layer(unsigned char datagram_len, unsigned char *datagram){
	//This function should abstract slightly the need to pass received data up to the next layer. This techically breaks layer isolation but does so in only
	//one location for now.
	__no_operation();
	uart_transport_rx_packet(datagram_len, datagram);
	__no_operation();
}

//volatile unsigned char rx_datalink_packet[128];
//volatile unsigned char rx_datalink_byte_cnt;
