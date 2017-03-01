/** @file Version.h
 *  @brief Header file that contains firmware revision information
 *
 *  This files contains information used to determine firmware
 *  revision identity.
 *
 */

/** @name Firmware Revision Constants
*
* 	Constants used for the firmware revision identification
*
@{**/
#define FIRMWARE_REVISION_SIZE 4 /**< Firmware revision is size long*/
/** @}*/

#ifndef VERSION_H_
#define VERSION_H_

const unsigned long firmware_revision = 0xc1489a4; //

#endif /* VERSION_H_ */
