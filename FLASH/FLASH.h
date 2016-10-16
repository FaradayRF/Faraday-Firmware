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

/** @brief FLASH Memory Chip Enable SPI
 *
 * 	Common function used to enable SPI operation by
 * 	setting the SPI chip select and other GPIO.
 *
 * 	@bug This is a potentially dangerous operation since it is sharing the SPI bus with other SPI IC(s) and not cordinated.
 *
@{**/
void Faraday_FLASH_SPI_Enable(void);
/** @}*/


/** @brief FLASH Memory Chip Disable SPI
 *
 * 	Common function used to disable SPI operation by
 * 	setting the SPI chip select and other GPIO.
 *
 * 	@bug This is a potentially dangerous operation since it is sharing the SPI bus with other SPI IC(s) and not cordinated.
 *
@{**/
void Faraday_FLASH_SPI_Disable(void);
/** @}*/


/** @brief FLASH Memory Manufacture and Device ID
 *
 * 	This function accepts a byte array and returns into the byte array
 * 	the FLASH manufacturing ID and Device ID bytes from the onboard
 * 	SPI FLASH device.
 *
 * 	@param id_data Pointer to a passed by reference array of size 4 that will be updated with the 4 manufacture and device ID bytes
 *
 *	@bug Is the correct returned number of bytes 3 or 4? This is unclear
@{**/
void Faraday_FLASH_Get_ID(unsigned char * id_data);
/** @}*/


/** @brief Get FLASH Status
 *
 * 	This function returns the current FLASH device status byte.
 *
 * 	@return Returns the current status byte
 *
@{**/
unsigned char Faraday_FLASH_Get_Status(void);
/** @}*/


/** @brief FLASH Write Enable
 *
 * 	This function enables the WLEN (Write Enable) bit in the device status
 * 	register. The WLEN bit must be set HIGH before each write operation,
 * 	including erase.
 *
 *
@{**/
void Faraday_FLASH_Write_Enable(void);
/** @}*/


void Faraday_FLASH_Write_Disable(void);

#endif /* FLASH_FLASH_H_ */
