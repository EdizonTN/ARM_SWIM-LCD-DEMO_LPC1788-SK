/*
 * sdram_k4s561632l.h
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#ifndef __SDRAM_K4S561632J_H_
#define __SDRAM_K4S561632J_H_
//#include "bsp.h"

// ******************************************************************************************************
// Configuration
// ******************************************************************************************************
#define SDRAM_BASE_ADDR     0xA0000000
#define SDRAM_SIZE          0x10000000

#define SDRAM_REFRESH         7813
#define SDRAM_TRP             20
#define SDRAM_TRAS            45
#define SDRAM_TAPR            1
#define SDRAM_TDAL            3
#define SDRAM_TWR             3
#define SDRAM_TRC             65
#define SDRAM_TRFC            66
#define SDRAM_TXSR            67
#define SDRAM_TRRD            15
#define SDRAM_TMRD            3


// ******************************************************************************************************
// Export
// ******************************************************************************************************
// Do NOT modify next lines !!!
extern void Init_SDRAM( void );

#endif /* __SDRAM_K4S561632J_H_ */
