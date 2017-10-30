/** @file SPI.h
 * 	@brief Hardware abstraction functions for SPI
 *
 * 	These functions provide an abstraction layer for the CC430 SPI peripheral.
 *
 */

#ifndef FARADAY_HAL_SPI_H_
#define FARADAY_HAL_SPI_H_


/* DEFINITIONS */
#define SPI_DUMMY_BYTE 0x00
#define SPI_HAL_CS_SRAM BIT0
#define SPI_HAL_CS_I2C BIT1
#define SPI_BYTE_CYCLES 2064

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
unsigned char spi_rx_byte(unsigned char delay_cycles);
unsigned char spi_enable_chip_select(unsigned char SPI_HAL_CS);
unsigned char spi_disable_chip_select(unsigned char SPI_HAL_CS);

/** @brief Enable the SPI SRAM IC chip select pin
 *
 *	Enables the chip select pin on the SRAM IC.
 *
 */
void Faraday_SRAM_CS_Enable(void);


/** @brief Disable the SPI SRAM IC chip select pin
 *
 * Disables the chip select pin on the SRAM IC.
 *
 */
void Faraday_SRAM_CS_Disable(void);


/** @brief Enables the SPI SRAM IC HOLD pin
 *
 * Enables the chip select pin on the SRAM IC.
 *
 */
void Faraday_SRAM_Hold_Enable(void);


/** @brief Disable the SPI SRAM IC HOLD pin
 *
 * Disables the HOLD pin on the SRAM IC.
 *
 */
void Faraday_SRAM_Hold_Disable(void);

void Faraday_C2120_CS_Enable(void);

void Faraday_C2120_CS_Disable(void);

#endif /* FARADAY_HAL_SPI_H_ */
