// ******************************************************************************************************
// main.c
//
//  Created on: 20.8.2014
//      Author: "EdizonTN@gmail.com"
//	   version: 0.1
// ******************************************************************************************************
#include "global.h"
#include "../Chip/Drivers/Include/lpc177x_8x_lcd.h"

// ******************************************************************************************************
// Globals
// ******************************************************************************************************
extern LCD_Config_Type 	lcd_config;						// LCD active struct

// ******************************************************************************************************
// Function prototypes
// ******************************************************************************************************





// ------------------------------------------------------------------------------------------------------
// Function description
void main(void)
{
	BOOL_32 Result;
    SWIM_WINDOW_T MainWindow;
    SWIM_WINDOW_T FloatWindow;
    COLOR_T clr, *fblog;


	Init_SDRAM();
	Init_LCD();
	//Init_LCD_Cursor();
	Init_LCD_BackLight();
	//Init_TS();

	Enable_LCD();

	Set_LCD_BackLight(100);								// set backlight to 20%

	fblog = (COLOR_T *)lcd_config.lcd_panel_upper;
	Result = swim_window_open(&MainWindow, LCD_H_SIZE, LCD_V_SIZE, fblog, 0, 0, 319, 239, 2, GREEN, WHITE, BLUE);
	//swim_set_title(&MainWindow, "Main\0", BLUE);
	swim_set_pen_color(&MainWindow, BLACK);
	swim_set_font(&MainWindow,(FONT_T *)&font_x5x7);
	swim_put_text(&MainWindow, "Font: font_x5x7\n");
	swim_set_font(&MainWindow,(FONT_T *)&font_x6x13);
	swim_put_text(&MainWindow, "Font: font_x6x13\n");
	swim_set_font(&MainWindow,(FONT_T *)&font_rom8x8);
	swim_put_text(&MainWindow, "Font: font_rom8x8\n");
	swim_set_font(&MainWindow,(FONT_T *)&font_rom8x16);
	swim_put_text(&MainWindow, "Font: font_rom8x16\n");
	swim_set_font(&MainWindow,(FONT_T *)&font_winfreesys14x16);
	swim_put_text(&MainWindow, "Font: font_winfreesys14x16\n");

	Result = swim_window_open(&FloatWindow, LCD_H_SIZE, LCD_V_SIZE, fblog, 0, 150, 220 , 220, 2, RED, YELLOW, YELLOW);
	swim_set_title(&FloatWindow, "Floating window\0", GREEN);
	swim_set_font(&FloatWindow,(FONT_T *)&font_x5x7);

	unsigned long i=0;
	unsigned char buff[200];
	do
	{
		swim_set_font(&MainWindow,(FONT_T *)&font_winfreesys14x16);
		sprintf(&buff[0],"Counter main: %d\n",i);
		swim_put_text_xy(&MainWindow, buff, 160,80);

		swim_set_font(&FloatWindow,(FONT_T *)&font_x5x7);
		sprintf(&buff[0],"Counter float: %d\n",i);
		swim_put_text_xy(&FloatWindow, buff,50,20);

		i ++;
		if(i%202 == 0)
		{
			if(i>5200) i=0;
			//swim_window_close(&FloatWindow);
			Result = swim_window_open(&FloatWindow, LCD_H_SIZE, LCD_V_SIZE, fblog, (i/100) +2, 150, (i/100 )+220 , 220, 2, RED, YELLOW, YELLOW);
			swim_set_title(&FloatWindow, "Floating window\0", GREEN);
		}

	}while(1);
}
