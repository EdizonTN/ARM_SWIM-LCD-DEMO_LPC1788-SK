/***********************************************************
 * global.h
 *
 *  Created on: 25.7.2014
 *      Author: peterj
 ***********************************************************/

// ******************************************************************************************************
// USER - some useful macros....
// ******************************************************************************************************
#ifndef GLOBAL_H_
#define GLOBAL_H_

// standard constants
#ifndef _NULL
	#define _NULL 					((void*) 0)
#endif

// BIT manipulation macros
#define _SBIT(word, bit)				(word |= 1 << (bit))			// Set bit macro
#define _CBIT(word, bit)				(word &= ~(1 << bit))			// Clear bit macro
#define _TBIT(word, bit)				((word && (1 << bit))? CBIT(word, bit): SBIT (word, bit))	// Toogle bit macro


// ******************************************************************************************************
// SYSTEM
// ******************************************************************************************************
#include "stdint.h"
#include "../Chip/Drivers/Include/lpc_types.h"
// ******************************************************************************************************
// PROJECT CONFIGURATION
// ******************************************************************************************************
#include "Configuration.h"

// ******************************************************************************************************
// CMSIS CORE
// ******************************************************************************************************
//#include "lpc177x_8x_libcfg_default.h"
//#include "../Chip/Include/arm_common_tables.h"
//#include "../Chip/Include/arm_const_structs.h"
//#include "../Chip/Include/arm_math.h"
//#include "../Chip/Include/core_cm0.h"
//#include "../Chip/Include/core_cm0plus.h"
//#include "../Chip/Include/core_cm3.h"
//#include "../Chip/Include/core_cm4.h"
//#include "../Chip/Include/core_cm4_simd.h"
//#include "../Chip/Include/core_cmFunc.h"
//#include "../Chip/Include/core_cmInstr.h"
//#include "../Chip/Include/core_sc000.h"
//#include "../Chip/Include/core_sc300.h"

// ******************************************************************************************************
// CMSIS Drivers
// ******************************************************************************************************
#include "../Chip/Drivers/Include/lpc177x_8x_pinsel.h"
// other CMSIS drivers called from included libraries, framevork or drivers


// ******************************************************************************************************
// BOARD SUPPORT PACKAGE HEADERS
// ******************************************************************************************************
#include "../BSP/bsp.h"


// ******************************************************************************************************
// FRAMEWORK HEADERS
// ******************************************************************************************************
//#include "bsp.h"
//#pragma GCC system_header
// SWIM Graphics User Interface Library
//#include "LPC177x_8x.h"
//#include "type.h"
//#include "ex_sdram.h"
//#include "lcd_params.h"
//#include "lcd_driver.h"
//#include "lcd_type.h"

// ******************************************************************************************************
// SWIM LIBRARY

#include "../LIB/GUI-SWIM/Include/lpc_swim_font.h"
#include "../LIB/GUI-SWIM/Include/lpc_swim.h"
#include "../LIB/GUI-SWIM/Include/lpc_rom8x16.h"
#include "../LIB/GUI-SWIM/Include/lpc_winfreesystem14x16.h"
#include "../LIB/GUI-SWIM/Include/lpc_x6x13.h"

#endif /* GLOBAL_H_ */
