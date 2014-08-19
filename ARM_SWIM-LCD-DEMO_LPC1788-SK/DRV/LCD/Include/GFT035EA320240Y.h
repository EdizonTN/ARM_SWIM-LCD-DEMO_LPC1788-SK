/*
 * GFT035EA320240Y.h
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#ifndef __GFT035EA320240Y_H
#define __GFT035EA320240Y_H


// ******************************************************************************************************
// Configuration
// ******************************************************************************************************
// LCD Config
#define LCD_H_SIZE           			320
#define LCD_H_PULSE          			30
#define LCD_H_FRONT_PORCH    			20
#define LCD_H_BACK_PORCH     			38
#define LCD_V_SIZE           			240
#define LCD_V_PULSE          			3
#define LCD_V_FRONT_PORCH    			5
#define LCD_V_BACK_PORCH     			15
#define LCD_PIX_CLK          			(6.5*1000000l)
// CUrsor config
#define LCD_CURSOR_SIZE					32
//Cursor 64x64 pixels
#define LCD_CURSOR_H_SIZE       		32
#define LCD_CURSOR_V_SIZE       		32
#define LCD_CURSOR_OFF_X       			(LCD_CURSOR_H_SIZE/2)
#define LCD_CURSOR_OFF_Y       			(LCD_CURSOR_V_SIZE/2)

// Cursor
#define LCD_VRAM_BASE_ADDR_UPPER 		((uint32_t)SDRAM_BASE_ADDR + 0x00100000)
#define LCD_VRAM_BASE_ADDR_LOWER 		(LCD_VRAM_BASE_ADDR_UPPER + 1024*768*4)
#define LCD_CURSOR_BASE_ADDR 	    	((uint32_t)0x20088800)

//  Backlight defines:
#define LCD_BACK_LIGHT_BASE_CLK 		(1000/4)
#define LCD_BL_PWM_BASE					(CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER) / LCD_BACK_LIGHT_BASE_CLK)				// base frequency for PWM backlight

//#define LCD_PWR_ENA_DIS_DLY  			10000

// ******************************************************************************************************
// Hardware connection - see bsp.h
// ******************************************************************************************************
#define LCD_BL_PWM_PERI_ID    			BSP_LCD_BL_PWM_PERI_ID
#define LCD_BL_PWM_PERI_CHA				BSP_LCD_BL_PWM_PERI_CHA			// Match channel register - cycle		- 100%
#define LCD_BL_PWM_PERI_CHB				BSP_LCD_BL_PWM_PERI_CHB			// Match channel register - duty cycle	- xx %
#define LCD_BL_PWM_PORT					BSP_LCD_BL_PWM_PORT				// pwm output port for pwm output pin...
#define LCD_BL_PWM_PIN					BSP_LCD_BL_PWM_PIN				// pwm output connected to LCD Backlight transistor's base

// ******************************************************************************************************
// Export
// ******************************************************************************************************
// Do NOT modify next lines !!!
extern void Init_LCD(void);
extern void Init_LCD_Cursor(void);
extern void Init_LCD_BackLight(void);
extern void Set_LCD_BackLight(uint16_t level);
extern void Enable_LCD(void);
extern void Disable_LCD(void);
extern void Enable_LCD_Cursor(void);
extern void Disable_LCD_Cursor(void);
extern const unsigned char Cursor[(LCD_CURSOR_H_SIZE/4)*LCD_CURSOR_H_SIZE];
extern void Set_LCD_Cursor(int x, int y);
#endif /* _GFT035EA320240Y_H */
