// ******************************************************************************************************
// bsp.h
//
//  Created on: 20.8.2014
//      Author: "EdizonTN@gmail.com"
//	Board support Package for IAR LPC1788-SK
// ******************************************************************************************************

#ifndef BSP_H_
#define BSP_H_

#include "global.h"


#ifndef 	__BUILD_WITH_EXAMPLE__
	#define __BUILD_WITH_EXAMPLE__			1
#endif


//LED indicators preset
#define BSP_LED_1_CONNECTED_PORT        	1
#define BSP_LED_1_CONNECTED_PIN         	13

#define BSP_LED_2_CONNECTED_PORT        	1
#define BSP_LED_2_CONNECTED_PIN         	18

// ******************************************************************************************************
// External SDRAM memory:
// ******************************************************************************************************
#include "../DRV/ExRAM/Include/sdram_k4s561632j.h"  			// include a driver

// ******************************************************************************************************
// LCD TFT Display - GiFar GFT035EA320240Y:
// ******************************************************************************************************
#define BSP_LCD_BL_PWM_PERI_ID    			PWM_1
#define BSP_LCD_BL_PWM_PERI_CHA				0			// Match channel register - cycle		- 100%
#define BSP_LCD_BL_PWM_PERI_CHB				2			// Match channel register - duty cycle	- xx %
#define BSP_LCD_BL_PWM_PORT					2			// pwm output port for pwm output pin...
#define BSP_LCD_BL_PWM_PIN					1			// pwm output connected to LCD Backlight transistor's base

#include "../DRV/LCD/Include/GFT035EA320240Y.h"  				// include a driver

// ******************************************************************************************************
// ADC Input - Potentiometer - hardware connection:
// ******************************************************************************************************
#define BSP_RPOT_ADC_PREPARED_CHANNEL        ADC_CHANNEL_7
//#define BSP_RPOT_ADC_PREPARED_INTR           ADC_ADINTEN7
#define BSP_RPOT_ADC_PREPARED_CH_PORT        0
#define BSP_RPOT_ADC_PREPARED_CH_PIN         13
#define BSP_RPOT_ADC_PREPARED_CH_FUNC_NO     3					// AD converter as alternative function no.3
#include "../DRV/RPOT/Include/RPOT.h"							// include a driver

// ******************************************************************************************************
// Touch screen reader - analog - hardware connection:
// ******************************************************************************************************
// X1 = X plus
// X2 = X minus
// Y1 = Y plus
// Y2 = Y minus
#define BSP_TS_X1_PORT        				0
#define BSP_TS_X1_PIN        				24						// ADC Input
#define BSP_TS_X1_ADC_CH       				ADC_CHANNEL_1			// ADC channel no.
#define BSP_TS_X1_FUNC_NO					1						// analog function of this pin is as alternate function no.1

#define BSP_TS_X2_PORT        				0
#define BSP_TS_X2_PIN        				19

#define BSP_TS_Y1_PORT        				0
#define BSP_TS_Y1_PIN        				23						// ADC input
#define BSP_TS_Y1_ADC_CH       				ADC_CHANNEL_0			// ADC channel no.
#define BSP_TS_Y1_FUNC_NO					1						// analog funsction of this pin is as alternate function no.1

#define BSP_TS_Y2_PORT        				0
#define BSP_TS_Y2_PIN        				21


#include "../DRV/TouchScreen/Include/TS_Analog.h"				// include a driver


#endif /* BSP_H_ */
