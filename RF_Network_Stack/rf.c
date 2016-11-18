/** @file rf.c
 * 	@brief The layer 2 RF experimental protocol
 *
 * 	These functions create the experimental RF layer 2 (datalink) protocol. The protocol is a fixed length protocol and provides
 * 	no error detection. Packet fragmentation is not supported.
 *
 * 	The current implementation of the protocol utilizes the CC430 packet handling hardware that limits the packet to 64 bytes. Updates
 * 	are known through CC430 application notes that all unlimited packet size as well as handling all packet functions in firmware for
 * 	maximum flexability. These updates would greatly increase throughput.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "rf.h"
#include "string.h"

/* faraday rf layer 4 include */
#include "rf_transport.h"

/* cc430 radio module hardware abstraction include */
#include "../HAL/RF1A.h"
#include "../HAL/hal_pmm.h"

/* faraday hardware abstraction */
#include "../HAL/GPIO.h"

/* faraday hardware allocation */
#include "../REVA_Faraday.h"

/* faraday fifo include */
#include "../Ring_Buffers/FIFO.h"

/* faraday device configuration application include */
#include "../Applications/Device_Config/Device_Config.h"


/** @name External Variables
* 	@brief Declare external variables
*
*	Declare external variables for use in the source file.
*
@{**/
extern RF_SETTINGS rfSettings; /**< CC430 radio module rf settings definitions */
/** @}*/


/** @name Radio Operation Flags
* 	@brief Flag bytes used to cordinate radio operations
*
*	Flag bytes used to cordinate radio operations, especially the transmit and receive functionality.
*
@{**/
unsigned char transmitting_flag = 0; /**< Transmit enabled flag */
unsigned char receiving_flag = 0; /**< Receive enabled flag */
/** @}*/


/** @name Transmit/Receive Bytearray Buffers
* 	@brief Buffers used to temporarally hold RX/TX data
*
*	Buffers used to temporarally hold RX/TX data
*
*	@bug Are these better suited for local function variables?
*
@{**/
volatile unsigned char rf_tx_datalink_buffer[RX_PACKET_LEN+RX_PKT_HANDLE_APPEND_LEN]; /**< Transmit packet buffer */
volatile unsigned char rf_rx_datalink_buffer[RX_PACKET_LEN+RX_PKT_HANDLE_APPEND_LEN]; /**< Receive packet buffer  */
/** @}*/


/** @name Layer 2 protocol FIFO Variables
* 	@brief Variables used to control and hold information for the RF layer 2 FIFO operations
*
*	Variables used to control and hold information for the RF layer 2 FIFO operations.
*
*
@{**/
volatile fifo_state_machine rf_datalink_tx_fifo_state_machine; /**< Structure for the transmit FIFO state machine */
volatile unsigned char rf_datalink_tx_fifo_buffer[RF_DATALINK_PACKET_PAYLOAD_LEN*RF_DATALINK_PACKET_FIFO_COUNT]; /**< Transmit FIFO buffer */
volatile fifo_state_machine rf_datalink_rx_fifo_state_machine; /**< Structure for the receive FIFO state machine */
volatile unsigned char rf_datalink_rx_fifo_buffer[(RF_DATALINK_PACKET_PAYLOAD_LEN+RF_DATALINK_PACKET_RX_FOOTER_LEN)*RF_DATALINK_PACKET_FIFO_COUNT]; /**< Transmit FIFO buffer */
/** @}*/


/** @name Layer 2 Packet Structures
* 	@brief Structures used to build and parse layer 2 protocol packets
*
*	Structures used to build and parse layer 2 protocol packets.
*
*
@{**/
volatile RF_DATALINK_PACKET_STRUCT rf_datalink_packet_tx_struct; /**< Transmit packet structure */
volatile RF_DATALINK_PACKET_STRUCT rf_datalink_packet_rx_struct; /**< Receive packet structure */
/** @}*/


void init_radio_faraday(void){
	// Increase PMMCOREV level to 2 for proper radio operation
	ResetRadioCore();
	receiving_flag = 1;

	// Set the High-Power Mode Request Enable bit so LPM3 can be entered
	// with active radio enabled
	PMMCTL0_H = 0xA5;
	PMMCTL0_L |= PMMHPMRE_L;
	PMMCTL0_H = 0x00;
	WriteRfSettings(&rfSettings);
	WriteSinglePATable(boot_rf_PATABLE);

	//Calibrate initial boot manually
	radio_manual_calibration_idle();

	//Turn receive mode ON after initial boot
	ReceiveOn();
	radio_manual_idle();
	radio_manual_calibration_idle();
	radio_manual_idle();
	TransmitOn();
	radio_manual_idle();
	radio_manual_calibration_idle();
	ReceiveOn();

	//Init FIFO buffers
	init_rf_fifo();
}

// radio_load_defaults overwrites the RFSettings structure with the default RF frequency for boot writting the entire radio settings
void radio_load_default_frequency(unsigned char freq2, unsigned char freq1, unsigned char freq0){
	rfSettings.freq2 = freq2;
	rfSettings.freq1 = freq1;
	rfSettings.freq0 = freq0;
}

void init_rf_fifo(void){
	//Application FIFO
	rf_datalink_tx_fifo_state_machine.debug = 0;
	rf_datalink_tx_fifo_state_machine.element_size = RF_DATALINK_PACKET_PAYLOAD_LEN;
	rf_datalink_tx_fifo_state_machine.head = 0;
	rf_datalink_tx_fifo_state_machine.inwaiting = 0;
	//rf_datalink_tx_fifo_state_machine.length = 0;
	rf_datalink_tx_fifo_state_machine.max_inwait = 0;
	rf_datalink_tx_fifo_state_machine.tail = 0;
	rf_datalink_tx_fifo_state_machine.buffer_size = RF_DATALINK_PACKET_PAYLOAD_LEN*5;


	rf_datalink_rx_fifo_state_machine.debug = 0;
	rf_datalink_rx_fifo_state_machine.element_size = RF_DATALINK_PACKET_PAYLOAD_LEN+RF_DATALINK_PACKET_RX_FOOTER_LEN;
	rf_datalink_rx_fifo_state_machine.head = 0;
	rf_datalink_rx_fifo_state_machine.inwaiting = 0;
	//rf_datalink_rx_fifo_state_machine.length = 0;
	rf_datalink_rx_fifo_state_machine.max_inwait = 0;
	rf_datalink_rx_fifo_state_machine.tail = 0;
	rf_datalink_rx_fifo_state_machine.buffer_size = (RF_DATALINK_PACKET_PAYLOAD_LEN+RF_DATALINK_PACKET_RX_FOOTER_LEN)*RF_DATALINK_PACKET_FIFO_COUNT;

}

void radio_manual_calibration_idle(void){
	//Calibration Initial
	Strobe( RF_SIDLE );
	Strobe( RF_SCAL );
	__delay_cycles(10000000); //This can be optimized shorter
}

void radio_manual_idle(void){
	//Calibration Initial
	Strobe( RF_SIDLE );
}


void Transmit(unsigned char *buffer, unsigned char length)
{

	TransmitOn();
	RF1AIES |= BIT9;
	RF1AIFG &= ~BIT9;                         // Clear pending interrupts
	RF1AIE |= BIT9;                           // Enable TX end-of-packet interrupt
	WriteBurstReg(RF_TXFIFOWR, buffer, length);
	Strobe( RF_STX );                         // Strobe STX

}

void TransmitOn(void)
{

	//Setup CC1190 to LNA
	CC1190_LNA_Disable();
	CC1190_PA_Enable();
	CC1190_HGM_Enable();
	receiving_flag = 0;
	transmitting_flag = 1;
}

void ReceiveOn(void)
{
	//Setup CC1190 to LNA
	CC1190_PA_Disable();
	CC1190_LNA_Enable();
	CC1190_HGM_Enable();

	//Setup RF interrupts
	RF1AIES |= BIT9;                          // Falling edge of RFIFG9
	RF1AIFG &= ~BIT9;                         // Clear a pending interrupt
	RF1AIE  |= BIT9;                          // Enable the interrupt
	transmitting_flag = 0;
	receiving_flag = 1;

	// Radio is in IDLE following a TX, so strobe SRX to enter Receive Mode
	Strobe( RF_SRX );
}

void ReceiveOff(void)
{
  RF1AIE &= ~BIT9;                          // Disable RX interrupts
  RF1AIFG &= ~BIT9;                         // Clear pending IFG

  // It is possible that ReceiveOff is called while radio is receiving a packet.
  // Therefore, it is necessary to flush the RX FIFO after issuing IDLE strobe
  // such that the RXFIFO is empty prior to receiving a packet.
  Strobe( RF_SIDLE );
  Strobe( RF_SFRX  );
}

void radio_isr(void){
	if(receiving_flag)			    // RX end of packet
	  {
		unsigned char RxBufferLength = 0;

		// Read the length byte from the FIFO
		RxBufferLength = ReadSingleReg( RXBYTES ); // WARNING: If this ever becomes variable length you MUST check it's validity or risk buffer overrun!
		ReadBurstReg(RF_RXFIFORD, rf_rx_datalink_buffer, RxBufferLength);

		// Stop here to see contents of RxBuffer
		__no_operation();

		unsigned char rssi;
		unsigned char lqi;
		unsigned char crc_bit;

		rssi = rf_rx_datalink_buffer[RX_PACKET_LEN];
		crc_bit = (rf_rx_datalink_buffer[RF_DATALINK_PKT_LQI_LOC] & BIT7)>>7;
		lqi = (rf_rx_datalink_buffer[RF_DATALINK_PKT_LQI_LOC] & 0x7f);

		//DEBUG - Disable CRC bit check (see Errata)
		crc_bit = 1;
		if(crc_bit == 1){
			//Put into RX packet buffer
			put_fifo(&rf_datalink_rx_fifo_state_machine, &rf_datalink_rx_fifo_buffer, rf_rx_datalink_buffer);
		}

		else{
			__no_operation(); //Bad CRC = corrupt data, discard.
		}
		ReceiveOn();
	  }
	  else if(transmitting_flag)		    // TX end of packet
	  {
		if(rf_check_tx_fifo()){
			//Packet waiting to be transmitted
			radio_manual_idle(); //Why IDLE here? Self Calibration?
			RF1AIE &= ~BIT9;                    // Disable TX end-of-packet interrupt
			rf_get_next_tx_fifo();
		}
		else{
			//No packets remain to transmit
			RF1AIE &= ~BIT9;                    // Disable TX end-of-packet interrupt
			radio_manual_idle(); // Goto IDLE first to force self calibration
			ReceiveOn();
		}

	  }
	  else{
		  //Default to Receive
		  receiving_flag = 1;
		  transmitting_flag = 0;

		  //TO-DO: Add flash statistical save function to save error log counts
	  }
}

void radio_tx(unsigned char *buffer, unsigned char buffer_len){
	unsigned char tx_buffer[62];
	unsigned char i;
	//BUG: Doesn't check for buffer size too long...
	for(i=0;i<buffer_len;i++){
		tx_buffer[i] = buffer[i];
	}
	for(i=buffer_len;i<TX_PACKET_LEN;i++){
		tx_buffer[i] = 0xff;
	}

	Transmit((unsigned char *)tx_buffer, TX_PACKET_LEN);

}

void rf_tx_put_packet_buffer(unsigned char *packet_data_pointer, unsigned char length){
	put_fifo(&rf_datalink_tx_fifo_state_machine, &rf_datalink_tx_fifo_buffer, packet_data_pointer);
}


void rf_get_next_tx_fifo(void){
	get_fifo(&rf_datalink_tx_fifo_state_machine, rf_datalink_tx_fifo_buffer, (unsigned char *)rf_tx_datalink_buffer);
	//Transmit packet from queue
	Transmit(&rf_tx_datalink_buffer,TX_PACKET_LEN);
}

unsigned char rf_check_tx_fifo(void){
	if(rf_datalink_tx_fifo_state_machine.inwaiting>0){
		return 1;
	}

	else{
		return 0;
	}
}

void rf_housekeeping(void){
	__no_operation();
	unsigned char status;
	if(rf_check_tx_fifo() && !transmitting_flag){
		ReceiveOff();
		rf_get_next_tx_fifo();
		}
	else if(rf_datalink_rx_fifo_state_machine.inwaiting>0){
		//Get packet from queue
		status = get_fifo(&rf_datalink_rx_fifo_state_machine, &rf_datalink_rx_fifo_buffer, rf_rx_datalink_buffer);

		//Parse received packet
		rf_datalink_parse(&rf_rx_datalink_buffer);

		//Determine destination of RX'd packet
		if(strstr((char *)rf_datalink_packet_rx_struct.destination_callsign, (char *)local_callsign) != NULL){
			if(rf_datalink_packet_rx_struct.destination_identifier == local_device_id){
				//__no_operation(); //This device!
				rf_transport_parse((unsigned char *)rf_datalink_packet_rx_struct.payload, 0);
			}
		}

		else if(*strstr((char *)rf_datalink_packet_rx_struct.destination_callsign, (char *)"CQCQCQ")){
			//__no_operation(); //Broadcast
				rf_transport_parse((unsigned char *)rf_datalink_packet_rx_struct.payload, 1);
		}

		else{
			//__no_operation(); //All others
		}
	}
	else{
	}
}

unsigned char rf_tx_datalink_packet(
	char *src_callsign,
	unsigned char src_callsign_len,
	unsigned char src_callsign_id,
	char *dest_callsign,
	unsigned char dest_callsign_len,
	unsigned char dest_callsign_id,
	unsigned char packet_type,
	unsigned char packet_config,
	unsigned char payload_len,
	unsigned char *payload){

	unsigned int i = 0;

	__no_operation();
	//Check if any field is too large and return 0 if it is to indicate a failed input to developer
	if((src_callsign_len<=RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN) & (dest_callsign_len<=RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN) & (payload_len<=RF_DATALINK_PKT_PAYLOAD_LEN))
		{
		//Place source callsign into packet struct
		for(i=0; i<=src_callsign_len; i++){
			rf_datalink_packet_tx_struct.source_callsign[i] = src_callsign[i];
		}
		//Pad source callsign
		for(i=src_callsign_len; i<RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN; i++){
			rf_datalink_packet_tx_struct.source_callsign[i] = 0xFF; //Padding
		}

		//Source callsign identifier
		rf_datalink_packet_tx_struct.source_indetifier = src_callsign_id;

		//Place destination callsign into packet struct
		for(i=0; i<RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN; i++){
			rf_datalink_packet_tx_struct.destination_callsign[i] = dest_callsign[i];
		}

		//Pad destination callsign
		for(i=dest_callsign_len; i<RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN; i++){
			rf_datalink_packet_tx_struct.destination_callsign[i] = 0xFF; //Padding
		}

		//Destination callsign identifier
		rf_datalink_packet_tx_struct.destination_identifier = dest_callsign_id;
		rf_datalink_packet_tx_struct.packet_type = packet_type;
		rf_datalink_packet_tx_struct.packet_config = packet_config;
		rf_datalink_packet_tx_struct.payload_length = payload_len;

		//Place payload into packet struct
		for(i=0; i<payload_len; i++){
			rf_datalink_packet_tx_struct.payload[i] = payload[i];
		}

		//Pad payload
		for(i=payload_len; i<RF_DATALINK_PKT_PAYLOAD_LEN; i++){
			rf_datalink_packet_tx_struct.payload[i] = 0xFF; //Padding
		}

		rf_datalink_packet_tx_struct.rssi = 0xAA; // RSSI only for RX, placing dummy bytes
		rf_datalink_packet_tx_struct.lqi = 0xBB; //LQI only for RX, placing dummy bytes

		//rf_put_transport(&rf_datalink_packet_tx_struct, 62);
		rf_rawpacket_tx(&rf_datalink_packet_tx_struct); // Limited to 62 bytes long! Should be a more clean way to do this BUG
		__no_operation();
		return 1;
	}
	else{
		return 0; //An argument is too large: ERROR
	}
}

void rf_rawpacket_tx(RF_DATALINK_PACKET_STRUCT *packet_data_pointer){
	__no_operation();
	rf_tx_put_packet_buffer((unsigned char *)packet_data_pointer, 62); //Chang length to #DEFINE
	__no_operation();
}



void rf_datalink_parse(unsigned char *packet){
	unsigned char i;
	for(i=RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC; i<RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC_LEN; i++){
		rf_datalink_packet_rx_struct.source_callsign[(i-RF_DATALINK_PKT_SOURCE_CALLSIGN_LOC)] = packet[i];
	}
	rf_datalink_packet_rx_struct.source_indetifier = packet[RF_DATALINK_PKT_SOURCE_CALLSIGN_ID_LOC];
	for(i=RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC; i<(RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC+RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC_LEN); i++){
		rf_datalink_packet_rx_struct.destination_callsign[(i-RF_DATALINK_PKT_DESTINATION_CALLSIGN_LOC)] = packet[i];
	}
	for(i=RF_DATALINK_PKT_PAYLOAD_LOC; i<(RF_DATALINK_PKT_PAYLOAD_LOC+RF_DATALINK_PKT_PAYLOAD_LEN); i++){
			rf_datalink_packet_rx_struct.payload[(i-RF_DATALINK_PKT_PAYLOAD_LOC)] = packet[i];
	}
	rf_datalink_packet_rx_struct.destination_identifier = packet[RF_DATALINK_PKT_DESTINATION_CALLSIGN_ID_LOC];
	rf_datalink_packet_rx_struct.packet_type = packet[RF_DATALINK_PKT_PKT_TYPE_LOC];
	rf_datalink_packet_rx_struct.packet_config = packet[RF_DATALINK_PKT_PKT_CONFIG_LOC];
	rf_datalink_packet_rx_struct.payload_length = packet[RF_DATALINK_PKT_PKT_LEN_LOC];
	rf_datalink_packet_rx_struct.rssi = packet[RF_DATALINK_PKT_RSSI_LOC]; // RSSI only for RX

	//LQI is only bits 0-6
	rf_datalink_packet_rx_struct.lqi = packet[RF_DATALINK_PKT_LQI_LOC]; //LQI only for RX
	rf_datalink_packet_rx_struct.lqi = (rf_datalink_packet_rx_struct.lqi & 0x7f);

	__no_operation();
}


void CC430_Program_Freq(unsigned char freq2, unsigned char freq1, unsigned char freq0){
	//Radio core must be in IDLE state to change frequency
	Strobe(RF_SIDLE);

	//Write carrier frequency bytes (24-bit word, 3 bytes)
	WriteSingleReg(FREQ2,   freq2);
	WriteSingleReg(FREQ1,   freq1);
	WriteSingleReg(FREQ0,   freq0);

	//Strobe the RF core no operation (not sure if really needed..)
	Strobe(RF_SNOP);
}

unsigned char CC430_Check_Transmitting_Flag(void){
	return transmitting_flag;
}
