/** @file SPI.c
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

/* -- Includes -- */

/* standard includes */
#include "cc430f6137.h"
#include "SPI.h"

void spi_tx(unsigned char tx){
	  while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	  UCB0TXBUF = tx;                     // Transmit first character
}
