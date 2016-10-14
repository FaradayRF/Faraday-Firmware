/* ============================================================================ */
/* Copyright (c) 2015, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* CC430x613x devices.
*
* Texas Instruments, Version 1.9
*
* Rev. 1.0, First Release
* Rev. 1.1, added TLV definitions
* Rev. 1.2, added some more DMA Trigger definitions
* Rev. 1.3, fixed LCDMEM access
* Rev. 1.4, changed RTC_A_VECTOR to RTC_VECTOR
* Rev. 1.5, clean up of Flash section
* Rev. 1.6, Changed access type of DMAxSZ registers to word only
* Rev. 1.7  Changed access type of TimerA/B registers to word only
* Rev. 1.8  Removed not available Definitions: RF1AIFIV_RFRXIFG and RF1AIFIV_TFRXIFG
* Rev. 1.9  Removed not available Definitions: CRCDIRB and CRCRESR
*
*
********************************************************************/

#ifndef __cc430x613x
#define __cc430x613x

#define __MSP430_HEADER_VERSION__ 1173

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/* PERIPHERAL FILE MAP                                                        */
/*----------------------------------------------------------------------------*/

#ifndef SFR_8BIT
/* External references resolved by a device-specific linker command file */
#define SFR_8BIT(address)   extern volatile unsigned char address
#define SFR_16BIT(address)  extern volatile unsigned int address
//#define SFR_20BIT(address)  extern volatile unsigned int address
typedef void (* __SFR_FARPTR)();
#define SFR_20BIT(address) extern __SFR_FARPTR address
#define SFR_32BIT(address)  extern volatile unsigned long address

#endif


/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                      (0x0001)
#define Z                      (0x0002)
#define N                      (0x0004)
#define V                      (0x0100)
#define GIE                    (0x0008)
#define CPUOFF                 (0x0010)
#define OSCOFF                 (0x0020)
#define SCG0                   (0x0040)
#define SCG1                   (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define LPM0                   (CPUOFF)
#define LPM1                   (SCG0+CPUOFF)
#define LPM2                   (SCG1+CPUOFF)
#define LPM3                   (SCG1+SCG0+CPUOFF)
#define LPM4                   (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits              (CPUOFF)
#define LPM1_bits              (SCG0+CPUOFF)
#define LPM2_bits              (SCG1+CPUOFF)
#define LPM3_bits              (SCG1+SCG0+CPUOFF)
#define LPM4_bits              (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"
#include <intrinsics.h>

#define LPM0      __bis_SR_register(LPM0_bits)         /* Enter Low Power Mode 0 */
#define LPM0_EXIT __bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      __bis_SR_register(LPM1_bits)         /* Enter Low Power Mode 1 */
#define LPM1_EXIT __bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      __bis_SR_register(LPM2_bits)         /* Enter Low Power Mode 2 */
#define LPM2_EXIT __bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      __bis_SR_register(LPM3_bits)         /* Enter Low Power Mode 3 */
#define LPM3_EXIT __bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      __bis_SR_register(LPM4_bits)         /* Enter Low Power Mode 4 */
#define LPM4_EXIT __bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* CPU
************************************************************/
#define __MSP430_HAS_MSP430XV2_CPU__                /* Definition to show that it has MSP430XV2 CPU */
#define __MSP430F5XX_6XX_FAMILY__

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* ADC12 PLUS
************************************************************/
#define __MSP430_HAS_ADC12_PLUS__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC12_PLUS__ 0x0700
#define ADC12_A_BASE           __MSP430_BASEADDRESS_ADC12_PLUS__

SFR_16BIT(ADC12CTL0);                         /* ADC12+ Control 0 */
SFR_8BIT(ADC12CTL0_L);                        /* ADC12+ Control 0 */
SFR_8BIT(ADC12CTL0_H);                        /* ADC12+ Control 0 */
SFR_16BIT(ADC12CTL1);                         /* ADC12+ Control 1 */
SFR_8BIT(ADC12CTL1_L);                        /* ADC12+ Control 1 */
SFR_8BIT(ADC12CTL1_H);                        /* ADC12+ Control 1 */
SFR_16BIT(ADC12CTL2);                         /* ADC12+ Control 2 */
SFR_8BIT(ADC12CTL2_L);                        /* ADC12+ Control 2 */
SFR_8BIT(ADC12CTL2_H);                        /* ADC12+ Control 2 */
SFR_16BIT(ADC12IFG);                          /* ADC12+ Interrupt Flag */
SFR_8BIT(ADC12IFG_L);                         /* ADC12+ Interrupt Flag */
SFR_8BIT(ADC12IFG_H);                         /* ADC12+ Interrupt Flag */
SFR_16BIT(ADC12IE);                           /* ADC12+ Interrupt Enable */
SFR_8BIT(ADC12IE_L);                          /* ADC12+ Interrupt Enable */
SFR_8BIT(ADC12IE_H);                          /* ADC12+ Interrupt Enable */
SFR_16BIT(ADC12IV);                           /* ADC12+ Interrupt Vector Word */
SFR_8BIT(ADC12IV_L);                          /* ADC12+ Interrupt Vector Word */
SFR_8BIT(ADC12IV_H);                          /* ADC12+ Interrupt Vector Word */

SFR_16BIT(ADC12MEM0);                         /* ADC12 Conversion Memory 0 */
SFR_8BIT(ADC12MEM0_L);                        /* ADC12 Conversion Memory 0 */
SFR_8BIT(ADC12MEM0_H);                        /* ADC12 Conversion Memory 0 */
SFR_16BIT(ADC12MEM1);                         /* ADC12 Conversion Memory 1 */
SFR_8BIT(ADC12MEM1_L);                        /* ADC12 Conversion Memory 1 */
SFR_8BIT(ADC12MEM1_H);                        /* ADC12 Conversion Memory 1 */
SFR_16BIT(ADC12MEM2);                         /* ADC12 Conversion Memory 2 */
SFR_8BIT(ADC12MEM2_L);                        /* ADC12 Conversion Memory 2 */
SFR_8BIT(ADC12MEM2_H);                        /* ADC12 Conversion Memory 2 */
SFR_16BIT(ADC12MEM3);                         /* ADC12 Conversion Memory 3 */
SFR_8BIT(ADC12MEM3_L);                        /* ADC12 Conversion Memory 3 */
SFR_8BIT(ADC12MEM3_H);                        /* ADC12 Conversion Memory 3 */
SFR_16BIT(ADC12MEM4);                         /* ADC12 Conversion Memory 4 */
SFR_8BIT(ADC12MEM4_L);                        /* ADC12 Conversion Memory 4 */
SFR_8BIT(ADC12MEM4_H);                        /* ADC12 Conversion Memory 4 */
SFR_16BIT(ADC12MEM5);                         /* ADC12 Conversion Memory 5 */
SFR_8BIT(ADC12MEM5_L);                        /* ADC12 Conversion Memory 5 */
SFR_8BIT(ADC12MEM5_H);                        /* ADC12 Conversion Memory 5 */
SFR_16BIT(ADC12MEM6);                         /* ADC12 Conversion Memory 6 */
SFR_8BIT(ADC12MEM6_L);                        /* ADC12 Conversion Memory 6 */
SFR_8BIT(ADC12MEM6_H);                        /* ADC12 Conversion Memory 6 */
SFR_16BIT(ADC12MEM7);                         /* ADC12 Conversion Memory 7 */
SFR_8BIT(ADC12MEM7_L);                        /* ADC12 Conversion Memory 7 */
SFR_8BIT(ADC12MEM7_H);                        /* ADC12 Conversion Memory 7 */
SFR_16BIT(ADC12MEM8);                         /* ADC12 Conversion Memory 8 */
SFR_8BIT(ADC12MEM8_L);                        /* ADC12 Conversion Memory 8 */
SFR_8BIT(ADC12MEM8_H);                        /* ADC12 Conversion Memory 8 */
SFR_16BIT(ADC12MEM9);                         /* ADC12 Conversion Memory 9 */
SFR_8BIT(ADC12MEM9_L);                        /* ADC12 Conversion Memory 9 */
SFR_8BIT(ADC12MEM9_H);                        /* ADC12 Conversion Memory 9 */
SFR_16BIT(ADC12MEM10);                        /* ADC12 Conversion Memory 10 */
SFR_8BIT(ADC12MEM10_L);                       /* ADC12 Conversion Memory 10 */
SFR_8BIT(ADC12MEM10_H);                       /* ADC12 Conversion Memory 10 */
SFR_16BIT(ADC12MEM11);                        /* ADC12 Conversion Memory 11 */
SFR_8BIT(ADC12MEM11_L);                       /* ADC12 Conversion Memory 11 */
SFR_8BIT(ADC12MEM11_H);                       /* ADC12 Conversion Memory 11 */
SFR_16BIT(ADC12MEM12);                        /* ADC12 Conversion Memory 12 */
SFR_8BIT(ADC12MEM12_L);                       /* ADC12 Conversion Memory 12 */
SFR_8BIT(ADC12MEM12_H);                       /* ADC12 Conversion Memory 12 */
SFR_16BIT(ADC12MEM13);                        /* ADC12 Conversion Memory 13 */
SFR_8BIT(ADC12MEM13_L);                       /* ADC12 Conversion Memory 13 */
SFR_8BIT(ADC12MEM13_H);                       /* ADC12 Conversion Memory 13 */
SFR_16BIT(ADC12MEM14);                        /* ADC12 Conversion Memory 14 */
SFR_8BIT(ADC12MEM14_L);                       /* ADC12 Conversion Memory 14 */
SFR_8BIT(ADC12MEM14_H);                       /* ADC12 Conversion Memory 14 */
SFR_16BIT(ADC12MEM15);                        /* ADC12 Conversion Memory 15 */
SFR_8BIT(ADC12MEM15_L);                       /* ADC12 Conversion Memory 15 */
SFR_8BIT(ADC12MEM15_H);                       /* ADC12 Conversion Memory 15 */
#define ADC12MEM_              ADC12MEM       /* ADC12 Conversion Memory */
#ifdef __ASM_HEADER__
#define ADC12MEM               ADC12MEM0      /* ADC12 Conversion Memory (for assembler) */
#else
#define ADC12MEM               ((int*)        &ADC12MEM0) /* ADC12 Conversion Memory (for C) */
#endif

SFR_8BIT(ADC12MCTL0);                         /* ADC12 Memory Control 0 */
SFR_8BIT(ADC12MCTL1);                         /* ADC12 Memory Control 1 */
SFR_8BIT(ADC12MCTL2);                         /* ADC12 Memory Control 2 */
SFR_8BIT(ADC12MCTL3);                         /* ADC12 Memory Control 3 */
SFR_8BIT(ADC12MCTL4);                         /* ADC12 Memory Control 4 */
SFR_8BIT(ADC12MCTL5);                         /* ADC12 Memory Control 5 */
SFR_8BIT(ADC12MCTL6);                         /* ADC12 Memory Control 6 */
SFR_8BIT(ADC12MCTL7);                         /* ADC12 Memory Control 7 */
SFR_8BIT(ADC12MCTL8);                         /* ADC12 Memory Control 8 */
SFR_8BIT(ADC12MCTL9);                         /* ADC12 Memory Control 9 */
SFR_8BIT(ADC12MCTL10);                        /* ADC12 Memory Control 10 */
SFR_8BIT(ADC12MCTL11);                        /* ADC12 Memory Control 11 */
SFR_8BIT(ADC12MCTL12);                        /* ADC12 Memory Control 12 */
SFR_8BIT(ADC12MCTL13);                        /* ADC12 Memory Control 13 */
SFR_8BIT(ADC12MCTL14);                        /* ADC12 Memory Control 14 */
SFR_8BIT(ADC12MCTL15);                        /* ADC12 Memory Control 15 */
#define ADC12MCTL_             ADC12MCTL      /* ADC12 Memory Control */
#ifdef __ASM_HEADER__
#define ADC12MCTL              ADC12MCTL0     /* ADC12 Memory Control (for assembler) */
#else
#define ADC12MCTL              ((char*)       &ADC12MCTL0) /* ADC12 Memory Control (for C) */
#endif

/* ADC12CTL0 Control Bits */
#define ADC12SC                (0x0001)       /* ADC12 Start Conversion */
#define ADC12ENC               (0x0002)       /* ADC12 Enable Conversion */
#define ADC12TOVIE             (0x0004)       /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE              (0x0008)       /* ADC12 Overflow interrupt enable */
#define ADC12ON                (0x0010)       /* ADC12 On/enable */
#define ADC12REFON             (0x0020)       /* ADC12 Reference on */
#define ADC12REF2_5V           (0x0040)       /* ADC12 Ref 0:1.5V / 1:2.5V */
#define ADC12MSC               (0x0080)       /* ADC12 Multiple SampleConversion */
#define ADC12SHT00             (0x0100)       /* ADC12 Sample Hold 0 Select Bit: 0 */
#define ADC12SHT01             (0x0200)       /* ADC12 Sample Hold 0 Select Bit: 1 */
#define ADC12SHT02             (0x0400)       /* ADC12 Sample Hold 0 Select Bit: 2 */
#define ADC12SHT03             (0x0800)       /* ADC12 Sample Hold 0 Select Bit: 3 */
#define ADC12SHT10             (0x1000)       /* ADC12 Sample Hold 1 Select Bit: 0 */
#define ADC12SHT11             (0x2000)       /* ADC12 Sample Hold 1 Select Bit: 1 */
#define ADC12SHT12             (0x4000)       /* ADC12 Sample Hold 1 Select Bit: 2 */
#define ADC12SHT13             (0x8000)       /* ADC12 Sample Hold 1 Select Bit: 3 */

/* ADC12CTL0 Control Bits */
#define ADC12SC_L              (0x0001)       /* ADC12 Start Conversion */
#define ADC12ENC_L             (0x0002)       /* ADC12 Enable Conversion */
#define ADC12TOVIE_L           (0x0004)       /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE_L            (0x0008)       /* ADC12 Overflow interrupt enable */
#define ADC12ON_L              (0x0010)       /* ADC12 On/enable */
#define ADC12REFON_L           (0x0020)       /* ADC12 Reference on */
#define ADC12REF2_5V_L         (0x0040)       /* ADC12 Ref 0:1.5V / 1:2.5V */
#define ADC12MSC_L             (0x0080)       /* ADC12 Multiple SampleConversion */

/* ADC12CTL0 Control Bits */
#define ADC12SHT00_H           (0x0001)       /* ADC12 Sample Hold 0 Select Bit: 0 */
#define ADC12SHT01_H           (0x0002)       /* ADC12 Sample Hold 0 Select Bit: 1 */
#define ADC12SHT02_H           (0x0004)       /* ADC12 Sample Hold 0 Select Bit: 2 */
#define ADC12SHT03_H           (0x0008)       /* ADC12 Sample Hold 0 Select Bit: 3 */
#define ADC12SHT10_H           (0x0010)       /* ADC12 Sample Hold 1 Select Bit: 0 */
#define ADC12SHT11_H           (0x0020)       /* ADC12 Sample Hold 1 Select Bit: 1 */
#define ADC12SHT12_H           (0x0040)       /* ADC12 Sample Hold 1 Select Bit: 2 */
#define ADC12SHT13_H           (0x0080)       /* ADC12 Sample Hold 1 Select Bit: 3 */

#define ADC12SHT0_0            (0*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 0 */
#define ADC12SHT0_1            (1*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 1 */
#define ADC12SHT0_2            (2*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 2 */
#define ADC12SHT0_3            (3*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 3 */
#define ADC12SHT0_4            (4*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 4 */
#define ADC12SHT0_5            (5*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 5 */
#define ADC12SHT0_6            (6*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 6 */
#define ADC12SHT0_7            (7*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 7 */
#define ADC12SHT0_8            (8*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 8 */
#define ADC12SHT0_9            (9*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 9 */
#define ADC12SHT0_10           (10*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 10 */
#define ADC12SHT0_11           (11*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 11 */
#define ADC12SHT0_12           (12*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 12 */
#define ADC12SHT0_13           (13*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 13 */
#define ADC12SHT0_14           (14*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 14 */
#define ADC12SHT0_15           (15*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 15 */

#define ADC12SHT1_0            (0*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 0 */
#define ADC12SHT1_1            (1*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 1 */
#define ADC12SHT1_2            (2*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 2 */
#define ADC12SHT1_3            (3*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 3 */
#define ADC12SHT1_4            (4*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 4 */
#define ADC12SHT1_5            (5*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 5 */
#define ADC12SHT1_6            (6*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 6 */
#define ADC12SHT1_7            (7*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 7 */
#define ADC12SHT1_8            (8*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 8 */
#define ADC12SHT1_9            (9*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 9 */
#define ADC12SHT1_10           (10*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 10 */
#define ADC12SHT1_11           (11*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 11 */
#define ADC12SHT1_12           (12*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 12 */
#define ADC12SHT1_13           (13*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 13 */
#define ADC12SHT1_14           (14*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 14 */
#define ADC12SHT1_15           (15*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 15 */

/* ADC12CTL1 Control Bits */
#define ADC12BUSY              (0x0001)       /* ADC12 Busy */
#define ADC12CONSEQ0           (0x0002)       /* ADC12 Conversion Sequence Select Bit: 0 */
#define ADC12CONSEQ1           (0x0004)       /* ADC12 Conversion Sequence Select Bit: 1 */
#define ADC12SSEL0             (0x0008)       /* ADC12 Clock Source Select Bit: 0 */
#define ADC12SSEL1             (0x0010)       /* ADC12 Clock Source Select Bit: 1 */
#define ADC12DIV0              (0x0020)       /* ADC12 Clock Divider Select Bit: 0 */
#define ADC12DIV1              (0x0040)       /* ADC12 Clock Divider Select Bit: 1 */
#define ADC12DIV2              (0x0080)       /* ADC12 Clock Divider Select Bit: 2 */
#define ADC12ISSH              (0x0100)       /* ADC12 Invert Sample Hold Signal */
#define ADC12SHP               (0x0200)       /* ADC12 Sample/Hold Pulse Mode */
#define ADC12SHS0              (0x0400)       /* ADC12 Sample/Hold Source Bit: 0 */
#define ADC12SHS1              (0x0800)       /* ADC12 Sample/Hold Source Bit: 1 */
#define ADC12CSTARTADD0        (0x1000)       /* ADC12 Conversion Start Address Bit: 0 */
#define ADC12CSTARTADD1        (0x2000)       /* ADC12 Conversion Start Address Bit: 1 */
#define ADC12CSTARTADD2        (0x4000)       /* ADC12 Conversion Start Address Bit: 2 */
#define ADC12CSTARTADD3        (0x8000)       /* ADC12 Conversion Start Address Bit: 3 */

/* ADC12CTL1 Control Bits */
#define ADC12BUSY_L            (0x0001)       /* ADC12 Busy */
#define ADC12CONSEQ0_L         (0x0002)       /* ADC12 Conversion Sequence Select Bit: 0 */
#define ADC12CONSEQ1_L         (0x0004)       /* ADC12 Conversion Sequence Select Bit: 1 */
#define ADC12SSEL0_L           (0x0008)       /* ADC12 Clock Source Select Bit: 0 */
#define ADC12SSEL1_L           (0x0010)       /* ADC12 Clock Source Select Bit: 1 */
#define ADC12DIV0_L            (0x0020)       /* ADC12 Clock Divider Select Bit: 0 */
#define ADC12DIV1_L            (0x0040)       /* ADC12 Clock Divider Select Bit: 1 */
#define ADC12DIV2_L            (0x0080)       /* ADC12 Clock Divider Select Bit: 2 */

/* ADC12CTL1 Control Bits */
#define ADC12ISSH_H            (0x0001)       /* ADC12 Invert Sample Hold Signal */
#define ADC12SHP_H             (0x0002)       /* ADC12 Sample/Hold Pulse Mode */
#define ADC12SHS0_H            (0x0004)       /* ADC12 Sample/Hold Source Bit: 0 */
#define ADC12SHS1_H            (0x0008)       /* ADC12 Sample/Hold Source Bit: 1 */
#define ADC12CSTARTADD0_H      (0x0010)       /* ADC12 Conversion Start Address Bit: 0 */
#define ADC12CSTARTADD1_H      (0x0020)       /* ADC12 Conversion Start Address Bit: 1 */
#define ADC12CSTARTADD2_H      (0x0040)       /* ADC12 Conversion Start Address Bit: 2 */
#define ADC12CSTARTADD3_H      (0x0080)       /* ADC12 Conversion Start Address Bit: 3 */

#define ADC12CONSEQ_0          (0*2u)         /* ADC12 Conversion Sequence Select: 0 */
#define ADC12CONSEQ_1          (1*2u)         /* ADC12 Conversion Sequence Select: 1 */
#define ADC12CONSEQ_2          (2*2u)         /* ADC12 Conversion Sequence Select: 2 */
#define ADC12CONSEQ_3          (3*2u)         /* ADC12 Conversion Sequence Select: 3 */

#define ADC12SSEL_0            (0*8u)         /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1            (1*8u)         /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2            (2*8u)         /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3            (3*8u)         /* ADC12 Clock Source Select: 3 */

#define ADC12DIV_0             (0*0x20u)      /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1             (1*0x20u)      /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2             (2*0x20u)      /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3             (3*0x20u)      /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4             (4*0x20u)      /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5             (5*0x20u)      /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6             (6*0x20u)      /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7             (7*0x20u)      /* ADC12 Clock Divider Select: 7 */

#define ADC12SHS_0             (0*0x400u)     /* ADC12 Sample/Hold Source: 0 */
#define ADC12SHS_1             (1*0x400u)     /* ADC12 Sample/Hold Source: 1 */
#define ADC12SHS_2             (2*0x400u)     /* ADC12 Sample/Hold Source: 2 */
#define ADC12SHS_3             (3*0x400u)     /* ADC12 Sample/Hold Source: 3 */

#define ADC12CSTARTADD_0       (0*0x1000u)    /* ADC12 Conversion Start Address: 0 */
#define ADC12CSTARTADD_1       (1*0x1000u)    /* ADC12 Conversion Start Address: 1 */
#define ADC12CSTARTADD_2       (2*0x1000u)    /* ADC12 Conversion Start Address: 2 */
#define ADC12CSTARTADD_3       (3*0x1000u)    /* ADC12 Conversion Start Address: 3 */
#define ADC12CSTARTADD_4       (4*0x1000u)    /* ADC12 Conversion Start Address: 4 */
#define ADC12CSTARTADD_5       (5*0x1000u)    /* ADC12 Conversion Start Address: 5 */
#define ADC12CSTARTADD_6       (6*0x1000u)    /* ADC12 Conversion Start Address: 6 */
#define ADC12CSTARTADD_7       (7*0x1000u)    /* ADC12 Conversion Start Address: 7 */
#define ADC12CSTARTADD_8       (8*0x1000u)    /* ADC12 Conversion Start Address: 8 */
#define ADC12CSTARTADD_9       (9*0x1000u)    /* ADC12 Conversion Start Address: 9 */
#define ADC12CSTARTADD_10      (10*0x1000u)   /* ADC12 Conversion Start Address: 10 */
#define ADC12CSTARTADD_11      (11*0x1000u)   /* ADC12 Conversion Start Address: 11 */
#define ADC12CSTARTADD_12      (12*0x1000u)   /* ADC12 Conversion Start Address: 12 */
#define ADC12CSTARTADD_13      (13*0x1000u)   /* ADC12 Conversion Start Address: 13 */
#define ADC12CSTARTADD_14      (14*0x1000u)   /* ADC12 Conversion Start Address: 14 */
#define ADC12CSTARTADD_15      (15*0x1000u)   /* ADC12 Conversion Start Address: 15 */

/* ADC12CTL2 Control Bits */
#define ADC12REFBURST          (0x0001)       /* ADC12+ Reference Burst */
#define ADC12REFOUT            (0x0002)       /* ADC12+ Reference Out */
#define ADC12SR                (0x0004)       /* ADC12+ Sampling Rate */
#define ADC12DF                (0x0008)       /* ADC12+ Data Format */
#define ADC12RES0              (0x0010)       /* ADC12+ Resolution Bit: 0 */
#define ADC12RES1              (0x0020)       /* ADC12+ Resolution Bit: 1 */
#define ADC12TCOFF             (0x0080)       /* ADC12+ Temperature Sensor Off */
#define ADC12PDIV              (0x0100)       /* ADC12+ predivider 0:/1   1:/4 */

/* ADC12CTL2 Control Bits */
#define ADC12REFBURST_L        (0x0001)       /* ADC12+ Reference Burst */
#define ADC12REFOUT_L          (0x0002)       /* ADC12+ Reference Out */
#define ADC12SR_L              (0x0004)       /* ADC12+ Sampling Rate */
#define ADC12DF_L              (0x0008)       /* ADC12+ Data Format */
#define ADC12RES0_L            (0x0010)       /* ADC12+ Resolution Bit: 0 */
#define ADC12RES1_L            (0x0020)       /* ADC12+ Resolution Bit: 1 */
#define ADC12TCOFF_L           (0x0080)       /* ADC12+ Temperature Sensor Off */

/* ADC12CTL2 Control Bits */
#define ADC12PDIV_H            (0x0001)       /* ADC12+ predivider 0:/1   1:/4 */

#define ADC12RES_0             (0x0000)       /* ADC12+ Resolution : 8 Bit */
#define ADC12RES_1             (0x0010)       /* ADC12+ Resolution : 10 Bit */
#define ADC12RES_2             (0x0020)       /* ADC12+ Resolution : 12 Bit */
#define ADC12RES_3             (0x0030)       /* ADC12+ Resolution : reserved */

/* ADC12MCTLx Control Bits */
#define ADC12INCH0             (0x0001)       /* ADC12 Input Channel Select Bit 0 */
#define ADC12INCH1             (0x0002)       /* ADC12 Input Channel Select Bit 1 */
#define ADC12INCH2             (0x0004)       /* ADC12 Input Channel Select Bit 2 */
#define ADC12INCH3             (0x0008)       /* ADC12 Input Channel Select Bit 3 */
#define ADC12SREF0             (0x0010)       /* ADC12 Select Reference Bit 0 */
#define ADC12SREF1             (0x0020)       /* ADC12 Select Reference Bit 1 */
#define ADC12SREF2             (0x0040)       /* ADC12 Select Reference Bit 2 */
#define ADC12EOS               (0x0080)       /* ADC12 End of Sequence */

#define ADC12INCH_0            (0x0000)       /* ADC12 Input Channel 0 */
#define ADC12INCH_1            (0x0001)       /* ADC12 Input Channel 1 */
#define ADC12INCH_2            (0x0002)       /* ADC12 Input Channel 2 */
#define ADC12INCH_3            (0x0003)       /* ADC12 Input Channel 3 */
#define ADC12INCH_4            (0x0004)       /* ADC12 Input Channel 4 */
#define ADC12INCH_5            (0x0005)       /* ADC12 Input Channel 5 */
#define ADC12INCH_6            (0x0006)       /* ADC12 Input Channel 6 */
#define ADC12INCH_7            (0x0007)       /* ADC12 Input Channel 7 */
#define ADC12INCH_8            (0x0008)       /* ADC12 Input Channel 8 */
#define ADC12INCH_9            (0x0009)       /* ADC12 Input Channel 9 */
#define ADC12INCH_10           (0x000A)       /* ADC12 Input Channel 10 */
#define ADC12INCH_11           (0x000B)       /* ADC12 Input Channel 11 */
#define ADC12INCH_12           (0x000C)       /* ADC12 Input Channel 12 */
#define ADC12INCH_13           (0x000D)       /* ADC12 Input Channel 13 */
#define ADC12INCH_14           (0x000E)       /* ADC12 Input Channel 14 */
#define ADC12INCH_15           (0x000F)       /* ADC12 Input Channel 15 */

#define ADC12SREF_0            (0*0x10u)      /* ADC12 Select Reference 0 */
#define ADC12SREF_1            (1*0x10u)      /* ADC12 Select Reference 1 */
#define ADC12SREF_2            (2*0x10u)      /* ADC12 Select Reference 2 */
#define ADC12SREF_3            (3*0x10u)      /* ADC12 Select Reference 3 */
#define ADC12SREF_4            (4*0x10u)      /* ADC12 Select Reference 4 */
#define ADC12SREF_5            (5*0x10u)      /* ADC12 Select Reference 5 */
#define ADC12SREF_6            (6*0x10u)      /* ADC12 Select Reference 6 */
#define ADC12SREF_7            (7*0x10u)      /* ADC12 Select Reference 7 */

#define ADC12IE0               (0x0001)       /* ADC12 Memory 0 Interrupt Enable */
#define ADC12IE1               (0x0002)       /* ADC12 Memory 1 Interrupt Enable */
#define ADC12IE2               (0x0004)       /* ADC12 Memory 2 Interrupt Enable */
#define ADC12IE3               (0x0008)       /* ADC12 Memory 3 Interrupt Enable */
#define ADC12IE4               (0x0010)       /* ADC12 Memory 4 Interrupt Enable */
#define ADC12IE5               (0x0020)       /* ADC12 Memory 5 Interrupt Enable */
#define ADC12IE6               (0x0040)       /* ADC12 Memory 6 Interrupt Enable */
#define ADC12IE7               (0x0080)       /* ADC12 Memory 7 Interrupt Enable */
#define ADC12IE8               (0x0100)       /* ADC12 Memory 8 Interrupt Enable */
#define ADC12IE9               (0x0200)       /* ADC12 Memory 9 Interrupt Enable */
#define ADC12IE10              (0x0400)       /* ADC12 Memory 10 Interrupt Enable */
#define ADC12IE11              (0x0800)       /* ADC12 Memory 11 Interrupt Enable */
#define ADC12IE12              (0x1000)       /* ADC12 Memory 12 Interrupt Enable */
#define ADC12IE13              (0x2000)       /* ADC12 Memory 13 Interrupt Enable */
#define ADC12IE14              (0x4000)       /* ADC12 Memory 14 Interrupt Enable */
#define ADC12IE15              (0x8000)       /* ADC12 Memory 15 Interrupt Enable */

#define ADC12IE0_L             (0x0001)       /* ADC12 Memory 0 Interrupt Enable */
#define ADC12IE1_L             (0x0002)       /* ADC12 Memory 1 Interrupt Enable */
#define ADC12IE2_L             (0x0004)       /* ADC12 Memory 2 Interrupt Enable */
#define ADC12IE3_L             (0x0008)       /* ADC12 Memory 3 Interrupt Enable */
#define ADC12IE4_L             (0x0010)       /* ADC12 Memory 4 Interrupt Enable */
#define ADC12IE5_L             (0x0020)       /* ADC12 Memory 5 Interrupt Enable */
#define ADC12IE6_L             (0x0040)       /* ADC12 Memory 6 Interrupt Enable */
#define ADC12IE7_L             (0x0080)       /* ADC12 Memory 7 Interrupt Enable */

#define ADC12IE8_H             (0x0001)       /* ADC12 Memory 8 Interrupt Enable */
#define ADC12IE9_H             (0x0002)       /* ADC12 Memory 9 Interrupt Enable */
#define ADC12IE10_H            (0x0004)       /* ADC12 Memory 10 Interrupt Enable */
#define ADC12IE11_H            (0x0008)       /* ADC12 Memory 11 Interrupt Enable */
#define ADC12IE12_H            (0x0010)       /* ADC12 Memory 12 Interrupt Enable */
#define ADC12IE13_H            (0x0020)       /* ADC12 Memory 13 Interrupt Enable */
#define ADC12IE14_H            (0x0040)       /* ADC12 Memory 14 Interrupt Enable */
#define ADC12IE15_H            (0x0080)       /* ADC12 Memory 15 Interrupt Enable */

#define ADC12IFG0              (0x0001)       /* ADC12 Memory 0 Interrupt Flag */
#define ADC12IFG1              (0x0002)       /* ADC12 Memory 1 Interrupt Flag */
#define ADC12IFG2              (0x0004)       /* ADC12 Memory 2 Interrupt Flag */
#define ADC12IFG3              (0x0008)       /* ADC12 Memory 3 Interrupt Flag */
#define ADC12IFG4              (0x0010)       /* ADC12 Memory 4 Interrupt Flag */
#define ADC12IFG5              (0x0020)       /* ADC12 Memory 5 Interrupt Flag */
#define ADC12IFG6              (0x0040)       /* ADC12 Memory 6 Interrupt Flag */
#define ADC12IFG7              (0x0080)       /* ADC12 Memory 7 Interrupt Flag */
#define ADC12IFG8              (0x0100)       /* ADC12 Memory 8 Interrupt Flag */
#define ADC12IFG9              (0x0200)       /* ADC12 Memory 9 Interrupt Flag */
#define ADC12IFG10             (0x0400)       /* ADC12 Memory 10 Interrupt Flag */
#define ADC12IFG11             (0x0800)       /* ADC12 Memory 11 Interrupt Flag */
#define ADC12IFG12             (0x1000)       /* ADC12 Memory 12 Interrupt Flag */
#define ADC12IFG13             (0x2000)       /* ADC12 Memory 13 Interrupt Flag */
#define ADC12IFG14             (0x4000)       /* ADC12 Memory 14 Interrupt Flag */
#define ADC12IFG15             (0x8000)       /* ADC12 Memory 15 Interrupt Flag */

#define ADC12IFG0_L            (0x0001)       /* ADC12 Memory 0 Interrupt Flag */
#define ADC12IFG1_L            (0x0002)       /* ADC12 Memory 1 Interrupt Flag */
#define ADC12IFG2_L            (0x0004)       /* ADC12 Memory 2 Interrupt Flag */
#define ADC12IFG3_L            (0x0008)       /* ADC12 Memory 3 Interrupt Flag */
#define ADC12IFG4_L            (0x0010)       /* ADC12 Memory 4 Interrupt Flag */
#define ADC12IFG5_L            (0x0020)       /* ADC12 Memory 5 Interrupt Flag */
#define ADC12IFG6_L            (0x0040)       /* ADC12 Memory 6 Interrupt Flag */
#define ADC12IFG7_L            (0x0080)       /* ADC12 Memory 7 Interrupt Flag */

#define ADC12IFG8_H            (0x0001)       /* ADC12 Memory 8 Interrupt Flag */
#define ADC12IFG9_H            (0x0002)       /* ADC12 Memory 9 Interrupt Flag */
#define ADC12IFG10_H           (0x0004)       /* ADC12 Memory 10 Interrupt Flag */
#define ADC12IFG11_H           (0x0008)       /* ADC12 Memory 11 Interrupt Flag */
#define ADC12IFG12_H           (0x0010)       /* ADC12 Memory 12 Interrupt Flag */
#define ADC12IFG13_H           (0x0020)       /* ADC12 Memory 13 Interrupt Flag */
#define ADC12IFG14_H           (0x0040)       /* ADC12 Memory 14 Interrupt Flag */
#define ADC12IFG15_H           (0x0080)       /* ADC12 Memory 15 Interrupt Flag */

/* ADC12IV Definitions */
#define ADC12IV_NONE           (0x0000)       /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG     (0x0002)       /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG    (0x0004)       /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0      (0x0006)       /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1      (0x0008)       /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2      (0x000A)       /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3      (0x000C)       /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4      (0x000E)       /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5      (0x0010)       /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6      (0x0012)       /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7      (0x0014)       /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8      (0x0016)       /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9      (0x0018)       /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10     (0x001A)       /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11     (0x001C)       /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12     (0x001E)       /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13     (0x0020)       /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14     (0x0022)       /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15     (0x0024)       /* ADC12IFG15 */

/************************************************************
* AES Accelerator
************************************************************/
#define __MSP430_HAS_AES__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_AES__ 0x09C0
#define AES_BASE               __MSP430_BASEADDRESS_AES__

SFR_16BIT(AESACTL0);                          /* AES accelerator control register 0 */
SFR_8BIT(AESACTL0_L);                         /* AES accelerator control register 0 */
SFR_8BIT(AESACTL0_H);                         /* AES accelerator control register 0 */
SFR_16BIT(AESASTAT);                          /* AES accelerator status register */
SFR_8BIT(AESASTAT_L);                         /* AES accelerator status register */
SFR_8BIT(AESASTAT_H);                         /* AES accelerator status register */
SFR_16BIT(AESAKEY);                           /* AES accelerator key register */
SFR_8BIT(AESAKEY_L);                          /* AES accelerator key register */
SFR_8BIT(AESAKEY_H);                          /* AES accelerator key register */
SFR_16BIT(AESADIN);                           /* AES accelerator data in register */
SFR_8BIT(AESADIN_L);                          /* AES accelerator data in register */
SFR_8BIT(AESADIN_H);                          /* AES accelerator data in register */
SFR_16BIT(AESADOUT);                          /* AES accelerator data out register  */
SFR_8BIT(AESADOUT_L);                         /* AES accelerator data out register  */
SFR_8BIT(AESADOUT_H);                         /* AES accelerator data out register  */

/* AESACTL0 Control Bits */
#define AESOP0                 (0x0001)       /* AES Operation Bit: 0 */
#define AESOP1                 (0x0002)       /* AES Operation Bit: 1 */
#define AESSWRST               (0x0080)       /* AES Software Reset */
#define AESRDYIFG              (0x0100)       /* AES ready interrupt flag */
#define AESERRFG               (0x0800)       /* AES Error Flag */
#define AESRDYIE               (0x1000)       /* AES ready interrupt enable*/

/* AESACTL0 Control Bits */
#define AESOP0_L               (0x0001)       /* AES Operation Bit: 0 */
#define AESOP1_L               (0x0002)       /* AES Operation Bit: 1 */
#define AESSWRST_L             (0x0080)       /* AES Software Reset */

/* AESACTL0 Control Bits */
#define AESRDYIFG_H            (0x0001)       /* AES ready interrupt flag */
#define AESERRFG_H             (0x0008)       /* AES Error Flag */
#define AESRDYIE_H             (0x0010)       /* AES ready interrupt enable*/

#define AESOP_0                (0x0000)       /* AES Operation: Encrypt */
#define AESOP_1                (0x0001)       /* AES Operation: Decrypt (same Key) */
#define AESOP_2                (0x0002)       /* AES Operation: Decrypt (frist round Key) */
#define AESOP_3                (0x0003)       /* AES Operation: Generate first round Key */

/* AESASTAT Control Bits */
#define AESBUSY                (0x0001)       /* AES Busy */
#define AESKEYWR               (0x0002)       /* AES All 16 bytes written to AESAKEY */
#define AESDINWR               (0x0004)       /* AES All 16 bytes written to AESADIN */
#define AESDOUTRD              (0x0008)       /* AES All 16 bytes read from AESADOUT */
#define AESKEYCNT0             (0x0010)       /* AES Bytes written via AESAKEY Bit: 0 */
#define AESKEYCNT1             (0x0020)       /* AES Bytes written via AESAKEY Bit: 1 */
#define AESKEYCNT2             (0x0040)       /* AES Bytes written via AESAKEY Bit: 2 */
#define AESKEYCNT3             (0x0080)       /* AES Bytes written via AESAKEY Bit: 3 */
#define AESDINCNT0             (0x0100)       /* AES Bytes written via AESADIN Bit: 0 */
#define AESDINCNT1             (0x0200)       /* AES Bytes written via AESADIN Bit: 1 */
#define AESDINCNT2             (0x0400)       /* AES Bytes written via AESADIN Bit: 2 */
#define AESDINCNT3             (0x0800)       /* AES Bytes written via AESADIN Bit: 3 */
#define AESDOUTCNT0            (0x1000)       /* AES Bytes read via AESADOUT Bit: 0 */
#define AESDOUTCNT1            (0x2000)       /* AES Bytes read via AESADOUT Bit: 1 */
#define AESDOUTCNT2            (0x4000)       /* AES Bytes read via AESADOUT Bit: 2 */
#define AESDOUTCNT3            (0x8000)       /* AES Bytes read via AESADOUT Bit: 3 */

/* AESASTAT Control Bits */
#define AESBUSY_L              (0x0001)       /* AES Busy */
#define AESKEYWR_L             (0x0002)       /* AES All 16 bytes written to AESAKEY */
#define AESDINWR_L             (0x0004)       /* AES All 16 bytes written to AESADIN */
#define AESDOUTRD_L            (0x0008)       /* AES All 16 bytes read from AESADOUT */
#define AESKEYCNT0_L           (0x0010)       /* AES Bytes written via AESAKEY Bit: 0 */
#define AESKEYCNT1_L           (0x0020)       /* AES Bytes written via AESAKEY Bit: 1 */
#define AESKEYCNT2_L           (0x0040)       /* AES Bytes written via AESAKEY Bit: 2 */
#define AESKEYCNT3_L           (0x0080)       /* AES Bytes written via AESAKEY Bit: 3 */

/* AESASTAT Control Bits */
#define AESDINCNT0_H           (0x0001)       /* AES Bytes written via AESADIN Bit: 0 */
#define AESDINCNT1_H           (0x0002)       /* AES Bytes written via AESADIN Bit: 1 */
#define AESDINCNT2_H           (0x0004)       /* AES Bytes written via AESADIN Bit: 2 */
#define AESDINCNT3_H           (0x0008)       /* AES Bytes written via AESADIN Bit: 3 */
#define AESDOUTCNT0_H          (0x0010)       /* AES Bytes read via AESADOUT Bit: 0 */
#define AESDOUTCNT1_H          (0x0020)       /* AES Bytes read via AESADOUT Bit: 1 */
#define AESDOUTCNT2_H          (0x0040)       /* AES Bytes read via AESADOUT Bit: 2 */
#define AESDOUTCNT3_H          (0x0080)       /* AES Bytes read via AESADOUT Bit: 3 */

/************************************************************
* Comparator B
************************************************************/
#define __MSP430_HAS_COMPB__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_COMPB__ 0x08C0
#define COMP_B_BASE            __MSP430_BASEADDRESS_COMPB__

SFR_16BIT(CBCTL0);                            /* Comparator B Control Register 0 */
SFR_8BIT(CBCTL0_L);                           /* Comparator B Control Register 0 */
SFR_8BIT(CBCTL0_H);                           /* Comparator B Control Register 0 */
SFR_16BIT(CBCTL1);                            /* Comparator B Control Register 1 */
SFR_8BIT(CBCTL1_L);                           /* Comparator B Control Register 1 */
SFR_8BIT(CBCTL1_H);                           /* Comparator B Control Register 1 */
SFR_16BIT(CBCTL2);                            /* Comparator B Control Register 2 */
SFR_8BIT(CBCTL2_L);                           /* Comparator B Control Register 2 */
SFR_8BIT(CBCTL2_H);                           /* Comparator B Control Register 2 */
SFR_16BIT(CBCTL3);                            /* Comparator B Control Register 3 */
SFR_8BIT(CBCTL3_L);                           /* Comparator B Control Register 3 */
SFR_8BIT(CBCTL3_H);                           /* Comparator B Control Register 3 */
SFR_16BIT(CBINT);                             /* Comparator B Interrupt Register */
SFR_8BIT(CBINT_L);                            /* Comparator B Interrupt Register */
SFR_8BIT(CBINT_H);                            /* Comparator B Interrupt Register */
SFR_16BIT(CBIV);                              /* Comparator B Interrupt Vector Word */

/* CBCTL0 Control Bits */
#define CBIPSEL0               (0x0001)       /* Comp. B Pos. Channel Input Select 0 */
#define CBIPSEL1               (0x0002)       /* Comp. B Pos. Channel Input Select 1 */
#define CBIPSEL2               (0x0004)       /* Comp. B Pos. Channel Input Select 2 */
#define CBIPSEL3               (0x0008)       /* Comp. B Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010)  /* Comp. B */
//#define RESERVED            (0x0020)  /* Comp. B */
//#define RESERVED            (0x0040)  /* Comp. B */
#define CBIPEN                 (0x0080)       /* Comp. B Pos. Channel Input Enable */
#define CBIMSEL0               (0x0100)       /* Comp. B Neg. Channel Input Select 0 */
#define CBIMSEL1               (0x0200)       /* Comp. B Neg. Channel Input Select 1 */
#define CBIMSEL2               (0x0400)       /* Comp. B Neg. Channel Input Select 2 */
#define CBIMSEL3               (0x0800)       /* Comp. B Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000)  /* Comp. B */
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */
#define CBIMEN                 (0x8000)       /* Comp. B Neg. Channel Input Enable */

/* CBCTL0 Control Bits */
#define CBIPSEL0_L             (0x0001)       /* Comp. B Pos. Channel Input Select 0 */
#define CBIPSEL1_L             (0x0002)       /* Comp. B Pos. Channel Input Select 1 */
#define CBIPSEL2_L             (0x0004)       /* Comp. B Pos. Channel Input Select 2 */
#define CBIPSEL3_L             (0x0008)       /* Comp. B Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010)  /* Comp. B */
//#define RESERVED            (0x0020)  /* Comp. B */
//#define RESERVED            (0x0040)  /* Comp. B */
#define CBIPEN_L               (0x0080)       /* Comp. B Pos. Channel Input Enable */
//#define RESERVED            (0x1000)  /* Comp. B */
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */

/* CBCTL0 Control Bits */
//#define RESERVED            (0x0010)  /* Comp. B */
//#define RESERVED            (0x0020)  /* Comp. B */
//#define RESERVED            (0x0040)  /* Comp. B */
#define CBIMSEL0_H             (0x0001)       /* Comp. B Neg. Channel Input Select 0 */
#define CBIMSEL1_H             (0x0002)       /* Comp. B Neg. Channel Input Select 1 */
#define CBIMSEL2_H             (0x0004)       /* Comp. B Neg. Channel Input Select 2 */
#define CBIMSEL3_H             (0x0008)       /* Comp. B Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000)  /* Comp. B */
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */
#define CBIMEN_H               (0x0080)       /* Comp. B Neg. Channel Input Enable */

#define CBIPSEL_0              (0x0000)       /* Comp. B V+ terminal Input Select: Channel 0 */
#define CBIPSEL_1              (0x0001)       /* Comp. B V+ terminal Input Select: Channel 1 */
#define CBIPSEL_2              (0x0002)       /* Comp. B V+ terminal Input Select: Channel 2 */
#define CBIPSEL_3              (0x0003)       /* Comp. B V+ terminal Input Select: Channel 3 */
#define CBIPSEL_4              (0x0004)       /* Comp. B V+ terminal Input Select: Channel 4 */
#define CBIPSEL_5              (0x0005)       /* Comp. B V+ terminal Input Select: Channel 5 */
#define CBIPSEL_6              (0x0006)       /* Comp. B V+ terminal Input Select: Channel 6 */
#define CBIPSEL_7              (0x0007)       /* Comp. B V+ terminal Input Select: Channel 7 */
#define CBIPSEL_8              (0x0008)       /* Comp. B V+ terminal Input Select: Channel 8 */
#define CBIPSEL_9              (0x0009)       /* Comp. B V+ terminal Input Select: Channel 9 */
#define CBIPSEL_10             (0x000A)       /* Comp. B V+ terminal Input Select: Channel 10 */
#define CBIPSEL_11             (0x000B)       /* Comp. B V+ terminal Input Select: Channel 11 */
#define CBIPSEL_12             (0x000C)       /* Comp. B V+ terminal Input Select: Channel 12 */
#define CBIPSEL_13             (0x000D)       /* Comp. B V+ terminal Input Select: Channel 13 */
#define CBIPSEL_14             (0x000E)       /* Comp. B V+ terminal Input Select: Channel 14 */
#define CBIPSEL_15             (0x000F)       /* Comp. B V+ terminal Input Select: Channel 15 */

#define CBIMSEL_0              (0x0000)       /* Comp. B V- Terminal Input Select: Channel 0 */
#define CBIMSEL_1              (0x0100)       /* Comp. B V- Terminal Input Select: Channel 1 */
#define CBIMSEL_2              (0x0200)       /* Comp. B V- Terminal Input Select: Channel 2 */
#define CBIMSEL_3              (0x0300)       /* Comp. B V- Terminal Input Select: Channel 3 */
#define CBIMSEL_4              (0x0400)       /* Comp. B V- Terminal Input Select: Channel 4 */
#define CBIMSEL_5              (0x0500)       /* Comp. B V- Terminal Input Select: Channel 5 */
#define CBIMSEL_6              (0x0600)       /* Comp. B V- Terminal Input Select: Channel 6 */
#define CBIMSEL_7              (0x0700)       /* Comp. B V- Terminal Input Select: Channel 7 */
#define CBIMSEL_8              (0x0800)       /* Comp. B V- terminal Input Select: Channel 8 */
#define CBIMSEL_9              (0x0900)       /* Comp. B V- terminal Input Select: Channel 9 */
#define CBIMSEL_10             (0x0A00)       /* Comp. B V- terminal Input Select: Channel 10 */
#define CBIMSEL_11             (0x0B00)       /* Comp. B V- terminal Input Select: Channel 11 */
#define CBIMSEL_12             (0x0C00)       /* Comp. B V- terminal Input Select: Channel 12 */
#define CBIMSEL_13             (0x0D00)       /* Comp. B V- terminal Input Select: Channel 13 */
#define CBIMSEL_14             (0x0E00)       /* Comp. B V- terminal Input Select: Channel 14 */
#define CBIMSEL_15             (0x0F00)       /* Comp. B V- terminal Input Select: Channel 15 */

/* CBCTL1 Control Bits */
#define CBOUT                  (0x0001)       /* Comp. B Output */
#define CBOUTPOL               (0x0002)       /* Comp. B Output Polarity */
#define CBF                    (0x0004)       /* Comp. B Enable Output Filter */
#define CBIES                  (0x0008)       /* Comp. B Interrupt Edge Select */
#define CBSHORT                (0x0010)       /* Comp. B Input Short */
#define CBEX                   (0x0020)       /* Comp. B Exchange Inputs */
#define CBFDLY0                (0x0040)       /* Comp. B Filter delay Bit 0 */
#define CBFDLY1                (0x0080)       /* Comp. B Filter delay Bit 1 */
#define CBPWRMD0               (0x0100)       /* Comp. B Power Mode Bit 0 */
#define CBPWRMD1               (0x0200)       /* Comp. B Power Mode Bit 1 */
#define CBON                   (0x0400)       /* Comp. B enable */
#define CBMRVL                 (0x0800)       /* Comp. B CBMRV Level */
#define CBMRVS                 (0x1000)       /* Comp. B Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */
//#define RESERVED            (0x8000)  /* Comp. B */

/* CBCTL1 Control Bits */
#define CBOUT_L                (0x0001)       /* Comp. B Output */
#define CBOUTPOL_L             (0x0002)       /* Comp. B Output Polarity */
#define CBF_L                  (0x0004)       /* Comp. B Enable Output Filter */
#define CBIES_L                (0x0008)       /* Comp. B Interrupt Edge Select */
#define CBSHORT_L              (0x0010)       /* Comp. B Input Short */
#define CBEX_L                 (0x0020)       /* Comp. B Exchange Inputs */
#define CBFDLY0_L              (0x0040)       /* Comp. B Filter delay Bit 0 */
#define CBFDLY1_L              (0x0080)       /* Comp. B Filter delay Bit 1 */
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */
//#define RESERVED            (0x8000)  /* Comp. B */

/* CBCTL1 Control Bits */
#define CBPWRMD0_H             (0x0001)       /* Comp. B Power Mode Bit 0 */
#define CBPWRMD1_H             (0x0002)       /* Comp. B Power Mode Bit 1 */
#define CBON_H                 (0x0004)       /* Comp. B enable */
#define CBMRVL_H               (0x0008)       /* Comp. B CBMRV Level */
#define CBMRVS_H               (0x0010)       /* Comp. B Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000)  /* Comp. B */
//#define RESERVED            (0x4000)  /* Comp. B */
//#define RESERVED            (0x8000)  /* Comp. B */

#define CBFDLY_0               (0x0000)       /* Comp. B Filter delay 0 : 450ns */
#define CBFDLY_1               (0x0040)       /* Comp. B Filter delay 1 : 900ns */
#define CBFDLY_2               (0x0080)       /* Comp. B Filter delay 2 : 1800ns */
#define CBFDLY_3               (0x00C0)       /* Comp. B Filter delay 3 : 3600ns */

#define CBPWRMD_0              (0x0000)       /* Comp. B Power Mode 0 : High speed */
#define CBPWRMD_1              (0x0100)       /* Comp. B Power Mode 1 : Normal */
#define CBPWRMD_2              (0x0200)       /* Comp. B Power Mode 2 : Ultra-Low*/
#define CBPWRMD_3              (0x0300)       /* Comp. B Power Mode 3 : Reserved */

/* CBCTL2 Control Bits */
#define CBREF00                (0x0001)       /* Comp. B Reference 0 Resistor Select Bit : 0 */
#define CBREF01                (0x0002)       /* Comp. B Reference 0 Resistor Select Bit : 1 */
#define CBREF02                (0x0004)       /* Comp. B Reference 0 Resistor Select Bit : 2 */
#define CBREF03                (0x0008)       /* Comp. B Reference 0 Resistor Select Bit : 3 */
#define CBREF04                (0x0010)       /* Comp. B Reference 0 Resistor Select Bit : 4 */
#define CBRSEL                 (0x0020)       /* Comp. B Reference select */
#define CBRS0                  (0x0040)       /* Comp. B Reference Source Bit : 0 */
#define CBRS1                  (0x0080)       /* Comp. B Reference Source Bit : 1 */
#define CBREF10                (0x0100)       /* Comp. B Reference 1 Resistor Select Bit : 0 */
#define CBREF11                (0x0200)       /* Comp. B Reference 1 Resistor Select Bit : 1 */
#define CBREF12                (0x0400)       /* Comp. B Reference 1 Resistor Select Bit : 2 */
#define CBREF13                (0x0800)       /* Comp. B Reference 1 Resistor Select Bit : 3 */
#define CBREF14                (0x1000)       /* Comp. B Reference 1 Resistor Select Bit : 4 */
#define CBREFL0                (0x2000)       /* Comp. B Reference voltage level Bit : 0 */
#define CBREFL1                (0x4000)       /* Comp. B Reference voltage level Bit : 1 */
#define CBREFACC               (0x8000)       /* Comp. B Reference Accuracy */

/* CBCTL2 Control Bits */
#define CBREF00_L              (0x0001)       /* Comp. B Reference 0 Resistor Select Bit : 0 */
#define CBREF01_L              (0x0002)       /* Comp. B Reference 0 Resistor Select Bit : 1 */
#define CBREF02_L              (0x0004)       /* Comp. B Reference 0 Resistor Select Bit : 2 */
#define CBREF03_L              (0x0008)       /* Comp. B Reference 0 Resistor Select Bit : 3 */
#define CBREF04_L              (0x0010)       /* Comp. B Reference 0 Resistor Select Bit : 4 */
#define CBRSEL_L               (0x0020)       /* Comp. B Reference select */
#define CBRS0_L                (0x0040)       /* Comp. B Reference Source Bit : 0 */
#define CBRS1_L                (0x0080)       /* Comp. B Reference Source Bit : 1 */

/* CBCTL2 Control Bits */
#define CBREF10_H              (0x0001)       /* Comp. B Reference 1 Resistor Select Bit : 0 */
#define CBREF11_H              (0x0002)       /* Comp. B Reference 1 Resistor Select Bit : 1 */
#define CBREF12_H              (0x0004)       /* Comp. B Reference 1 Resistor Select Bit : 2 */
#define CBREF13_H              (0x0008)       /* Comp. B Reference 1 Resistor Select Bit : 3 */
#define CBREF14_H              (0x0010)       /* Comp. B Reference 1 Resistor Select Bit : 4 */
#define CBREFL0_H              (0x0020)       /* Comp. B Reference voltage level Bit : 0 */
#define CBREFL1_H              (0x0040)       /* Comp. B Reference voltage level Bit : 1 */
#define CBREFACC_H             (0x0080)       /* Comp. B Reference Accuracy */

#define CBREF0_0               (0x0000)       /* Comp. B Int. Ref.0 Select 0 : 1/32 */
#define CBREF0_1               (0x0001)       /* Comp. B Int. Ref.0 Select 1 : 2/32 */
#define CBREF0_2               (0x0002)       /* Comp. B Int. Ref.0 Select 2 : 3/32 */
#define CBREF0_3               (0x0003)       /* Comp. B Int. Ref.0 Select 3 : 4/32 */
#define CBREF0_4               (0x0004)       /* Comp. B Int. Ref.0 Select 4 : 5/32 */
#define CBREF0_5               (0x0005)       /* Comp. B Int. Ref.0 Select 5 : 6/32 */
#define CBREF0_6               (0x0006)       /* Comp. B Int. Ref.0 Select 6 : 7/32 */
#define CBREF0_7               (0x0007)       /* Comp. B Int. Ref.0 Select 7 : 8/32 */
#define CBREF0_8               (0x0008)       /* Comp. B Int. Ref.0 Select 0 : 9/32 */
#define CBREF0_9               (0x0009)       /* Comp. B Int. Ref.0 Select 1 : 10/32 */
#define CBREF0_10              (0x000A)       /* Comp. B Int. Ref.0 Select 2 : 11/32 */
#define CBREF0_11              (0x000B)       /* Comp. B Int. Ref.0 Select 3 : 12/32 */
#define CBREF0_12              (0x000C)       /* Comp. B Int. Ref.0 Select 4 : 13/32 */
#define CBREF0_13              (0x000D)       /* Comp. B Int. Ref.0 Select 5 : 14/32 */
#define CBREF0_14              (0x000E)       /* Comp. B Int. Ref.0 Select 6 : 15/32 */
#define CBREF0_15              (0x000F)       /* Comp. B Int. Ref.0 Select 7 : 16/32 */
#define CBREF0_16              (0x0010)       /* Comp. B Int. Ref.0 Select 0 : 17/32 */
#define CBREF0_17              (0x0011)       /* Comp. B Int. Ref.0 Select 1 : 18/32 */
#define CBREF0_18              (0x0012)       /* Comp. B Int. Ref.0 Select 2 : 19/32 */
#define CBREF0_19              (0x0013)       /* Comp. B Int. Ref.0 Select 3 : 20/32 */
#define CBREF0_20              (0x0014)       /* Comp. B Int. Ref.0 Select 4 : 21/32 */
#define CBREF0_21              (0x0015)       /* Comp. B Int. Ref.0 Select 5 : 22/32 */
#define CBREF0_22              (0x0016)       /* Comp. B Int. Ref.0 Select 6 : 23/32 */
#define CBREF0_23              (0x0017)       /* Comp. B Int. Ref.0 Select 7 : 24/32 */
#define CBREF0_24              (0x0018)       /* Comp. B Int. Ref.0 Select 0 : 25/32 */
#define CBREF0_25              (0x0019)       /* Comp. B Int. Ref.0 Select 1 : 26/32 */
#define CBREF0_26              (0x001A)       /* Comp. B Int. Ref.0 Select 2 : 27/32 */
#define CBREF0_27              (0x001B)       /* Comp. B Int. Ref.0 Select 3 : 28/32 */
#define CBREF0_28              (0x001C)       /* Comp. B Int. Ref.0 Select 4 : 29/32 */
#define CBREF0_29              (0x001D)       /* Comp. B Int. Ref.0 Select 5 : 30/32 */
#define CBREF0_30              (0x001E)       /* Comp. B Int. Ref.0 Select 6 : 31/32 */
#define CBREF0_31              (0x001F)       /* Comp. B Int. Ref.0 Select 7 : 32/32 */

#define CBRS_0                 (0x0000)       /* Comp. B Reference Source 0 : Off */
#define CBRS_1                 (0x0040)       /* Comp. B Reference Source 1 : Vcc */
#define CBRS_2                 (0x0080)       /* Comp. B Reference Source 2 : Shared Ref. */
#define CBRS_3                 (0x00C0)       /* Comp. B Reference Source 3 : Shared Ref. / Off */

#define CBREF1_0               (0x0000)       /* Comp. B Int. Ref.1 Select 0 : 1/32 */
#define CBREF1_1               (0x0100)       /* Comp. B Int. Ref.1 Select 1 : 2/32 */
#define CBREF1_2               (0x0200)       /* Comp. B Int. Ref.1 Select 2 : 3/32 */
#define CBREF1_3               (0x0300)       /* Comp. B Int. Ref.1 Select 3 : 4/32 */
#define CBREF1_4               (0x0400)       /* Comp. B Int. Ref.1 Select 4 : 5/32 */
#define CBREF1_5               (0x0500)       /* Comp. B Int. Ref.1 Select 5 : 6/32 */
#define CBREF1_6               (0x0600)       /* Comp. B Int. Ref.1 Select 6 : 7/32 */
#define CBREF1_7               (0x0700)       /* Comp. B Int. Ref.1 Select 7 : 8/32 */
#define CBREF1_8               (0x0800)       /* Comp. B Int. Ref.1 Select 0 : 9/32 */
#define CBREF1_9               (0x0900)       /* Comp. B Int. Ref.1 Select 1 : 10/32 */
#define CBREF1_10              (0x0A00)       /* Comp. B Int. Ref.1 Select 2 : 11/32 */
#define CBREF1_11              (0x0B00)       /* Comp. B Int. Ref.1 Select 3 : 12/32 */
#define CBREF1_12              (0x0C00)       /* Comp. B Int. Ref.1 Select 4 : 13/32 */
#define CBREF1_13              (0x0D00)       /* Comp. B Int. Ref.1 Select 5 : 14/32 */
#define CBREF1_14              (0x0E00)       /* Comp. B Int. Ref.1 Select 6 : 15/32 */
#define CBREF1_15              (0x0F00)       /* Comp. B Int. Ref.1 Select 7 : 16/32 */
#define CBREF1_16              (0x1000)       /* Comp. B Int. Ref.1 Select 0 : 17/32 */
#define CBREF1_17              (0x1100)       /* Comp. B Int. Ref.1 Select 1 : 18/32 */
#define CBREF1_18              (0x1200)       /* Comp. B Int. Ref.1 Select 2 : 19/32 */
#define CBREF1_19              (0x1300)       /* Comp. B Int. Ref.1 Select 3 : 20/32 */
#define CBREF1_20              (0x1400)       /* Comp. B Int. Ref.1 Select 4 : 21/32 */
#define CBREF1_21              (0x1500)       /* Comp. B Int. Ref.1 Select 5 : 22/32 */
#define CBREF1_22              (0x1600)       /* Comp. B Int. Ref.1 Select 6 : 23/32 */
#define CBREF1_23              (0x1700)       /* Comp. B Int. Ref.1 Select 7 : 24/32 */
#define CBREF1_24              (0x1800)       /* Comp. B Int. Ref.1 Select 0 : 25/32 */
#define CBREF1_25              (0x1900)       /* Comp. B Int. Ref.1 Select 1 : 26/32 */
#define CBREF1_26              (0x1A00)       /* Comp. B Int. Ref.1 Select 2 : 27/32 */
#define CBREF1_27              (0x1B00)       /* Comp. B Int. Ref.1 Select 3 : 28/32 */
#define CBREF1_28              (0x1C00)       /* Comp. B Int. Ref.1 Select 4 : 29/32 */
#define CBREF1_29              (0x1D00)       /* Comp. B Int. Ref.1 Select 5 : 30/32 */
#define CBREF1_30              (0x1E00)       /* Comp. B Int. Ref.1 Select 6 : 31/32 */
#define CBREF1_31              (0x1F00)       /* Comp. B Int. Ref.1 Select 7 : 32/32 */

#define CBREFL_0               (0x0000)       /* Comp. B Reference voltage level 0 : None */
#define CBREFL_1               (0x2000)       /* Comp. B Reference voltage level 1 : 1.5V */
#define CBREFL_2               (0x4000)       /* Comp. B Reference voltage level 2 : 2.0V  */
#define CBREFL_3               (0x6000)       /* Comp. B Reference voltage level 3 : 2.5V  */

#define CBPD0                  (0x0001)       /* Comp. B Disable Input Buffer of Port Register .0 */
#define CBPD1                  (0x0002)       /* Comp. B Disable Input Buffer of Port Register .1 */
#define CBPD2                  (0x0004)       /* Comp. B Disable Input Buffer of Port Register .2 */
#define CBPD3                  (0x0008)       /* Comp. B Disable Input Buffer of Port Register .3 */
#define CBPD4                  (0x0010)       /* Comp. B Disable Input Buffer of Port Register .4 */
#define CBPD5                  (0x0020)       /* Comp. B Disable Input Buffer of Port Register .5 */
#define CBPD6                  (0x0040)       /* Comp. B Disable Input Buffer of Port Register .6 */
#define CBPD7                  (0x0080)       /* Comp. B Disable Input Buffer of Port Register .7 */
#define CBPD8                  (0x0100)       /* Comp. B Disable Input Buffer of Port Register .8 */
#define CBPD9                  (0x0200)       /* Comp. B Disable Input Buffer of Port Register .9 */
#define CBPD10                 (0x0400)       /* Comp. B Disable Input Buffer of Port Register .10 */
#define CBPD11                 (0x0800)       /* Comp. B Disable Input Buffer of Port Register .11 */
#define CBPD12                 (0x1000)       /* Comp. B Disable Input Buffer of Port Register .12 */
#define CBPD13                 (0x2000)       /* Comp. B Disable Input Buffer of Port Register .13 */
#define CBPD14                 (0x4000)       /* Comp. B Disable Input Buffer of Port Register .14 */
#define CBPD15                 (0x8000)       /* Comp. B Disable Input Buffer of Port Register .15 */

#define CBPD0_L                (0x0001)       /* Comp. B Disable Input Buffer of Port Register .0 */
#define CBPD1_L                (0x0002)       /* Comp. B Disable Input Buffer of Port Register .1 */
#define CBPD2_L                (0x0004)       /* Comp. B Disable Input Buffer of Port Register .2 */
#define CBPD3_L                (0x0008)       /* Comp. B Disable Input Buffer of Port Register .3 */
#define CBPD4_L                (0x0010)       /* Comp. B Disable Input Buffer of Port Register .4 */
#define CBPD5_L                (0x0020)       /* Comp. B Disable Input Buffer of Port Register .5 */
#define CBPD6_L                (0x0040)       /* Comp. B Disable Input Buffer of Port Register .6 */
#define CBPD7_L                (0x0080)       /* Comp. B Disable Input Buffer of Port Register .7 */

#define CBPD8_H                (0x0001)       /* Comp. B Disable Input Buffer of Port Register .8 */
#define CBPD9_H                (0x0002)       /* Comp. B Disable Input Buffer of Port Register .9 */
#define CBPD10_H               (0x0004)       /* Comp. B Disable Input Buffer of Port Register .10 */
#define CBPD11_H               (0x0008)       /* Comp. B Disable Input Buffer of Port Register .11 */
#define CBPD12_H               (0x0010)       /* Comp. B Disable Input Buffer of Port Register .12 */
#define CBPD13_H               (0x0020)       /* Comp. B Disable Input Buffer of Port Register .13 */
#define CBPD14_H               (0x0040)       /* Comp. B Disable Input Buffer of Port Register .14 */
#define CBPD15_H               (0x0080)       /* Comp. B Disable Input Buffer of Port Register .15 */

/* CBINT Control Bits */
#define CBIFG                  (0x0001)       /* Comp. B Interrupt Flag */
#define CBIIFG                 (0x0002)       /* Comp. B Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004)  /* Comp. B */
//#define RESERVED             (0x0008)  /* Comp. B */
//#define RESERVED             (0x0010)  /* Comp. B */
//#define RESERVED             (0x0020)  /* Comp. B */
//#define RESERVED             (0x0040)  /* Comp. B */
//#define RESERVED             (0x0080)  /* Comp. B */
#define CBIE                   (0x0100)       /* Comp. B Interrupt Enable */
#define CBIIE                  (0x0200)       /* Comp. B Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400)  /* Comp. B */
//#define RESERVED             (0x0800)  /* Comp. B */
//#define RESERVED             (0x1000)  /* Comp. B */
//#define RESERVED             (0x2000)  /* Comp. B */
//#define RESERVED             (0x4000)  /* Comp. B */
//#define RESERVED             (0x8000)  /* Comp. B */

/* CBINT Control Bits */
#define CBIFG_L                (0x0001)       /* Comp. B Interrupt Flag */
#define CBIIFG_L               (0x0002)       /* Comp. B Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004)  /* Comp. B */
//#define RESERVED             (0x0008)  /* Comp. B */
//#define RESERVED             (0x0010)  /* Comp. B */
//#define RESERVED             (0x0020)  /* Comp. B */
//#define RESERVED             (0x0040)  /* Comp. B */
//#define RESERVED             (0x0080)  /* Comp. B */
//#define RESERVED             (0x0400)  /* Comp. B */
//#define RESERVED             (0x0800)  /* Comp. B */
//#define RESERVED             (0x1000)  /* Comp. B */
//#define RESERVED             (0x2000)  /* Comp. B */
//#define RESERVED             (0x4000)  /* Comp. B */
//#define RESERVED             (0x8000)  /* Comp. B */

/* CBINT Control Bits */
//#define RESERVED             (0x0004)  /* Comp. B */
//#define RESERVED             (0x0008)  /* Comp. B */
//#define RESERVED             (0x0010)  /* Comp. B */
//#define RESERVED             (0x0020)  /* Comp. B */
//#define RESERVED             (0x0040)  /* Comp. B */
//#define RESERVED             (0x0080)  /* Comp. B */
#define CBIE_H                 (0x0001)       /* Comp. B Interrupt Enable */
#define CBIIE_H                (0x0002)       /* Comp. B Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400)  /* Comp. B */
//#define RESERVED             (0x0800)  /* Comp. B */
//#define RESERVED             (0x1000)  /* Comp. B */
//#define RESERVED             (0x2000)  /* Comp. B */
//#define RESERVED             (0x4000)  /* Comp. B */
//#define RESERVED             (0x8000)  /* Comp. B */

/* CBIV Definitions */
#define CBIV_NONE              (0x0000)       /* No Interrupt pending */
#define CBIV_CBIFG             (0x0002)       /* CBIFG */
#define CBIV_CBIIFG            (0x0004)       /* CBIIFG */

/************************************************************
* CC1101 Radio Interface
************************************************************/
#define __MSP430_HAS_CC1101__                 /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CC1101__ 0x0F00
#define RF1A_BASE              __MSP430_BASEADDRESS_CC1101__

SFR_16BIT(RF1AIFCTL0);                        /* Radio interface control register 0 */
SFR_8BIT(RF1AIFCTL0_L);                       /* Radio interface control register 0 */
SFR_8BIT(RF1AIFCTL0_H);                       /* Radio interface control register 0 */
SFR_16BIT(RF1AIFCTL1);                        /* Radio interface control register 1 */
SFR_8BIT(RF1AIFCTL1_L);                       /* Radio interface control register 1 */
SFR_8BIT(RF1AIFCTL1_H);                       /* Radio interface control register 1 */
#define  RF1AIFIFG             RF1AIFCTL1_L   /* Radio interface interrupt flag register */
#define  RF1AIFIE              RF1AIFCTL1_H   /* Radio interface interrupt enable register */
SFR_16BIT(RF1AIFCTL2);                        /* (Radio interface control register 2) */
SFR_8BIT(RF1AIFCTL2_L);                       /* (Radio interface control register 2) */
SFR_8BIT(RF1AIFCTL2_H);                       /* (Radio interface control register 2) */
SFR_16BIT(RF1AIFERR);                         /* Radio interface error flag register */
SFR_8BIT(RF1AIFERR_L);                        /* Radio interface error flag register */
SFR_8BIT(RF1AIFERR_H);                        /* Radio interface error flag register */
SFR_16BIT(RF1AIFERRV);                        /* Radio interface error vector word register */
SFR_8BIT(RF1AIFERRV_L);                       /* Radio interface error vector word register */
SFR_8BIT(RF1AIFERRV_H);                       /* Radio interface error vector word register */
SFR_16BIT(RF1AIFIV);                          /* Radio interface interrupt vector word register */
SFR_8BIT(RF1AIFIV_L);                         /* Radio interface interrupt vector word register */
SFR_8BIT(RF1AIFIV_H);                         /* Radio interface interrupt vector word register */
SFR_16BIT(RF1AINSTRW);                        /* Radio instruction word register */
SFR_8BIT(RF1AINSTRW_L);                       /* Radio instruction word register */
SFR_8BIT(RF1AINSTRW_H);                       /* Radio instruction word register */
#define  RF1ADINB              RF1AINSTRW_L   /* Radio instruction byte register */
#define  RF1AINSTRB            RF1AINSTRW_H   /* Radio byte data in register */
SFR_16BIT(RF1AINSTR1W);                       /* Radio instruction 1-byte register with autoread */
SFR_8BIT(RF1AINSTR1W_L);                      /* Radio instruction 1-byte register with autoread */
SFR_8BIT(RF1AINSTR1W_H);                      /* Radio instruction 1-byte register with autoread */
#define  RF1AINSTR1B           RF1AINSTR1W_H  /* Radio instruction 1-byte register with autoread */
SFR_16BIT(RF1AINSTR2W);                       /* Radio instruction 2-byte register with autoread */
SFR_8BIT(RF1AINSTR2W_L);                      /* Radio instruction 2-byte register with autoread */
SFR_8BIT(RF1AINSTR2W_H);                      /* Radio instruction 2-byte register with autoread */
#define  RF1AINSTR2B           RF1AINSTR1W_H  /* Radio instruction 2-byte register with autoread */
SFR_16BIT(RF1ADINW);                          /* Radio word data in register */
SFR_8BIT(RF1ADINW_L);                         /* Radio word data in register */
SFR_8BIT(RF1ADINW_H);                         /* Radio word data in register */

SFR_16BIT(RF1ASTAT0W);                        /* Radio status word register without auto-read */
SFR_8BIT(RF1ASTAT0W_L);                       /* Radio status word register without auto-read */
SFR_8BIT(RF1ASTAT0W_H);                       /* Radio status word register without auto-read */
#define  RF1ADOUT0B            RF1ASTAT0W_L   /* Radio byte data out register without auto-read */
#define  RF1ASTAT0B            RF1ASTAT0W_H   /* Radio status byte register without auto-read */
#define  RF1ASTATW             RF1ASTAT0W     /* Radio status word register without auto-read */
#define  RF1ADOUTB             RF1ASTAT0W_L   /* Radio byte data out register without auto-read */
#define  RF1ASTATB             RF1ASTAT0W_H   /* Radio status byte register without auto-read */
SFR_16BIT(RF1ASTAT1W);                        /* Radio status word register with 1-byte auto-read */
SFR_8BIT(RF1ASTAT1W_L);                       /* Radio status word register with 1-byte auto-read */
SFR_8BIT(RF1ASTAT1W_H);                       /* Radio status word register with 1-byte auto-read */
#define  RF1ADOUT1B            RF1ASTAT1W_L   /* Radio byte data out register with 1-byte auto-read */
#define  RF1ASTAT1B            RF1ASTAT1W_H   /* Radio status byte register with 1-byte auto-read */
SFR_16BIT(RF1ASTAT2W);                        /* Radio status word register with 2-byte auto-read */
SFR_8BIT(RF1ASTAT2W_L);                       /* Radio status word register with 2-byte auto-read */
SFR_8BIT(RF1ASTAT2W_H);                       /* Radio status word register with 2-byte auto-read */
#define  RF1ADOUT2B            RF1ASTAT2W_L   /* Radio byte data out register with 2-byte auto-read */
#define  RF1ASTAT2B            RF1ASTAT2W_H   /* Radio status byte register with 2-byte auto-read */
SFR_16BIT(RF1ADOUT0W);                        /* Radio core word data out register without auto-read */
SFR_8BIT(RF1ADOUT0W_L);                       /* Radio core word data out register without auto-read */
SFR_8BIT(RF1ADOUT0W_H);                       /* Radio core word data out register without auto-read */
#define  RF1ADOUTW             RF1ADOUT0W     /* Radio core word data out register without auto-read */
#define  RF1ADOUTW_L           RF1ADOUT0W_L   /* Radio core word data out register without auto-read */
#define  RF1ADOUTW_H           RF1ADOUT0W_H   /* Radio core word data out register without auto-read */
SFR_16BIT(RF1ADOUT1W);                        /* Radio core word data out register with 1-byte auto-read */
SFR_8BIT(RF1ADOUT1W_L);                       /* Radio core word data out register with 1-byte auto-read */
SFR_8BIT(RF1ADOUT1W_H);                       /* Radio core word data out register with 1-byte auto-read */
SFR_16BIT(RF1ADOUT2W);                        /* Radio core word data out register with 2-byte auto-read */
SFR_8BIT(RF1ADOUT2W_L);                       /* Radio core word data out register with 2-byte auto-read */
SFR_8BIT(RF1ADOUT2W_H);                       /* Radio core word data out register with 2-byte auto-read */
SFR_16BIT(RF1AIN);                            /* Radio core signal input register */
SFR_8BIT(RF1AIN_L);                           /* Radio core signal input register */
SFR_8BIT(RF1AIN_H);                           /* Radio core signal input register */
SFR_16BIT(RF1AIFG);                           /* Radio core interrupt flag register */
SFR_8BIT(RF1AIFG_L);                          /* Radio core interrupt flag register */
SFR_8BIT(RF1AIFG_H);                          /* Radio core interrupt flag register */
SFR_16BIT(RF1AIES);                           /* Radio core interrupt edge select register */
SFR_8BIT(RF1AIES_L);                          /* Radio core interrupt edge select register */
SFR_8BIT(RF1AIES_H);                          /* Radio core interrupt edge select register */
SFR_16BIT(RF1AIE);                            /* Radio core interrupt enable register */
SFR_8BIT(RF1AIE_L);                           /* Radio core interrupt enable register */
SFR_8BIT(RF1AIE_H);                           /* Radio core interrupt enable register */
SFR_16BIT(RF1AIV);                            /* Radio core interrupt vector word register */
SFR_8BIT(RF1AIV_L);                           /* Radio core interrupt vector word register */
SFR_8BIT(RF1AIV_H);                           /* Radio core interrupt vector word register */
SFR_16BIT(RF1ARXFIFO);                        /* Direct receive FIFO access register */
SFR_8BIT(RF1ARXFIFO_L);                       /* Direct receive FIFO access register */
SFR_8BIT(RF1ARXFIFO_H);                       /* Direct receive FIFO access register */
SFR_16BIT(RF1ATXFIFO);                        /* Direct transmit FIFO access register */
SFR_8BIT(RF1ATXFIFO_L);                       /* Direct transmit FIFO access register */
SFR_8BIT(RF1ATXFIFO_H);                       /* Direct transmit FIFO access register */

/* RF1AIFCTL0 Control Bits */
#define RFFIFOEN               (0x0001)       /* CC1101 Direct FIFO access enable */
#define RFENDIAN               (0x0002)       /* CC1101 Disable endianness conversion */

/* RF1AIFCTL0 Control Bits */
#define RFFIFOEN_L             (0x0001)       /* CC1101 Direct FIFO access enable */
#define RFENDIAN_L             (0x0002)       /* CC1101 Disable endianness conversion */

/* RF1AIFCTL1 Control Bits */
#define RFRXIFG                (0x0001)       /* Radio interface direct FIFO access receive interrupt flag */
#define RFTXIFG                (0x0002)       /* Radio interface direct FIFO access transmit interrupt flag */
#define RFERRIFG               (0x0004)       /* Radio interface error interrupt flag */
#define RFINSTRIFG             (0x0010)       /* Radio interface instruction interrupt flag */
#define RFDINIFG               (0x0020)       /* Radio interface data in interrupt flag */
#define RFSTATIFG              (0x0040)       /* Radio interface status interrupt flag */
#define RFDOUTIFG              (0x0080)       /* Radio interface data out interrupt flag */
#define RFRXIE                 (0x0100)       /* Radio interface direct FIFO access receive interrupt enable */
#define RFTXIE                 (0x0200)       /* Radio interface direct FIFO access transmit interrupt enable */
#define RFERRIE                (0x0400)       /* Radio interface error interrupt enable */
#define RFINSTRIE              (0x1000)       /* Radio interface instruction interrupt enable */
#define RFDINIE                (0x2000)       /* Radio interface data in interrupt enable */
#define RFSTATIE               (0x4000)       /* Radio interface status interrupt enable */
#define RFDOUTIE               (0x8000)       /* Radio interface data out interrupt enable */

/* RF1AIFCTL1 Control Bits */
#define RFRXIFG_L              (0x0001)       /* Radio interface direct FIFO access receive interrupt flag */
#define RFTXIFG_L              (0x0002)       /* Radio interface direct FIFO access transmit interrupt flag */
#define RFERRIFG_L             (0x0004)       /* Radio interface error interrupt flag */
#define RFINSTRIFG_L           (0x0010)       /* Radio interface instruction interrupt flag */
#define RFDINIFG_L             (0x0020)       /* Radio interface data in interrupt flag */
#define RFSTATIFG_L            (0x0040)       /* Radio interface status interrupt flag */
#define RFDOUTIFG_L            (0x0080)       /* Radio interface data out interrupt flag */

/* RF1AIFCTL1 Control Bits */
#define RFRXIE_H               (0x0001)       /* Radio interface direct FIFO access receive interrupt enable */
#define RFTXIE_H               (0x0002)       /* Radio interface direct FIFO access transmit interrupt enable */
#define RFERRIE_H              (0x0004)       /* Radio interface error interrupt enable */
#define RFINSTRIE_H            (0x0010)       /* Radio interface instruction interrupt enable */
#define RFDINIE_H              (0x0020)       /* Radio interface data in interrupt enable */
#define RFSTATIE_H             (0x0040)       /* Radio interface status interrupt enable */
#define RFDOUTIE_H             (0x0080)       /* Radio interface data out interrupt enable */

/* RF1AIFERR Control Bits */
#define LVERR                  (0x0001)       /* Low Core Voltage Error Flag */
#define OPERR                  (0x0002)       /* Operand Error Flag */
#define OUTERR                 (0x0004)       /* Output data not available Error Flag */
#define OPOVERR                (0x0008)       /* Operand Overwrite Error Flag */

/* RF1AIFERR Control Bits */
#define LVERR_L                (0x0001)       /* Low Core Voltage Error Flag */
#define OPERR_L                (0x0002)       /* Operand Error Flag */
#define OUTERR_L               (0x0004)       /* Output data not available Error Flag */
#define OPOVERR_L              (0x0008)       /* Operand Overwrite Error Flag */

/* RF1AIFERRV Definitions */
#define RF1AIFERRV_NONE        (0x0000)       /* No Error pending */
#define RF1AIFERRV_LVERR       (0x0002)       /* Low core voltage error */
#define RF1AIFERRV_OPERR       (0x0004)       /* Operand Error */
#define RF1AIFERRV_OUTERR      (0x0006)       /* Output data not available Error */
#define RF1AIFERRV_OPOVERR     (0x0008)       /* Operand Overwrite Error */

/* RF1AIFIV Definitions */
#define RF1AIFIV_NONE          (0x0000)       /* No Interrupt pending */
#define RF1AIFIV_RFERRIFG      (0x0002)       /* Radio interface error */
#define RF1AIFIV_RFDOUTIFG     (0x0004)       /* Radio i/f data out */
#define RF1AIFIV_RFSTATIFG     (0x0006)       /* Radio i/f status out */
#define RF1AIFIV_RFDINIFG      (0x0008)       /* Radio i/f data in */
#define RF1AIFIV_RFINSTRIFG    (0x000A)       /* Radio i/f instruction in */

/* RF1AIV Definitions */
#define RF1AIV_NONE            (0x0000)       /* No Interrupt pending */
#define RF1AIV_RFIFG0          (0x0002)       /* RFIFG0 */
#define RF1AIV_RFIFG1          (0x0004)       /* RFIFG1 */
#define RF1AIV_RFIFG2          (0x0006)       /* RFIFG2 */
#define RF1AIV_RFIFG3          (0x0008)       /* RFIFG3 */
#define RF1AIV_RFIFG4          (0x000A)       /* RFIFG4 */
#define RF1AIV_RFIFG5          (0x000C)       /* RFIFG5 */
#define RF1AIV_RFIFG6          (0x000E)       /* RFIFG6 */
#define RF1AIV_RFIFG7          (0x0010)       /* RFIFG7 */
#define RF1AIV_RFIFG8          (0x0012)       /* RFIFG8 */
#define RF1AIV_RFIFG9          (0x0014)       /* RFIFG9 */
#define RF1AIV_RFIFG10         (0x0016)       /* RFIFG10 */
#define RF1AIV_RFIFG11         (0x0018)       /* RFIFG11 */
#define RF1AIV_RFIFG12         (0x001A)       /* RFIFG12 */
#define RF1AIV_RFIFG13         (0x001C)       /* RFIFG13 */
#define RF1AIV_RFIFG14         (0x001E)       /* RFIFG14 */
#define RF1AIV_RFIFG15         (0x0020)       /* RFIFG15 */

// Radio Core Registers
#define IOCFG2                 0x00           /*  IOCFG2   - GDO2 output pin configuration  */
#define IOCFG1                 0x01           /*  IOCFG1   - GDO1 output pin configuration  */
#define IOCFG0                 0x02           /*  IOCFG1   - GDO0 output pin configuration  */
#define FIFOTHR                0x03           /*  FIFOTHR  - RX FIFO and TX FIFO thresholds */
#define SYNC1                  0x04           /*  SYNC1    - Sync word, high byte */
#define SYNC0                  0x05           /*  SYNC0    - Sync word, low byte */
#define PKTLEN                 0x06           /*  PKTLEN   - Packet length */
#define PKTCTRL1               0x07           /*  PKTCTRL1 - Packet automation control */
#define PKTCTRL0               0x08           /*  PKTCTRL0 - Packet automation control */
#define ADDR                   0x09           /*  ADDR     - Device address */
#define CHANNR                 0x0A           /*  CHANNR   - Channel number */
#define FSCTRL1                0x0B           /*  FSCTRL1  - Frequency synthesizer control */
#define FSCTRL0                0x0C           /*  FSCTRL0  - Frequency synthesizer control */
#define FREQ2                  0x0D           /*  FREQ2    - Frequency control word, high byte */
#define FREQ1                  0x0E           /*  FREQ1    - Frequency control word, middle byte */
#define FREQ0                  0x0F           /*  FREQ0    - Frequency control word, low byte */
#define MDMCFG4                0x10           /*  MDMCFG4  - Modem configuration */
#define MDMCFG3                0x11           /*  MDMCFG3  - Modem configuration */
#define MDMCFG2                0x12           /*  MDMCFG2  - Modem configuration */
#define MDMCFG1                0x13           /*  MDMCFG1  - Modem configuration */
#define MDMCFG0                0x14           /*  MDMCFG0  - Modem configuration */
#define DEVIATN                0x15           /*  DEVIATN  - Modem deviation setting */
#define MCSM2                  0x16           /*  MCSM2    - Main Radio Control State Machine configuration */
#define MCSM1                  0x17           /*  MCSM1    - Main Radio Control State Machine configuration */
#define MCSM0                  0x18           /*  MCSM0    - Main Radio Control State Machine configuration */
#define FOCCFG                 0x19           /*  FOCCFG   - Frequency Offset Compensation configuration */
#define BSCFG                  0x1A           /*  BSCFG    - Bit Synchronization configuration */
#define AGCCTRL2               0x1B           /*  AGCCTRL2 - AGC control */
#define AGCCTRL1               0x1C           /*  AGCCTRL1 - AGC control */
#define AGCCTRL0               0x1D           /*  AGCCTRL0 - AGC control */
#define WOREVT1                0x1E           /*  WOREVT1  - High byte Event0 timeout */
#define WOREVT0                0x1F           /*  WOREVT0  - Low byte Event0 timeout */
#define WORCTRL                0x20           /*  WORCTRL  - Wake On Radio control */
#define FREND1                 0x21           /*  FREND1   - Front end RX configuration */
#define FREND0                 0x22           /*  FREDN0   - Front end TX configuration */
#define FSCAL3                 0x23           /*  FSCAL3   - Frequency synthesizer calibration */
#define FSCAL2                 0x24           /*  FSCAL2   - Frequency synthesizer calibration */
#define FSCAL1                 0x25           /*  FSCAL1   - Frequency synthesizer calibration */
#define FSCAL0                 0x26           /*  FSCAL0   - Frequency synthesizer calibration */
//#define RCCTRL1             0x27      /*  RCCTRL1  - RC oscillator configuration */
//#define RCCTRL0             0x28      /*  RCCTRL0  - RC oscillator configuration */
#define FSTEST                 0x29           /*  FSTEST   - Frequency synthesizer calibration control */
#define PTEST                  0x2A           /*  PTEST    - Production test */
#define AGCTEST                0x2B           /*  AGCTEST  - AGC test */
#define TEST2                  0x2C           /*  TEST2    - Various test settings */
#define TEST1                  0x2D           /*  TEST1    - Various test settings */
#define TEST0                  0x2E           /*  TEST0    - Various test settings */

/* status registers */
#define PARTNUM                0x30           /*  PARTNUM    - Chip ID */
#define VERSION                0x31           /*  VERSION    - Chip ID */
#define FREQEST                0x32           /*  FREQEST    � Frequency Offset Estimate from demodulator */
#define LQI                    0x33           /*  LQI        � Demodulator estimate for Link Quality */
#define RSSI                   0x34           /*  RSSI       � Received signal strength indication */
#define MARCSTATE              0x35           /*  MARCSTATE  � Main Radio Control State Machine state */
#define WORTIME1               0x36           /*  WORTIME1   � High byte of WOR time */
#define WORTIME0               0x37           /*  WORTIME0   � Low byte of WOR time */
#define PKTSTATUS              0x38           /*  PKTSTATUS  � Current GDOx status and packet status */
#define VCO_VC_DAC             0x39           /*  VCO_VC_DAC � Current setting from PLL calibration module */
#define TXBYTES                0x3A           /*  TXBYTES    � Underflow and number of bytes */
#define RXBYTES                0x3B           /*  RXBYTES    � Overflow and number of bytes */

/* burst write registers */
#define PATABLE                0x3E           /*  PATABLE - PA control settings table */
#define TXFIFO                 0x3F           /*  TXFIFO  - Transmit FIFO */
#define RXFIFO                 0x3F           /*  RXFIFO  - Receive FIFO */

/* Radio Core Instructions */
/* command strobes               */
#define RF_SRES                0x30           /*  SRES    - Reset chip. */
#define RF_SFSTXON             0x31           /*  SFSTXON - Enable and calibrate frequency synthesizer. */
#define RF_SXOFF               0x32           /*  SXOFF   - Turn off crystal oscillator. */
#define RF_SCAL                0x33           /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
#define RF_SRX                 0x34           /*  SRX     - Enable RX. Perform calibration if enabled. */
#define RF_STX                 0x35           /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
#define RF_SIDLE               0x36           /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
//#define RF_SRSVD            0x37      /*  SRVSD   - Reserved.  Do not use. */
#define RF_SWOR                0x38           /*  SWOR    - Start automatic RX polling sequence (Wake-on-Radio) */
#define RF_SPWD                0x39           /*  SPWD    - Enter power down mode when CSn goes high. */
#define RF_SFRX                0x3A           /*  SFRX    - Flush the RX FIFO buffer. */
#define RF_SFTX                0x3B           /*  SFTX    - Flush the TX FIFO buffer. */
#define RF_SWORRST             0x3C           /*  SWORRST - Reset real time clock. */
#define RF_SNOP                0x3D           /*  SNOP    - No operation. Returns status byte. */

#define RF_RXSTAT              0x80           /* Used in combination with strobe commands delivers number of availabe bytes in RX FIFO with return status */
#define RF_TXSTAT              0x00           /* Used in combination with strobe commands delivers number of availabe bytes in TX FIFO with return status */

/* other radio instr */
#define RF_SNGLREGRD           0x80
#define RF_SNGLREGWR           0x00
#define RF_REGRD               0xC0
#define RF_REGWR               0x40
#define RF_STATREGRD           0xC0           /* Read single radio core status register */
#define RF_SNGLPATABRD         (RF_SNGLREGRD+PATABLE)
#define RF_SNGLPATABWR         (RF_SNGLREGWR+PATABLE)
#define RF_PATABRD             (RF_REGRD+PATABLE)
#define RF_PATABWR             (RF_REGWR+PATABLE)
#define RF_SNGLRXRD            (RF_SNGLREGRD+RXFIFO)
#define RF_SNGLTXWR            (RF_SNGLREGWR+TXFIFO)
#define RF_RXFIFORD            (RF_REGRD+RXFIFO)
#define RF_TXFIFOWR            (RF_REGWR+TXFIFO)

/*************************************************************
* CRC Module
*************************************************************/
#define __MSP430_HAS_CRC__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x0150
#define CRC_BASE               __MSP430_BASEADDRESS_CRC__

SFR_16BIT(CRCDI);                             /* CRC Data In Register */
SFR_8BIT(CRCDI_L);                            /* CRC Data In Register */
SFR_8BIT(CRCDI_H);                            /* CRC Data In Register */
SFR_16BIT(CRCINIRES);                         /* CRC Initialisation Register and Result Register*/
SFR_8BIT(CRCINIRES_L);                        /* CRC Initialisation Register and Result Register*/
SFR_8BIT(CRCINIRES_H);                        /* CRC Initialisation Register and Result Register*/

/************************************************************
* DMA_X
************************************************************/
#define __MSP430_HAS_DMAX_3__                 /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_DMAX_3__ 0x0500
#define DMA_BASE               __MSP430_BASEADDRESS_DMAX_3__

SFR_16BIT(DMACTL0);                           /* DMA Module Control 0 */
SFR_8BIT(DMACTL0_L);                          /* DMA Module Control 0 */
SFR_8BIT(DMACTL0_H);                          /* DMA Module Control 0 */
SFR_16BIT(DMACTL1);                           /* DMA Module Control 1 */
SFR_8BIT(DMACTL1_L);                          /* DMA Module Control 1 */
SFR_8BIT(DMACTL1_H);                          /* DMA Module Control 1 */
SFR_16BIT(DMACTL2);                           /* DMA Module Control 2 */
SFR_8BIT(DMACTL2_L);                          /* DMA Module Control 2 */
SFR_8BIT(DMACTL2_H);                          /* DMA Module Control 2 */
SFR_16BIT(DMACTL3);                           /* DMA Module Control 3 */
SFR_8BIT(DMACTL3_L);                          /* DMA Module Control 3 */
SFR_8BIT(DMACTL3_H);                          /* DMA Module Control 3 */
SFR_16BIT(DMACTL4);                           /* DMA Module Control 4 */
SFR_8BIT(DMACTL4_L);                          /* DMA Module Control 4 */
SFR_8BIT(DMACTL4_H);                          /* DMA Module Control 4 */
SFR_16BIT(DMAIV);                             /* DMA Interrupt Vector Word */
SFR_8BIT(DMAIV_L);                            /* DMA Interrupt Vector Word */
SFR_8BIT(DMAIV_H);                            /* DMA Interrupt Vector Word */

SFR_16BIT(DMA0CTL);                           /* DMA Channel 0 Control */
SFR_8BIT(DMA0CTL_L);                          /* DMA Channel 0 Control */
SFR_8BIT(DMA0CTL_H);                          /* DMA Channel 0 Control */
SFR_20BIT(DMA0SA);                            /* DMA Channel 0 Source Address */
SFR_16BIT(DMA0SAL);                           /* DMA Channel 0 Source Address */
SFR_16BIT(DMA0SAH);                           /* DMA Channel 0 Source Address */
SFR_20BIT(DMA0DA);                            /* DMA Channel 0 Destination Address */
SFR_16BIT(DMA0DAL);                           /* DMA Channel 0 Destination Address */
SFR_16BIT(DMA0DAH);                           /* DMA Channel 0 Destination Address */
SFR_16BIT(DMA0SZ);                            /* DMA Channel 0 Transfer Size */

SFR_16BIT(DMA1CTL);                           /* DMA Channel 1 Control */
SFR_8BIT(DMA1CTL_L);                          /* DMA Channel 1 Control */
SFR_8BIT(DMA1CTL_H);                          /* DMA Channel 1 Control */
SFR_20BIT(DMA1SA);                            /* DMA Channel 1 Source Address */
SFR_16BIT(DMA1SAL);                           /* DMA Channel 1 Source Address */
SFR_16BIT(DMA1SAH);                           /* DMA Channel 1 Source Address */
SFR_20BIT(DMA1DA);                            /* DMA Channel 1 Destination Address */
SFR_16BIT(DMA1DAL);                           /* DMA Channel 1 Destination Address */
SFR_16BIT(DMA1DAH);                           /* DMA Channel 1 Destination Address */
SFR_16BIT(DMA1SZ);                            /* DMA Channel 1 Transfer Size */

SFR_16BIT(DMA2CTL);                           /* DMA Channel 2 Control */
SFR_8BIT(DMA2CTL_L);                          /* DMA Channel 2 Control */
SFR_8BIT(DMA2CTL_H);                          /* DMA Channel 2 Control */
SFR_20BIT(DMA2SA);                            /* DMA Channel 2 Source Address */
SFR_16BIT(DMA2SAL);                           /* DMA Channel 2 Source Address */
SFR_16BIT(DMA2SAH);                           /* DMA Channel 2 Source Address */
SFR_20BIT(DMA2DA);                            /* DMA Channel 2 Destination Address */
SFR_16BIT(DMA2DAL);                           /* DMA Channel 2 Destination Address */
SFR_16BIT(DMA2DAH);                           /* DMA Channel 2 Destination Address */
SFR_16BIT(DMA2SZ);                            /* DMA Channel 2 Transfer Size */

/* DMACTL0 Control Bits */
#define DMA0TSEL0              (0x0001)       /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1              (0x0002)       /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2              (0x0004)       /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3              (0x0008)       /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4              (0x0010)       /* DMA channel 0 transfer select bit 4 */
#define DMA1TSEL0              (0x0100)       /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1              (0x0200)       /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2              (0x0400)       /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3              (0x0800)       /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4              (0x1000)       /* DMA channel 1 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA0TSEL0_L            (0x0001)       /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L            (0x0002)       /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L            (0x0004)       /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L            (0x0008)       /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L            (0x0010)       /* DMA channel 0 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA1TSEL0_H            (0x0001)       /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H            (0x0002)       /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H            (0x0004)       /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H            (0x0008)       /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H            (0x0010)       /* DMA channel 1 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0              (0x0001)       /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1              (0x0002)       /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2              (0x0004)       /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3              (0x0008)       /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4              (0x0010)       /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0_L            (0x0001)       /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L            (0x0002)       /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L            (0x0004)       /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L            (0x0008)       /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L            (0x0010)       /* DMA channel 2 transfer select bit 4 */

/* DMACTL4 Control Bits */
#define ENNMI                  (0x0001)       /* Enable NMI interruption of DMA */
#define ROUNDROBIN             (0x0002)       /* Round-Robin DMA channel priorities */
#define DMARMWDIS              (0x0004)       /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */
#define ENNMI_L                (0x0001)       /* Enable NMI interruption of DMA */
#define ROUNDROBIN_L           (0x0002)       /* Round-Robin DMA channel priorities */
#define DMARMWDIS_L            (0x0004)       /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMAxCTL Control Bits */
#define DMAREQ                 (0x0001)       /* Initiate DMA transfer with DMATSEL */
#define DMAABORT               (0x0002)       /* DMA transfer aborted by NMI */
#define DMAIE                  (0x0004)       /* DMA interrupt enable */
#define DMAIFG                 (0x0008)       /* DMA interrupt flag */
#define DMAEN                  (0x0010)       /* DMA enable */
#define DMALEVEL               (0x0020)       /* DMA level sensitive trigger select */
#define DMASRCBYTE             (0x0040)       /* DMA source byte */
#define DMADSTBYTE             (0x0080)       /* DMA destination byte */
#define DMASRCINCR0            (0x0100)       /* DMA source increment bit 0 */
#define DMASRCINCR1            (0x0200)       /* DMA source increment bit 1 */
#define DMADSTINCR0            (0x0400)       /* DMA destination increment bit 0 */
#define DMADSTINCR1            (0x0800)       /* DMA destination increment bit 1 */
#define DMADT0                 (0x1000)       /* DMA transfer mode bit 0 */
#define DMADT1                 (0x2000)       /* DMA transfer mode bit 1 */
#define DMADT2                 (0x4000)       /* DMA transfer mode bit 2 */

/* DMAxCTL Control Bits */
#define DMAREQ_L               (0x0001)       /* Initiate DMA transfer with DMATSEL */
#define DMAABORT_L             (0x0002)       /* DMA transfer aborted by NMI */
#define DMAIE_L                (0x0004)       /* DMA interrupt enable */
#define DMAIFG_L               (0x0008)       /* DMA interrupt flag */
#define DMAEN_L                (0x0010)       /* DMA enable */
#define DMALEVEL_L             (0x0020)       /* DMA level sensitive trigger select */
#define DMASRCBYTE_L           (0x0040)       /* DMA source byte */
#define DMADSTBYTE_L           (0x0080)       /* DMA destination byte */

/* DMAxCTL Control Bits */
#define DMASRCINCR0_H          (0x0001)       /* DMA source increment bit 0 */
#define DMASRCINCR1_H          (0x0002)       /* DMA source increment bit 1 */
#define DMADSTINCR0_H          (0x0004)       /* DMA destination increment bit 0 */
#define DMADSTINCR1_H          (0x0008)       /* DMA destination increment bit 1 */
#define DMADT0_H               (0x0010)       /* DMA transfer mode bit 0 */
#define DMADT1_H               (0x0020)       /* DMA transfer mode bit 1 */
#define DMADT2_H               (0x0040)       /* DMA transfer mode bit 2 */

#define DMASWDW                (0*0x0040u)    /* DMA transfer: source word to destination word */
#define DMASBDW                (1*0x0040u)    /* DMA transfer: source byte to destination word */
#define DMASWDB                (2*0x0040u)    /* DMA transfer: source word to destination byte */
#define DMASBDB                (3*0x0040u)    /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0           (0*0x0100u)    /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1           (1*0x0100u)    /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2           (2*0x0100u)    /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3           (3*0x0100u)    /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0           (0*0x0400u)    /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1           (1*0x0400u)    /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2           (2*0x0400u)    /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3           (3*0x0400u)    /* DMA destination increment 3: destination address incremented */

#define DMADT_0                (0*0x1000u)    /* DMA transfer mode 0: Single transfer */
#define DMADT_1                (1*0x1000u)    /* DMA transfer mode 1: Block transfer */
#define DMADT_2                (2*0x1000u)    /* DMA transfer mode 2: Burst-Block transfer */
#define DMADT_3                (3*0x1000u)    /* DMA transfer mode 3: Burst-Block transfer */
#define DMADT_4                (4*0x1000u)    /* DMA transfer mode 4: Repeated Single transfer */
#define DMADT_5                (5*0x1000u)    /* DMA transfer mode 5: Repeated Block transfer */
#define DMADT_6                (6*0x1000u)    /* DMA transfer mode 6: Repeated Burst-Block transfer */
#define DMADT_7                (7*0x1000u)    /* DMA transfer mode 7: Repeated Burst-Block transfer */

/* DMAIV Definitions */
#define DMAIV_NONE             (0x0000)       /* No Interrupt pending */
#define DMAIV_DMA0IFG          (0x0002)       /* DMA0IFG*/
#define DMAIV_DMA1IFG          (0x0004)       /* DMA1IFG*/
#define DMAIV_DMA2IFG          (0x0006)       /* DMA2IFG*/

#define DMA0TSEL_0             (0*0x0001u)    /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL_1             (1*0x0001u)    /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL_2             (2*0x0001u)    /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL_3             (3*0x0001u)    /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL_4             (4*0x0001u)    /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL_5             (5*0x0001u)    /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL_6             (6*0x0001u)    /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL_7             (7*0x0001u)    /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL_8             (8*0x0001u)    /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL_9             (9*0x0001u)    /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL_10            (10*0x0001u)   /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL_11            (11*0x0001u)   /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL_12            (12*0x0001u)   /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL_13            (13*0x0001u)   /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL_14            (14*0x0001u)   /* DMA channel 0 transfer select 14: RFRXIFG */
#define DMA0TSEL_15            (15*0x0001u)   /* DMA channel 0 transfer select 15: RFTXIFG */
#define DMA0TSEL_16            (16*0x0001u)   /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL_17            (17*0x0001u)   /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL_18            (18*0x0001u)   /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL_19            (19*0x0001u)   /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL_20            (20*0x0001u)   /* DMA channel 0 transfer select 20: Reserved  */
#define DMA0TSEL_21            (21*0x0001u)   /* DMA channel 0 transfer select 21: Reserved  */
#define DMA0TSEL_22            (22*0x0001u)   /* DMA channel 0 transfer select 22: Reserved  */
#define DMA0TSEL_23            (23*0x0001u)   /* DMA channel 0 transfer select 23: Reserved  */
#define DMA0TSEL_24            (24*0x0001u)   /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL_25            (25*0x0001u)   /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL_26            (26*0x0001u)   /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL_27            (27*0x0001u)   /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL_28            (28*0x0001u)   /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL_29            (29*0x0001u)   /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL_30            (30*0x0001u)   /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL_31            (31*0x0001u)   /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL_0             (0*0x0100u)    /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL_1             (1*0x0100u)    /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL_2             (2*0x0100u)    /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL_3             (3*0x0100u)    /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL_4             (4*0x0100u)    /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL_5             (5*0x0100u)    /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL_6             (6*0x0100u)    /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL_7             (7*0x0100u)    /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL_8             (8*0x0100u)    /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL_9             (9*0x0100u)    /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL_10            (10*0x0100u)   /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL_11            (11*0x0100u)   /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL_12            (12*0x0100u)   /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL_13            (13*0x0100u)   /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL_14            (14*0x0100u)   /* DMA channel 1 transfer select 14: RFRXIFG */
#define DMA1TSEL_15            (15*0x0100u)   /* DMA channel 1 transfer select 15: RFTXIFG */
#define DMA1TSEL_16            (16*0x0100u)   /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL_17            (17*0x0100u)   /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL_18            (18*0x0100u)   /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL_19            (19*0x0100u)   /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL_20            (20*0x0100u)   /* DMA channel 1 transfer select 20: Reserved  */
#define DMA1TSEL_21            (21*0x0100u)   /* DMA channel 1 transfer select 21: Reserved  */
#define DMA1TSEL_22            (22*0x0100u)   /* DMA channel 1 transfer select 22: Reserved  */
#define DMA1TSEL_23            (23*0x0100u)   /* DMA channel 1 transfer select 23: Reserved  */
#define DMA1TSEL_24            (24*0x0100u)   /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL_25            (25*0x0100u)   /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL_26            (26*0x0100u)   /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL_27            (27*0x0100u)   /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL_28            (28*0x0100u)   /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL_29            (29*0x0100u)   /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL_30            (30*0x0100u)   /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL_31            (31*0x0100u)   /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL_0             (0*0x0001u)    /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL_1             (1*0x0001u)    /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL_2             (2*0x0001u)    /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL_3             (3*0x0001u)    /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL_4             (4*0x0001u)    /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL_5             (5*0x0001u)    /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL_6             (6*0x0001u)    /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL_7             (7*0x0001u)    /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL_8             (8*0x0001u)    /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL_9             (9*0x0001u)    /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL_10            (10*0x0001u)   /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL_11            (11*0x0001u)   /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL_12            (12*0x0001u)   /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL_13            (13*0x0001u)   /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL_14            (14*0x0001u)   /* DMA channel 2 transfer select 14: RFRXIFG */
#define DMA2TSEL_15            (15*0x0001u)   /* DMA channel 2 transfer select 15: RFTXIFG */
#define DMA2TSEL_16            (16*0x0001u)   /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL_17            (17*0x0001u)   /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL_18            (18*0x0001u)   /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL_19            (19*0x0001u)   /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL_20            (20*0x0001u)   /* DMA channel 2 transfer select 20: Reserved  */
#define DMA2TSEL_21            (21*0x0001u)   /* DMA channel 2 transfer select 21: Reserved  */
#define DMA2TSEL_22            (22*0x0001u)   /* DMA channel 2 transfer select 22: Reserved  */
#define DMA2TSEL_23            (23*0x0001u)   /* DMA channel 2 transfer select 23: Reserved  */
#define DMA2TSEL_24            (24*0x0001u)   /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL_25            (25*0x0001u)   /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL_26            (26*0x0001u)   /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL_27            (27*0x0001u)   /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL_28            (28*0x0001u)   /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL_29            (29*0x0001u)   /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL_30            (30*0x0001u)   /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL_31            (31*0x0001u)   /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

#define DMA0TSEL__DMA_REQ      (0*0x0001u)    /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL__TA0CCR0      (1*0x0001u)    /* DMA channel 0 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA0TSEL__TA0CCR2      (2*0x0001u)    /* DMA channel 0 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA0TSEL__TA1CCR0      (3*0x0001u)    /* DMA channel 0 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA0TSEL__TA1CCR2      (4*0x0001u)    /* DMA channel 0 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA0TSEL__TB0CCR0      (5*0x0001u)    /* DMA channel 0 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA0TSEL__TB0CCR2      (6*0x0001u)    /* DMA channel 0 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA0TSEL__RES7         (7*0x0001u)    /* DMA channel 0 transfer select 7:  Reserved */
#define DMA0TSEL__RES8         (8*0x0001u)    /* DMA channel 0 transfer select 8:  Reserved */
#define DMA0TSEL__RES9         (9*0x0001u)    /* DMA channel 0 transfer select 9:  Reserved */
#define DMA0TSEL__RES10        (10*0x0001u)   /* DMA channel 0 transfer select 10: Reserved */
#define DMA0TSEL__RES11        (11*0x0001u)   /* DMA channel 0 transfer select 11: Reserved */
#define DMA0TSEL__RES12        (12*0x0001u)   /* DMA channel 0 transfer select 12: Reserved */
#define DMA0TSEL__RES13        (13*0x0001u)   /* DMA channel 0 transfer select 13: Reserved */
#define DMA0TSEL__RFRXIFG      (14*0x0001u)   /* DMA channel 0 transfer select 14: RFRXIFG */
#define DMA0TSEL__RFTXIFG      (15*0x0001u)   /* DMA channel 0 transfer select 15: RFTXIFG */
#define DMA0TSEL__USCIA0RX     (16*0x0001u)   /* DMA channel 0 transfer select 16: USCIA0 receive */
#define DMA0TSEL__USCIA0TX     (17*0x0001u)   /* DMA channel 0 transfer select 17: USCIA0 transmit */
#define DMA0TSEL__USCIB0RX     (18*0x0001u)   /* DMA channel 0 transfer select 18: USCIB0 receive */
#define DMA0TSEL__USCIB0TX     (19*0x0001u)   /* DMA channel 0 transfer select 19: USCIB0 transmit */
#define DMA0TSEL__RES20        (20*0x0001u)   /* DMA channel 0 transfer select 20: Reserved  */
#define DMA0TSEL__RES21        (21*0x0001u)   /* DMA channel 0 transfer select 21: Reserved  */
#define DMA0TSEL__RES22        (22*0x0001u)   /* DMA channel 0 transfer select 22: Reserved  */
#define DMA0TSEL__RES23        (23*0x0001u)   /* DMA channel 0 transfer select 23: Reserved  */
#define DMA0TSEL__ADC12IFG     (24*0x0001u)   /* DMA channel 0 transfer select 24: ADC12IFGx */
#define DMA0TSEL__RES25        (25*0x0001u)   /* DMA channel 0 transfer select 25: Reserved */
#define DMA0TSEL__RES26        (26*0x0001u)   /* DMA channel 0 transfer select 26: Reserved */
#define DMA0TSEL__RES27        (27*0x0001u)   /* DMA channel 0 transfer select 27: Reserved */
#define DMA0TSEL__RES28        (28*0x0001u)   /* DMA channel 0 transfer select 28: Reserved */
#define DMA0TSEL__MPY          (29*0x0001u)   /* DMA channel 0 transfer select 29: Multiplier ready */
#define DMA0TSEL__DMA2IFG      (30*0x0001u)   /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL__DMAE0        (31*0x0001u)   /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL__DMA_REQ      (0*0x0100u)    /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL__TA0CCR0      (1*0x0100u)    /* DMA channel 1 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA1TSEL__TA0CCR2      (2*0x0100u)    /* DMA channel 1 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA1TSEL__TA1CCR0      (3*0x0100u)    /* DMA channel 1 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA1TSEL__TA1CCR2      (4*0x0100u)    /* DMA channel 1 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA1TSEL__TB0CCR0      (5*0x0100u)    /* DMA channel 1 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA1TSEL__TB0CCR2      (6*0x0100u)    /* DMA channel 1 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA1TSEL__RES7         (7*0x0100u)    /* DMA channel 1 transfer select 7:  Reserved */
#define DMA1TSEL__RES8         (8*0x0100u)    /* DMA channel 1 transfer select 8:  Reserved */
#define DMA1TSEL__RES9         (9*0x0100u)    /* DMA channel 1 transfer select 9:  Reserved */
#define DMA1TSEL__RES10        (10*0x0100u)   /* DMA channel 1 transfer select 10: Reserved */
#define DMA1TSEL__RES11        (11*0x0100u)   /* DMA channel 1 transfer select 11: Reserved */
#define DMA1TSEL__RES12        (12*0x0100u)   /* DMA channel 1 transfer select 12: Reserved */
#define DMA1TSEL__RES13        (13*0x0100u)   /* DMA channel 1 transfer select 13: Reserved */
#define DMA1TSEL__RFRXIFG      (14*0x0100u)   /* DMA channel 1 transfer select 14: RFRXIFG */
#define DMA1TSEL__RFTXIFG      (15*0x0100u)   /* DMA channel 1 transfer select 15: RFTXIFG */
#define DMA1TSEL__USCIA0RX     (16*0x0100u)   /* DMA channel 1 transfer select 16: USCIA0 receive */
#define DMA1TSEL__USCIA0TX     (17*0x0100u)   /* DMA channel 1 transfer select 17: USCIA0 transmit */
#define DMA1TSEL__USCIB0RX     (18*0x0100u)   /* DMA channel 1 transfer select 18: USCIB0 receive */
#define DMA1TSEL__USCIB0TX     (19*0x0100u)   /* DMA channel 1 transfer select 19: USCIB0 transmit */
#define DMA1TSEL__RES20        (20*0x0100u)   /* DMA channel 1 transfer select 20: Reserved  */
#define DMA1TSEL__RES21        (21*0x0100u)   /* DMA channel 1 transfer select 21: Reserved  */
#define DMA1TSEL__RES22        (22*0x0100u)   /* DMA channel 1 transfer select 22: Reserved  */
#define DMA1TSEL__RES23        (23*0x0100u)   /* DMA channel 1 transfer select 23: Reserved  */
#define DMA1TSEL__ADC12IFG     (24*0x0100u)   /* DMA channel 1 transfer select 24: ADC12IFGx */
#define DMA1TSEL__RES25        (25*0x0100u)   /* DMA channel 1 transfer select 25: Reserved */
#define DMA1TSEL__RES26        (26*0x0100u)   /* DMA channel 1 transfer select 26: Reserved */
#define DMA1TSEL__RES27        (27*0x0100u)   /* DMA channel 1 transfer select 27: Reserved */
#define DMA1TSEL__RES28        (28*0x0100u)   /* DMA channel 1 transfer select 28: Reserved */
#define DMA1TSEL__MPY          (29*0x0100u)   /* DMA channel 1 transfer select 29: Multiplier ready */
#define DMA1TSEL__DMA0IFG      (30*0x0100u)   /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL__DMAE0        (31*0x0100u)   /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL__DMA_REQ      (0*0x0001u)    /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL__TA0CCR0      (1*0x0001u)    /* DMA channel 2 transfer select 1:  Timer0_A (TA0CCR0.IFG) */
#define DMA2TSEL__TA0CCR2      (2*0x0001u)    /* DMA channel 2 transfer select 2:  Timer0_A (TA0CCR2.IFG) */
#define DMA2TSEL__TA1CCR0      (3*0x0001u)    /* DMA channel 2 transfer select 3:  Timer1_A (TA1CCR0.IFG) */
#define DMA2TSEL__TA1CCR2      (4*0x0001u)    /* DMA channel 2 transfer select 4:  Timer1_A (TA1CCR2.IFG) */
#define DMA2TSEL__TB0CCR0      (5*0x0001u)    /* DMA channel 2 transfer select 5:  TimerB (TB0CCR0.IFG) */
#define DMA2TSEL__TB0CCR2      (6*0x0001u)    /* DMA channel 2 transfer select 6:  TimerB (TB0CCR2.IFG) */
#define DMA2TSEL__RES7         (7*0x0001u)    /* DMA channel 2 transfer select 7:  Reserved */
#define DMA2TSEL__RES8         (8*0x0001u)    /* DMA channel 2 transfer select 8:  Reserved */
#define DMA2TSEL__RES9         (9*0x0001u)    /* DMA channel 2 transfer select 9:  Reserved */
#define DMA2TSEL__RES10        (10*0x0001u)   /* DMA channel 2 transfer select 10: Reserved */
#define DMA2TSEL__RES11        (11*0x0001u)   /* DMA channel 2 transfer select 11: Reserved */
#define DMA2TSEL__RES12        (12*0x0001u)   /* DMA channel 2 transfer select 12: Reserved */
#define DMA2TSEL__RES13        (13*0x0001u)   /* DMA channel 2 transfer select 13: Reserved */
#define DMA2TSEL__RFRXIFG      (14*0x0001u)   /* DMA channel 2 transfer select 14: RFRXIFG */
#define DMA2TSEL__RFTXIFG      (15*0x0001u)   /* DMA channel 2 transfer select 15: RFTXIFG */
#define DMA2TSEL__USCIA0RX     (16*0x0001u)   /* DMA channel 2 transfer select 16: USCIA0 receive */
#define DMA2TSEL__USCIA0TX     (17*0x0001u)   /* DMA channel 2 transfer select 17: USCIA0 transmit */
#define DMA2TSEL__USCIB0RX     (18*0x0001u)   /* DMA channel 2 transfer select 18: USCIB0 receive */
#define DMA2TSEL__USCIB0TX     (19*0x0001u)   /* DMA channel 2 transfer select 19: USCIB0 transmit */
#define DMA2TSEL__RES20        (20*0x0001u)   /* DMA channel 2 transfer select 20: Reserved  */
#define DMA2TSEL__RES21        (21*0x0001u)   /* DMA channel 2 transfer select 21: Reserved  */
#define DMA2TSEL__RES22        (22*0x0001u)   /* DMA channel 2 transfer select 22: Reserved  */
#define DMA2TSEL__RES23        (23*0x0001u)   /* DMA channel 2 transfer select 23: Reserved  */
#define DMA2TSEL__ADC12IFG     (24*0x0001u)   /* DMA channel 2 transfer select 24: ADC12IFGx */
#define DMA2TSEL__RES25        (25*0x0001u)   /* DMA channel 2 transfer select 25: Reserved */
#define DMA2TSEL__RES26        (26*0x0001u)   /* DMA channel 2 transfer select 26: Reserved */
#define DMA2TSEL__RES27        (27*0x0001u)   /* DMA channel 2 transfer select 27: Reserved */
#define DMA2TSEL__RES28        (28*0x0001u)   /* DMA channel 2 transfer select 28: Reserved */
#define DMA2TSEL__MPY          (29*0x0001u)   /* DMA channel 2 transfer select 29: Multiplier ready */
#define DMA2TSEL__DMA1IFG      (30*0x0001u)   /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL__DMAE0        (31*0x0001u)   /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FLASH__ 0x0140
#define FLASH_BASE             __MSP430_BASEADDRESS_FLASH__

SFR_16BIT(FCTL1);                             /* FLASH Control 1 */
SFR_8BIT(FCTL1_L);                            /* FLASH Control 1 */
SFR_8BIT(FCTL1_H);                            /* FLASH Control 1 */
//sfrbw    FCTL2                  (0x0142)  /* FLASH Control 2 */
SFR_16BIT(FCTL3);                             /* FLASH Control 3 */
SFR_8BIT(FCTL3_L);                            /* FLASH Control 3 */
SFR_8BIT(FCTL3_H);                            /* FLASH Control 3 */
SFR_16BIT(FCTL4);                             /* FLASH Control 4 */
SFR_8BIT(FCTL4_L);                            /* FLASH Control 4 */
SFR_8BIT(FCTL4_H);                            /* FLASH Control 4 */

#define FRPW                   (0x9600)       /* Flash password returned by read */
#define FWPW                   (0xA500)       /* Flash password for write */
#define FXPW                   (0x3300)       /* for use with XOR instruction */
#define FRKEY                  (0x9600)       /* (legacy definition) Flash key returned by read */
#define FWKEY                  (0xA500)       /* (legacy definition) Flash key for write */
#define FXKEY                  (0x3300)       /* (legacy definition) for use with XOR instruction */

/* FCTL1 Control Bits */
//#define RESERVED            (0x0001)  /* Reserved */
#define ERASE                  (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS                  (0x0004)       /* Enable bit for Flash mass erase */
//#define RESERVED            (0x0008)  /* Reserved */
//#define RESERVED            (0x0010)  /* Reserved */
#define SWRT                   (0x0020)       /* Smart Write enable */
#define WRT                    (0x0040)       /* Enable bit for Flash write */
#define BLKWRT                 (0x0080)       /* Enable bit for Flash segment write */

/* FCTL1 Control Bits */
//#define RESERVED            (0x0001)  /* Reserved */
#define ERASE_L                (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS_L                (0x0004)       /* Enable bit for Flash mass erase */
//#define RESERVED            (0x0008)  /* Reserved */
//#define RESERVED            (0x0010)  /* Reserved */
#define SWRT_L                 (0x0020)       /* Smart Write enable */
#define WRT_L                  (0x0040)       /* Enable bit for Flash write */
#define BLKWRT_L               (0x0080)       /* Enable bit for Flash segment write */

/* FCTL3 Control Bits */
#define BUSY                   (0x0001)       /* Flash busy: 1 */
#define KEYV                   (0x0002)       /* Flash Key violation flag */
#define ACCVIFG                (0x0004)       /* Flash Access violation flag */
#define WAIT                   (0x0008)       /* Wait flag for segment write */
#define LOCK                   (0x0010)       /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX                   (0x0020)       /* Flash Emergency Exit */
#define LOCKA                  (0x0040)       /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
//#define RESERVED            (0x0080)  /* Reserved */

/* FCTL3 Control Bits */
#define BUSY_L                 (0x0001)       /* Flash busy: 1 */
#define KEYV_L                 (0x0002)       /* Flash Key violation flag */
#define ACCVIFG_L              (0x0004)       /* Flash Access violation flag */
#define WAIT_L                 (0x0008)       /* Wait flag for segment write */
#define LOCK_L                 (0x0010)       /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX_L                 (0x0020)       /* Flash Emergency Exit */
#define LOCKA_L                (0x0040)       /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
//#define RESERVED            (0x0080)  /* Reserved */

/* FCTL4 Control Bits */
#define VPE                    (0x0001)       /* Voltage Changed during Program Error Flag */
#define MGR0                   (0x0010)       /* Marginal read 0 mode. */
#define MGR1                   (0x0020)       /* Marginal read 1 mode. */
#define LOCKINFO               (0x0080)       /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */

/* FCTL4 Control Bits */
#define VPE_L                  (0x0001)       /* Voltage Changed during Program Error Flag */
#define MGR0_L                 (0x0010)       /* Marginal read 0 mode. */
#define MGR1_L                 (0x0020)       /* Marginal read 1 mode. */
#define LOCKINFO_L             (0x0080)       /* Lock INFO Memory bit: read = 1 - Segment is locked (read only) */

/************************************************************
* LCD_B
************************************************************/
#define __MSP430_HAS_LCD_B__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_LCD_B__ 0x0A00
#define LCD_B_BASE             __MSP430_BASEADDRESS_LCD_B__

SFR_16BIT(LCDBCTL0);                          /* LCD_B Control Register 0 */
SFR_8BIT(LCDBCTL0_L);                         /* LCD_B Control Register 0 */
SFR_8BIT(LCDBCTL0_H);                         /* LCD_B Control Register 0 */
SFR_16BIT(LCDBCTL1);                          /* LCD_B Control Register 1 */
SFR_8BIT(LCDBCTL1_L);                         /* LCD_B Control Register 1 */
SFR_8BIT(LCDBCTL1_H);                         /* LCD_B Control Register 1 */
SFR_16BIT(LCDBBLKCTL);                        /* LCD_B blinking control register */
SFR_8BIT(LCDBBLKCTL_L);                       /* LCD_B blinking control register */
SFR_8BIT(LCDBBLKCTL_H);                       /* LCD_B blinking control register */
SFR_16BIT(LCDBMEMCTL);                        /* LCD_B memory control register */
SFR_8BIT(LCDBMEMCTL_L);                       /* LCD_B memory control register */
SFR_8BIT(LCDBMEMCTL_H);                       /* LCD_B memory control register */
SFR_16BIT(LCDBVCTL);                          /* LCD_B Voltage Control Register */
SFR_8BIT(LCDBVCTL_L);                         /* LCD_B Voltage Control Register */
SFR_8BIT(LCDBVCTL_H);                         /* LCD_B Voltage Control Register */
SFR_16BIT(LCDBPCTL0);                         /* LCD_B Port Control Register 0 */
SFR_8BIT(LCDBPCTL0_L);                        /* LCD_B Port Control Register 0 */
SFR_8BIT(LCDBPCTL0_H);                        /* LCD_B Port Control Register 0 */
SFR_16BIT(LCDBPCTL1);                         /* LCD_B Port Control Register 1 */
SFR_8BIT(LCDBPCTL1_L);                        /* LCD_B Port Control Register 1 */
SFR_8BIT(LCDBPCTL1_H);                        /* LCD_B Port Control Register 1 */
SFR_16BIT(LCDBPCTL2);                         /* LCD_B Port Control Register 2 */
SFR_8BIT(LCDBPCTL2_L);                        /* LCD_B Port Control Register 2 */
SFR_8BIT(LCDBPCTL2_H);                        /* LCD_B Port Control Register 2 */
SFR_16BIT(LCDBPCTL3);                         /* LCD_B Port Control Register 3 */
SFR_8BIT(LCDBPCTL3_L);                        /* LCD_B Port Control Register 3 */
SFR_8BIT(LCDBPCTL3_H);                        /* LCD_B Port Control Register 3 */
SFR_16BIT(LCDBCPCTL);                         /* LCD_B Charge Pump Control Register 3 */
SFR_8BIT(LCDBCPCTL_L);                        /* LCD_B Charge Pump Control Register 3 */
SFR_8BIT(LCDBCPCTL_H);                        /* LCD_B Charge Pump Control Register 3 */
SFR_16BIT(LCDBIV);                            /* LCD_B Interrupt Vector Register */

// LCDBCTL0
#define LCDON                  (0x0001)       /* LCD_B LCD On */
#define LCDSON                 (0x0004)       /* LCD_B LCD Segments On */
#define LCDMX0                 (0x0008)       /* LCD_B Mux Rate Bit: 0 */
#define LCDMX1                 (0x0010)       /* LCD_B Mux Rate Bit: 1 */
//#define RESERVED            (0x0020)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040)  /* LCD_B RESERVED */
#define LCDSSEL                (0x0080)       /* LCD_B Clock Select */
#define LCDPRE0                (0x0100)       /* LCD_B LCD frequency pre-scaler Bit: 0 */
#define LCDPRE1                (0x0200)       /* LCD_B LCD frequency pre-scaler Bit: 1 */
#define LCDPRE2                (0x0400)       /* LCD_B LCD frequency pre-scaler Bit: 2 */
#define LCDDIV0                (0x0800)       /* LCD_B LCD frequency divider Bit: 0 */
#define LCDDIV1                (0x1000)       /* LCD_B LCD frequency divider Bit: 1 */
#define LCDDIV2                (0x2000)       /* LCD_B LCD frequency divider Bit: 2 */
#define LCDDIV3                (0x4000)       /* LCD_B LCD frequency divider Bit: 3 */
#define LCDDIV4                (0x8000)       /* LCD_B LCD frequency divider Bit: 4 */

// LCDBCTL0
#define LCDON_L                (0x0001)       /* LCD_B LCD On */
#define LCDSON_L               (0x0004)       /* LCD_B LCD Segments On */
#define LCDMX0_L               (0x0008)       /* LCD_B Mux Rate Bit: 0 */
#define LCDMX1_L               (0x0010)       /* LCD_B Mux Rate Bit: 1 */
//#define RESERVED            (0x0020)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040)  /* LCD_B RESERVED */
#define LCDSSEL_L              (0x0080)       /* LCD_B Clock Select */

// LCDBCTL0
//#define RESERVED            (0x0020)  /* LCD_B RESERVED */
//#define RESERVED            (0x0040)  /* LCD_B RESERVED */
#define LCDPRE0_H              (0x0001)       /* LCD_B LCD frequency pre-scaler Bit: 0 */
#define LCDPRE1_H              (0x0002)       /* LCD_B LCD frequency pre-scaler Bit: 1 */
#define LCDPRE2_H              (0x0004)       /* LCD_B LCD frequency pre-scaler Bit: 2 */
#define LCDDIV0_H              (0x0008)       /* LCD_B LCD frequency divider Bit: 0 */
#define LCDDIV1_H              (0x0010)       /* LCD_B LCD frequency divider Bit: 1 */
#define LCDDIV2_H              (0x0020)       /* LCD_B LCD frequency divider Bit: 2 */
#define LCDDIV3_H              (0x0040)       /* LCD_B LCD frequency divider Bit: 3 */
#define LCDDIV4_H              (0x0080)       /* LCD_B LCD frequency divider Bit: 4 */

#define LCDPRE_0               (0x0000)       /* LCD_B LCD frequency pre-scaler: /1 */
#define LCDPRE_1               (0x0100)       /* LCD_B LCD frequency pre-scaler: /2 */
#define LCDPRE_2               (0x0200)       /* LCD_B LCD frequency pre-scaler: /4 */
#define LCDPRE_3               (0x0300)       /* LCD_B LCD frequency pre-scaler: /8 */
#define LCDPRE_4               (0x0400)       /* LCD_B LCD frequency pre-scaler: /16 */
#define LCDPRE_5               (0x0500)       /* LCD_B LCD frequency pre-scaler: /32 */
#define LCDPRE__1              (0x0000)       /* LCD_B LCD frequency pre-scaler: /1 */
#define LCDPRE__2              (0x0100)       /* LCD_B LCD frequency pre-scaler: /2 */
#define LCDPRE__4              (0x0200)       /* LCD_B LCD frequency pre-scaler: /4 */
#define LCDPRE__8              (0x0300)       /* LCD_B LCD frequency pre-scaler: /8 */
#define LCDPRE__16             (0x0400)       /* LCD_B LCD frequency pre-scaler: /16 */
#define LCDPRE__32             (0x0500)       /* LCD_B LCD frequency pre-scaler: /32 */

#define LCDDIV_0               (0x0000)       /* LCD_B LCD frequency divider: /1 */
#define LCDDIV_1               (0x0800)       /* LCD_B LCD frequency divider: /2 */
#define LCDDIV_2               (0x1000)       /* LCD_B LCD frequency divider: /3 */
#define LCDDIV_3               (0x1800)       /* LCD_B LCD frequency divider: /4 */
#define LCDDIV_4               (0x2000)       /* LCD_B LCD frequency divider: /5 */
#define LCDDIV_5               (0x2800)       /* LCD_B LCD frequency divider: /6 */
#define LCDDIV_6               (0x3000)       /* LCD_B LCD frequency divider: /7 */
#define LCDDIV_7               (0x3800)       /* LCD_B LCD frequency divider: /8 */
#define LCDDIV_8               (0x4000)       /* LCD_B LCD frequency divider: /9 */
#define LCDDIV_9               (0x4800)       /* LCD_B LCD frequency divider: /10 */
#define LCDDIV_10              (0x5000)       /* LCD_B LCD frequency divider: /11 */
#define LCDDIV_11              (0x5800)       /* LCD_B LCD frequency divider: /12 */
#define LCDDIV_12              (0x6000)       /* LCD_B LCD frequency divider: /13 */
#define LCDDIV_13              (0x6800)       /* LCD_B LCD frequency divider: /14 */
#define LCDDIV_14              (0x7000)       /* LCD_B LCD frequency divider: /15 */
#define LCDDIV_15              (0x7800)       /* LCD_B LCD frequency divider: /16 */
#define LCDDIV_16              (0x8000)       /* LCD_B LCD frequency divider: /17 */
#define LCDDIV_17              (0x8800)       /* LCD_B LCD frequency divider: /18 */
#define LCDDIV_18              (0x9000)       /* LCD_B LCD frequency divider: /19 */
#define LCDDIV_19              (0x9800)       /* LCD_B LCD frequency divider: /20 */
#define LCDDIV_20              (0xA000)       /* LCD_B LCD frequency divider: /21 */
#define LCDDIV_21              (0xA800)       /* LCD_B LCD frequency divider: /22 */
#define LCDDIV_22              (0xB000)       /* LCD_B LCD frequency divider: /23 */
#define LCDDIV_23              (0xB800)       /* LCD_B LCD frequency divider: /24 */
#define LCDDIV_24              (0xC000)       /* LCD_B LCD frequency divider: /25 */
#define LCDDIV_25              (0xC800)       /* LCD_B LCD frequency divider: /26 */
#define LCDDIV_26              (0xD000)       /* LCD_B LCD frequency divider: /27 */
#define LCDDIV_27              (0xD800)       /* LCD_B LCD frequency divider: /28 */
#define LCDDIV_28              (0xE000)       /* LCD_B LCD frequency divider: /29 */
#define LCDDIV_29              (0xE800)       /* LCD_B LCD frequency divider: /30 */
#define LCDDIV_30              (0xF000)       /* LCD_B LCD frequency divider: /31 */
#define LCDDIV_31              (0xF800)       /* LCD_B LCD frequency divider: /32 */
#define LCDDIV__1              (0x0000)       /* LCD_B LCD frequency divider: /1 */
#define LCDDIV__2              (0x0800)       /* LCD_B LCD frequency divider: /2 */
#define LCDDIV__3              (0x1000)       /* LCD_B LCD frequency divider: /3 */
#define LCDDIV__4              (0x1800)       /* LCD_B LCD frequency divider: /4 */
#define LCDDIV__5              (0x2000)       /* LCD_B LCD frequency divider: /5 */
#define LCDDIV__6              (0x2800)       /* LCD_B LCD frequency divider: /6 */
#define LCDDIV__7              (0x3000)       /* LCD_B LCD frequency divider: /7 */
#define LCDDIV__8              (0x3800)       /* LCD_B LCD frequency divider: /8 */
#define LCDDIV__9              (0x4000)       /* LCD_B LCD frequency divider: /9 */
#define LCDDIV__10             (0x4800)       /* LCD_B LCD frequency divider: /10 */
#define LCDDIV__11             (0x5000)       /* LCD_B LCD frequency divider: /11 */
#define LCDDIV__12             (0x5800)       /* LCD_B LCD frequency divider: /12 */
#define LCDDIV__13             (0x6000)       /* LCD_B LCD frequency divider: /13 */
#define LCDDIV__14             (0x6800)       /* LCD_B LCD frequency divider: /14 */
#define LCDDIV__15             (0x7000)       /* LCD_B LCD frequency divider: /15 */
#define LCDDIV__16             (0x7800)       /* LCD_B LCD frequency divider: /16 */
#define LCDDIV__17             (0x8000)       /* LCD_B LCD frequency divider: /17 */
#define LCDDIV__18             (0x8800)       /* LCD_B LCD frequency divider: /18 */
#define LCDDIV__19             (0x9000)       /* LCD_B LCD frequency divider: /19 */
#define LCDDIV__20             (0x9800)       /* LCD_B LCD frequency divider: /20 */
#define LCDDIV__21             (0xA000)       /* LCD_B LCD frequency divider: /21 */
#define LCDDIV__22             (0xA800)       /* LCD_B LCD frequency divider: /22 */
#define LCDDIV__23             (0xB000)       /* LCD_B LCD frequency divider: /23 */
#define LCDDIV__24             (0xB800)       /* LCD_B LCD frequency divider: /24 */
#define LCDDIV__25             (0xC000)       /* LCD_B LCD frequency divider: /25 */
#define LCDDIV__26             (0xC800)       /* LCD_B LCD frequency divider: /26 */
#define LCDDIV__27             (0xD000)       /* LCD_B LCD frequency divider: /27 */
#define LCDDIV__28             (0xD800)       /* LCD_B LCD frequency divider: /28 */
#define LCDDIV__29             (0xE000)       /* LCD_B LCD frequency divider: /29 */
#define LCDDIV__30             (0xE800)       /* LCD_B LCD frequency divider: /30 */
#define LCDDIV__31             (0xF000)       /* LCD_B LCD frequency divider: /31 */
#define LCDDIV__32             (0xF800)       /* LCD_B LCD frequency divider: /32 */

/* Display modes coded with Bits 2-4 */
#define LCDSTATIC              (LCDSON)
#define LCD2MUX                (LCDMX0+LCDSON)
#define LCD3MUX                (LCDMX1+LCDSON)
#define LCD4MUX                (LCDMX1+LCDMX0+LCDSON)

// LCDBCTL1
#define LCDFRMIFG              (0x0001)       /* LCD_B LCD frame interrupt flag */
#define LCDBLKOFFIFG           (0x0002)       /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIFG            (0x0004)       /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIFG            (0x0008)       /* LCD_B No cpacitance connected interrupt flag */
#define LCDFRMIE               (0x0100)       /* LCD_B LCD frame interrupt enable */
#define LCDBLKOFFIE            (0x0200)       /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIE             (0x0400)       /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIE             (0x0800)       /* LCD_B No cpacitance connected interrupt enable */

// LCDBCTL1
#define LCDFRMIFG_L            (0x0001)       /* LCD_B LCD frame interrupt flag */
#define LCDBLKOFFIFG_L         (0x0002)       /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIFG_L          (0x0004)       /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIFG_L          (0x0008)       /* LCD_B No cpacitance connected interrupt flag */

// LCDBCTL1
#define LCDFRMIE_H             (0x0001)       /* LCD_B LCD frame interrupt enable */
#define LCDBLKOFFIE_H          (0x0002)       /* LCD_B LCD blinking off interrupt flag, */
#define LCDBLKONIE_H           (0x0004)       /* LCD_B LCD blinking on interrupt flag, */
#define LCDNOCAPIE_H           (0x0008)       /* LCD_B No cpacitance connected interrupt enable */

// LCDBBLKCTL
#define LCDBLKMOD0             (0x0001)       /* LCD_B Blinking mode Bit: 0 */
#define LCDBLKMOD1             (0x0002)       /* LCD_B Blinking mode Bit: 1 */
#define LCDBLKPRE0             (0x0004)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 0 */
#define LCDBLKPRE1             (0x0008)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 1 */
#define LCDBLKPRE2             (0x0010)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 2 */
#define LCDBLKDIV0             (0x0020)       /* LCD_B Clock divider for blinking frequency Bit: 0 */
#define LCDBLKDIV1             (0x0040)       /* LCD_B Clock divider for blinking frequency Bit: 1 */
#define LCDBLKDIV2             (0x0080)       /* LCD_B Clock divider for blinking frequency Bit: 2 */

// LCDBBLKCTL
#define LCDBLKMOD0_L           (0x0001)       /* LCD_B Blinking mode Bit: 0 */
#define LCDBLKMOD1_L           (0x0002)       /* LCD_B Blinking mode Bit: 1 */
#define LCDBLKPRE0_L           (0x0004)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 0 */
#define LCDBLKPRE1_L           (0x0008)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 1 */
#define LCDBLKPRE2_L           (0x0010)       /* LCD_B Clock pre-scaler for blinking frequency Bit: 2 */
#define LCDBLKDIV0_L           (0x0020)       /* LCD_B Clock divider for blinking frequency Bit: 0 */
#define LCDBLKDIV1_L           (0x0040)       /* LCD_B Clock divider for blinking frequency Bit: 1 */
#define LCDBLKDIV2_L           (0x0080)       /* LCD_B Clock divider for blinking frequency Bit: 2 */

#define LCDBLKMOD_0            (0x0000)       /* LCD_B Blinking mode: Off */
#define LCDBLKMOD_1            (0x0001)       /* LCD_B Blinking mode: Individual */
#define LCDBLKMOD_2            (0x0002)       /* LCD_B Blinking mode: All */
#define LCDBLKMOD_3            (0x0003)       /* LCD_B Blinking mode: Switching */

#define LCDBLKPRE_0            (0x0000)       /* LCD_B Clock pre-scaler for blinking frequency: 0 */
#define LCDBLKPRE_1            (0x0004)       /* LCD_B Clock pre-scaler for blinking frequency: 1 */
#define LCDBLKPRE_2            (0x0008)       /* LCD_B Clock pre-scaler for blinking frequency: 2 */
#define LCDBLKPRE_3            (0x000C)       /* LCD_B Clock pre-scaler for blinking frequency: 3 */
#define LCDBLKPRE_4            (0x0010)       /* LCD_B Clock pre-scaler for blinking frequency: 4 */
#define LCDBLKPRE_5            (0x0014)       /* LCD_B Clock pre-scaler for blinking frequency: 5 */
#define LCDBLKPRE_6            (0x0018)       /* LCD_B Clock pre-scaler for blinking frequency: 6 */
#define LCDBLKPRE_7            (0x001C)       /* LCD_B Clock pre-scaler for blinking frequency: 7 */

#define LCDBLKPRE__512         (0x0000)       /* LCD_B Clock pre-scaler for blinking frequency: 512   */
#define LCDBLKPRE__1024        (0x0004)       /* LCD_B Clock pre-scaler for blinking frequency: 1024  */
#define LCDBLKPRE__2048        (0x0008)       /* LCD_B Clock pre-scaler for blinking frequency: 2048  */
#define LCDBLKPRE__4096        (0x000C)       /* LCD_B Clock pre-scaler for blinking frequency: 4096  */
#define LCDBLKPRE__8192        (0x0010)       /* LCD_B Clock pre-scaler for blinking frequency: 8192  */
#define LCDBLKPRE__16384       (0x0014)       /* LCD_B Clock pre-scaler for blinking frequency: 16384 */
#define LCDBLKPRE__32768       (0x0018)       /* LCD_B Clock pre-scaler for blinking frequency: 32768 */
#define LCDBLKPRE__65536       (0x001C)       /* LCD_B Clock pre-scaler for blinking frequency: 65536 */

#define LCDBLKDIV_0            (0x0000)       /* LCD_B Clock divider for blinking frequency: 0 */
#define LCDBLKDIV_1            (0x0020)       /* LCD_B Clock divider for blinking frequency: 1 */
#define LCDBLKDIV_2            (0x0040)       /* LCD_B Clock divider for blinking frequency: 2 */
#define LCDBLKDIV_3            (0x0060)       /* LCD_B Clock divider for blinking frequency: 3 */
#define LCDBLKDIV_4            (0x0080)       /* LCD_B Clock divider for blinking frequency: 4 */
#define LCDBLKDIV_5            (0x00A0)       /* LCD_B Clock divider for blinking frequency: 5 */
#define LCDBLKDIV_6            (0x00C0)       /* LCD_B Clock divider for blinking frequency: 6 */
#define LCDBLKDIV_7            (0x00E0)       /* LCD_B Clock divider for blinking frequency: 7 */

#define LCDBLKDIV__1           (0x0000)       /* LCD_B Clock divider for blinking frequency: /1 */
#define LCDBLKDIV__2           (0x0020)       /* LCD_B Clock divider for blinking frequency: /2 */
#define LCDBLKDIV__3           (0x0040)       /* LCD_B Clock divider for blinking frequency: /3 */
#define LCDBLKDIV__4           (0x0060)       /* LCD_B Clock divider for blinking frequency: /4 */
#define LCDBLKDIV__5           (0x0080)       /* LCD_B Clock divider for blinking frequency: /5 */
#define LCDBLKDIV__6           (0x00A0)       /* LCD_B Clock divider for blinking frequency: /6 */
#define LCDBLKDIV__7           (0x00C0)       /* LCD_B Clock divider for blinking frequency: /7 */
#define LCDBLKDIV__8           (0x00E0)       /* LCD_B Clock divider for blinking frequency: /8 */

// LCDBMEMCTL
#define LCDDISP                (0x0001)       /* LCD_B LCD memory registers for display */
#define LCDCLRM                (0x0002)       /* LCD_B Clear LCD memory */
#define LCDCLRBM               (0x0004)       /* LCD_B Clear LCD blinking memory */

// LCDBMEMCTL
#define LCDDISP_L              (0x0001)       /* LCD_B LCD memory registers for display */
#define LCDCLRM_L              (0x0002)       /* LCD_B Clear LCD memory */
#define LCDCLRBM_L             (0x0004)       /* LCD_B Clear LCD blinking memory */

// LCDBVCTL
#define LCD2B                  (0x0001)       /* Selects 1/2 bias. */
#define VLCDREF0               (0x0002)       /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1               (0x0004)       /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN                (0x0008)       /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT                (0x0010)       /* Select external source for VLCD. */
#define LCDEXTBIAS             (0x0020)       /* V2 - V4 voltage select. */
#define R03EXT                 (0x0040)       /* Selects external connections for LCD mid voltages. */
#define LCDREXT                (0x0080)       /* Selects external connection for lowest LCD voltage. */
#define VLCD0                  (0x0200)       /* VLCD select: 0 */
#define VLCD1                  (0x0400)       /* VLCD select: 1 */
#define VLCD2                  (0x0800)       /* VLCD select: 2 */
#define VLCD3                  (0x1000)       /* VLCD select: 3 */

// LCDBVCTL
#define LCD2B_L                (0x0001)       /* Selects 1/2 bias. */
#define VLCDREF0_L             (0x0002)       /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1_L             (0x0004)       /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN_L              (0x0008)       /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT_L              (0x0010)       /* Select external source for VLCD. */
#define LCDEXTBIAS_L           (0x0020)       /* V2 - V4 voltage select. */
#define R03EXT_L               (0x0040)       /* Selects external connections for LCD mid voltages. */
#define LCDREXT_L              (0x0080)       /* Selects external connection for lowest LCD voltage. */

// LCDBVCTL
#define VLCD0_H                (0x0002)       /* VLCD select: 0 */
#define VLCD1_H                (0x0004)       /* VLCD select: 1 */
#define VLCD2_H                (0x0008)       /* VLCD select: 2 */
#define VLCD3_H                (0x0010)       /* VLCD select: 3 */

/* Reference voltage source select for the regulated charge pump */
#define VLCDREF_0              (0<<1)         /* Internal */
#define VLCDREF_1              (1<<1)         /* External */
#define VLCDREF_2              (2<<1)         /* Reserved */
#define VLCDREF_3              (3<<1)         /* Reserved */

/* Charge pump voltage selections */
#define VLCD_0                 (0<<9)         /* Charge pump disabled */
#define VLCD_1                 (1<<9)         /* VLCD = 2.60V */
#define VLCD_2                 (2<<9)         /* VLCD = 2.66V */
#define VLCD_3                 (3<<9)         /* VLCD = 2.72V */
#define VLCD_4                 (4<<9)         /* VLCD = 2.78V */
#define VLCD_5                 (5<<9)         /* VLCD = 2.84V */
#define VLCD_6                 (6<<9)         /* VLCD = 2.90V */
#define VLCD_7                 (7<<9)         /* VLCD = 2.96V */
#define VLCD_8                 (8<<9)         /* VLCD = 3.02V */
#define VLCD_9                 (9<<9)         /* VLCD = 3.08V */
#define VLCD_10                (10<<9)        /* VLCD = 3.14V */
#define VLCD_11                (11<<9)        /* VLCD = 3.20V */
#define VLCD_12                (12<<9)        /* VLCD = 3.26V */
#define VLCD_13                (13<<9)        /* VLCD = 3.32V */
#define VLCD_14                (14<<9)        /* VLCD = 3.38V */
#define VLCD_15                (15<<9)        /* VLCD = 3.44V */

#define VLCD_DISABLED          (0<<9)         /* Charge pump disabled */
#define VLCD_2_60              (1<<9)         /* VLCD = 2.60V */
#define VLCD_2_66              (2<<9)         /* VLCD = 2.66V */
#define VLCD_2_72              (3<<9)         /* VLCD = 2.72V */
#define VLCD_2_78              (4<<9)         /* VLCD = 2.78V */
#define VLCD_2_84              (5<<9)         /* VLCD = 2.84V */
#define VLCD_2_90              (6<<9)         /* VLCD = 2.90V */
#define VLCD_2_96              (7<<9)         /* VLCD = 2.96V */
#define VLCD_3_02              (8<<9)         /* VLCD = 3.02V */
#define VLCD_3_08              (9<<9)         /* VLCD = 3.08V */
#define VLCD_3_14              (10<<9)        /* VLCD = 3.14V */
#define VLCD_3_20              (11<<9)        /* VLCD = 3.20V */
#define VLCD_3_26              (12<<9)        /* VLCD = 3.26V */
#define VLCD_3_32              (13<<9)        /* VLCD = 3.32V */
#define VLCD_3_38              (14<<9)        /* VLCD = 3.38V */
#define VLCD_3_44              (15<<9)        /* VLCD = 3.44V */

// LCDBPCTL0
#define LCDS0                  (0x0001)       /* LCD Segment  0 enable. */
#define LCDS1                  (0x0002)       /* LCD Segment  1 enable. */
#define LCDS2                  (0x0004)       /* LCD Segment  2 enable. */
#define LCDS3                  (0x0008)       /* LCD Segment  3 enable. */
#define LCDS4                  (0x0010)       /* LCD Segment  4 enable. */
#define LCDS5                  (0x0020)       /* LCD Segment  5 enable. */
#define LCDS6                  (0x0040)       /* LCD Segment  6 enable. */
#define LCDS7                  (0x0080)       /* LCD Segment  7 enable. */
#define LCDS8                  (0x0100)       /* LCD Segment  8 enable. */
#define LCDS9                  (0x0200)       /* LCD Segment  9 enable. */
#define LCDS10                 (0x0400)       /* LCD Segment 10 enable. */
#define LCDS11                 (0x0800)       /* LCD Segment 11 enable. */
#define LCDS12                 (0x1000)       /* LCD Segment 12 enable. */
#define LCDS13                 (0x2000)       /* LCD Segment 13 enable. */
#define LCDS14                 (0x4000)       /* LCD Segment 14 enable. */
#define LCDS15                 (0x8000)       /* LCD Segment 15 enable. */

// LCDBPCTL0
#define LCDS0_L                (0x0001)       /* LCD Segment  0 enable. */
#define LCDS1_L                (0x0002)       /* LCD Segment  1 enable. */
#define LCDS2_L                (0x0004)       /* LCD Segment  2 enable. */
#define LCDS3_L                (0x0008)       /* LCD Segment  3 enable. */
#define LCDS4_L                (0x0010)       /* LCD Segment  4 enable. */
#define LCDS5_L                (0x0020)       /* LCD Segment  5 enable. */
#define LCDS6_L                (0x0040)       /* LCD Segment  6 enable. */
#define LCDS7_L                (0x0080)       /* LCD Segment  7 enable. */

// LCDBPCTL0
#define LCDS8_H                (0x0001)       /* LCD Segment  8 enable. */
#define LCDS9_H                (0x0002)       /* LCD Segment  9 enable. */
#define LCDS10_H               (0x0004)       /* LCD Segment 10 enable. */
#define LCDS11_H               (0x0008)       /* LCD Segment 11 enable. */
#define LCDS12_H               (0x0010)       /* LCD Segment 12 enable. */
#define LCDS13_H               (0x0020)       /* LCD Segment 13 enable. */
#define LCDS14_H               (0x0040)       /* LCD Segment 14 enable. */
#define LCDS15_H               (0x0080)       /* LCD Segment 15 enable. */

// LCDBPCTL1
#define LCDS16                 (0x0001)       /* LCD Segment 16 enable. */
#define LCDS17                 (0x0002)       /* LCD Segment 17 enable. */
#define LCDS18                 (0x0004)       /* LCD Segment 18 enable. */
#define LCDS19                 (0x0008)       /* LCD Segment 19 enable. */
#define LCDS20                 (0x0010)       /* LCD Segment 20 enable. */
#define LCDS21                 (0x0020)       /* LCD Segment 21 enable. */
#define LCDS22                 (0x0040)       /* LCD Segment 22 enable. */
#define LCDS23                 (0x0080)       /* LCD Segment 23 enable. */
#define LCDS24                 (0x0100)       /* LCD Segment 24 enable. */
#define LCDS25                 (0x0200)       /* LCD Segment 25 enable. */
#define LCDS26                 (0x0400)       /* LCD Segment 26 enable. */
#define LCDS27                 (0x0800)       /* LCD Segment 27 enable. */
#define LCDS28                 (0x1000)       /* LCD Segment 28 enable. */
#define LCDS29                 (0x2000)       /* LCD Segment 29 enable. */
#define LCDS30                 (0x4000)       /* LCD Segment 30 enable. */
#define LCDS31                 (0x8000)       /* LCD Segment 31 enable. */

// LCDBPCTL1
#define LCDS16_L               (0x0001)       /* LCD Segment 16 enable. */
#define LCDS17_L               (0x0002)       /* LCD Segment 17 enable. */
#define LCDS18_L               (0x0004)       /* LCD Segment 18 enable. */
#define LCDS19_L               (0x0008)       /* LCD Segment 19 enable. */
#define LCDS20_L               (0x0010)       /* LCD Segment 20 enable. */
#define LCDS21_L               (0x0020)       /* LCD Segment 21 enable. */
#define LCDS22_L               (0x0040)       /* LCD Segment 22 enable. */
#define LCDS23_L               (0x0080)       /* LCD Segment 23 enable. */

// LCDBPCTL1
#define LCDS24_H               (0x0001)       /* LCD Segment 24 enable. */
#define LCDS25_H               (0x0002)       /* LCD Segment 25 enable. */
#define LCDS26_H               (0x0004)       /* LCD Segment 26 enable. */
#define LCDS27_H               (0x0008)       /* LCD Segment 27 enable. */
#define LCDS28_H               (0x0010)       /* LCD Segment 28 enable. */
#define LCDS29_H               (0x0020)       /* LCD Segment 29 enable. */
#define LCDS30_H               (0x0040)       /* LCD Segment 30 enable. */
#define LCDS31_H               (0x0080)       /* LCD Segment 31 enable. */

// LCDBPCTL2
#define LCDS32                 (0x0001)       /* LCD Segment 32 enable. */
#define LCDS33                 (0x0002)       /* LCD Segment 33 enable. */
#define LCDS34                 (0x0004)       /* LCD Segment 34 enable. */
#define LCDS35                 (0x0008)       /* LCD Segment 35 enable. */
#define LCDS36                 (0x0010)       /* LCD Segment 36 enable. */
#define LCDS37                 (0x0020)       /* LCD Segment 37 enable. */
#define LCDS38                 (0x0040)       /* LCD Segment 38 enable. */
#define LCDS39                 (0x0080)       /* LCD Segment 39 enable. */
#define LCDS40                 (0x0100)       /* LCD Segment 40 enable. */
#define LCDS41                 (0x0200)       /* LCD Segment 41 enable. */
#define LCDS42                 (0x0400)       /* LCD Segment 42 enable. */
#define LCDS43                 (0x0800)       /* LCD Segment 43 enable. */
#define LCDS44                 (0x1000)       /* LCD Segment 44 enable. */
#define LCDS45                 (0x2000)       /* LCD Segment 45 enable. */
#define LCDS46                 (0x4000)       /* LCD Segment 46 enable. */
#define LCDS47                 (0x8000)       /* LCD Segment 47 enable. */

// LCDBPCTL2
#define LCDS32_L               (0x0001)       /* LCD Segment 32 enable. */
#define LCDS33_L               (0x0002)       /* LCD Segment 33 enable. */
#define LCDS34_L               (0x0004)       /* LCD Segment 34 enable. */
#define LCDS35_L               (0x0008)       /* LCD Segment 35 enable. */
#define LCDS36_L               (0x0010)       /* LCD Segment 36 enable. */
#define LCDS37_L               (0x0020)       /* LCD Segment 37 enable. */
#define LCDS38_L               (0x0040)       /* LCD Segment 38 enable. */
#define LCDS39_L               (0x0080)       /* LCD Segment 39 enable. */

// LCDBPCTL2
#define LCDS40_H               (0x0001)       /* LCD Segment 40 enable. */
#define LCDS41_H               (0x0002)       /* LCD Segment 41 enable. */
#define LCDS42_H               (0x0004)       /* LCD Segment 42 enable. */
#define LCDS43_H               (0x0008)       /* LCD Segment 43 enable. */
#define LCDS44_H               (0x0010)       /* LCD Segment 44 enable. */
#define LCDS45_H               (0x0020)       /* LCD Segment 45 enable. */
#define LCDS46_H               (0x0040)       /* LCD Segment 46 enable. */
#define LCDS47_H               (0x0080)       /* LCD Segment 47 enable. */

// LCDBPCTL3
#define LCDS48                 (0x0001)       /* LCD Segment 48 enable. */
#define LCDS49                 (0x0002)       /* LCD Segment 49 enable. */
#define LCDS50                 (0x0004)       /* LCD Segment 50 enable. */

// LCDBPCTL3
#define LCDS48_L               (0x0001)       /* LCD Segment 48 enable. */
#define LCDS49_L               (0x0002)       /* LCD Segment 49 enable. */
#define LCDS50_L               (0x0004)       /* LCD Segment 50 enable. */

// LCDBCPCTL
#define LCDCPDIS0              (0x0001)       /* LCD charge pump disable */
#define LCDCPDIS1              (0x0002)       /* LCD charge pump disable */
#define LCDCPDIS2              (0x0004)       /* LCD charge pump disable */
#define LCDCPDIS3              (0x0008)       /* LCD charge pump disable */
#define LCDCPDIS4              (0x0010)       /* LCD charge pump disable */
#define LCDCPDIS5              (0x0020)       /* LCD charge pump disable */
#define LCDCPDIS6              (0x0040)       /* LCD charge pump disable */
#define LCDCPDIS7              (0x0080)       /* LCD charge pump disable */
#define LCDCPCLKSYNC           (0x8000)       /* LCD charge pump clock synchronization */

// LCDBCPCTL
#define LCDCPDIS0_L            (0x0001)       /* LCD charge pump disable */
#define LCDCPDIS1_L            (0x0002)       /* LCD charge pump disable */
#define LCDCPDIS2_L            (0x0004)       /* LCD charge pump disable */
#define LCDCPDIS3_L            (0x0008)       /* LCD charge pump disable */
#define LCDCPDIS4_L            (0x0010)       /* LCD charge pump disable */
#define LCDCPDIS5_L            (0x0020)       /* LCD charge pump disable */
#define LCDCPDIS6_L            (0x0040)       /* LCD charge pump disable */
#define LCDCPDIS7_L            (0x0080)       /* LCD charge pump disable */

// LCDBCPCTL
#define LCDCPCLKSYNC_H         (0x0080)       /* LCD charge pump clock synchronization */

SFR_8BIT(LCDM1);                              /* LCD Memory 1 */
#define LCDMEM_                LCDM1          /* LCD Memory */
#ifdef __ASM_HEADER__
#define LCDMEM                 LCDM1          /* LCD Memory (for assembler) */
#else
#define LCDMEM                 ((char*)       &LCDM1) /* LCD Memory (for C) */
#endif
SFR_8BIT(LCDM2);                              /* LCD Memory 2 */
SFR_8BIT(LCDM3);                              /* LCD Memory 3 */
SFR_8BIT(LCDM4);                              /* LCD Memory 4 */
SFR_8BIT(LCDM5);                              /* LCD Memory 5 */
SFR_8BIT(LCDM6);                              /* LCD Memory 6 */
SFR_8BIT(LCDM7);                              /* LCD Memory 7 */
SFR_8BIT(LCDM8);                              /* LCD Memory 8 */
SFR_8BIT(LCDM9);                              /* LCD Memory 9 */
SFR_8BIT(LCDM10);                             /* LCD Memory 10 */
SFR_8BIT(LCDM11);                             /* LCD Memory 11 */
SFR_8BIT(LCDM12);                             /* LCD Memory 12 */
SFR_8BIT(LCDM13);                             /* LCD Memory 13 */
SFR_8BIT(LCDM14);                             /* LCD Memory 14 */
SFR_8BIT(LCDM15);                             /* LCD Memory 15 */
SFR_8BIT(LCDM16);                             /* LCD Memory 16 */
SFR_8BIT(LCDM17);                             /* LCD Memory 17 */
SFR_8BIT(LCDM18);                             /* LCD Memory 18 */
SFR_8BIT(LCDM19);                             /* LCD Memory 19 */
SFR_8BIT(LCDM20);                             /* LCD Memory 20 */
SFR_8BIT(LCDM21);                             /* LCD Memory 21 */
SFR_8BIT(LCDM22);                             /* LCD Memory 22 */
SFR_8BIT(LCDM23);                             /* LCD Memory 23 */
SFR_8BIT(LCDM24);                             /* LCD Memory 24 */

SFR_8BIT(LCDBM1);                             /* LCD Blinking Memory 1 */
#define LCDBMEM_               LCDBM1         /* LCD Blinking Memory */
#ifdef __ASM_HEADER__
#define LCDBMEM                (LCDBM1)       /* LCD Blinking Memory (for assembler) */
#else
#define LCDBMEM                ((char*)       &LCDBM1) /* LCD Blinking Memory (for C) */
#endif
SFR_8BIT(LCDBM2);                             /* LCD Blinking Memory 2 */
SFR_8BIT(LCDBM3);                             /* LCD Blinking Memory 3 */
SFR_8BIT(LCDBM4);                             /* LCD Blinking Memory 4 */
SFR_8BIT(LCDBM5);                             /* LCD Blinking Memory 5 */
SFR_8BIT(LCDBM6);                             /* LCD Blinking Memory 6 */
SFR_8BIT(LCDBM7);                             /* LCD Blinking Memory 7 */
SFR_8BIT(LCDBM8);                             /* LCD Blinking Memory 8 */
SFR_8BIT(LCDBM9);                             /* LCD Blinking Memory 9 */
SFR_8BIT(LCDBM10);                            /* LCD Blinking Memory 10 */
SFR_8BIT(LCDBM11);                            /* LCD Blinking Memory 11 */
SFR_8BIT(LCDBM12);                            /* LCD Blinking Memory 12 */
SFR_8BIT(LCDBM13);                            /* LCD Blinking Memory 13 */
SFR_8BIT(LCDBM14);                            /* LCD Blinking Memory 14 */
SFR_8BIT(LCDBM15);                            /* LCD Blinking Memory 15 */
SFR_8BIT(LCDBM16);                            /* LCD Blinking Memory 16 */
SFR_8BIT(LCDBM17);                            /* LCD Blinking Memory 17 */
SFR_8BIT(LCDBM18);                            /* LCD Blinking Memory 18 */
SFR_8BIT(LCDBM19);                            /* LCD Blinking Memory 19 */
SFR_8BIT(LCDBM20);                            /* LCD Blinking Memory 20 */
SFR_8BIT(LCDBM21);                            /* LCD Blinking Memory 21 */
SFR_8BIT(LCDBM22);                            /* LCD Blinking Memory 22 */
SFR_8BIT(LCDBM23);                            /* LCD Blinking Memory 23 */
SFR_8BIT(LCDBM24);                            /* LCD Blinking Memory 24 */

/* LCDBIV Definitions */
#define LCDBIV_NONE            (0x0000)       /* No Interrupt pending */
#define LCDBIV_LCDNOCAPIFG     (0x0002)       /* No capacitor connected */
#define LCDBIV_LCDBLKOFFIFG    (0x0004)       /* Blink, segments off */
#define LCDBIV_LCDBLKONIFG     (0x0006)       /* Blink, segments on */
#define LCDBIV_LCDFRMIFG       (0x0008)       /* Frame interrupt */

/************************************************************
* HARDWARE MULTIPLIER 32Bit
************************************************************/
#define __MSP430_HAS_MPY32__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPY32__ 0x04C0
#define MPY32_BASE             __MSP430_BASEADDRESS_MPY32__

SFR_16BIT(MPY);                               /* Multiply Unsigned/Operand 1 */
SFR_8BIT(MPY_L);                              /* Multiply Unsigned/Operand 1 */
SFR_8BIT(MPY_H);                              /* Multiply Unsigned/Operand 1 */
SFR_16BIT(MPYS);                              /* Multiply Signed/Operand 1 */
SFR_8BIT(MPYS_L);                             /* Multiply Signed/Operand 1 */
SFR_8BIT(MPYS_H);                             /* Multiply Signed/Operand 1 */
SFR_16BIT(MAC);                               /* Multiply Unsigned and Accumulate/Operand 1 */
SFR_8BIT(MAC_L);                              /* Multiply Unsigned and Accumulate/Operand 1 */
SFR_8BIT(MAC_H);                              /* Multiply Unsigned and Accumulate/Operand 1 */
SFR_16BIT(MACS);                              /* Multiply Signed and Accumulate/Operand 1 */
SFR_8BIT(MACS_L);                             /* Multiply Signed and Accumulate/Operand 1 */
SFR_8BIT(MACS_H);                             /* Multiply Signed and Accumulate/Operand 1 */
SFR_16BIT(OP2);                               /* Operand 2 */
SFR_8BIT(OP2_L);                              /* Operand 2 */
SFR_8BIT(OP2_H);                              /* Operand 2 */
SFR_16BIT(RESLO);                             /* Result Low Word */
SFR_8BIT(RESLO_L);                            /* Result Low Word */
SFR_8BIT(RESLO_H);                            /* Result Low Word */
SFR_16BIT(RESHI);                             /* Result High Word */
SFR_8BIT(RESHI_L);                            /* Result High Word */
SFR_8BIT(RESHI_H);                            /* Result High Word */
SFR_16BIT(SUMEXT);                            /* Sum Extend */
SFR_8BIT(SUMEXT_L);                           /* Sum Extend */
SFR_8BIT(SUMEXT_H);                           /* Sum Extend */

SFR_16BIT(MPY32L);                            /* 32-bit operand 1 - multiply - low word */
SFR_8BIT(MPY32L_L);                           /* 32-bit operand 1 - multiply - low word */
SFR_8BIT(MPY32L_H);                           /* 32-bit operand 1 - multiply - low word */
SFR_16BIT(MPY32H);                            /* 32-bit operand 1 - multiply - high word */
SFR_8BIT(MPY32H_L);                           /* 32-bit operand 1 - multiply - high word */
SFR_8BIT(MPY32H_H);                           /* 32-bit operand 1 - multiply - high word */
SFR_16BIT(MPYS32L);                           /* 32-bit operand 1 - signed multiply - low word */
SFR_8BIT(MPYS32L_L);                          /* 32-bit operand 1 - signed multiply - low word */
SFR_8BIT(MPYS32L_H);                          /* 32-bit operand 1 - signed multiply - low word */
SFR_16BIT(MPYS32H);                           /* 32-bit operand 1 - signed multiply - high word */
SFR_8BIT(MPYS32H_L);                          /* 32-bit operand 1 - signed multiply - high word */
SFR_8BIT(MPYS32H_H);                          /* 32-bit operand 1 - signed multiply - high word */
SFR_16BIT(MAC32L);                            /* 32-bit operand 1 - multiply accumulate - low word */
SFR_8BIT(MAC32L_L);                           /* 32-bit operand 1 - multiply accumulate - low word */
SFR_8BIT(MAC32L_H);                           /* 32-bit operand 1 - multiply accumulate - low word */
SFR_16BIT(MAC32H);                            /* 32-bit operand 1 - multiply accumulate - high word */
SFR_8BIT(MAC32H_L);                           /* 32-bit operand 1 - multiply accumulate - high word */
SFR_8BIT(MAC32H_H);                           /* 32-bit operand 1 - multiply accumulate - high word */
SFR_16BIT(MACS32L);                           /* 32-bit operand 1 - signed multiply accumulate - low word */
SFR_8BIT(MACS32L_L);                          /* 32-bit operand 1 - signed multiply accumulate - low word */
SFR_8BIT(MACS32L_H);                          /* 32-bit operand 1 - signed multiply accumulate - low word */
SFR_16BIT(MACS32H);                           /* 32-bit operand 1 - signed multiply accumulate - high word */
SFR_8BIT(MACS32H_L);                          /* 32-bit operand 1 - signed multiply accumulate - high word */
SFR_8BIT(MACS32H_H);                          /* 32-bit operand 1 - signed multiply accumulate - high word */
SFR_16BIT(OP2L);                              /* 32-bit operand 2 - low word */
SFR_8BIT(OP2L_L);                             /* 32-bit operand 2 - low word */
SFR_8BIT(OP2L_H);                             /* 32-bit operand 2 - low word */
SFR_16BIT(OP2H);                              /* 32-bit operand 2 - high word */
SFR_8BIT(OP2H_L);                             /* 32-bit operand 2 - high word */
SFR_8BIT(OP2H_H);                             /* 32-bit operand 2 - high word */
SFR_16BIT(RES0);                              /* 32x32-bit result 0 - least significant word */
SFR_8BIT(RES0_L);                             /* 32x32-bit result 0 - least significant word */
SFR_8BIT(RES0_H);                             /* 32x32-bit result 0 - least significant word */
SFR_16BIT(RES1);                              /* 32x32-bit result 1 */
SFR_8BIT(RES1_L);                             /* 32x32-bit result 1 */
SFR_8BIT(RES1_H);                             /* 32x32-bit result 1 */
SFR_16BIT(RES2);                              /* 32x32-bit result 2 */
SFR_8BIT(RES2_L);                             /* 32x32-bit result 2 */
SFR_8BIT(RES2_H);                             /* 32x32-bit result 2 */
SFR_16BIT(RES3);                              /* 32x32-bit result 3 - most significant word */
SFR_8BIT(RES3_L);                             /* 32x32-bit result 3 - most significant word */
SFR_8BIT(RES3_H);                             /* 32x32-bit result 3 - most significant word */
SFR_16BIT(MPY32CTL0);                         /* MPY32 Control Register 0 */
SFR_8BIT(MPY32CTL0_L);                        /* MPY32 Control Register 0 */
SFR_8BIT(MPY32CTL0_H);                        /* MPY32 Control Register 0 */

#define MPY_B                  MPY_L          /* Multiply Unsigned/Operand 1 (Byte Access) */
#define MPYS_B                 MPYS_L         /* Multiply Signed/Operand 1 (Byte Access) */
#define MAC_B                  MAC_L          /* Multiply Unsigned and Accumulate/Operand 1 (Byte Access) */
#define MACS_B                 MACS_L         /* Multiply Signed and Accumulate/Operand 1 (Byte Access) */
#define OP2_B                  OP2_L          /* Operand 2 (Byte Access) */
#define MPY32L_B               MPY32L_L       /* 32-bit operand 1 - multiply - low word (Byte Access) */
#define MPY32H_B               MPY32H_L       /* 32-bit operand 1 - multiply - high word (Byte Access) */
#define MPYS32L_B              MPYS32L_L      /* 32-bit operand 1 - signed multiply - low word (Byte Access) */
#define MPYS32H_B              MPYS32H_L      /* 32-bit operand 1 - signed multiply - high word (Byte Access) */
#define MAC32L_B               MAC32L_L       /* 32-bit operand 1 - multiply accumulate - low word (Byte Access) */
#define MAC32H_B               MAC32H_L       /* 32-bit operand 1 - multiply accumulate - high word (Byte Access) */
#define MACS32L_B              MACS32L_L      /* 32-bit operand 1 - signed multiply accumulate - low word (Byte Access) */
#define MACS32H_B              MACS32H_L      /* 32-bit operand 1 - signed multiply accumulate - high word (Byte Access) */
#define OP2L_B                 OP2L_L         /* 32-bit operand 2 - low word (Byte Access) */
#define OP2H_B                 OP2H_L         /* 32-bit operand 2 - high word (Byte Access) */

/* MPY32CTL0 Control Bits */
#define MPYC                   (0x0001)       /* Carry of the multiplier */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYFRAC                (0x0004)       /* Fractional mode */
#define MPYSAT                 (0x0008)       /* Saturation mode */
#define MPYM0                  (0x0010)       /* Multiplier mode Bit:0 */
#define MPYM1                  (0x0020)       /* Multiplier mode Bit:1 */
#define OP1_32                 (0x0040)       /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32                 (0x0080)       /* Bit-width of operand 2 0:16Bit / 1:32Bit */
#define MPYDLYWRTEN            (0x0100)       /* Delayed write enable */
#define MPYDLY32               (0x0200)       /* Delayed write mode */

/* MPY32CTL0 Control Bits */
#define MPYC_L                 (0x0001)       /* Carry of the multiplier */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYFRAC_L              (0x0004)       /* Fractional mode */
#define MPYSAT_L               (0x0008)       /* Saturation mode */
#define MPYM0_L                (0x0010)       /* Multiplier mode Bit:0 */
#define MPYM1_L                (0x0020)       /* Multiplier mode Bit:1 */
#define OP1_32_L               (0x0040)       /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32_L               (0x0080)       /* Bit-width of operand 2 0:16Bit / 1:32Bit */

/* MPY32CTL0 Control Bits */
//#define RESERVED            (0x0002)  /* Reserved */
#define MPYDLYWRTEN_H          (0x0001)       /* Delayed write enable */
#define MPYDLY32_H             (0x0002)       /* Delayed write mode */

#define MPYM_0                 (0x0000)       /* Multiplier mode: MPY */
#define MPYM_1                 (0x0010)       /* Multiplier mode: MPYS */
#define MPYM_2                 (0x0020)       /* Multiplier mode: MAC */
#define MPYM_3                 (0x0030)       /* Multiplier mode: MACS */
#define MPYM__MPY              (0x0000)       /* Multiplier mode: MPY */
#define MPYM__MPYS             (0x0010)       /* Multiplier mode: MPYS */
#define MPYM__MAC              (0x0020)       /* Multiplier mode: MAC */
#define MPYM__MACS             (0x0030)       /* Multiplier mode: MACS */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define P1_BASE                __MSP430_BASEADDRESS_PORT1_R__
#define __MSP430_HAS_PORT2_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define P2_BASE                __MSP430_BASEADDRESS_PORT2_R__
#define __MSP430_HAS_PORTA_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200
#define PA_BASE                __MSP430_BASEADDRESS_PORTA_R__
#define __MSP430_HAS_P1SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P2SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_PASEL__                  /* Define for DriverLib */

SFR_16BIT(PAIN);                              /* Port A Input */
SFR_8BIT(PAIN_L);                             /* Port A Input */
SFR_8BIT(PAIN_H);                             /* Port A Input */
SFR_16BIT(PAOUT);                             /* Port A Output */
SFR_8BIT(PAOUT_L);                            /* Port A Output */
SFR_8BIT(PAOUT_H);                            /* Port A Output */
SFR_16BIT(PADIR);                             /* Port A Direction */
SFR_8BIT(PADIR_L);                            /* Port A Direction */
SFR_8BIT(PADIR_H);                            /* Port A Direction */
SFR_16BIT(PAREN);                             /* Port A Resistor Enable */
SFR_8BIT(PAREN_L);                            /* Port A Resistor Enable */
SFR_8BIT(PAREN_H);                            /* Port A Resistor Enable */
SFR_16BIT(PADS);                              /* Port A Drive Strenght */
SFR_8BIT(PADS_L);                             /* Port A Drive Strenght */
SFR_8BIT(PADS_H);                             /* Port A Drive Strenght */
SFR_16BIT(PASEL);                             /* Port A Selection */
SFR_8BIT(PASEL_L);                            /* Port A Selection */
SFR_8BIT(PASEL_H);                            /* Port A Selection */
SFR_16BIT(PAIES);                             /* Port A Interrupt Edge Select */
SFR_8BIT(PAIES_L);                            /* Port A Interrupt Edge Select */
SFR_8BIT(PAIES_H);                            /* Port A Interrupt Edge Select */
SFR_16BIT(PAIE);                              /* Port A Interrupt Enable */
SFR_8BIT(PAIE_L);                             /* Port A Interrupt Enable */
SFR_8BIT(PAIE_H);                             /* Port A Interrupt Enable */
SFR_16BIT(PAIFG);                             /* Port A Interrupt Flag */
SFR_8BIT(PAIFG_L);                            /* Port A Interrupt Flag */
SFR_8BIT(PAIFG_H);                            /* Port A Interrupt Flag */


SFR_16BIT(P1IV);                              /* Port 1 Interrupt Vector Word */
SFR_16BIT(P2IV);                              /* Port 2 Interrupt Vector Word */
#define P1IN                   (PAIN_L)       /* Port 1 Input */
#define P1OUT                  (PAOUT_L)      /* Port 1 Output */
#define P1DIR                  (PADIR_L)      /* Port 1 Direction */
#define P1REN                  (PAREN_L)      /* Port 1 Resistor Enable */
#define P1DS                   (PADS_L)       /* Port 1 Drive Strenght */
#define P1SEL                  (PASEL_L)      /* Port 1 Selection */
#define P1IES                  (PAIES_L)      /* Port 1 Interrupt Edge Select */
#define P1IE                   (PAIE_L)       /* Port 1 Interrupt Enable */
#define P1IFG                  (PAIFG_L)      /* Port 1 Interrupt Flag */

//Definitions for P1IV
#define P1IV_NONE              (0x0000)       /* No Interrupt pending */
#define P1IV_P1IFG0            (0x0002)       /* P1IV P1IFG.0 */
#define P1IV_P1IFG1            (0x0004)       /* P1IV P1IFG.1 */
#define P1IV_P1IFG2            (0x0006)       /* P1IV P1IFG.2 */
#define P1IV_P1IFG3            (0x0008)       /* P1IV P1IFG.3 */
#define P1IV_P1IFG4            (0x000A)       /* P1IV P1IFG.4 */
#define P1IV_P1IFG5            (0x000C)       /* P1IV P1IFG.5 */
#define P1IV_P1IFG6            (0x000E)       /* P1IV P1IFG.6 */
#define P1IV_P1IFG7            (0x0010)       /* P1IV P1IFG.7 */

#define P2IN                   (PAIN_H)       /* Port 2 Input */
#define P2OUT                  (PAOUT_H)      /* Port 2 Output */
#define P2DIR                  (PADIR_H)      /* Port 2 Direction */
#define P2REN                  (PAREN_H)      /* Port 2 Resistor Enable */
#define P2DS                   (PADS_H)       /* Port 2 Drive Strenght */
#define P2SEL                  (PASEL_H)      /* Port 2 Selection */
#define P2IES                  (PAIES_H)      /* Port 2 Interrupt Edge Select */
#define P2IE                   (PAIE_H)       /* Port 2 Interrupt Enable */
#define P2IFG                  (PAIFG_H)      /* Port 2 Interrupt Flag */

//Definitions for P2IV
#define P2IV_NONE              (0x0000)       /* No Interrupt pending */
#define P2IV_P2IFG0            (0x0002)       /* P2IV P2IFG.0 */
#define P2IV_P2IFG1            (0x0004)       /* P2IV P2IFG.1 */
#define P2IV_P2IFG2            (0x0006)       /* P2IV P2IFG.2 */
#define P2IV_P2IFG3            (0x0008)       /* P2IV P2IFG.3 */
#define P2IV_P2IFG4            (0x000A)       /* P2IV P2IFG.4 */
#define P2IV_P2IFG5            (0x000C)       /* P2IV P2IFG.5 */
#define P2IV_P2IFG6            (0x000E)       /* P2IV P2IFG.6 */
#define P2IV_P2IFG7            (0x0010)       /* P2IV P2IFG.7 */


/************************************************************
* DIGITAL I/O Port3/4 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT3_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_R__ 0x0220
#define P3_BASE                __MSP430_BASEADDRESS_PORT3_R__
#define __MSP430_HAS_PORT4_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT4_R__ 0x0220
#define P4_BASE                __MSP430_BASEADDRESS_PORT4_R__
#define __MSP430_HAS_PORTB_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTB_R__ 0x0220
#define PB_BASE                __MSP430_BASEADDRESS_PORTB_R__
#define __MSP430_HAS_P3SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_P4SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_PBSEL__                  /* Define for DriverLib */

SFR_16BIT(PBIN);                              /* Port B Input */
SFR_8BIT(PBIN_L);                             /* Port B Input */
SFR_8BIT(PBIN_H);                             /* Port B Input */
SFR_16BIT(PBOUT);                             /* Port B Output */
SFR_8BIT(PBOUT_L);                            /* Port B Output */
SFR_8BIT(PBOUT_H);                            /* Port B Output */
SFR_16BIT(PBDIR);                             /* Port B Direction */
SFR_8BIT(PBDIR_L);                            /* Port B Direction */
SFR_8BIT(PBDIR_H);                            /* Port B Direction */
SFR_16BIT(PBREN);                             /* Port B Resistor Enable */
SFR_8BIT(PBREN_L);                            /* Port B Resistor Enable */
SFR_8BIT(PBREN_H);                            /* Port B Resistor Enable */
SFR_16BIT(PBDS);                              /* Port B Drive Strenght */
SFR_8BIT(PBDS_L);                             /* Port B Drive Strenght */
SFR_8BIT(PBDS_H);                             /* Port B Drive Strenght */
SFR_16BIT(PBSEL);                             /* Port B Selection */
SFR_8BIT(PBSEL_L);                            /* Port B Selection */
SFR_8BIT(PBSEL_H);                            /* Port B Selection */


#define P3IN                   (PBIN_L)       /* Port 3 Input */
#define P3OUT                  (PBOUT_L)      /* Port 3 Output */
#define P3DIR                  (PBDIR_L)      /* Port 3 Direction */
#define P3REN                  (PBREN_L)      /* Port 3 Resistor Enable */
#define P3DS                   (PBDS_L)       /* Port 3 Drive Strenght */
#define P3SEL                  (PBSEL_L)      /* Port 3 Selection */

#define P4IN                   (PBIN_H)       /* Port 4 Input */
#define P4OUT                  (PBOUT_H)      /* Port 4 Output */
#define P4DIR                  (PBDIR_H)      /* Port 4 Direction */
#define P4REN                  (PBREN_H)      /* Port 4 Resistor Enable */
#define P4DS                   (PBDS_H)       /* Port 4 Drive Strenght */
#define P4SEL                  (PBSEL_H)      /* Port 4 Selection */


/************************************************************
* DIGITAL I/O Port5 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT5_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT5_R__ 0x0240
#define P5_BASE                __MSP430_BASEADDRESS_PORT5_R__
#define __MSP430_HAS_PORTC_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTC_R__ 0x0240
#define PC_BASE                __MSP430_BASEADDRESS_PORTC_R__
#define __MSP430_HAS_P5SEL__                  /* Define for DriverLib */
#define __MSP430_HAS_PCSEL__                  /* Define for DriverLib */

SFR_16BIT(PCIN);                              /* Port C Input */
SFR_8BIT(PCIN_L);                             /* Port C Input */
SFR_8BIT(PCIN_H);                             /* Port C Input */
SFR_16BIT(PCOUT);                             /* Port C Output */
SFR_8BIT(PCOUT_L);                            /* Port C Output */
SFR_8BIT(PCOUT_H);                            /* Port C Output */
SFR_16BIT(PCDIR);                             /* Port C Direction */
SFR_8BIT(PCDIR_L);                            /* Port C Direction */
SFR_8BIT(PCDIR_H);                            /* Port C Direction */
SFR_16BIT(PCREN);                             /* Port C Resistor Enable */
SFR_8BIT(PCREN_L);                            /* Port C Resistor Enable */
SFR_8BIT(PCREN_H);                            /* Port C Resistor Enable */
SFR_16BIT(PCDS);                              /* Port C Drive Strenght */
SFR_8BIT(PCDS_L);                             /* Port C Drive Strenght */
SFR_8BIT(PCDS_H);                             /* Port C Drive Strenght */
SFR_16BIT(PCSEL);                             /* Port C Selection */
SFR_8BIT(PCSEL_L);                            /* Port C Selection */
SFR_8BIT(PCSEL_H);                            /* Port C Selection */


#define P5IN                   (PCIN_L)       /* Port 5 Input */
#define P5OUT                  (PCOUT_L)      /* Port 5 Output */
#define P5DIR                  (PCDIR_L)      /* Port 5 Direction */
#define P5REN                  (PCREN_L)      /* Port 5 Resistor Enable */
#define P5DS                   (PCDS_L)       /* Port 5 Drive Strenght */
#define P5SEL                  (PCSEL_L)      /* Port 5 Selection */


/************************************************************
* DIGITAL I/O PortJ Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORTJ_R__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTJ_R__ 0x0320
#define PJ_BASE                __MSP430_BASEADDRESS_PORTJ_R__

SFR_16BIT(PJIN);                              /* Port J Input */
SFR_8BIT(PJIN_L);                             /* Port J Input */
SFR_8BIT(PJIN_H);                             /* Port J Input */
SFR_16BIT(PJOUT);                             /* Port J Output */
SFR_8BIT(PJOUT_L);                            /* Port J Output */
SFR_8BIT(PJOUT_H);                            /* Port J Output */
SFR_16BIT(PJDIR);                             /* Port J Direction */
SFR_8BIT(PJDIR_L);                            /* Port J Direction */
SFR_8BIT(PJDIR_H);                            /* Port J Direction */
SFR_16BIT(PJREN);                             /* Port J Resistor Enable */
SFR_8BIT(PJREN_L);                            /* Port J Resistor Enable */
SFR_8BIT(PJREN_H);                            /* Port J Resistor Enable */
SFR_16BIT(PJDS);                              /* Port J Drive Strenght */
SFR_8BIT(PJDS_L);                             /* Port J Drive Strenght */
SFR_8BIT(PJDS_H);                             /* Port J Drive Strenght */

/************************************************************
* PORT MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT_MAPPING__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT_MAPPING__ 0x01C0
#define PMAP_CTRL_BASE         __MSP430_BASEADDRESS_PORT_MAPPING__

SFR_16BIT(PMAPKEYID);                         /* Port Mapping Key register */
SFR_8BIT(PMAPKEYID_L);                        /* Port Mapping Key register */
SFR_8BIT(PMAPKEYID_H);                        /* Port Mapping Key register */
SFR_16BIT(PMAPCTL);                           /* Port Mapping control register */
SFR_8BIT(PMAPCTL_L);                          /* Port Mapping control register */
SFR_8BIT(PMAPCTL_H);                          /* Port Mapping control register */

#define  PMAPKEY               (0x2D52)       /* Port Mapping Key */
#define  PMAPPWD               PMAPKEYID      /* Legacy Definition: Mapping Key register */
#define  PMAPPW                (0x2D52)       /* Legacy Definition: Port Mapping Password */

/* PMAPCTL Control Bits */
#define PMAPLOCKED             (0x0001)       /* Port Mapping Lock bit. Read only */
#define PMAPRECFG              (0x0002)       /* Port Mapping re-configuration control bit */

/* PMAPCTL Control Bits */
#define PMAPLOCKED_L           (0x0001)       /* Port Mapping Lock bit. Read only */
#define PMAPRECFG_L            (0x0002)       /* Port Mapping re-configuration control bit */

/************************************************************
* PORT 1 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT1_MAPPING__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_MAPPING__ 0x01C8
#define P1MAP_BASE             __MSP430_BASEADDRESS_PORT1_MAPPING__

SFR_16BIT(P1MAP01);                           /* Port P1.0/1 mapping register */
SFR_8BIT(P1MAP01_L);                          /* Port P1.0/1 mapping register */
SFR_8BIT(P1MAP01_H);                          /* Port P1.0/1 mapping register */
SFR_16BIT(P1MAP23);                           /* Port P1.2/3 mapping register */
SFR_8BIT(P1MAP23_L);                          /* Port P1.2/3 mapping register */
SFR_8BIT(P1MAP23_H);                          /* Port P1.2/3 mapping register */
SFR_16BIT(P1MAP45);                           /* Port P1.4/5 mapping register */
SFR_8BIT(P1MAP45_L);                          /* Port P1.4/5 mapping register */
SFR_8BIT(P1MAP45_H);                          /* Port P1.4/5 mapping register */
SFR_16BIT(P1MAP67);                           /* Port P1.6/7 mapping register */
SFR_8BIT(P1MAP67_L);                          /* Port P1.6/7 mapping register */
SFR_8BIT(P1MAP67_H);                          /* Port P1.6/7 mapping register */

#define  P1MAP0                P1MAP01_L      /* Port P1.0 mapping register */
#define  P1MAP1                P1MAP01_H      /* Port P1.1 mapping register */
#define  P1MAP2                P1MAP23_L      /* Port P1.2 mapping register */
#define  P1MAP3                P1MAP23_H      /* Port P1.3 mapping register */
#define  P1MAP4                P1MAP45_L      /* Port P1.4 mapping register */
#define  P1MAP5                P1MAP45_H      /* Port P1.5 mapping register */
#define  P1MAP6                P1MAP67_L      /* Port P1.6 mapping register */
#define  P1MAP7                P1MAP67_H      /* Port P1.7 mapping register */

/************************************************************
* PORT 2 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT2_MAPPING__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_MAPPING__ 0x01D0
#define P2MAP_BASE             __MSP430_BASEADDRESS_PORT2_MAPPING__

SFR_16BIT(P2MAP01);                           /* Port P2.0/1 mapping register */
SFR_8BIT(P2MAP01_L);                          /* Port P2.0/1 mapping register */
SFR_8BIT(P2MAP01_H);                          /* Port P2.0/1 mapping register */
SFR_16BIT(P2MAP23);                           /* Port P2.2/3 mapping register */
SFR_8BIT(P2MAP23_L);                          /* Port P2.2/3 mapping register */
SFR_8BIT(P2MAP23_H);                          /* Port P2.2/3 mapping register */
SFR_16BIT(P2MAP45);                           /* Port P2.4/5 mapping register */
SFR_8BIT(P2MAP45_L);                          /* Port P2.4/5 mapping register */
SFR_8BIT(P2MAP45_H);                          /* Port P2.4/5 mapping register */
SFR_16BIT(P2MAP67);                           /* Port P2.6/7 mapping register */
SFR_8BIT(P2MAP67_L);                          /* Port P2.6/7 mapping register */
SFR_8BIT(P2MAP67_H);                          /* Port P2.6/7 mapping register */

#define  P2MAP0                P2MAP01_L      /* Port P2.0 mapping register */
#define  P2MAP1                P2MAP01_H      /* Port P2.1 mapping register */
#define  P2MAP2                P2MAP23_L      /* Port P2.2 mapping register */
#define  P2MAP3                P2MAP23_H      /* Port P2.3 mapping register */
#define  P2MAP4                P2MAP45_L      /* Port P2.4 mapping register */
#define  P2MAP5                P2MAP45_H      /* Port P2.5 mapping register */
#define  P2MAP6                P2MAP67_L      /* Port P2.6 mapping register */
#define  P2MAP7                P2MAP67_H      /* Port P2.7 mapping register */

/************************************************************
* PORT 3 MAPPING CONTROLLER
************************************************************/
#define __MSP430_HAS_PORT3_MAPPING__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT3_MAPPING__ 0x01D8
#define P3MAP_BASE             __MSP430_BASEADDRESS_PORT3_MAPPING__

SFR_16BIT(P3MAP01);                           /* Port P3.0/1 mapping register */
SFR_8BIT(P3MAP01_L);                          /* Port P3.0/1 mapping register */
SFR_8BIT(P3MAP01_H);                          /* Port P3.0/1 mapping register */
SFR_16BIT(P3MAP23);                           /* Port P3.2/3 mapping register */
SFR_8BIT(P3MAP23_L);                          /* Port P3.2/3 mapping register */
SFR_8BIT(P3MAP23_H);                          /* Port P3.2/3 mapping register */
SFR_16BIT(P3MAP45);                           /* Port P3.4/5 mapping register */
SFR_8BIT(P3MAP45_L);                          /* Port P3.4/5 mapping register */
SFR_8BIT(P3MAP45_H);                          /* Port P3.4/5 mapping register */
SFR_16BIT(P3MAP67);                           /* Port P3.6/7 mapping register */
SFR_8BIT(P3MAP67_L);                          /* Port P3.6/7 mapping register */
SFR_8BIT(P3MAP67_H);                          /* Port P3.6/7 mapping register */

#define  P3MAP0                P3MAP01_L      /* Port P3.0 mapping register */
#define  P3MAP1                P3MAP01_H      /* Port P3.1 mapping register */
#define  P3MAP2                P3MAP23_L      /* Port P3.2 mapping register */
#define  P3MAP3                P3MAP23_H      /* Port P3.3 mapping register */
#define  P3MAP4                P3MAP45_L      /* Port P3.4 mapping register */
#define  P3MAP5                P3MAP45_H      /* Port P3.5 mapping register */
#define  P3MAP6                P3MAP67_L      /* Port P3.6 mapping register */
#define  P3MAP7                P3MAP67_H      /* Port P3.7 mapping register */

#define PM_NONE                0
#define PM_CBOUT0              1
#define PM_TA0CLK              1
#define PM_CBOUT1              2
#define PM_TA1CLK              2
#define PM_ACLK                3
#define PM_MCLK                4
#define PM_SMCLK               5
#define PM_RTCCLK              6
#define PM_MODCLK              7
#define PM_DMAE0               7
#define PM_SVMOUT              8
#define PM_TA0CCR0A            9
#define PM_TA0CCR1A            10
#define PM_TA0CCR2A            11
#define PM_TA0CCR3A            12
#define PM_TA0CCR4A            13
#define PM_TA1CCR0A            14
#define PM_TA1CCR1A            15
#define PM_TA1CCR2A            16
#define PM_UCA0RXD             17
#define PM_UCA0SOMI            17
#define PM_UCA0TXD             18
#define PM_UCA0SIMO            18
#define PM_UCA0CLK             19
#define PM_UCB0STE             19
#define PM_UCB0SOMI            20
#define PM_UCB0SCL             20
#define PM_UCB0SIMO            21
#define PM_UCB0SDA             21
#define PM_UCB0CLK             22
#define PM_UCA0STE             22
#define PM_RFGDO0              23
#define PM_RFGDO1              24
#define PM_RFGDO2              25
#define PM_ANALOG              31

/************************************************************
* PMM - Power Management System
************************************************************/
#define __MSP430_HAS_PMM__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM__ 0x0120
#define PMM_BASE               __MSP430_BASEADDRESS_PMM__

SFR_16BIT(PMMCTL0);                           /* PMM Control 0 */
SFR_8BIT(PMMCTL0_L);                          /* PMM Control 0 */
SFR_8BIT(PMMCTL0_H);                          /* PMM Control 0 */
SFR_16BIT(PMMCTL1);                           /* PMM Control 1 */
SFR_8BIT(PMMCTL1_L);                          /* PMM Control 1 */
SFR_8BIT(PMMCTL1_H);                          /* PMM Control 1 */
SFR_16BIT(SVSMHCTL);                          /* SVS and SVM high side control register */
SFR_8BIT(SVSMHCTL_L);                         /* SVS and SVM high side control register */
SFR_8BIT(SVSMHCTL_H);                         /* SVS and SVM high side control register */
SFR_16BIT(SVSMLCTL);                          /* SVS and SVM low side control register */
SFR_8BIT(SVSMLCTL_L);                         /* SVS and SVM low side control register */
SFR_8BIT(SVSMLCTL_H);                         /* SVS and SVM low side control register */
SFR_16BIT(SVSMIO);                            /* SVSIN and SVSOUT control register */
SFR_8BIT(SVSMIO_L);                           /* SVSIN and SVSOUT control register */
SFR_8BIT(SVSMIO_H);                           /* SVSIN and SVSOUT control register */
SFR_16BIT(PMMIFG);                            /* PMM Interrupt Flag */
SFR_8BIT(PMMIFG_L);                           /* PMM Interrupt Flag */
SFR_8BIT(PMMIFG_H);                           /* PMM Interrupt Flag */
SFR_16BIT(PMMRIE);                            /* PMM and RESET Interrupt Enable */
SFR_8BIT(PMMRIE_L);                           /* PMM and RESET Interrupt Enable */
SFR_8BIT(PMMRIE_H);                           /* PMM and RESET Interrupt Enable */

#define PMMPW                  (0xA500)       /* PMM Register Write Password */
#define PMMPW_H                (0xA5)         /* PMM Register Write Password for high word access */

/* PMMCTL0 Control Bits */
#define PMMCOREV0              (0x0001)       /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1              (0x0002)       /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR               (0x0004)       /* PMM Software BOR */
#define PMMSWPOR               (0x0008)       /* PMM Software POR */
#define PMMREGOFF              (0x0010)       /* PMM Turn Regulator off */
#define PMMHPMRE               (0x0080)       /* PMM Global High Power Module Request Enable */

/* PMMCTL0 Control Bits */
#define PMMCOREV0_L            (0x0001)       /* PMM Core Voltage Bit: 0 */
#define PMMCOREV1_L            (0x0002)       /* PMM Core Voltage Bit: 1 */
#define PMMSWBOR_L             (0x0004)       /* PMM Software BOR */
#define PMMSWPOR_L             (0x0008)       /* PMM Software POR */
#define PMMREGOFF_L            (0x0010)       /* PMM Turn Regulator off */
#define PMMHPMRE_L             (0x0080)       /* PMM Global High Power Module Request Enable */

#define PMMCOREV_0             (0x0000)       /* PMM Core Voltage 0 (1.35V) */
#define PMMCOREV_1             (0x0001)       /* PMM Core Voltage 1 (1.55V) */
#define PMMCOREV_2             (0x0002)       /* PMM Core Voltage 2 (1.75V) */
#define PMMCOREV_3             (0x0003)       /* PMM Core Voltage 3 (1.85V) */

/* PMMCTL1 Control Bits */
#define PMMREFMD               (0x0001)       /* PMM Reference Mode */
#define PMMCMD0                (0x0010)       /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1                (0x0020)       /* PMM Voltage Regulator Current Mode Bit: 1 */

/* PMMCTL1 Control Bits */
#define PMMREFMD_L             (0x0001)       /* PMM Reference Mode */
#define PMMCMD0_L              (0x0010)       /* PMM Voltage Regulator Current Mode Bit: 0 */
#define PMMCMD1_L              (0x0020)       /* PMM Voltage Regulator Current Mode Bit: 1 */

/* SVSMHCTL Control Bits */
#define SVSMHRRL0              (0x0001)       /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1              (0x0002)       /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2              (0x0004)       /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST             (0x0008)       /* SVS and SVM high side delay status */
#define SVSHMD                 (0x0010)       /* SVS high side mode */
#define SVSMHEVM               (0x0040)       /* SVS and SVM high side event mask */
#define SVSMHACE               (0x0080)       /* SVS and SVM high side auto control enable */
#define SVSHRVL0               (0x0100)       /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1               (0x0200)       /* SVS high side reset voltage level Bit: 1 */
#define SVSHE                  (0x0400)       /* SVS high side enable */
#define SVSHFP                 (0x0800)       /* SVS high side full performace mode */
#define SVMHOVPE               (0x1000)       /* SVM high side over-voltage enable */
#define SVMHE                  (0x4000)       /* SVM high side enable */
#define SVMHFP                 (0x8000)       /* SVM high side full performace mode */

/* SVSMHCTL Control Bits */
#define SVSMHRRL0_L            (0x0001)       /* SVS and SVM high side Reset Release Voltage Level Bit: 0 */
#define SVSMHRRL1_L            (0x0002)       /* SVS and SVM high side Reset Release Voltage Level Bit: 1 */
#define SVSMHRRL2_L            (0x0004)       /* SVS and SVM high side Reset Release Voltage Level Bit: 2 */
#define SVSMHDLYST_L           (0x0008)       /* SVS and SVM high side delay status */
#define SVSHMD_L               (0x0010)       /* SVS high side mode */
#define SVSMHEVM_L             (0x0040)       /* SVS and SVM high side event mask */
#define SVSMHACE_L             (0x0080)       /* SVS and SVM high side auto control enable */

/* SVSMHCTL Control Bits */
#define SVSHRVL0_H             (0x0001)       /* SVS high side reset voltage level Bit: 0 */
#define SVSHRVL1_H             (0x0002)       /* SVS high side reset voltage level Bit: 1 */
#define SVSHE_H                (0x0004)       /* SVS high side enable */
#define SVSHFP_H               (0x0008)       /* SVS high side full performace mode */
#define SVMHOVPE_H             (0x0010)       /* SVM high side over-voltage enable */
#define SVMHE_H                (0x0040)       /* SVM high side enable */
#define SVMHFP_H               (0x0080)       /* SVM high side full performace mode */

#define SVSMHRRL_0             (0x0000)       /* SVS and SVM high side Reset Release Voltage Level 0 */
#define SVSMHRRL_1             (0x0001)       /* SVS and SVM high side Reset Release Voltage Level 1 */
#define SVSMHRRL_2             (0x0002)       /* SVS and SVM high side Reset Release Voltage Level 2 */
#define SVSMHRRL_3             (0x0003)       /* SVS and SVM high side Reset Release Voltage Level 3 */
#define SVSMHRRL_4             (0x0004)       /* SVS and SVM high side Reset Release Voltage Level 4 */
#define SVSMHRRL_5             (0x0005)       /* SVS and SVM high side Reset Release Voltage Level 5 */
#define SVSMHRRL_6             (0x0006)       /* SVS and SVM high side Reset Release Voltage Level 6 */
#define SVSMHRRL_7             (0x0007)       /* SVS and SVM high side Reset Release Voltage Level 7 */

#define SVSHRVL_0              (0x0000)       /* SVS high side Reset Release Voltage Level 0 */
#define SVSHRVL_1              (0x0100)       /* SVS high side Reset Release Voltage Level 1 */
#define SVSHRVL_2              (0x0200)       /* SVS high side Reset Release Voltage Level 2 */
#define SVSHRVL_3              (0x0300)       /* SVS high side Reset Release Voltage Level 3 */

/* SVSMLCTL Control Bits */
#define SVSMLRRL0              (0x0001)       /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1              (0x0002)       /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2              (0x0004)       /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST             (0x0008)       /* SVS and SVM low side delay status */
#define SVSLMD                 (0x0010)       /* SVS low side mode */
#define SVSMLEVM               (0x0040)       /* SVS and SVM low side event mask */
#define SVSMLACE               (0x0080)       /* SVS and SVM low side auto control enable */
#define SVSLRVL0               (0x0100)       /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1               (0x0200)       /* SVS low side reset voltage level Bit: 1 */
#define SVSLE                  (0x0400)       /* SVS low side enable */
#define SVSLFP                 (0x0800)       /* SVS low side full performace mode */
#define SVMLOVPE               (0x1000)       /* SVM low side over-voltage enable */
#define SVMLE                  (0x4000)       /* SVM low side enable */
#define SVMLFP                 (0x8000)       /* SVM low side full performace mode */

/* SVSMLCTL Control Bits */
#define SVSMLRRL0_L            (0x0001)       /* SVS and SVM low side Reset Release Voltage Level Bit: 0 */
#define SVSMLRRL1_L            (0x0002)       /* SVS and SVM low side Reset Release Voltage Level Bit: 1 */
#define SVSMLRRL2_L            (0x0004)       /* SVS and SVM low side Reset Release Voltage Level Bit: 2 */
#define SVSMLDLYST_L           (0x0008)       /* SVS and SVM low side delay status */
#define SVSLMD_L               (0x0010)       /* SVS low side mode */
#define SVSMLEVM_L             (0x0040)       /* SVS and SVM low side event mask */
#define SVSMLACE_L             (0x0080)       /* SVS and SVM low side auto control enable */

/* SVSMLCTL Control Bits */
#define SVSLRVL0_H             (0x0001)       /* SVS low side reset voltage level Bit: 0 */
#define SVSLRVL1_H             (0x0002)       /* SVS low side reset voltage level Bit: 1 */
#define SVSLE_H                (0x0004)       /* SVS low side enable */
#define SVSLFP_H               (0x0008)       /* SVS low side full performace mode */
#define SVMLOVPE_H             (0x0010)       /* SVM low side over-voltage enable */
#define SVMLE_H                (0x0040)       /* SVM low side enable */
#define SVMLFP_H               (0x0080)       /* SVM low side full performace mode */

#define SVSMLRRL_0             (0x0000)       /* SVS and SVM low side Reset Release Voltage Level 0 */
#define SVSMLRRL_1             (0x0001)       /* SVS and SVM low side Reset Release Voltage Level 1 */
#define SVSMLRRL_2             (0x0002)       /* SVS and SVM low side Reset Release Voltage Level 2 */
#define SVSMLRRL_3             (0x0003)       /* SVS and SVM low side Reset Release Voltage Level 3 */
#define SVSMLRRL_4             (0x0004)       /* SVS and SVM low side Reset Release Voltage Level 4 */
#define SVSMLRRL_5             (0x0005)       /* SVS and SVM low side Reset Release Voltage Level 5 */
#define SVSMLRRL_6             (0x0006)       /* SVS and SVM low side Reset Release Voltage Level 6 */
#define SVSMLRRL_7             (0x0007)       /* SVS and SVM low side Reset Release Voltage Level 7 */

#define SVSLRVL_0              (0x0000)       /* SVS low side Reset Release Voltage Level 0 */
#define SVSLRVL_1              (0x0100)       /* SVS low side Reset Release Voltage Level 1 */
#define SVSLRVL_2              (0x0200)       /* SVS low side Reset Release Voltage Level 2 */
#define SVSLRVL_3              (0x0300)       /* SVS low side Reset Release Voltage Level 3 */

/* SVSMIO Control Bits */
#define SVMLOE                 (0x0008)       /* SVM low side output enable */
#define SVMLVLROE              (0x0010)       /* SVM low side voltage level reached output enable */
#define SVMOUTPOL              (0x0020)       /* SVMOUT pin polarity */
#define SVMHOE                 (0x0800)       /* SVM high side output enable */
#define SVMHVLROE              (0x1000)       /* SVM high side voltage level reached output enable */

/* SVSMIO Control Bits */
#define SVMLOE_L               (0x0008)       /* SVM low side output enable */
#define SVMLVLROE_L            (0x0010)       /* SVM low side voltage level reached output enable */
#define SVMOUTPOL_L            (0x0020)       /* SVMOUT pin polarity */

/* SVSMIO Control Bits */
#define SVMHOE_H               (0x0008)       /* SVM high side output enable */
#define SVMHVLROE_H            (0x0010)       /* SVM high side voltage level reached output enable */

/* PMMIFG Control Bits */
#define SVSMLDLYIFG            (0x0001)       /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG                (0x0002)       /* SVM low side interrupt flag */
#define SVMLVLRIFG             (0x0004)       /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG            (0x0010)       /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG                (0x0020)       /* SVM high side interrupt flag */
#define SVMHVLRIFG             (0x0040)       /* SVM high side Voltage Level Reached interrupt flag */
#define PMMBORIFG              (0x0100)       /* PMM Software BOR interrupt flag */
#define PMMRSTIFG              (0x0200)       /* PMM RESET pin interrupt flag */
#define PMMPORIFG              (0x0400)       /* PMM Software POR interrupt flag */
#define SVSHIFG                (0x1000)       /* SVS low side interrupt flag */
#define SVSLIFG                (0x2000)       /* SVS high side interrupt flag */
#define PMMLPM5IFG             (0x8000)       /* LPM5 indication Flag */

/* PMMIFG Control Bits */
#define SVSMLDLYIFG_L          (0x0001)       /* SVS and SVM low side Delay expired interrupt flag */
#define SVMLIFG_L              (0x0002)       /* SVM low side interrupt flag */
#define SVMLVLRIFG_L           (0x0004)       /* SVM low side Voltage Level Reached interrupt flag */
#define SVSMHDLYIFG_L          (0x0010)       /* SVS and SVM high side Delay expired interrupt flag */
#define SVMHIFG_L              (0x0020)       /* SVM high side interrupt flag */
#define SVMHVLRIFG_L           (0x0040)       /* SVM high side Voltage Level Reached interrupt flag */

/* PMMIFG Control Bits */
#define PMMBORIFG_H            (0x0001)       /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H            (0x0002)       /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H            (0x0004)       /* PMM Software POR interrupt flag */
#define SVSHIFG_H              (0x0010)       /* SVS low side interrupt flag */
#define SVSLIFG_H              (0x0020)       /* SVS high side interrupt flag */
#define PMMLPM5IFG_H           (0x0080)       /* LPM5 indication Flag */

#define PMMRSTLPM5IFG          PMMLPM5IFG     /* LPM5 indication Flag */

/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE             (0x0001)       /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE                 (0x0002)       /* SVM low side interrupt enable */
#define SVMLVLRIE              (0x0004)       /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE             (0x0010)       /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE                 (0x0020)       /* SVM high side interrupt enable */
#define SVMHVLRIE              (0x0040)       /* SVM high side Voltage Level Reached interrupt enable */
#define SVSLPE                 (0x0100)       /* SVS low side POR enable */
#define SVMLVLRPE              (0x0200)       /* SVM low side Voltage Level reached POR enable */
#define SVSHPE                 (0x1000)       /* SVS high side POR enable */
#define SVMHVLRPE              (0x2000)       /* SVM high side Voltage Level reached POR enable */

/* PMMIE and RESET Control Bits */
#define SVSMLDLYIE_L           (0x0001)       /* SVS and SVM low side Delay expired interrupt enable */
#define SVMLIE_L               (0x0002)       /* SVM low side interrupt enable */
#define SVMLVLRIE_L            (0x0004)       /* SVM low side Voltage Level Reached interrupt enable */
#define SVSMHDLYIE_L           (0x0010)       /* SVS and SVM high side Delay expired interrupt enable */
#define SVMHIE_L               (0x0020)       /* SVM high side interrupt enable */
#define SVMHVLRIE_L            (0x0040)       /* SVM high side Voltage Level Reached interrupt enable */

/* PMMIE and RESET Control Bits */
#define SVSLPE_H               (0x0001)       /* SVS low side POR enable */
#define SVMLVLRPE_H            (0x0002)       /* SVM low side Voltage Level reached POR enable */
#define SVSHPE_H               (0x0010)       /* SVS high side POR enable */
#define SVMHVLRPE_H            (0x0020)       /* SVM high side Voltage Level reached POR enable */

/*************************************************************
* RAM Control Module
*************************************************************/
#define __MSP430_HAS_RC__                     /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RC__ 0x0158
#define RAM_BASE               __MSP430_BASEADDRESS_RC__

SFR_16BIT(RCCTL0);                            /* Ram Controller Control Register */
SFR_8BIT(RCCTL0_L);                           /* Ram Controller Control Register */
SFR_8BIT(RCCTL0_H);                           /* Ram Controller Control Register */

/* RCCTL0 Control Bits */
#define RCRS0OFF               (0x0001)       /* RAM Controller RAM Sector 0 Off */
#define RCRS1OFF               (0x0002)       /* RAM Controller RAM Sector 1 Off */
#define RCRS2OFF               (0x0004)       /* RAM Controller RAM Sector 2 Off */
#define RCRS3OFF               (0x0008)       /* RAM Controller RAM Sector 3 Off */

/* RCCTL0 Control Bits */
#define RCRS0OFF_L             (0x0001)       /* RAM Controller RAM Sector 0 Off */
#define RCRS1OFF_L             (0x0002)       /* RAM Controller RAM Sector 1 Off */
#define RCRS2OFF_L             (0x0004)       /* RAM Controller RAM Sector 2 Off */
#define RCRS3OFF_L             (0x0008)       /* RAM Controller RAM Sector 3 Off */

#define RCKEY                  (0x5A00)

/************************************************************
* Shared Reference
************************************************************/
#define __MSP430_HAS_REF__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_REF__ 0x01B0
#define REF_BASE               __MSP430_BASEADDRESS_REF__

SFR_16BIT(REFCTL0);                           /* REF Shared Reference control register 0 */
SFR_8BIT(REFCTL0_L);                          /* REF Shared Reference control register 0 */
SFR_8BIT(REFCTL0_H);                          /* REF Shared Reference control register 0 */

/* REFCTL0 Control Bits */
#define REFON                  (0x0001)       /* REF Reference On */
#define REFOUT                 (0x0002)       /* REF Reference output Buffer On */
//#define RESERVED            (0x0004)  /* Reserved */
#define REFTCOFF               (0x0008)       /* REF Temp.Sensor off */
#define REFVSEL0               (0x0010)       /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1               (0x0020)       /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040)  /* Reserved */
#define REFMSTR                (0x0080)       /* REF Master Control */
#define REFGENACT              (0x0100)       /* REF Reference generator active */
#define REFBGACT               (0x0200)       /* REF Reference bandgap active */
#define REFGENBUSY             (0x0400)       /* REF Reference generator busy */
#define BGMODE                 (0x0800)       /* REF Bandgap mode */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

/* REFCTL0 Control Bits */
#define REFON_L                (0x0001)       /* REF Reference On */
#define REFOUT_L               (0x0002)       /* REF Reference output Buffer On */
//#define RESERVED            (0x0004)  /* Reserved */
#define REFTCOFF_L             (0x0008)       /* REF Temp.Sensor off */
#define REFVSEL0_L             (0x0010)       /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1_L             (0x0020)       /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040)  /* Reserved */
#define REFMSTR_L              (0x0080)       /* REF Master Control */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

/* REFCTL0 Control Bits */
//#define RESERVED            (0x0004)  /* Reserved */
//#define RESERVED            (0x0040)  /* Reserved */
#define REFGENACT_H            (0x0001)       /* REF Reference generator active */
#define REFBGACT_H             (0x0002)       /* REF Reference bandgap active */
#define REFGENBUSY_H           (0x0004)       /* REF Reference generator busy */
#define BGMODE_H               (0x0008)       /* REF Bandgap mode */
//#define RESERVED            (0x1000)  /* Reserved */
//#define RESERVED            (0x2000)  /* Reserved */
//#define RESERVED            (0x4000)  /* Reserved */
//#define RESERVED            (0x8000)  /* Reserved */

#define REFVSEL_0              (0x0000)       /* REF Reference Voltage Level Select 1.5V */
#define REFVSEL_1              (0x0010)       /* REF Reference Voltage Level Select 2.0V */
#define REFVSEL_2              (0x0020)       /* REF Reference Voltage Level Select 2.5V */
#define REFVSEL_3              (0x0030)       /* REF Reference Voltage Level Select 2.5V */

/************************************************************
* Real Time Clock
************************************************************/
#define __MSP430_HAS_RTC__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC__ 0x04A0
#define RTC_A_BASE             __MSP430_BASEADDRESS_RTC__

SFR_16BIT(RTCCTL01);                          /* Real Timer Control 0/1 */
SFR_8BIT(RTCCTL01_L);                         /* Real Timer Control 0/1 */
SFR_8BIT(RTCCTL01_H);                         /* Real Timer Control 0/1 */
SFR_16BIT(RTCCTL23);                          /* Real Timer Control 2/3 */
SFR_8BIT(RTCCTL23_L);                         /* Real Timer Control 2/3 */
SFR_8BIT(RTCCTL23_H);                         /* Real Timer Control 2/3 */
SFR_16BIT(RTCPS0CTL);                         /* Real Timer Prescale Timer 0 Control */
SFR_8BIT(RTCPS0CTL_L);                        /* Real Timer Prescale Timer 0 Control */
SFR_8BIT(RTCPS0CTL_H);                        /* Real Timer Prescale Timer 0 Control */
SFR_16BIT(RTCPS1CTL);                         /* Real Timer Prescale Timer 1 Control */
SFR_8BIT(RTCPS1CTL_L);                        /* Real Timer Prescale Timer 1 Control */
SFR_8BIT(RTCPS1CTL_H);                        /* Real Timer Prescale Timer 1 Control */
SFR_16BIT(RTCPS);                             /* Real Timer Prescale Timer Control */
SFR_8BIT(RTCPS_L);                            /* Real Timer Prescale Timer Control */
SFR_8BIT(RTCPS_H);                            /* Real Timer Prescale Timer Control */
SFR_16BIT(RTCIV);                             /* Real Time Clock Interrupt Vector */
SFR_16BIT(RTCTIM0);                           /* Real Time Clock Time 0 */
SFR_8BIT(RTCTIM0_L);                          /* Real Time Clock Time 0 */
SFR_8BIT(RTCTIM0_H);                          /* Real Time Clock Time 0 */
SFR_16BIT(RTCTIM1);                           /* Real Time Clock Time 1 */
SFR_8BIT(RTCTIM1_L);                          /* Real Time Clock Time 1 */
SFR_8BIT(RTCTIM1_H);                          /* Real Time Clock Time 1 */
SFR_16BIT(RTCDATE);                           /* Real Time Clock Date */
SFR_8BIT(RTCDATE_L);                          /* Real Time Clock Date */
SFR_8BIT(RTCDATE_H);                          /* Real Time Clock Date */
SFR_16BIT(RTCYEAR);                           /* Real Time Clock Year */
SFR_8BIT(RTCYEAR_L);                          /* Real Time Clock Year */
SFR_8BIT(RTCYEAR_H);                          /* Real Time Clock Year */
SFR_16BIT(RTCAMINHR);                         /* Real Time Clock Alarm Min/Hour */
SFR_8BIT(RTCAMINHR_L);                        /* Real Time Clock Alarm Min/Hour */
SFR_8BIT(RTCAMINHR_H);                        /* Real Time Clock Alarm Min/Hour */
SFR_16BIT(RTCADOWDAY);                        /* Real Time Clock Alarm day of week/day */
SFR_8BIT(RTCADOWDAY_L);                       /* Real Time Clock Alarm day of week/day */
SFR_8BIT(RTCADOWDAY_H);                       /* Real Time Clock Alarm day of week/day */

#define RTCCTL0                RTCCTL01_L     /* Real Time Clock Control 0 */
#define RTCCTL1                RTCCTL01_H     /* Real Time Clock Control 1 */
#define RTCCTL2                RTCCTL23_L     /* Real Time Clock Control 2 */
#define RTCCTL3                RTCCTL23_H     /* Real Time Clock Control 3 */
#define RTCNT12                RTCTIM0
#define RTCNT34                RTCTIM1
#define RTCNT1                 RTCTIM0_L
#define RTCNT2                 RTCTIM0_H
#define RTCNT3                 RTCTIM1_L
#define RTCNT4                 RTCTIM1_H
#define RTCSEC                 RTCTIM0_L
#define RTCMIN                 RTCTIM0_H
#define RTCHOUR                RTCTIM1_L
#define RTCDOW                 RTCTIM1_H
#define RTCDAY                 RTCDATE_L
#define RTCMON                 RTCDATE_H
#define RTCYEARL               RTCYEAR_L
#define RTCYEARH               RTCYEAR_H
#define RT0PS                  RTCPS_L
#define RT1PS                  RTCPS_H
#define RTCAMIN                RTCAMINHR_L    /* Real Time Clock Alarm Min */
#define RTCAHOUR               RTCAMINHR_H    /* Real Time Clock Alarm Hour */
#define RTCADOW                RTCADOWDAY_L   /* Real Time Clock Alarm day of week */
#define RTCADAY                RTCADOWDAY_H   /* Real Time Clock Alarm day */

/* RTCCTL01 Control Bits */
#define RTCBCD                 (0x8000)       /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD                (0x4000)       /* RTC Hold */
#define RTCMODE                (0x2000)       /* RTC Mode 0:Counter / 1: Calendar */
#define RTCRDY                 (0x1000)       /* RTC Ready */
#define RTCSSEL1               (0x0800)       /* RTC Source Select 1 */
#define RTCSSEL0               (0x0400)       /* RTC Source Select 0 */
#define RTCTEV1                (0x0200)       /* RTC Time Event 1 */
#define RTCTEV0                (0x0100)       /* RTC Time Event 0 */
//#define Reserved          (0x0080)
#define RTCTEVIE               (0x0040)       /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE                 (0x0020)       /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE               (0x0010)       /* RTC Ready Interrupt Enable Flag */
//#define Reserved          (0x0008)
#define RTCTEVIFG              (0x0004)       /* RTC Time Event Interrupt Flag */
#define RTCAIFG                (0x0002)       /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG              (0x0001)       /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
//#define Reserved          (0x0080)
#define RTCTEVIE_L             (0x0040)       /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE_L               (0x0020)       /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE_L             (0x0010)       /* RTC Ready Interrupt Enable Flag */
//#define Reserved          (0x0008)
#define RTCTEVIFG_L            (0x0004)       /* RTC Time Event Interrupt Flag */
#define RTCAIFG_L              (0x0002)       /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG_L            (0x0001)       /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
#define RTCBCD_H               (0x0080)       /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD_H              (0x0040)       /* RTC Hold */
#define RTCMODE_H              (0x0020)       /* RTC Mode 0:Counter / 1: Calendar */
#define RTCRDY_H               (0x0010)       /* RTC Ready */
#define RTCSSEL1_H             (0x0008)       /* RTC Source Select 1 */
#define RTCSSEL0_H             (0x0004)       /* RTC Source Select 0 */
#define RTCTEV1_H              (0x0002)       /* RTC Time Event 1 */
#define RTCTEV0_H              (0x0001)       /* RTC Time Event 0 */
//#define Reserved          (0x0080)
//#define Reserved          (0x0008)

#define RTCSSEL_0              (0x0000)       /* RTC Source Select ACLK */
#define RTCSSEL_1              (0x0400)       /* RTC Source Select SMCLK */
#define RTCSSEL_2              (0x0800)       /* RTC Source Select RT1PS */
#define RTCSSEL_3              (0x0C00)       /* RTC Source Select RT1PS */
#define RTCSSEL__ACLK          (0x0000)       /* RTC Source Select ACLK */
#define RTCSSEL__SMCLK         (0x0400)       /* RTC Source Select SMCLK */
#define RTCSSEL__RT1PS         (0x0800)       /* RTC Source Select RT1PS */
#define RTCTEV_0               (0x0000)       /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1               (0x0100)       /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2               (0x0200)       /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3               (0x0300)       /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN            (0x0000)       /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR           (0x0100)       /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__0000           (0x0200)       /* RTC Time Event: 2 (00:00 changed) */
#define RTCTEV__1200           (0x0300)       /* RTC Time Event: 3 (12:00 changed) */

/* RTCCTL23 Control Bits */
#define RTCCALF1               (0x0200)       /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0               (0x0100)       /* RTC Calibration Frequency Bit 0 */
#define RTCCALS                (0x0080)       /* RTC Calibration Sign */
//#define Reserved          (0x0040)
#define RTCCAL5                (0x0020)       /* RTC Calibration Bit 5 */
#define RTCCAL4                (0x0010)       /* RTC Calibration Bit 4 */
#define RTCCAL3                (0x0008)       /* RTC Calibration Bit 3 */
#define RTCCAL2                (0x0004)       /* RTC Calibration Bit 2 */
#define RTCCAL1                (0x0002)       /* RTC Calibration Bit 1 */
#define RTCCAL0                (0x0001)       /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALS_L              (0x0080)       /* RTC Calibration Sign */
//#define Reserved          (0x0040)
#define RTCCAL5_L              (0x0020)       /* RTC Calibration Bit 5 */
#define RTCCAL4_L              (0x0010)       /* RTC Calibration Bit 4 */
#define RTCCAL3_L              (0x0008)       /* RTC Calibration Bit 3 */
#define RTCCAL2_L              (0x0004)       /* RTC Calibration Bit 2 */
#define RTCCAL1_L              (0x0002)       /* RTC Calibration Bit 1 */
#define RTCCAL0_L              (0x0001)       /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALF1_H             (0x0002)       /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0_H             (0x0001)       /* RTC Calibration Frequency Bit 0 */
//#define Reserved          (0x0040)

#define RTCCALF_0              (0x0000)       /* RTC Calibration Frequency: No Output */
#define RTCCALF_1              (0x0100)       /* RTC Calibration Frequency: 512 Hz */
#define RTCCALF_2              (0x0200)       /* RTC Calibration Frequency: 256 Hz */
#define RTCCALF_3              (0x0300)       /* RTC Calibration Frequency: 1 Hz */

#define RTCAE                  (0x80)         /* Real Time Clock Alarm enable */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000)
#define RT0SSEL                (0x4000)       /* RTC Prescale Timer 0 Source Select 0:ACLK / 1:SMCLK */
#define RT0PSDIV2              (0x2000)       /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
#define RT0PSDIV1              (0x1000)       /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
#define RT0PSDIV0              (0x0800)       /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
#define RT0PSHOLD              (0x0100)       /* RTC Prescale Timer 0 Hold */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT0IP2                 (0x0010)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1                 (0x0008)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0                 (0x0004)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE                (0x0002)       /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG               (0x0001)       /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000)
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT0IP2_L               (0x0010)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1_L               (0x0008)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0_L               (0x0004)       /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE_L              (0x0002)       /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG_L             (0x0001)       /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x8000)
#define RT0SSEL_H              (0x0040)       /* RTC Prescale Timer 0 Source Select 0:ACLK / 1:SMCLK */
#define RT0PSDIV2_H            (0x0020)       /* RTC Prescale Timer 0 Clock Divide Bit: 2 */
#define RT0PSDIV1_H            (0x0010)       /* RTC Prescale Timer 0 Clock Divide Bit: 1 */
#define RT0PSDIV0_H            (0x0008)       /* RTC Prescale Timer 0 Clock Divide Bit: 0 */
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
#define RT0PSHOLD_H            (0x0001)       /* RTC Prescale Timer 0 Hold */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)

#define RT0IP_0                (0x0000)       /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1                (0x0004)       /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2                (0x0008)       /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3                (0x000C)       /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4                (0x0010)       /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5                (0x0014)       /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6                (0x0018)       /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7                (0x001C)       /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0PSDIV_0             (0x0000)       /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1             (0x0800)       /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2             (0x1000)       /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3             (0x1800)       /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4             (0x2000)       /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5             (0x2800)       /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6             (0x3000)       /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7             (0x3800)       /* RTC Prescale Timer 0 Clock Divide /256 */

/* RTCPS1CTL Control Bits */
#define RT1SSEL1               (0x8000)       /* RTC Prescale Timer 1 Source Select Bit 1 */
#define RT1SSEL0               (0x4000)       /* RTC Prescale Timer 1 Source Select Bit 0 */
#define RT1PSDIV2              (0x2000)       /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
#define RT1PSDIV1              (0x1000)       /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
#define RT1PSDIV0              (0x0800)       /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
#define RT1PSHOLD              (0x0100)       /* RTC Prescale Timer 1 Hold */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT1IP2                 (0x0010)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1                 (0x0008)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0                 (0x0004)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE                (0x0002)       /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG               (0x0001)       /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)
#define RT1IP2_L               (0x0010)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1_L               (0x0008)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0_L               (0x0004)       /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE_L              (0x0002)       /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG_L             (0x0001)       /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
#define RT1SSEL1_H             (0x0080)       /* RTC Prescale Timer 1 Source Select Bit 1 */
#define RT1SSEL0_H             (0x0040)       /* RTC Prescale Timer 1 Source Select Bit 0 */
#define RT1PSDIV2_H            (0x0020)       /* RTC Prescale Timer 1 Clock Divide Bit: 2 */
#define RT1PSDIV1_H            (0x0010)       /* RTC Prescale Timer 1 Clock Divide Bit: 1 */
#define RT1PSDIV0_H            (0x0008)       /* RTC Prescale Timer 1 Clock Divide Bit: 0 */
//#define Reserved          (0x0400)
//#define Reserved          (0x0200)
#define RT1PSHOLD_H            (0x0001)       /* RTC Prescale Timer 1 Hold */
//#define Reserved          (0x0080)
//#define Reserved          (0x0040)
//#define Reserved          (0x0020)

#define RT1IP_0                (0x0000)       /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1                (0x0004)       /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2                (0x0008)       /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3                (0x000C)       /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4                (0x0010)       /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5                (0x0014)       /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6                (0x0018)       /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7                (0x001C)       /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1PSDIV_0             (0x0000)       /* RTC Prescale Timer 1 Clock Divide /2 */
#define RT1PSDIV_1             (0x0800)       /* RTC Prescale Timer 1 Clock Divide /4 */
#define RT1PSDIV_2             (0x1000)       /* RTC Prescale Timer 1 Clock Divide /8 */
#define RT1PSDIV_3             (0x1800)       /* RTC Prescale Timer 1 Clock Divide /16 */
#define RT1PSDIV_4             (0x2000)       /* RTC Prescale Timer 1 Clock Divide /32 */
#define RT1PSDIV_5             (0x2800)       /* RTC Prescale Timer 1 Clock Divide /64 */
#define RT1PSDIV_6             (0x3000)       /* RTC Prescale Timer 1 Clock Divide /128 */
#define RT1PSDIV_7             (0x3800)       /* RTC Prescale Timer 1 Clock Divide /256 */

#define RT1SSEL_0              (0x0000)       /* RTC Prescale Timer Source Select ACLK */
#define RT1SSEL_1              (0x4000)       /* RTC Prescale Timer Source Select SMCLK */
#define RT1SSEL_2              (0x8000)       /* RTC Prescale Timer Source Select RT0PS */
#define RT1SSEL_3              (0xC000)       /* RTC Prescale Timer Source Select RT0PS */

/* RTC Definitions */
#define RTCIV_NONE             (0x0000)       /* No Interrupt pending */
#define RTCIV_RTCRDYIFG        (0x0002)       /* RTC ready: RTCRDYIFG */
#define RTCIV_RTCTEVIFG        (0x0004)       /* RTC interval timer: RTCTEVIFG */
#define RTCIV_RTCAIFG          (0x0006)       /* RTC user alarm: RTCAIFG */
#define RTCIV_RT0PSIFG         (0x0008)       /* RTC prescaler 0: RT0PSIFG */
#define RTCIV_RT1PSIFG         (0x000A)       /* RTC prescaler 1: RT1PSIFG */

/* Legacy Definitions */
#define RTC_NONE               (0x0000)       /* No Interrupt pending */
#define RTC_RTCRDYIFG          (0x0002)       /* RTC ready: RTCRDYIFG */
#define RTC_RTCTEVIFG          (0x0004)       /* RTC interval timer: RTCTEVIFG */
#define RTC_RTCAIFG            (0x0006)       /* RTC user alarm: RTCAIFG */
#define RTC_RT0PSIFG           (0x0008)       /* RTC prescaler 0: RT0PSIFG */
#define RTC_RT1PSIFG           (0x000A)       /* RTC prescaler 1: RT1PSIFG */

#define RTC_A_VECTOR           RTC_VECTOR     /* 0xFFDC RTC */

/************************************************************
* SFR - Special Function Register Module
************************************************************/
#define __MSP430_HAS_SFR__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100
#define SFR_BASE               __MSP430_BASEADDRESS_SFR__

SFR_16BIT(SFRIE1);                            /* Interrupt Enable 1 */
SFR_8BIT(SFRIE1_L);                           /* Interrupt Enable 1 */
SFR_8BIT(SFRIE1_H);                           /* Interrupt Enable 1 */

/* SFRIE1 Control Bits */
#define WDTIE                  (0x0001)       /* WDT Interrupt Enable */
#define OFIE                   (0x0002)       /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE                  (0x0008)       /* Vacant Memory Interrupt Enable */
#define NMIIE                  (0x0010)       /* NMI Interrupt Enable */
#define ACCVIE                 (0x0020)       /* Flash Access Violation Interrupt Enable */
#define JMBINIE                (0x0040)       /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE               (0x0080)       /* JTAG Mail Box output Interrupt Enable */

#define WDTIE_L                (0x0001)       /* WDT Interrupt Enable */
#define OFIE_L                 (0x0002)       /* Osc Fault Enable */
//#define Reserved          (0x0004)
#define VMAIE_L                (0x0008)       /* Vacant Memory Interrupt Enable */
#define NMIIE_L                (0x0010)       /* NMI Interrupt Enable */
#define ACCVIE_L               (0x0020)       /* Flash Access Violation Interrupt Enable */
#define JMBINIE_L              (0x0040)       /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L             (0x0080)       /* JTAG Mail Box output Interrupt Enable */

SFR_16BIT(SFRIFG1);                           /* Interrupt Flag 1 */
SFR_8BIT(SFRIFG1_L);                          /* Interrupt Flag 1 */
SFR_8BIT(SFRIFG1_H);                          /* Interrupt Flag 1 */
/* SFRIFG1 Control Bits */
#define WDTIFG                 (0x0001)       /* WDT Interrupt Flag */
#define OFIFG                  (0x0002)       /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG                 (0x0008)       /* Vacant Memory Interrupt Flag */
#define NMIIFG                 (0x0010)       /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG               (0x0040)       /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG              (0x0080)       /* JTAG Mail Box output Interrupt Flag */

#define WDTIFG_L               (0x0001)       /* WDT Interrupt Flag */
#define OFIFG_L                (0x0002)       /* Osc Fault Flag */
//#define Reserved          (0x0004)
#define VMAIFG_L               (0x0008)       /* Vacant Memory Interrupt Flag */
#define NMIIFG_L               (0x0010)       /* NMI Interrupt Flag */
//#define Reserved          (0x0020)
#define JMBINIFG_L             (0x0040)       /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L            (0x0080)       /* JTAG Mail Box output Interrupt Flag */

SFR_16BIT(SFRRPCR);                           /* RESET Pin Control Register */
SFR_8BIT(SFRRPCR_L);                          /* RESET Pin Control Register */
SFR_8BIT(SFRRPCR_H);                          /* RESET Pin Control Register */
/* SFRRPCR Control Bits */
#define SYSNMI                 (0x0001)       /* NMI select */
#define SYSNMIIES              (0x0002)       /* NMI edge select */
#define SYSRSTUP               (0x0004)       /* RESET Pin pull down/up select */
#define SYSRSTRE               (0x0008)       /* RESET Pin Resistor enable */

#define SYSNMI_L               (0x0001)       /* NMI select */
#define SYSNMIIES_L            (0x0002)       /* NMI edge select */
#define SYSRSTUP_L             (0x0004)       /* RESET Pin pull down/up select */
#define SYSRSTRE_L             (0x0008)       /* RESET Pin Resistor enable */

/************************************************************
* SYS - System Module
************************************************************/
#define __MSP430_HAS_SYS__                    /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0180
#define SYS_BASE               __MSP430_BASEADDRESS_SYS__

SFR_16BIT(SYSCTL);                            /* System control */
SFR_8BIT(SYSCTL_L);                           /* System control */
SFR_8BIT(SYSCTL_H);                           /* System control */
SFR_16BIT(SYSBSLC);                           /* Boot strap configuration area */
SFR_8BIT(SYSBSLC_L);                          /* Boot strap configuration area */
SFR_8BIT(SYSBSLC_H);                          /* Boot strap configuration area */
SFR_16BIT(SYSJMBC);                           /* JTAG mailbox control */
SFR_8BIT(SYSJMBC_L);                          /* JTAG mailbox control */
SFR_8BIT(SYSJMBC_H);                          /* JTAG mailbox control */
SFR_16BIT(SYSJMBI0);                          /* JTAG mailbox input 0 */
SFR_8BIT(SYSJMBI0_L);                         /* JTAG mailbox input 0 */
SFR_8BIT(SYSJMBI0_H);                         /* JTAG mailbox input 0 */
SFR_16BIT(SYSJMBI1);                          /* JTAG mailbox input 1 */
SFR_8BIT(SYSJMBI1_L);                         /* JTAG mailbox input 1 */
SFR_8BIT(SYSJMBI1_H);                         /* JTAG mailbox input 1 */
SFR_16BIT(SYSJMBO0);                          /* JTAG mailbox output 0 */
SFR_8BIT(SYSJMBO0_L);                         /* JTAG mailbox output 0 */
SFR_8BIT(SYSJMBO0_H);                         /* JTAG mailbox output 0 */
SFR_16BIT(SYSJMBO1);                          /* JTAG mailbox output 1 */
SFR_8BIT(SYSJMBO1_L);                         /* JTAG mailbox output 1 */
SFR_8BIT(SYSJMBO1_H);                         /* JTAG mailbox output 1 */

SFR_16BIT(SYSBERRIV);                         /* Bus Error vector generator */
SFR_8BIT(SYSBERRIV_L);                        /* Bus Error vector generator */
SFR_8BIT(SYSBERRIV_H);                        /* Bus Error vector generator */
SFR_16BIT(SYSUNIV);                           /* User NMI vector generator */
SFR_8BIT(SYSUNIV_L);                          /* User NMI vector generator */
SFR_8BIT(SYSUNIV_H);                          /* User NMI vector generator */
SFR_16BIT(SYSSNIV);                           /* System NMI vector generator */
SFR_8BIT(SYSSNIV_L);                          /* System NMI vector generator */
SFR_8BIT(SYSSNIV_H);                          /* System NMI vector generator */
SFR_16BIT(SYSRSTIV);                          /* Reset vector generator */
SFR_8BIT(SYSRSTIV_L);                         /* Reset vector generator */
SFR_8BIT(SYSRSTIV_H);                         /* Reset vector generator */

/* SYSCTL Control Bits */
#define SYSRIVECT              (0x0001)       /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE               (0x0004)       /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND              (0x0010)       /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN             (0x0020)       /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSCTL Control Bits */
#define SYSRIVECT_L            (0x0001)       /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002)  /* SYS - Reserved */
#define SYSPMMPE_L             (0x0004)       /* SYS - PMM access protect */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
#define SYSBSLIND_L            (0x0010)       /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L           (0x0020)       /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0            (0x0001)       /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1            (0x0002)       /* SYS - BSL Protection Size 1 */
#define SYSBSLR                (0x0004)       /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF              (0x4000)       /* SYS - BSL Memory disabled */
#define SYSBSLPE               (0x8000)       /* SYS - BSL Memory protection enabled */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L          (0x0001)       /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L          (0x0002)       /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L              (0x0004)       /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
//#define RESERVED            (0x0008)  /* SYS - Reserved */
//#define RESERVED            (0x0010)  /* SYS - Reserved */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
//#define RESERVED            (0x0040)  /* SYS - Reserved */
//#define RESERVED            (0x0080)  /* SYS - Reserved */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
#define SYSBSLOFF_H            (0x0040)       /* SYS - BSL Memory disabled */
#define SYSBSLPE_H             (0x0080)       /* SYS - BSL Memory protection enabled */

/* SYSJMBC Control Bits */
#define JMBIN0FG               (0x0001)       /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG               (0x0002)       /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG              (0x0004)       /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG              (0x0008)       /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE                (0x0010)       /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF             (0x0040)       /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF             (0x0080)       /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
#define JMBIN0FG_L             (0x0001)       /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L             (0x0002)       /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L            (0x0004)       /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L            (0x0008)       /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L              (0x0010)       /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020)  /* SYS - Reserved */
#define JMBCLR0OFF_L           (0x0040)       /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L           (0x0080)       /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100)  /* SYS - Reserved */
//#define RESERVED            (0x0200)  /* SYS - Reserved */
//#define RESERVED            (0x0400)  /* SYS - Reserved */
//#define RESERVED            (0x0800)  /* SYS - Reserved */
//#define RESERVED            (0x1000)  /* SYS - Reserved */
//#define RESERVED            (0x2000)  /* SYS - Reserved */
//#define RESERVED            (0x4000)  /* SYS - Reserved */
//#define RESERVED            (0x8000)  /* SYS - Reserved */


/* SYSUNIV Definitions */
#define SYSUNIV_NONE           (0x0000)       /* No Interrupt pending */
#define SYSUNIV_NMIIFG         (0x0002)       /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG          (0x0004)       /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_ACCVIFG        (0x0006)       /* SYSUNIV : Access Violation - ACCVIFG */
#define SYSUNIV_SYSBERRIV      (0x0008)       /* SYSUNIV : Bus Error - SYSBERRIV */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE           (0x0000)       /* No Interrupt pending */
#define SYSSNIV_SVMLIFG        (0x0002)       /* SYSSNIV : SVMLIFG */
#define SYSSNIV_SVMHIFG        (0x0004)       /* SYSSNIV : SVMHIFG */
#define SYSSNIV_DLYLIFG        (0x0006)       /* SYSSNIV : DLYLIFG */
#define SYSSNIV_DLYHIFG        (0x0008)       /* SYSSNIV : DLYHIFG */
#define SYSSNIV_VMAIFG         (0x000A)       /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG       (0x000C)       /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG      (0x000E)       /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_VLRLIFG        (0x0010)       /* SYSSNIV : VLRLIFG */
#define SYSSNIV_VLRHIFG        (0x0012)       /* SYSSNIV : VLRHIFG */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE          (0x0000)       /* No Interrupt pending */
#define SYSRSTIV_BOR           (0x0002)       /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI        (0x0004)       /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR         (0x0006)       /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU        (0x0008)       /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV         (0x000A)       /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSL          (0x000C)       /* SYSRSTIV : SVSL */
#define SYSRSTIV_SVSH          (0x000E)       /* SYSRSTIV : SVSH */
#define SYSRSTIV_SVML_OVP      (0x0010)       /* SYSRSTIV : SVML_OVP */
#define SYSRSTIV_SVMH_OVP      (0x0012)       /* SYSRSTIV : SVMH_OVP */
#define SYSRSTIV_DOPOR         (0x0014)       /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO         (0x0016)       /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY        (0x0018)       /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_KEYV          (0x001A)       /* SYSRSTIV : Flash Key violation */
#define SYSRSTIV_PLLUL         (0x001C)       /* SYSRSTIV : PLL unlock */
#define SYSRSTIV_PERF          (0x001E)       /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMKEY        (0x0020)       /* SYSRSTIV : PMMKEY violation */

#define SYSRSTIV_PSSKEY        (0x0020)       /* SYSRSTIV : Legacy: PMMKEY violation */

/************************************************************
* Timer0_A5
************************************************************/
#define __MSP430_HAS_T0A5__                   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A5__ 0x0340
#define TIMER_A0_BASE          __MSP430_BASEADDRESS_T0A5__

SFR_16BIT(TA0CTL);                            /* Timer0_A5 Control */
SFR_16BIT(TA0CCTL0);                          /* Timer0_A5 Capture/Compare Control 0 */
SFR_16BIT(TA0CCTL1);                          /* Timer0_A5 Capture/Compare Control 1 */
SFR_16BIT(TA0CCTL2);                          /* Timer0_A5 Capture/Compare Control 2 */
SFR_16BIT(TA0CCTL3);                          /* Timer0_A5 Capture/Compare Control 3 */
SFR_16BIT(TA0CCTL4);                          /* Timer0_A5 Capture/Compare Control 4 */
SFR_16BIT(TA0R);                              /* Timer0_A5 */
SFR_16BIT(TA0CCR0);                           /*   // Internal timer output (10.5 kHz) to Radio TX
  // NOTE: SMARTF_CC430 IOCFG0 should = 0x2E. When IOCFG0 = 0x2D,
  // asynchronous data into the radio is taken from GDO0 and not the timer.
  TA1CCR0 = 50;
  TA1CCR1 = 50;

  TA1CCTL0 = OUTMOD_4;
  TA1CCTL1 = OUTMOD_4;
  TA1CTL = TASSEL__SMCLK + MC_1 + TACLR; Capture/Compare 0 */
SFR_16BIT(TA0CCR1);                           /* Timer0_A5 Capture/Compare 1 */
SFR_16BIT(TA0CCR2);                           /* Timer0_A5 Capture/Compare 2 */
SFR_16BIT(TA0CCR3);                           /* Timer0_A5 Capture/Compare 3 */
SFR_16BIT(TA0CCR4);                           /* Timer0_A5 Capture/Compare 4 */
SFR_16BIT(TA0IV);                             /* Timer0_A5 Interrupt Vector Word */
SFR_16BIT(TA0EX0);                            /* Timer0_A5 Expansion Register 0 */

/* TAxCTL Control Bits */
#define TASSEL1                (0x0200)       /* Timer A clock source select 1 */
#define TASSEL0                (0x0100)       /* Timer A clock source select 0 */
#define ID1                    (0x0080)       /* Timer A clock input divider 1 */
#define ID0                    (0x0040)       /* Timer A clock input divider 0 */
#define MC1                    (0x0020)       /* Timer A mode control 1 */
#define MC0                    (0x0010)       /* Timer A mode control 0 */
#define TACLR                  (0x0004)       /* Timer A counter clear */
#define TAIE                   (0x0002)       /* Timer A counter interrupt enable */
#define TAIFG                  (0x0001)       /* Timer A counter interrupt flag */

#define MC_0                   (0*0x10u)      /* Timer A mode control: 0 - Stop */
#define MC_1                   (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                   (2*0x10u)      /* Timer A mode control: 2 - Continuous up */
#define MC_3                   (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID_0                   (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID_1                   (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID_2                   (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID_3                   (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL_0               (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1               (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2               (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3               (3*0x100u)     /* Timer A clock source select: 3 - INCLK */
#define MC__STOP               (0*0x10u)      /* Timer A mode control: 0 - Stop */
#define MC__UP                 (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINUOUS         (2*0x10u)      /* Timer A mode control: 2 - Continuous up */
#define MC__CONTINOUS          (2*0x10u)      /* Legacy define */
#define MC__UPDOWN             (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID__1                  (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID__2                  (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID__4                  (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID__8                  (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK          (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK           (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK          (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK          (3*0x100u)     /* Timer A clock source select: 3 - INCLK */

/* TAxCCTLx Control Bits */
#define CM1                    (0x8000)       /* Capture mode 1 */
#define CM0                    (0x4000)       /* Capture mode 0 */
#define CCIS1                  (0x2000)       /* Capture input select 1 */
#define CCIS0                  (0x1000)       /* Capture input select 0 */
#define SCS                    (0x0800)       /* Capture sychronize */
#define SCCI                   (0x0400)       /* Latched capture signal (read) */
#define CAP                    (0x0100)       /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2                (0x0080)       /* Output mode 2 */
#define OUTMOD1                (0x0040)       /* Output mode 1 */
#define OUTMOD0                (0x0020)       /* Output mode 0 */
#define CCIE                   (0x0010)       /* Capture/compare interrupt enable */
#define CCI                    (0x0008)       /* Capture input signal (read) */
#define OUT                    (0x0004)       /* PWM Output signal if output mode 0 */
#define COV                    (0x0002)       /* Capture/compare overflow flag */
#define CCIFG                  (0x0001)       /* Capture/compare interrupt flag */

#define OUTMOD_0               (0*0x20u)      /* PWM output mode: 0 - output only */
#define OUTMOD_1               (1*0x20u)      /* PWM output mode: 1 - set */
#define OUTMOD_2               (2*0x20u)      /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3               (3*0x20u)      /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4               (4*0x20u)      /* PWM output mode: 4 - toggle */
#define OUTMOD_5               (5*0x20u)      /* PWM output mode: 5 - Reset */
#define OUTMOD_6               (6*0x20u)      /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7               (7*0x20u)      /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0                 (0*0x1000u)    /* Capture input select: 0 - CCIxA */
#define CCIS_1                 (1*0x1000u)    /* Capture input select: 1 - CCIxB */
#define CCIS_2                 (2*0x1000u)    /* Capture input select: 2 - GND */
#define CCIS_3                 (3*0x1000u)    /* Capture input select: 3 - Vcc */
#define CM_0                   (0*0x4000u)    /* Capture mode: 0 - disabled */
#define CM_1                   (1*0x4000u)    /* Capture mode: 1 - pos. edge */
#define CM_2                   (2*0x4000u)    /* Capture mode: 1 - neg. edge */
#define CM_3                   (3*0x4000u)    /* Capture mode: 1 - both edges */

/* TAxEX0 Control Bits */
#define TAIDEX0                (0x0001)       /* Timer A Input divider expansion Bit: 0 */
#define TAIDEX1                (0x0002)       /* Timer A Input divider expansion Bit: 1 */
#define TAIDEX2                (0x0004)       /* Timer A Input divider expansion Bit: 2 */

#define TAIDEX_0               (0*0x0001u)    /* Timer A Input divider expansion : /1 */
#define TAIDEX_1               (1*0x0001u)    /* Timer A Input divider expansion : /2 */
#define TAIDEX_2               (2*0x0001u)    /* Timer A Input divider expansion : /3 */
#define TAIDEX_3               (3*0x0001u)    /* Timer A Input divider expansion : /4 */
#define TAIDEX_4               (4*0x0001u)    /* Timer A Input divider expansion : /5 */
#define TAIDEX_5               (5*0x0001u)    /* Timer A Input divider expansion : /6 */
#define TAIDEX_6               (6*0x0001u)    /* Timer A Input divider expansion : /7 */
#define TAIDEX_7               (7*0x0001u)    /* Timer A Input divider expansion : /8 */

/* T0A5IV Definitions */
#define TA0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA0IV_TACCR1           (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2           (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_TACCR3           (0x0006)       /* TA0CCR3_CCIFG */
#define TA0IV_TACCR4           (0x0008)       /* TA0CCR4_CCIFG */
#define TA0IV_5                (0x000A)       /* Reserved */
#define TA0IV_6                (0x000C)       /* Reserved */
#define TA0IV_TAIFG            (0x000E)       /* TA0IFG */

/* Legacy Defines */
#define TA0IV_TA0CCR1          (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2          (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_TA0CCR3          (0x0006)       /* TA0CCR3_CCIFG */
#define TA0IV_TA0CCR4          (0x0008)       /* TA0CCR4_CCIFG */
#define TA0IV_TA0IFG           (0x000E)       /* TA0IFG */

/************************************************************
* Timer1_A3
************************************************************/
#define __MSP430_HAS_T1A3__                   /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0380
#define TIMER_A1_BASE          __MSP430_BASEADDRESS_T1A3__

SFR_16BIT(TA1CTL);                            /* Timer1_A3 Control */
SFR_16BIT(TA1CCTL0);                          /* Timer1_A3 Capture/Compare Control 0 */
SFR_16BIT(TA1CCTL1);                          /* Timer1_A3 Capture/Compare Control 1 */
SFR_16BIT(TA1CCTL2);                          /* Timer1_A3 Capture/Compare Control 2 */
SFR_16BIT(TA1R);                              /* Timer1_A3 */
SFR_16BIT(TA1CCR0);                           /* Timer1_A3 Capture/Compare 0 */
SFR_16BIT(TA1CCR1);                           /* Timer1_A3 Capture/Compare 1 */
SFR_16BIT(TA1CCR2);                           /* Timer1_A3 Capture/Compare 2 */
SFR_16BIT(TA1IV);                             /* Timer1_A3 Interrupt Vector Word */
SFR_16BIT(TA1EX0);                            /* Timer1_A3 Expansion Register 0 */

/* Bits are already defined within the Timer0_Ax */

/* TA1IV Definitions */
#define TA1IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA1IV_TACCR1           (0x0002)       /* TA1CCR1_CCIFG */
#define TA1IV_TACCR2           (0x0004)       /* TA1CCR2_CCIFG */
#define TA1IV_3                (0x0006)       /* Reserved */
#define TA1IV_4                (0x0008)       /* Reserved */
#define TA1IV_5                (0x000A)       /* Reserved */
#define TA1IV_6                (0x000C)       /* Reserved */
#define TA1IV_TAIFG            (0x000E)       /* TA1IFG */

/* Legacy Defines */
#define TA1IV_TA1CCR1          (0x0002)       /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2          (0x0004)       /* TA1CCR2_CCIFG */
#define TA1IV_TA1IFG           (0x000E)       /* TA1IFG */

/************************************************************
* UNIFIED CLOCK SYSTEM FOR Radio Devices
************************************************************/
#define __MSP430_HAS_UCS_RF__                 /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_UCS_RF__ 0x0160
#define UCS_BASE               __MSP430_BASEADDRESS_UCS_RF__

SFR_16BIT(UCSCTL0);                           /* UCS Control Register 0 */
SFR_8BIT(UCSCTL0_L);                          /* UCS Control Register 0 */
SFR_8BIT(UCSCTL0_H);                          /* UCS Control Register 0 */
SFR_16BIT(UCSCTL1);                           /* UCS Control Register 1 */
SFR_8BIT(UCSCTL1_L);                          /* UCS Control Register 1 */
SFR_8BIT(UCSCTL1_H);                          /* UCS Control Register 1 */
SFR_16BIT(UCSCTL2);                           /* UCS Control Register 2 */
SFR_8BIT(UCSCTL2_L);                          /* UCS Control Register 2 */
SFR_8BIT(UCSCTL2_H);                          /* UCS Control Register 2 */
SFR_16BIT(UCSCTL3);                           /* UCS Control Register 3 */
SFR_8BIT(UCSCTL3_L);                          /* UCS Control Register 3 */
SFR_8BIT(UCSCTL3_H);                          /* UCS Control Register 3 */
SFR_16BIT(UCSCTL4);                           /* UCS Control Register 4 */
SFR_8BIT(UCSCTL4_L);                          /* UCS Control Register 4 */
SFR_8BIT(UCSCTL4_H);                          /* UCS Control Register 4 */
SFR_16BIT(UCSCTL5);                           /* UCS Control Register 5 */
SFR_8BIT(UCSCTL5_L);                          /* UCS Control Register 5 */
SFR_8BIT(UCSCTL5_H);                          /* UCS Control Register 5 */
SFR_16BIT(UCSCTL6);                           /* UCS Control Register 6 */
SFR_8BIT(UCSCTL6_L);                          /* UCS Control Register 6 */
SFR_8BIT(UCSCTL6_H);                          /* UCS Control Register 6 */
SFR_16BIT(UCSCTL7);                           /* UCS Control Register 7 */
SFR_8BIT(UCSCTL7_L);                          /* UCS Control Register 7 */
SFR_8BIT(UCSCTL7_H);                          /* UCS Control Register 7 */
SFR_16BIT(UCSCTL8);                           /* UCS Control Register 8 */
SFR_8BIT(UCSCTL8_L);                          /* UCS Control Register 8 */
SFR_8BIT(UCSCTL8_H);                          /* UCS Control Register 8 */

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001)    /* RESERVED */
//#define RESERVED            (0x0002)    /* RESERVED */
//#define RESERVED            (0x0004)    /* RESERVED */
#define MOD0                   (0x0008)       /* Modulation Bit Counter Bit : 0 */
#define MOD1                   (0x0010)       /* Modulation Bit Counter Bit : 1 */
#define MOD2                   (0x0020)       /* Modulation Bit Counter Bit : 2 */
#define MOD3                   (0x0040)       /* Modulation Bit Counter Bit : 3 */
#define MOD4                   (0x0080)       /* Modulation Bit Counter Bit : 4 */
#define DCO0                   (0x0100)       /* DCO TAP Bit : 0 */
#define DCO1                   (0x0200)       /* DCO TAP Bit : 1 */
#define DCO2                   (0x0400)       /* DCO TAP Bit : 2 */
#define DCO3                   (0x0800)       /* DCO TAP Bit : 3 */
#define DCO4                   (0x1000)       /* DCO TAP Bit : 4 */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001)    /* RESERVED */
//#define RESERVED            (0x0002)    /* RESERVED */
//#define RESERVED            (0x0004)    /* RESERVED */
#define MOD0_L                 (0x0008)       /* Modulation Bit Counter Bit : 0 */
#define MOD1_L                 (0x0010)       /* Modulation Bit Counter Bit : 1 */
#define MOD2_L                 (0x0020)       /* Modulation Bit Counter Bit : 2 */
#define MOD3_L                 (0x0040)       /* Modulation Bit Counter Bit : 3 */
#define MOD4_L                 (0x0080)       /* Modulation Bit Counter Bit : 4 */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL0 Control Bits */
//#define RESERVED            (0x0001)    /* RESERVED */
//#define RESERVED            (0x0002)    /* RESERVED */
//#define RESERVED            (0x0004)    /* RESERVED */
#define DCO0_H                 (0x0001)       /* DCO TAP Bit : 0 */
#define DCO1_H                 (0x0002)       /* DCO TAP Bit : 1 */
#define DCO2_H                 (0x0004)       /* DCO TAP Bit : 2 */
#define DCO3_H                 (0x0008)       /* DCO TAP Bit : 3 */
#define DCO4_H                 (0x0010)       /* DCO TAP Bit : 4 */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL1 Control Bits */
#define DISMOD                 (0x0001)       /* Disable Modulation */
//#define RESERVED            (0x0002)    /* RESERVED */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DCORSEL0               (0x0010)       /* DCO Freq. Range Select Bit : 0 */
#define DCORSEL1               (0x0020)       /* DCO Freq. Range Select Bit : 1 */
#define DCORSEL2               (0x0040)       /* DCO Freq. Range Select Bit : 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL1 Control Bits */
#define DISMOD_L               (0x0001)       /* Disable Modulation */
//#define RESERVED            (0x0002)    /* RESERVED */
//#define RESERVED            (0x0004)    /* RESERVED */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DCORSEL0_L             (0x0010)       /* DCO Freq. Range Select Bit : 0 */
#define DCORSEL1_L             (0x0020)       /* DCO Freq. Range Select Bit : 1 */
#define DCORSEL2_L             (0x0040)       /* DCO Freq. Range Select Bit : 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define DCORSEL_0              (0x0000)       /* DCO RSEL 0 */
#define DCORSEL_1              (0x0010)       /* DCO RSEL 1 */
#define DCORSEL_2              (0x0020)       /* DCO RSEL 2 */
#define DCORSEL_3              (0x0030)       /* DCO RSEL 3 */
#define DCORSEL_4              (0x0040)       /* DCO RSEL 4 */
#define DCORSEL_5              (0x0050)       /* DCO RSEL 5 */
#define DCORSEL_6              (0x0060)       /* DCO RSEL 6 */
#define DCORSEL_7              (0x0070)       /* DCO RSEL 7 */

/* UCSCTL2 Control Bits */
#define FLLN0                  (0x0001)       /* FLL Multipier Bit : 0 */
#define FLLN1                  (0x0002)       /* FLL Multipier Bit : 1 */
#define FLLN2                  (0x0004)       /* FLL Multipier Bit : 2 */
#define FLLN3                  (0x0008)       /* FLL Multipier Bit : 3 */
#define FLLN4                  (0x0010)       /* FLL Multipier Bit : 4 */
#define FLLN5                  (0x0020)       /* FLL Multipier Bit : 5 */
#define FLLN6                  (0x0040)       /* FLL Multipier Bit : 6 */
#define FLLN7                  (0x0080)       /* FLL Multipier Bit : 7 */
#define FLLN8                  (0x0100)       /* FLL Multipier Bit : 8 */
#define FLLN9                  (0x0200)       /* FLL Multipier Bit : 9 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
#define FLLD0                  (0x1000)       /* Loop Divider Bit : 0 */
#define FLLD1                  (0x2000)       /* Loop Divider Bit : 1 */
#define FLLD2                  (0x4000)       /* Loop Divider Bit : 1 */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL2 Control Bits */
#define FLLN0_L                (0x0001)       /* FLL Multipier Bit : 0 */
#define FLLN1_L                (0x0002)       /* FLL Multipier Bit : 1 */
#define FLLN2_L                (0x0004)       /* FLL Multipier Bit : 2 */
#define FLLN3_L                (0x0008)       /* FLL Multipier Bit : 3 */
#define FLLN4_L                (0x0010)       /* FLL Multipier Bit : 4 */
#define FLLN5_L                (0x0020)       /* FLL Multipier Bit : 5 */
#define FLLN6_L                (0x0040)       /* FLL Multipier Bit : 6 */
#define FLLN7_L                (0x0080)       /* FLL Multipier Bit : 7 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL2 Control Bits */
#define FLLN8_H                (0x0001)       /* FLL Multipier Bit : 8 */
#define FLLN9_H                (0x0002)       /* FLL Multipier Bit : 9 */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
#define FLLD0_H                (0x0010)       /* Loop Divider Bit : 0 */
#define FLLD1_H                (0x0020)       /* Loop Divider Bit : 1 */
#define FLLD2_H                (0x0040)       /* Loop Divider Bit : 1 */
//#define RESERVED            (0x8000)    /* RESERVED */

#define FLLD_0                 (0x0000)       /* Multiply Selected Loop Freq. 1 */
#define FLLD_1                 (0x1000)       /* Multiply Selected Loop Freq. 2 */
#define FLLD_2                 (0x2000)       /* Multiply Selected Loop Freq. 4 */
#define FLLD_3                 (0x3000)       /* Multiply Selected Loop Freq. 8 */
#define FLLD_4                 (0x4000)       /* Multiply Selected Loop Freq. 16 */
#define FLLD_5                 (0x5000)       /* Multiply Selected Loop Freq. 32 */
#define FLLD_6                 (0x6000)       /* Multiply Selected Loop Freq. 32 */
#define FLLD_7                 (0x7000)       /* Multiply Selected Loop Freq. 32 */
#define FLLD__1                (0x0000)       /* Multiply Selected Loop Freq. By 1 */
#define FLLD__2                (0x1000)       /* Multiply Selected Loop Freq. By 2 */
#define FLLD__4                (0x2000)       /* Multiply Selected Loop Freq. By 4 */
#define FLLD__8                (0x3000)       /* Multiply Selected Loop Freq. By 8 */
#define FLLD__16               (0x4000)       /* Multiply Selected Loop Freq. By 16 */
#define FLLD__32               (0x5000)       /* Multiply Selected Loop Freq. By 32 */

/* UCSCTL3 Control Bits */
#define FLLREFDIV0             (0x0001)       /* Reference Divider Bit : 0 */
#define FLLREFDIV1             (0x0002)       /* Reference Divider Bit : 1 */
#define FLLREFDIV2             (0x0004)       /* Reference Divider Bit : 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELREF0                (0x0010)       /* FLL Reference Clock Select Bit : 0 */
#define SELREF1                (0x0020)       /* FLL Reference Clock Select Bit : 1 */
#define SELREF2                (0x0040)       /* FLL Reference Clock Select Bit : 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL3 Control Bits */
#define FLLREFDIV0_L           (0x0001)       /* Reference Divider Bit : 0 */
#define FLLREFDIV1_L           (0x0002)       /* Reference Divider Bit : 1 */
#define FLLREFDIV2_L           (0x0004)       /* Reference Divider Bit : 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELREF0_L              (0x0010)       /* FLL Reference Clock Select Bit : 0 */
#define SELREF1_L              (0x0020)       /* FLL Reference Clock Select Bit : 1 */
#define SELREF2_L              (0x0040)       /* FLL Reference Clock Select Bit : 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define FLLREFDIV_0            (0x0000)       /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV_1            (0x0001)       /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV_2            (0x0002)       /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV_3            (0x0003)       /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV_4            (0x0004)       /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV_5            (0x0005)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_6            (0x0006)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV_7            (0x0007)       /* Reference Divider: f(LFCLK)/16 */
#define FLLREFDIV__1           (0x0000)       /* Reference Divider: f(LFCLK)/1 */
#define FLLREFDIV__2           (0x0001)       /* Reference Divider: f(LFCLK)/2 */
#define FLLREFDIV__4           (0x0002)       /* Reference Divider: f(LFCLK)/4 */
#define FLLREFDIV__8           (0x0003)       /* Reference Divider: f(LFCLK)/8 */
#define FLLREFDIV__12          (0x0004)       /* Reference Divider: f(LFCLK)/12 */
#define FLLREFDIV__16          (0x0005)       /* Reference Divider: f(LFCLK)/16 */
#define SELREF_0               (0x0000)       /* FLL Reference Clock Select 0 */
#define SELREF_1               (0x0010)       /* FLL Reference Clock Select 1 */
#define SELREF_2               (0x0020)       /* FLL Reference Clock Select 2 */
#define SELREF_3               (0x0030)       /* FLL Reference Clock Select 3 */
#define SELREF_4               (0x0040)       /* FLL Reference Clock Select 4 */
#define SELREF_5               (0x0050)       /* FLL Reference Clock Select 5 */
#define SELREF_6               (0x0060)       /* FLL Reference Clock Select 6 */
#define SELREF_7               (0x0070)       /* FLL Reference Clock Select 7 */
#define SELREF__XT1CLK         (0x0000)       /* Multiply Selected Loop Freq. By XT1CLK */
#define SELREF__REFOCLK        (0x0020)       /* Multiply Selected Loop Freq. By REFOCLK */
#define SELREF__XT2CLK         (0x0050)       /* Multiply Selected Loop Freq. By XT2CLK */

/* UCSCTL4 Control Bits */
#define SELM0                  (0x0001)       /* MCLK Source Select Bit: 0 */
#define SELM1                  (0x0002)       /* MCLK Source Select Bit: 1 */
#define SELM2                  (0x0004)       /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELS0                  (0x0010)       /* SMCLK Source Select Bit: 0 */
#define SELS1                  (0x0020)       /* SMCLK Source Select Bit: 1 */
#define SELS2                  (0x0040)       /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
#define SELA0                  (0x0100)       /* ACLK Source Select Bit: 0 */
#define SELA1                  (0x0200)       /* ACLK Source Select Bit: 1 */
#define SELA2                  (0x0400)       /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL4 Control Bits */
#define SELM0_L                (0x0001)       /* MCLK Source Select Bit: 0 */
#define SELM1_L                (0x0002)       /* MCLK Source Select Bit: 1 */
#define SELM2_L                (0x0004)       /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define SELS0_L                (0x0010)       /* SMCLK Source Select Bit: 0 */
#define SELS1_L                (0x0020)       /* SMCLK Source Select Bit: 1 */
#define SELS2_L                (0x0040)       /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL4 Control Bits */
//#define RESERVED            (0x0008)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define SELA0_H                (0x0001)       /* ACLK Source Select Bit: 0 */
#define SELA1_H                (0x0002)       /* ACLK Source Select Bit: 1 */
#define SELA2_H                (0x0004)       /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define SELM_0                 (0x0000)       /* MCLK Source Select 0 */
#define SELM_1                 (0x0001)       /* MCLK Source Select 1 */
#define SELM_2                 (0x0002)       /* MCLK Source Select 2 */
#define SELM_3                 (0x0003)       /* MCLK Source Select 3 */
#define SELM_4                 (0x0004)       /* MCLK Source Select 4 */
#define SELM_5                 (0x0005)       /* MCLK Source Select 5 */
#define SELM_6                 (0x0006)       /* MCLK Source Select 6 */
#define SELM_7                 (0x0007)       /* MCLK Source Select 7 */
#define SELM__XT1CLK           (0x0000)       /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK           (0x0001)       /* MCLK Source Select VLOCLK */
#define SELM__REFOCLK          (0x0002)       /* MCLK Source Select REFOCLK */
#define SELM__DCOCLK           (0x0003)       /* MCLK Source Select DCOCLK */
#define SELM__DCOCLKDIV        (0x0004)       /* MCLK Source Select DCOCLKDIV */
#define SELM__XT2CLK           (0x0005)       /* MCLK Source Select XT2CLK */

#define SELS_0                 (0x0000)       /* SMCLK Source Select 0 */
#define SELS_1                 (0x0010)       /* SMCLK Source Select 1 */
#define SELS_2                 (0x0020)       /* SMCLK Source Select 2 */
#define SELS_3                 (0x0030)       /* SMCLK Source Select 3 */
#define SELS_4                 (0x0040)       /* SMCLK Source Select 4 */
#define SELS_5                 (0x0050)       /* SMCLK Source Select 5 */
#define SELS_6                 (0x0060)       /* SMCLK Source Select 6 */
#define SELS_7                 (0x0070)       /* SMCLK Source Select 7 */
#define SELS__XT1CLK           (0x0000)       /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK           (0x0010)       /* SMCLK Source Select VLOCLK */
#define SELS__REFOCLK          (0x0020)       /* SMCLK Source Select REFOCLK */
#define SELS__DCOCLK           (0x0030)       /* SMCLK Source Select DCOCLK */
#define SELS__DCOCLKDIV        (0x0040)       /* SMCLK Source Select DCOCLKDIV */
#define SELS__XT2CLK           (0x0050)       /* SMCLK Source Select XT2CLK */

#define SELA_0                 (0x0000)       /* ACLK Source Select 0 */
#define SELA_1                 (0x0100)       /* ACLK Source Select 1 */
#define SELA_2                 (0x0200)       /* ACLK Source Select 2 */
#define SELA_3                 (0x0300)       /* ACLK Source Select 3 */
#define SELA_4                 (0x0400)       /* ACLK Source Select 4 */
#define SELA_5                 (0x0500)       /* ACLK Source Select 5 */
#define SELA_6                 (0x0600)       /* ACLK Source Select 6 */
#define SELA_7                 (0x0700)       /* ACLK Source Select 7 */
#define SELA__XT1CLK           (0x0000)       /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK           (0x0100)       /* ACLK Source Select VLOCLK */
#define SELA__REFOCLK          (0x0200)       /* ACLK Source Select REFOCLK */
#define SELA__DCOCLK           (0x0300)       /* ACLK Source Select DCOCLK */
#define SELA__DCOCLKDIV        (0x0400)       /* ACLK Source Select DCOCLKDIV */
#define SELA__XT2CLK           (0x0500)       /* ACLK Source Select XT2CLK */

/* UCSCTL5 Control Bits */
#define DIVM0                  (0x0001)       /* MCLK Divider Bit: 0 */
#define DIVM1                  (0x0002)       /* MCLK Divider Bit: 1 */
#define DIVM2                  (0x0004)       /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DIVS0                  (0x0010)       /* SMCLK Divider Bit: 0 */
#define DIVS1                  (0x0020)       /* SMCLK Divider Bit: 1 */
#define DIVS2                  (0x0040)       /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
#define DIVA0                  (0x0100)       /* ACLK Divider Bit: 0 */
#define DIVA1                  (0x0200)       /* ACLK Divider Bit: 1 */
#define DIVA2                  (0x0400)       /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0800)    /* RESERVED */
#define DIVPA0                 (0x1000)       /* ACLK from Pin Divider Bit: 0 */
#define DIVPA1                 (0x2000)       /* ACLK from Pin Divider Bit: 1 */
#define DIVPA2                 (0x4000)       /* ACLK from Pin Divider Bit: 2 */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL5 Control Bits */
#define DIVM0_L                (0x0001)       /* MCLK Divider Bit: 0 */
#define DIVM1_L                (0x0002)       /* MCLK Divider Bit: 1 */
#define DIVM2_L                (0x0004)       /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0008)    /* RESERVED */
#define DIVS0_L                (0x0010)       /* SMCLK Divider Bit: 0 */
#define DIVS1_L                (0x0020)       /* SMCLK Divider Bit: 1 */
#define DIVS2_L                (0x0040)       /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL5 Control Bits */
//#define RESERVED            (0x0008)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
#define DIVA0_H                (0x0001)       /* ACLK Divider Bit: 0 */
#define DIVA1_H                (0x0002)       /* ACLK Divider Bit: 1 */
#define DIVA2_H                (0x0004)       /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0800)    /* RESERVED */
#define DIVPA0_H               (0x0010)       /* ACLK from Pin Divider Bit: 0 */
#define DIVPA1_H               (0x0020)       /* ACLK from Pin Divider Bit: 1 */
#define DIVPA2_H               (0x0040)       /* ACLK from Pin Divider Bit: 2 */
//#define RESERVED            (0x8000)    /* RESERVED */

#define DIVM_0                 (0x0000)       /* MCLK Source Divider 0 */
#define DIVM_1                 (0x0001)       /* MCLK Source Divider 1 */
#define DIVM_2                 (0x0002)       /* MCLK Source Divider 2 */
#define DIVM_3                 (0x0003)       /* MCLK Source Divider 3 */
#define DIVM_4                 (0x0004)       /* MCLK Source Divider 4 */
#define DIVM_5                 (0x0005)       /* MCLK Source Divider 5 */
#define DIVM_6                 (0x0006)       /* MCLK Source Divider 6 */
#define DIVM_7                 (0x0007)       /* MCLK Source Divider 7 */
#define DIVM__1                (0x0000)       /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2                (0x0001)       /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4                (0x0002)       /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8                (0x0003)       /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16               (0x0004)       /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32               (0x0005)       /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0                 (0x0000)       /* SMCLK Source Divider 0 */
#define DIVS_1                 (0x0010)       /* SMCLK Source Divider 1 */
#define DIVS_2                 (0x0020)       /* SMCLK Source Divider 2 */
#define DIVS_3                 (0x0030)       /* SMCLK Source Divider 3 */
#define DIVS_4                 (0x0040)       /* SMCLK Source Divider 4 */
#define DIVS_5                 (0x0050)       /* SMCLK Source Divider 5 */
#define DIVS_6                 (0x0060)       /* SMCLK Source Divider 6 */
#define DIVS_7                 (0x0070)       /* SMCLK Source Divider 7 */
#define DIVS__1                (0x0000)       /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2                (0x0010)       /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4                (0x0020)       /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8                (0x0030)       /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16               (0x0040)       /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32               (0x0050)       /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0                 (0x0000)       /* ACLK Source Divider 0 */
#define DIVA_1                 (0x0100)       /* ACLK Source Divider 1 */
#define DIVA_2                 (0x0200)       /* ACLK Source Divider 2 */
#define DIVA_3                 (0x0300)       /* ACLK Source Divider 3 */
#define DIVA_4                 (0x0400)       /* ACLK Source Divider 4 */
#define DIVA_5                 (0x0500)       /* ACLK Source Divider 5 */
#define DIVA_6                 (0x0600)       /* ACLK Source Divider 6 */
#define DIVA_7                 (0x0700)       /* ACLK Source Divider 7 */
#define DIVA__1                (0x0000)       /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2                (0x0100)       /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4                (0x0200)       /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8                (0x0300)       /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16               (0x0400)       /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32               (0x0500)       /* ACLK Source Divider f(ACLK)/32 */

#define DIVPA_0                (0x0000)       /* ACLK from Pin Source Divider 0 */
#define DIVPA_1                (0x1000)       /* ACLK from Pin Source Divider 1 */
#define DIVPA_2                (0x2000)       /* ACLK from Pin Source Divider 2 */
#define DIVPA_3                (0x3000)       /* ACLK from Pin Source Divider 3 */
#define DIVPA_4                (0x4000)       /* ACLK from Pin Source Divider 4 */
#define DIVPA_5                (0x5000)       /* ACLK from Pin Source Divider 5 */
#define DIVPA_6                (0x6000)       /* ACLK from Pin Source Divider 6 */
#define DIVPA_7                (0x7000)       /* ACLK from Pin Source Divider 7 */
#define DIVPA__1               (0x0000)       /* ACLK from Pin Source Divider f(ACLK)/1 */
#define DIVPA__2               (0x1000)       /* ACLK from Pin Source Divider f(ACLK)/2 */
#define DIVPA__4               (0x2000)       /* ACLK from Pin Source Divider f(ACLK)/4 */
#define DIVPA__8               (0x3000)       /* ACLK from Pin Source Divider f(ACLK)/8 */
#define DIVPA__16              (0x4000)       /* ACLK from Pin Source Divider f(ACLK)/16 */
#define DIVPA__32              (0x5000)       /* ACLK from Pin Source Divider f(ACLK)/32 */

/* UCSCTL6 Control Bits */
#define XT1OFF                 (0x0001)       /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF               (0x0002)       /* SMCLK Off */
#define XCAP0                  (0x0004)       /* XIN/XOUT Cap Bit: 0 */
#define XCAP1                  (0x0008)       /* XIN/XOUT Cap Bit: 1 */
#define XT1BYPASS              (0x0010)       /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS                    (0x0020)       /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0              (0x0040)       /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1              (0x0080)       /* XT1 Drive Level mode Bit 1 */
#define XT2OFF                 (0x0100)       /* High Frequency Oscillator 2 (XT2) disable */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL6 Control Bits */
#define XT1OFF_L               (0x0001)       /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF_L             (0x0002)       /* SMCLK Off */
#define XCAP0_L                (0x0004)       /* XIN/XOUT Cap Bit: 0 */
#define XCAP1_L                (0x0008)       /* XIN/XOUT Cap Bit: 1 */
#define XT1BYPASS_L            (0x0010)       /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L                  (0x0020)       /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L            (0x0040)       /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L            (0x0080)       /* XT1 Drive Level mode Bit 1 */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL6 Control Bits */
#define XT2OFF_H               (0x0001)       /* High Frequency Oscillator 2 (XT2) disable */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

#define XCAP_0                 (0x0000)       /* XIN/XOUT Cap 0 */
#define XCAP_1                 (0x0004)       /* XIN/XOUT Cap 1 */
#define XCAP_2                 (0x0008)       /* XIN/XOUT Cap 2 */
#define XCAP_3                 (0x000C)       /* XIN/XOUT Cap 3 */
#define XT1DRIVE_0             (0x0000)       /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1             (0x0040)       /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2             (0x0080)       /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3             (0x00C0)       /* XT1 Drive Level mode: 3 */

/* UCSCTL7 Control Bits */
#define DCOFFG                 (0x0001)       /* DCO Fault Flag */
#define XT1LFOFFG              (0x0002)       /* XT1 Low Frequency Oscillator Fault Flag */
#define XT1HFOFFG              (0x0004)       /* XT1 High Frequency Oscillator 1 Fault Flag */
#define XT2OFFG                (0x0008)       /* High Frequency Oscillator 2 Fault Flag */
//#define RESERVED            (0x0010)    /* RESERVED */
//#define RESERVED            (0x0020)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL7 Control Bits */
#define DCOFFG_L               (0x0001)       /* DCO Fault Flag */
#define XT1LFOFFG_L            (0x0002)       /* XT1 Low Frequency Oscillator Fault Flag */
#define XT1HFOFFG_L            (0x0004)       /* XT1 High Frequency Oscillator 1 Fault Flag */
#define XT2OFFG_L              (0x0008)       /* High Frequency Oscillator 2 Fault Flag */
//#define RESERVED            (0x0010)    /* RESERVED */
//#define RESERVED            (0x0020)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL8 Control Bits */
#define ACLKREQEN              (0x0001)       /* ACLK Clock Request Enable */
#define MCLKREQEN              (0x0002)       /* MCLK Clock Request Enable */
#define SMCLKREQEN             (0x0004)       /* SMCLK Clock Request Enable */
#define MODOSCREQEN            (0x0008)       /* MODOSC Clock Request Enable */
//#define RESERVED            (0x0010)    /* RESERVED */
//#define RESERVED            (0x0020)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/* UCSCTL8 Control Bits */
#define ACLKREQEN_L            (0x0001)       /* ACLK Clock Request Enable */
#define MCLKREQEN_L            (0x0002)       /* MCLK Clock Request Enable */
#define SMCLKREQEN_L           (0x0004)       /* SMCLK Clock Request Enable */
#define MODOSCREQEN_L          (0x0008)       /* MODOSC Clock Request Enable */
//#define RESERVED            (0x0010)    /* RESERVED */
//#define RESERVED            (0x0020)    /* RESERVED */
//#define RESERVED            (0x0040)    /* RESERVED */
//#define RESERVED            (0x0080)    /* RESERVED */
//#define RESERVED            (0x0100)    /* RESERVED */
//#define RESERVED            (0x0200)    /* RESERVED */
//#define RESERVED            (0x0400)    /* RESERVED */
//#define RESERVED            (0x0800)    /* RESERVED */
//#define RESERVED            (0x1000)    /* RESERVED */
//#define RESERVED            (0x2000)    /* RESERVED */
//#define RESERVED            (0x4000)    /* RESERVED */
//#define RESERVED            (0x8000)    /* RESERVED */

/************************************************************
* USCI A0
************************************************************/
#define __MSP430_HAS_USCI_A0__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_A0__ 0x05C0
#define USCI_A0_BASE           __MSP430_BASEADDRESS_USCI_A0__

SFR_16BIT(UCA0CTLW0);                         /* USCI A0 Control Word Register 0 */
SFR_8BIT(UCA0CTLW0_L);                        /* USCI A0 Control Word Register 0 */
SFR_8BIT(UCA0CTLW0_H);                        /* USCI A0 Control Word Register 0 */
#define UCA0CTL1               UCA0CTLW0_L    /* USCI A0 Control Register 1 */
#define UCA0CTL0               UCA0CTLW0_H    /* USCI A0 Control Register 0 */
SFR_16BIT(UCA0BRW);                           /* USCI A0 Baud Word Rate 0 */
SFR_8BIT(UCA0BRW_L);                          /* USCI A0 Baud Word Rate 0 */
SFR_8BIT(UCA0BRW_H);                          /* USCI A0 Baud Word Rate 0 */
#define UCA0BR0                UCA0BRW_L      /* USCI A0 Baud Rate 0 */
#define UCA0BR1                UCA0BRW_H      /* USCI A0 Baud Rate 1 */
SFR_8BIT(UCA0MCTL);                           /* USCI A0 Modulation Control */
SFR_8BIT(UCA0STAT);                           /* USCI A0 Status Register */
SFR_8BIT(UCA0RXBUF);                          /* USCI A0 Receive Buffer */
SFR_8BIT(UCA0TXBUF);                          /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0ABCTL);                          /* USCI A0 LIN Control */
SFR_16BIT(UCA0IRCTL);                         /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRCTL_L);                        /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRCTL_H);                        /* USCI A0 IrDA Transmit Control */
#define UCA0IRTCTL             UCA0IRCTL_L    /* USCI A0 IrDA Transmit Control */
#define UCA0IRRCTL             UCA0IRCTL_H    /* USCI A0 IrDA Receive Control */
SFR_16BIT(UCA0ICTL);                          /* USCI A0 Interrupt Enable Register */
SFR_8BIT(UCA0ICTL_L);                         /* USCI A0 Interrupt Enable Register */
SFR_8BIT(UCA0ICTL_H);                         /* USCI A0 Interrupt Enable Register */
#define UCA0IE                 UCA0ICTL_L     /* USCI A0 Interrupt Enable Register */
#define UCA0IFG                UCA0ICTL_H     /* USCI A0 Interrupt Flags Register */
SFR_16BIT(UCA0IV);                            /* USCI A0 Interrupt Vector Register */


/************************************************************
* USCI B0
************************************************************/
#define __MSP430_HAS_USCI_B0__                /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_USCI_B0__ 0x05E0
#define USCI_B0_BASE           __MSP430_BASEADDRESS_USCI_B0__


SFR_16BIT(UCB0CTLW0);                         /* USCI B0 Control Word Register 0 */
SFR_8BIT(UCB0CTLW0_L);                        /* USCI B0 Control Word Register 0 */
SFR_8BIT(UCB0CTLW0_H);                        /* USCI B0 Control Word Register 0 */
#define UCB0CTL1               UCB0CTLW0_L    /* USCI B0 Control Register 1 */
#define UCB0CTL0               UCB0CTLW0_H    /* USCI B0 Control Register 0 */
SFR_16BIT(UCB0BRW);                           /* USCI B0 Baud Word Rate 0 */
SFR_8BIT(UCB0BRW_L);                          /* USCI B0 Baud Word Rate 0 */
SFR_8BIT(UCB0BRW_H);                          /* USCI B0 Baud Word Rate 0 */
#define UCB0BR0                UCB0BRW_L      /* USCI B0 Baud Rate 0 */
#define UCB0BR1                UCB0BRW_H      /* USCI B0 Baud Rate 1 */
SFR_8BIT(UCB0STAT);                           /* USCI B0 Status Register */
SFR_8BIT(UCB0RXBUF);                          /* USCI B0 Receive Buffer */
SFR_8BIT(UCB0TXBUF);                          /* USCI B0 Transmit Buffer */
SFR_16BIT(UCB0I2COA);                         /* USCI B0 I2C Own Address */
SFR_8BIT(UCB0I2COA_L);                        /* USCI B0 I2C Own Address */
SFR_8BIT(UCB0I2COA_H);                        /* USCI B0 I2C Own Address */
SFR_16BIT(UCB0I2CSA);                         /* USCI B0 I2C Slave Address */
SFR_8BIT(UCB0I2CSA_L);                        /* USCI B0 I2C Slave Address */
SFR_8BIT(UCB0I2CSA_H);                        /* USCI B0 I2C Slave Address */
SFR_16BIT(UCB0ICTL);                          /* USCI B0 Interrupt Enable Register */
SFR_8BIT(UCB0ICTL_L);                         /* USCI B0 Interrupt Enable Register */
SFR_8BIT(UCB0ICTL_H);                         /* USCI B0 Interrupt Enable Register */
#define UCB0IE                 UCB0ICTL_L     /* USCI B0 Interrupt Enable Register */
#define UCB0IFG                UCB0ICTL_H     /* USCI B0 Interrupt Flags Register */
SFR_16BIT(UCB0IV);                            /* USCI B0 Interrupt Vector Register */

// UCAxCTL0 UART-Mode Control Bits
#define UCPEN                  (0x80)         /* Async. Mode: Parity enable */
#define UCPAR                  (0x40)         /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB                  (0x20)         /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT                 (0x10)         /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB                  (0x08)         /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1                (0x04)         /* Async. Mode: USCI Mode 1 */
#define UCMODE0                (0x02)         /* Async. Mode: USCI Mode 0 */
#define UCSYNC                 (0x01)         /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// UCxxCTL0 SPI-Mode Control Bits
#define UCCKPH                 (0x80)         /* Sync. Mode: Clock Phase */
#define UCCKPL                 (0x40)         /* Sync. Mode: Clock Polarity */
#define UCMST                  (0x08)         /* Sync. Mode: Master Select */

// UCBxCTL0 I2C-Mode Control Bits
#define UCA10                  (0x80)         /* 10-bit Address Mode */
#define UCSLA10                (0x40)         /* 10-bit Slave Address Mode */
#define UCMM                   (0x20)         /* Multi-Master Environment */
//#define res               (0x10)    /* reserved */
#define UCMODE_0               (0x00)         /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1               (0x02)         /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2               (0x04)         /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3               (0x06)         /* Sync. Mode: USCI Mode: 3 */

// UCAxCTL1 UART-Mode Control Bits
#define UCSSEL1                (0x80)         /* USCI 0 Clock Source Select 1 */
#define UCSSEL0                (0x40)         /* USCI 0 Clock Source Select 0 */
#define UCRXEIE                (0x20)         /* RX Error interrupt enable */
#define UCBRKIE                (0x10)         /* Break interrupt enable */
#define UCDORM                 (0x08)         /* Dormant (Sleep) Mode */
#define UCTXADDR               (0x04)         /* Send next Data as Address */
#define UCTXBRK                (0x02)         /* Send next Data as Break */
#define UCSWRST                (0x01)         /* USCI Software Reset */

// UCxxCTL1 SPI-Mode Control Bits
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
//#define res               (0x08)    /* reserved */
//#define res               (0x04)    /* reserved */
//#define res               (0x02)    /* reserved */

// UCBxCTL1 I2C-Mode Control Bits
//#define res               (0x20)    /* reserved */
#define UCTR                   (0x10)         /* Transmit/Receive Select/Flag */
#define UCTXNACK               (0x08)         /* Transmit NACK */
#define UCTXSTP                (0x04)         /* Transmit STOP */
#define UCTXSTT                (0x02)         /* Transmit START */
#define UCSSEL_0               (0x00)         /* USCI 0 Clock Source: 0 */
#define UCSSEL_1               (0x40)         /* USCI 0 Clock Source: 1 */
#define UCSSEL_2               (0x80)         /* USCI 0 Clock Source: 2 */
#define UCSSEL_3               (0xC0)         /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK           (0x00)         /* USCI 0 Clock Source: UCLK */
#define UCSSEL__ACLK           (0x40)         /* USCI 0 Clock Source: ACLK */
#define UCSSEL__SMCLK          (0x80)         /* USCI 0 Clock Source: SMCLK */

/* UCAxMCTL Control Bits */
#define UCBRF3                 (0x80)         /* USCI First Stage Modulation Select 3 */
#define UCBRF2                 (0x40)         /* USCI First Stage Modulation Select 2 */
#define UCBRF1                 (0x20)         /* USCI First Stage Modulation Select 1 */
#define UCBRF0                 (0x10)         /* USCI First Stage Modulation Select 0 */
#define UCBRS2                 (0x08)         /* USCI Second Stage Modulation Select 2 */
#define UCBRS1                 (0x04)         /* USCI Second Stage Modulation Select 1 */
#define UCBRS0                 (0x02)         /* USCI Second Stage Modulation Select 0 */
#define UCOS16                 (0x01)         /* USCI 16-times Oversampling enable */

#define UCBRF_0                (0x00)         /* USCI First Stage Modulation: 0 */
#define UCBRF_1                (0x10)         /* USCI First Stage Modulation: 1 */
#define UCBRF_2                (0x20)         /* USCI First Stage Modulation: 2 */
#define UCBRF_3                (0x30)         /* USCI First Stage Modulation: 3 */
#define UCBRF_4                (0x40)         /* USCI First Stage Modulation: 4 */
#define UCBRF_5                (0x50)         /* USCI First Stage Modulation: 5 */
#define UCBRF_6                (0x60)         /* USCI First Stage Modulation: 6 */
#define UCBRF_7                (0x70)         /* USCI First Stage Modulation: 7 */
#define UCBRF_8                (0x80)         /* USCI First Stage Modulation: 8 */
#define UCBRF_9                (0x90)         /* USCI First Stage Modulation: 9 */
#define UCBRF_10               (0xA0)         /* USCI First Stage Modulation: A */
#define UCBRF_11               (0xB0)         /* USCI First Stage Modulation: B */
#define UCBRF_12               (0xC0)         /* USCI First Stage Modulation: C */
#define UCBRF_13               (0xD0)         /* USCI First Stage Modulation: D */
#define UCBRF_14               (0xE0)         /* USCI First Stage Modulation: E */
#define UCBRF_15               (0xF0)         /* USCI First Stage Modulation: F */

#define UCBRS_0                (0x00)         /* USCI Second Stage Modulation: 0 */
#define UCBRS_1                (0x02)         /* USCI Second Stage Modulation: 1 */
#define UCBRS_2                (0x04)         /* USCI Second Stage Modulation: 2 */
#define UCBRS_3                (0x06)         /* USCI Second Stage Modulation: 3 */
#define UCBRS_4                (0x08)         /* USCI Second Stage Modulation: 4 */
#define UCBRS_5                (0x0A)         /* USCI Second Stage Modulation: 5 */
#define UCBRS_6                (0x0C)         /* USCI Second Stage Modulation: 6 */
#define UCBRS_7                (0x0E)         /* USCI Second Stage Modulation: 7 */

/* UCAxSTAT Control Bits */
#define UCLISTEN               (0x80)         /* USCI Listen mode */
#define UCFE                   (0x40)         /* USCI Frame Error Flag */
#define UCOE                   (0x20)         /* USCI Overrun Error Flag */
#define UCPE                   (0x10)         /* USCI Parity Error Flag */
#define UCBRK                  (0x08)         /* USCI Break received */
#define UCRXERR                (0x04)         /* USCI RX Error Flag */
#define UCADDR                 (0x02)         /* USCI Address received Flag */
#define UCBUSY                 (0x01)         /* USCI Busy Flag */
#define UCIDLE                 (0x02)         /* USCI Idle line detected Flag */

/* UCBxSTAT Control Bits */
#define UCSCLLOW               (0x40)         /* SCL low */
#define UCGC                   (0x20)         /* General Call address received Flag */
#define UCBBUSY                (0x10)         /* Bus Busy Flag */

/* UCAxIRTCTL Control Bits */
#define UCIRTXPL5              (0x80)         /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4              (0x40)         /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3              (0x20)         /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2              (0x10)         /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1              (0x08)         /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0              (0x04)         /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK              (0x02)         /* IRDA Transmit Pulse Clock Select */
#define UCIREN                 (0x01)         /* IRDA Encoder/Decoder enable */

/* UCAxIRRCTL Control Bits */
#define UCIRRXFL5              (0x80)         /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4              (0x40)         /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3              (0x20)         /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2              (0x10)         /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1              (0x08)         /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0              (0x04)         /* IRDA Receive Filter Length 0 */
#define UCIRRXPL               (0x02)         /* IRDA Receive Input Polarity */
#define UCIRRXFE               (0x01)         /* IRDA Receive Filter enable */

/* UCAxABCTL Control Bits */
//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1               (0x20)         /* Break Sync Delimiter 1 */
#define UCDELIM0               (0x10)         /* Break Sync Delimiter 0 */
#define UCSTOE                 (0x08)         /* Sync-Field Timeout error */
#define UCBTOE                 (0x04)         /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN                (0x01)         /* Auto Baud Rate detect enable */

/* UCBxI2COA Control Bits */
#define UCGCEN                 (0x8000)       /* I2C General Call enable */
#define UCOA9                  (0x0200)       /* I2C Own Address 9 */
#define UCOA8                  (0x0100)       /* I2C Own Address 8 */
#define UCOA7                  (0x0080)       /* I2C Own Address 7 */
#define UCOA6                  (0x0040)       /* I2C Own Address 6 */
#define UCOA5                  (0x0020)       /* I2C Own Address 5 */
#define UCOA4                  (0x0010)       /* I2C Own Address 4 */
#define UCOA3                  (0x0008)       /* I2C Own Address 3 */
#define UCOA2                  (0x0004)       /* I2C Own Address 2 */
#define UCOA1                  (0x0002)       /* I2C Own Address 1 */
#define UCOA0                  (0x0001)       /* I2C Own Address 0 */

/* UCBxI2COA Control Bits */
#define UCOA7_L                (0x0080)       /* I2C Own Address 7 */
#define UCOA6_L                (0x0040)       /* I2C Own Address 6 */
#define UCOA5_L                (0x0020)       /* I2C Own Address 5 */
#define UCOA4_L                (0x0010)       /* I2C Own Address 4 */
#define UCOA3_L                (0x0008)       /* I2C Own Address 3 */
#define UCOA2_L                (0x0004)       /* I2C Own Address 2 */
#define UCOA1_L                (0x0002)       /* I2C Own Address 1 */
#define UCOA0_L                (0x0001)       /* I2C Own Address 0 */

/* UCBxI2COA Control Bits */
#define UCGCEN_H               (0x0080)       /* I2C General Call enable */
#define UCOA9_H                (0x0002)       /* I2C Own Address 9 */
#define UCOA8_H                (0x0001)       /* I2C Own Address 8 */

/* UCBxI2CSA Control Bits */
#define UCSA9                  (0x0200)       /* I2C Slave Address 9 */
#define UCSA8                  (0x0100)       /* I2C Slave Address 8 */
#define UCSA7                  (0x0080)       /* I2C Slave Address 7 */
#define UCSA6                  (0x0040)       /* I2C Slave Address 6 */
#define UCSA5                  (0x0020)       /* I2C Slave Address 5 */
#define UCSA4                  (0x0010)       /* I2C Slave Address 4 */
#define UCSA3                  (0x0008)       /* I2C Slave Address 3 */
#define UCSA2                  (0x0004)       /* I2C Slave Address 2 */
#define UCSA1                  (0x0002)       /* I2C Slave Address 1 */
#define UCSA0                  (0x0001)       /* I2C Slave Address 0 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L                (0x0080)       /* I2C Slave Address 7 */
#define UCSA6_L                (0x0040)       /* I2C Slave Address 6 */
#define UCSA5_L                (0x0020)       /* I2C Slave Address 5 */
#define UCSA4_L                (0x0010)       /* I2C Slave Address 4 */
#define UCSA3_L                (0x0008)       /* I2C Slave Address 3 */
#define UCSA2_L                (0x0004)       /* I2C Slave Address 2 */
#define UCSA1_L                (0x0002)       /* I2C Slave Address 1 */
#define UCSA0_L                (0x0001)       /* I2C Slave Address 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H                (0x0002)       /* I2C Slave Address 9 */
#define UCSA8_H                (0x0001)       /* I2C Slave Address 8 */

/* UCAxIE Control Bits */
#define UCTXIE                 (0x0002)       /* USCI Transmit Interrupt Enable */
#define UCRXIE                 (0x0001)       /* USCI Receive Interrupt Enable */

/* UCBxIE Control Bits */
#define UCNACKIE               (0x0020)       /* NACK Condition interrupt enable */
#define UCALIE                 (0x0010)       /* Arbitration Lost interrupt enable */
#define UCSTPIE                (0x0008)       /* STOP Condition interrupt enable */
#define UCSTTIE                (0x0004)       /* START Condition interrupt enable */
#define UCTXIE                 (0x0002)       /* USCI Transmit Interrupt Enable */
#define UCRXIE                 (0x0001)       /* USCI Receive Interrupt Enable */

/* UCAxIFG Control Bits */
#define UCTXIFG                (0x0002)       /* USCI Transmit Interrupt Flag */
#define UCRXIFG                (0x0001)       /* USCI Receive Interrupt Flag */

/* UCBxIFG Control Bits */
#define UCNACKIFG              (0x0020)       /* NAK Condition interrupt Flag */
#define UCALIFG                (0x0010)       /* Arbitration Lost interrupt Flag */
#define UCSTPIFG               (0x0008)       /* STOP Condition interrupt Flag */
#define UCSTTIFG               (0x0004)       /* START Condition interrupt Flag */
#define UCTXIFG                (0x0002)       /* USCI Transmit Interrupt Flag */
#define UCRXIFG                (0x0001)       /* USCI Receive Interrupt Flag */

/* USCI Definitions */
#define USCI_NONE              (0x0000)       /* No Interrupt pending */
#define USCI_UCRXIFG           (0x0002)       /* USCI UCRXIFG */
#define USCI_UCTXIFG           (0x0004)       /* USCI UCTXIFG */
#define USCI_I2C_UCALIFG       (0x0002)       /* USCI I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG     (0x0004)       /* USCI I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG      (0x0006)       /* USCI I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG      (0x0008)       /* USCI I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG       (0x000A)       /* USCI I2C Mode: UCRXIFG */
#define USCI_I2C_UCTXIFG       (0x000C)       /* USCI I2C Mode: UCTXIFG */

/************************************************************
* WATCHDOG TIMER A
************************************************************/
#define __MSP430_HAS_WDT_A__                  /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x0150
#define WDT_A_BASE             __MSP430_BASEADDRESS_WDT_A__

SFR_16BIT(WDTCTL);                            /* Watchdog Timer Control */
SFR_8BIT(WDTCTL_L);                           /* Watchdog Timer Control */
SFR_8BIT(WDTCTL_H);                           /* Watchdog Timer Control */
/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0                 (0x0001)       /* WDT - Timer Interval Select 0 */
#define WDTIS1                 (0x0002)       /* WDT - Timer Interval Select 1 */
#define WDTIS2                 (0x0004)       /* WDT - Timer Interval Select 2 */
#define WDTCNTCL               (0x0008)       /* WDT - Timer Clear */
#define WDTTMSEL               (0x0010)       /* WDT - Timer Mode Select */
#define WDTSSEL0               (0x0020)       /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1               (0x0040)       /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD                (0x0080)       /* WDT - Timer hold */

/* WDTCTL Control Bits */
#define WDTIS0_L               (0x0001)       /* WDT - Timer Interval Select 0 */
#define WDTIS1_L               (0x0002)       /* WDT - Timer Interval Select 1 */
#define WDTIS2_L               (0x0004)       /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L             (0x0008)       /* WDT - Timer Clear */
#define WDTTMSEL_L             (0x0010)       /* WDT - Timer Mode Select */
#define WDTSSEL0_L             (0x0020)       /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L             (0x0040)       /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L              (0x0080)       /* WDT - Timer hold */

#define WDTPW                  (0x5A00)

#define WDTIS_0                (0*0x0001u)    /* WDT - Timer Interval Select: /2G */
#define WDTIS_1                (1*0x0001u)    /* WDT - Timer Interval Select: /128M */
#define WDTIS_2                (2*0x0001u)    /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3                (3*0x0001u)    /* WDT - Timer Interval Select: /512k */
#define WDTIS_4                (4*0x0001u)    /* WDT - Timer Interval Select: /32k */
#define WDTIS_5                (5*0x0001u)    /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6                (6*0x0001u)    /* WDT - Timer Interval Select: /512 */
#define WDTIS_7                (7*0x0001u)    /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G              (0*0x0001u)    /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M            (1*0x0001u)    /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K           (2*0x0001u)    /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K            (3*0x0001u)    /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K             (4*0x0001u)    /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192            (5*0x0001u)    /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512             (6*0x0001u)    /* WDT - Timer Interval Select: /512 */
#define WDTIS__64              (7*0x0001u)    /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0              (0*0x0020u)    /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1              (1*0x0020u)    /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2              (2*0x0020u)    /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3              (3*0x0020u)    /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK         (0*0x0020u)    /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK          (1*0x0020u)    /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO           (2*0x0020u)    /* WDT - Timer Clock Source Select: VLO_CLK */

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */


/************************************************************
* TLV Descriptors
************************************************************/
#define __MSP430_HAS_TLV__                    /* Definition to show that Module is available */
#define TLV_BASE               __MSP430_BASEADDRESS_TLV__

#define TLV_CRC_LENGTH         (0x1A01)       /* CRC length of the TLV structure */
#define TLV_CRC_VALUE          (0x1A02)       /* CRC value of the TLV structure */
#define TLV_START              (0x1A08)       /* Start Address of the TLV structure */
#define TLV_END                (0x1AFF)       /* End Address of the TLV structure */

#define TLV_LDTAG              (0x01)         /*  Legacy descriptor (1xx, 2xx, 4xx families) */
#define TLV_PDTAG              (0x02)         /*  Peripheral discovery descriptor */
#define TLV_Reserved3          (0x03)         /*  Future usage */
#define TLV_Reserved4          (0x04)         /*  Future usage */
#define TLV_BLANK              (0x05)         /*  Blank descriptor */
#define TLV_Reserved6          (0x06)         /*  Future usage */
#define TLV_Reserved7          (0x07)         /*  Serial Number */
#define TLV_DIERECORD          (0x08)         /*  Die Record  */
#define TLV_ADCCAL             (0x11)         /*  ADC12 calibration */
#define TLV_ADC12CAL           (0x11)         /*  ADC12 calibration */
#define TLV_ADC10CAL           (0x13)         /*  ADC10 calibration */
#define TLV_REFCAL             (0x12)         /*  REF calibration */
#define TLV_TAGEXT             (0xFE)         /*  Tag extender */
#define TLV_TAGEND             (0xFF)         //  Tag End of Table

/************************************************************
* Interrupt Vectors (offset from 0xFF80)
************************************************************/

#pragma diag_suppress 1107
#define VECTOR_NAME(name)             name##_ptr
#define EMIT_PRAGMA(x)                _Pragma(#x)
#define CREATE_VECTOR(name)           void * const VECTOR_NAME(name) = (void *)(long)&name
#define PLACE_VECTOR(vector,section)  EMIT_PRAGMA(DATA_SECTION(vector,section))
#define PLACE_INTERRUPT(func)         EMIT_PRAGMA(CODE_SECTION(func,".text:_isr"))
#define ISR_VECTOR(func,offset)       CREATE_VECTOR(func); \
                                      PLACE_VECTOR(VECTOR_NAME(func), offset) \
                                      PLACE_INTERRUPT(func)


#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define AES_VECTOR              ".int45"                     /* 0xFFDA AES */
#else
#define AES_VECTOR              (45 * 1u)                    /* 0xFFDA AES */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RTC_VECTOR              ".int46"                     /* 0xFFDC RTC */
#else
#define RTC_VECTOR              (46 * 1u)                    /* 0xFFDC RTC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define LCD_B_VECTOR            ".int47"                     /* 0xFFDE LCD B */
#else
#define LCD_B_VECTOR            (47 * 1u)                    /* 0xFFDE LCD B */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int48"                     /* 0xFFE0 Port 2 */
#else
#define PORT2_VECTOR            (48 * 1u)                    /* 0xFFE0 Port 2 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int49"                     /* 0xFFE2 Port 1 */
#else
#define PORT1_VECTOR            (49 * 1u)                    /* 0xFFE2 Port 1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A1_VECTOR        ".int50"                     /* 0xFFE4 Timer1_A3 CC1-2, TA1 */
#else
#define TIMER1_A1_VECTOR        (50 * 1u)                    /* 0xFFE4 Timer1_A3 CC1-2, TA1 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A0_VECTOR        ".int51"                     /* 0xFFE6 Timer1_A3 CC0 */
#else
#define TIMER1_A0_VECTOR        (51 * 1u)                    /* 0xFFE6 Timer1_A3 CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define DMA_VECTOR              ".int52"                     /* 0xFFE8 DMA */
#else
#define DMA_VECTOR              (52 * 1u)                    /* 0xFFE8 DMA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define CC1101_VECTOR           ".int53"                     /* 0xFFEA CC1101 Radio Interface */
#else
#define CC1101_VECTOR           (53 * 1u)                    /* 0xFFEA CC1101 Radio Interface */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A1_VECTOR        ".int54"                     /* 0xFFEC Timer0_A5 CC1-4, TA */
#else
#define TIMER0_A1_VECTOR        (54 * 1u)                    /* 0xFFEC Timer0_A5 CC1-4, TA */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A0_VECTOR        ".int55"                     /* 0xFFEE Timer0_A5 CC0 */
#else
#define TIMER0_A0_VECTOR        (55 * 1u)                    /* 0xFFEE Timer0_A5 CC0 */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC12_VECTOR            ".int56"                     /* 0xFFF0 ADC */
#else
#define ADC12_VECTOR            (56 * 1u)                    /* 0xFFF0 ADC */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCI_B0_VECTOR          ".int57"                     /* 0xFFF2 USCI B0 Receive/Transmit */
#else
#define USCI_B0_VECTOR          (57 * 1u)                    /* 0xFFF2 USCI B0 Receive/Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCI_A0_VECTOR          ".int58"                     /* 0xFFF4 USCI A0 Receive/Transmit */
#else
#define USCI_A0_VECTOR          (58 * 1u)                    /* 0xFFF4 USCI A0 Receive/Transmit */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int59"                     /* 0xFFF6 Watchdog Timer */
#else
#define WDT_VECTOR              (59 * 1u)                    /* 0xFFF6 Watchdog Timer */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define COMP_B_VECTOR           ".int60"                     /* 0xFFF8 Comparator B */
#else
#define COMP_B_VECTOR           (60 * 1u)                    /* 0xFFF8 Comparator B */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define UNMI_VECTOR             ".int61"                     /* 0xFFFA User Non-maskable */
#else
#define UNMI_VECTOR             (61 * 1u)                    /* 0xFFFA User Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define SYSNMI_VECTOR           ".int62"                     /* 0xFFFC System Non-maskable */
#else
#define SYSNMI_VECTOR           (62 * 1u)                    /* 0xFFFC System Non-maskable */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                     /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (63 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
#endif

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __cc430x613x */

