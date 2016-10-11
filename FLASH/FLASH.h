/** @file FLASH.h
 *  @brief Hardware abstraction for the onboard Faraday FLASH memory IC.
 *
 *  The functions below provide input/output ability with the onboard
 *  FLASH memory IC using SPI. Read and Write functioanlity is supportted.
 *
 */

#ifndef FLASH_FLASH_H_
#define FLASH_FLASH_H_


/** @brief SPI FLASH Memory Chip Enable
 *
 * 	Enables the SPI FLASH IC's "Chip Enable" pin. This pin is Active LOW.
 *
@{**/
void Faraday_FLASH_CE_Enable(void);
/** @}*/


/** @brief SPI FLASH Memory Chip Disable
 *
 * 	Disables the SPI FLASH IC's "Chip Enable" pin. This pin is Active LOW.
 *
@{**/
void Faraday_FLASH_CE_Disable(void);
/** @}*/


/** @brief FLASH Memory Chip HOLD Enable
 *
 * 	Enables the FLASH IC's "HOLD pin. This pin is Active LOW and allows the
 * 	read/write operations to be paused and resumed (to allow other higher
 * 	priority SPI bus operations to occur if needed).
 *
@{**/
void Faraday_FLASH_Hold_Enable(void);
/** @}*/


/** @brief FLASH Memory Chip HOLD Disable
 *
 * 	Disable the FLASH IC's "HOLD pin. This pin is Active LOW and allows the
 * 	read/write operations to be paused and resumed (to allow other higher
 * 	priority SPI bus operations to occur if needed).
 *
@{**/
void Faraday_FLASH_Hold_Disable(void);
/** @}*/


#endif /* FLASH_FLASH_H_ */
