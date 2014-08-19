/*
 * GFT035EA320240Y.c
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#include "global.h"
#include "../Chip/Drivers/Include/lpc177x_8x_lcd.h"
#include "../Chip/Drivers/Include/lpc177x_8x_pwm.h"
#include "../Chip/Drivers/Include/lpc177x_8x_gpio.h"
#include "../Chip/Drivers/Include/lpc177x_8x_clkpwr.h"


// ******************************************************************************************************
// Function prototypes
// ******************************************************************************************************
void Init_LCD_BackLight(void);
void Set_LCD_BackLight(uint16_t level);
void Init_LCD(void);
void Enable_LCD(void);
void Disable_LCD(void);

// ******************************************************************************************************
// Globals
// ******************************************************************************************************
LCD_Cursor_Config_Type cursor_config;


// --------------------------------------------------
void Enable_LCD(void)
{
	  LCD_Enable (ENABLE);				// Enable LCD
}

void Disable_LCD(void)
{
	  LCD_Enable (DISABLE);				// Disable LCD
}

void Enable_LCD_Cursor(void)
{
	LCD_Cursor_Enable(ENABLE, 0);		// ToDo: Cursor is hardly set to zero. In future make it as variable
}
void Disable_LCD_Cursor(void)
{
	LCD_Cursor_Enable(DISABLE, 0);
}


void Init_LCD(void)
{
	  LCD_Config_Type lcd_config;

	  LCD_Enable (FALSE);

	  lcd_config.big_endian_byte = 0;
	  lcd_config.big_endian_pixel = 0;
	  lcd_config.hConfig.hbp = LCD_H_BACK_PORCH;
	  lcd_config.hConfig.hfp = LCD_H_FRONT_PORCH;
	  lcd_config.hConfig.hsw = LCD_H_PULSE;
	  lcd_config.hConfig.ppl = LCD_H_SIZE;
	  lcd_config.vConfig.lpp = LCD_V_SIZE;
	  lcd_config.vConfig.vbp = LCD_V_BACK_PORCH;
	  lcd_config.vConfig.vfp = LCD_V_FRONT_PORCH;
	  lcd_config.vConfig.vsw = LCD_V_PULSE;
	  lcd_config.panel_clk   = LCD_PIX_CLK;
	  lcd_config.polarity.active_high = 1;
	  lcd_config.polarity.cpl = LCD_H_SIZE;
	  lcd_config.polarity.invert_hsync = 1;
	  lcd_config.polarity.invert_vsync = 1;
	  lcd_config.polarity.invert_panel_clock = 1;

	  lcd_config.lcd_panel_upper =  LCD_VRAM_BASE_ADDR_UPPER;
	  lcd_config.lcd_panel_lower =  LCD_VRAM_BASE_ADDR_LOWER;

	  lcd_config.lcd_bpp = LCD_BPP_24;
	  lcd_config.lcd_type = LCD_TFT;
	  lcd_config.lcd_palette = _NULL;
	  lcd_config.lcd_bgr = FALSE;

	  // Init LCD HW
	  LCD_Init (&lcd_config);

	  // clear background.
	  LCD_SetImage(LCD_PANEL_UPPER, NULL);
	  LCD_SetImage(LCD_PANEL_LOWER, NULL);
}

void Init_LCD_Cursor(void)
{
	 cursor_config.baseaddress = LCD_CURSOR_BASE_ADDR;
	  cursor_config.framesync = 1;
	#if (CURSOR_SIZE == 64)
	  cursor_config.size32 = 0;
	#else
	  cursor_config.size32 = 1;
	#endif
	  cursor_config.palette[0].Red = 0x00;
	  cursor_config.palette[0].Green = 0x00;
	  cursor_config.palette[0].Blue = 0x00;
	  cursor_config.palette[1].Red = 0xFF;
	  cursor_config.palette[1].Green = 0xFF;
	  cursor_config.palette[1].Blue = 0xFF;
	  LCD_Cursor_Cfg(&cursor_config);
	  LCD_Cursor_SetImage((uint32_t *)Cursor, 0, sizeof(Cursor)/sizeof(uint32_t)) ;
}
// --------------------------------------------------
// Initialization of the backlight LCD. Using PWM.
void Init_LCD_BackLight(void)
{
    uint32_t pclk;
	PWM_TIMERCFG_Type PWMCfgDat;
	PWM_MATCHCFG_Type PWMMatchCfgDat;

	pclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
	PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
	PWMCfgDat.PrescaleValue = 1;
	PWM_Init(LCD_BL_PWM_PERI_ID, PWM_MODE_TIMER, (void *) &PWMCfgDat);
	PINSEL_ConfigPin(LCD_BL_PWM_PORT, LCD_BL_PWM_PIN, 1);		// funct.no.1 - PWM1[2] — Pulse Width Modulator 1, channel 2 output.
	PWM_MatchUpdate(LCD_BL_PWM_PERI_ID, LCD_BL_PWM_PERI_CHA, pclk / LCD_BL_PWM_BASE, PWM_MATCH_UPDATE_NOW);

	// UPDATE VALUE OF THE PWM DUTY CYCLE
	PWM_MatchUpdate(LCD_BL_PWM_PERI_ID, LCD_BL_PWM_PERI_CHB , 0 *(( pclk / LCD_BL_PWM_BASE) / 100), PWM_MATCH_UPDATE_NOW); // switch off backlight
	PWMMatchCfgDat.IntOnMatch = DISABLE;							// without interrupt
	PWMMatchCfgDat.MatchChannel = LCD_BL_PWM_PERI_CHB;			// Match channel register - duty cycle	- xx %
	PWMMatchCfgDat.ResetOnMatch = DISABLE;						//
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LCD_BL_PWM_PERI_ID, &PWMMatchCfgDat);		// store it
	PWM_ChannelCmd(LCD_BL_PWM_PERI_ID, LCD_BL_PWM_PERI_CHB, ENABLE);	// Enable PWM Channel Output

	PWM_ResetCounter(LCD_BL_PWM_PERI_ID);						// reset and start counter
	PWM_CounterCmd(LCD_BL_PWM_PERI_ID, ENABLE);					// start PWM Counter
	PWM_Cmd(LCD_BL_PWM_PERI_ID, ENABLE);						// start PWM
}

// --------------------------------------------------
// Set nev intensity [%] of backlight.
void Set_LCD_BackLight(uint16_t level)		// Level: 0-100%
{
	uint32_t pclk;
	pclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);
	if (level > 100) level = 100;
	PWM_MatchUpdate(LCD_BL_PWM_PERI_ID, LCD_BL_PWM_PERI_CHB,level * ((pclk / LCD_BL_PWM_BASE) / 100), PWM_MATCH_UPDATE_NOW);
}

void Set_LCD_Cursor(int x, int y)
{
	LCD_Move_Cursor( x, y);
}
