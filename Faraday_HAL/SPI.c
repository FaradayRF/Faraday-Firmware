/*
 * SPI.c
 *
 *  Created on: Oct 13, 2015
 *      Author: Brent
 */

#include <msp430.h>
#include "SPI.h"

void spi_tx(unsigned char tx){
	  while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	  UCB0TXBUF = tx;                     // Transmit first character
	  //__delay_cycles(50);
}
