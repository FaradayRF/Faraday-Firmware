/** @file SPI.h
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

#ifndef FARADAY_HAL_SPI_H_
#define FARADAY_HAL_SPI_H_


/**@brief Shift a byte into the SPI transmit register (polling)
 *
 * This is the main function used to directly shift a byte into the SPI transmit register
 * to transmit the byte over SPI.
 *
 * @note This routine is a polling method SPI interaction.
 *
 *
 */
void spi_tx(unsigned char tx);

#endif /* FARADAY_HAL_SPI_H_ */
