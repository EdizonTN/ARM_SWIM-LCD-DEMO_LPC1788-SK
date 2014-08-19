/*
 * TS_Analog.h
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#ifndef TS_ANALOG_H_
#define TS_ANALOG_H_

// ******************************************************************************************************
// Configuration
// ******************************************************************************************************
#define	debounce 						100 				// debounce delay#define num_samples 					16 					// number of A/D samples per axis
#define	TS_SETTLING_TIME 				100 				// settling time delay
#define TS_CONVERSION_MAX     			0xfff				// max vaule of the AD Converter for TS inputs

#define TOUCH_AD_LEFT    				34					// default values, have to calibrate it
#define TOUCH_AD_RIGHT   				220					// default values, have to calibrate it
#define TOUCH_AD_TOP     				46					// default values, have to calibrate it
#define TOUCH_AD_BOTTOM  				212					// default values, have to calibrate it
// ******************************************************************************************************
// Hardware connection - see bsp.h
// ******************************************************************************************************
#define TS_X1_PORT						BSP_TS_X1_PORT
#define TS_X1_PIN						BSP_TS_X1_PIN
#define TS_X1_IRQ						PIN_INT0_IRQHandler	// route wakeup event to IRQ
#define TS_X1_ADC_CH					BSP_TS_X1_ADC_CH
#define TS_X1_FUNC_NO					BSP_TS_X1_FUNC_NO

#define TS_X2_PORT						BSP_TS_X2_PORT
#define TS_X2_PIN						BSP_TS_X2_PIN

#define TS_Y1_PORT						BSP_TS_Y1_PORT
#define TS_Y1_PIN						BSP_TS_Y1_PIN
#define TS_Y1_ADC_CH					BSP_TS_Y1_ADC_CH
#define TS_Y1_FUNC_NO					BSP_TS_Y1_FUNC_NO

#define TS_Y2_PORT						BSP_TS_Y2_PORT
#define TS_Y2_PIN						BSP_TS_Y2_PIN




// ******************************************************************************************************
// Export
// ******************************************************************************************************
// Do NOT modify next lines !!!

typedef struct
{
	int16_t ad_left;                        				// left margin
	int16_t ad_right;                       				// right margin
	int16_t ad_top;                        					// top margin
	int16_t ad_bottom;                      				// bottom margin
	int16_t lcd_h_size;                     				// lcd horizontal size
	int16_t lcd_v_size;                     				// lcd vertical size
	uint8_t Priority;										// priority level for TS Interrupt
} TS_Init_Type;

extern TS_Init_Type TS_Config;
extern uint8_t TS_Activated_Flag;
// Initialize TS on analog sub-system
void Init_TS(void);
void Enable_TS(void);
void Disable_TS(void);
void GetTouchCoord(int16_t *pX, int16_t* pY);				// Get current Touch Coordinates


#endif /* TS_ANALOG_H_ */
