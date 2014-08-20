/***********************************************************
 * Configuration.h
 *
 *  Created on: 25.7.2014
 *      Author: peterj
 ***********************************************************/

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



#define CHIP_LPC177X_8X
#define __STACK_SIZE	0x400
#define __HEAP_SIZE		0xd00

#warning "Add into assembler's include also Configuration.h file!"
#define ARM_MATH_CM3

//HW drivers loading:
#define _CURR_USING_BRD 			_IAR_OLIMEX_BOARD		// nacuita drivery !!!!


// ********************************************************************************

// SWIM Configuration
#define COLORS_DEF 		16
#define PORTRAIT		1
#define FONT  font_x6x13 			        // font_x5x7 font_x6x13 font_rom8x8 font_rom8x16 font_winfreesys14x16

#endif /* CONFIGURATION_H_ */
