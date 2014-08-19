/**********************************************************************
* $Id$		lpc17xx_8x_libcfg.h			28.07.2014
*//**
* @file		lpc17xx_8x_libcfg.h
* @brief	Library configuration file
**********************************************************************/

#ifndef _LPC177x_8x_LIBCFG_H_
#define _LPC177x_8x_LIBCFG_H_

#include "lpc_types.h"

/************************** DEBUG MODE DEFINITIONS *********************************/
/* Un-comment the line below to compile the library in DEBUG mode, this will expanse
   the "CHECK_PARAM" macro in the FW library code */

#define DEBUG

/******************* PERIPHERAL FW LIBRARY CONFIGURATION DEFINITIONS ***********************/
/* Comment the line below to disable the specific peripheral inclusion */

/* DEBUG_FRAMWORK -------------------- */
#define _DBGFWK

/* Clock & Power -------------------- */
#define _CLKPWR

/* CRC -------------------- */
#define _CRC

/* GPIO ------------------------------- */
#define _GPIO

/* NVIC ------------------------------- */
#define _NVIC

/* PINSEL ------------------------------- */
#define _PINSEL

/* EXTI ------------------------------- */
//#define _EXTI

/* EMC ------------------------------- */
//#define _EMC

/* UART ------------------------------- */
#define _UART

/* SPI ------------------------------- */
//#define _SPI

/* SYSTICK --------------------------- */
//#define _SYSTICK

/* SSP ------------------------------- */
//#define _SSP


/* I2C ------------------------------- */
//#define _I2C

/* TIMER ------------------------------- */
//#define _TIM

/* WDT ------------------------------- */
//#define _WDT


/* GPDMA ------------------------------- */
//#define _GPDMA


/* DAC ------------------------------- */
//#define _DAC

/* ADC ------------------------------- */
//#define _ADC

/* EEPROM ------------------------------- */
//#define _EEPROM

/* PWM ------------------------------- */
//#define _PWM

/* RTC ------------------------------- */
//#define _RTC

/* I2S ------------------------------- */
//#define _I2S

/* USB device ------------------------------- */
//#define _USBDEV

/* USB Host ------------------------------- */
//#define _USBHost

/* QEI ------------------------------- */
//#define _QEI

/* MCPWM ------------------------------- */
//#define _MCPWM

/* CAN--------------------------------*/
//#define _CAN

/* EMAC ------------------------------ */
//#define _EMAC

/* LCD ------------------------------ */
//#define _LCD

/* MCI ------------------------------ */
//#define _MCI

/************************** GLOBAL/PUBLIC MACRO DEFINITIONS *********************************/
#endif /* _LPC177x_8x_LIBCFG_H_ */
