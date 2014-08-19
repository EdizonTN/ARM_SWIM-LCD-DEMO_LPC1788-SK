/*
 * TS_Analog.c
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#include "global.h"
#include "../Chip/Drivers/Include/lpc177x_8x_timer.h"
#include "../Chip/Drivers/Include/lpc177x_8x_gpio.h"
#include "../Chip/Drivers/Include/lpc177x_8x_pinsel.h"
#include "../Chip/Drivers/Include/lpc177x_8x_adc.h"


// ******************************************************************************************************
// Function prototypes
// ******************************************************************************************************
// extern unsigned long install_irq(unsigned long IntNumber, void *HandlerAddr, unsigned long Priority);
void Init_TS(void);
void Enable_TS(void);
void Disable_TS(void);
// private
static void _Set_TS_to_digital(void);									// switch pin function to digital sensing of press touch area

// ******************************************************************************************************
// Globals
// ******************************************************************************************************
static int16_t ConvertCoord(int16_t Coord, int16_t MinVal, int16_t MaxVal, int16_t TrueSize);
uint8_t TS_Activated_Flag;
unsigned int x_values[num_samples]; 									// array to store x_samples
unsigned int y_values[num_samples]; 									// array to store y_samples
static short TS_x_value = 1;
static short TS_y_value = -1;
TS_Init_Type TS_Config;
// --------------------------------------------------

// --------------------------------------------------
// Reconfigure appropriate pins connected to TS for digital function.
// After press to TS, this event generate interrupt.
void _Set_TS_to_digital(void)
{
	//unsigned int test;

	//X2 pin - Input, without pull resistors
	PINSEL_ConfigPin(TS_X2_PORT,TS_X2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_X2_PORT,TS_X2_PIN, PINSEL_BASICMODE_PULLUP);	// without pull resistors
	FIO_SetDir(TS_X2_PORT, 1 << TS_X2_PIN, GPIO_DIRECTION_INPUT);		// Set as Input

	//Y2 pin - Output, set to 0
	PINSEL_ConfigPin(TS_Y2_PORT,TS_Y2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_Y2_PORT,TS_Y2_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_Y2_PORT, 1 << TS_Y2_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_ClearValue(TS_Y2_PORT, 1 << TS_Y2_PIN);							// set to log.0

	//Y1 pin - Output, without pull resistors
	PINSEL_ConfigPin(TS_Y1_PORT,TS_Y1_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_Y1_PORT,TS_Y1_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_Y1_PORT, 1 << TS_Y1_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_ClearValue(TS_Y1_PORT, 1 << TS_Y1_PIN);							// set to log.0

	//X1 pin - Input, without pull resistors
	PINSEL_SetAnalogPinMode(TS_X1_PORT, TS_X1_PIN, DISABLE);			// set to analog mode
	PINSEL_ConfigPin(TS_X1_PORT,TS_X1_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_X1_PORT,TS_X1_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_X1_PORT, 1 << TS_X1_PIN, GPIO_DIRECTION_INPUT);		// Set as Input

}


// --------------------------------------------------
// return True if Touch screen is pressed
int _Get_TS_PressStatus(void)
{
	if ((GPIO_ReadValue(TS_X1_PORT) & (1 << TS_X1_PIN))) return (FALSE);
	else return (TRUE);
}


// --------------------------------------------------
// Detected IRQ event from X-Plus line, Falling edge.
void GPIO_IRQHandler(void)
{
	if(GPIO_GetIntStatus(TS_X1_PORT, TS_X1_PIN, 1))
	{
		GPIO_ClearInt(TS_X1_PORT, 1 << TS_X1_PIN);
		if (TS_Activated_Flag == TRUE) return;
		TIM_Waitms (debounce); 											// debounce the touch
		if(_Get_TS_PressStatus() == TRUE )								// set flag ...
		{
			TS_Activated_Flag = SET;
		}
	}
}


// --------------------------------------------------
// Firts initialization of the TS hardware
void Init_TS(void)
{
	TIM_TIMERCFG_Type TIM_ConfigStruct;


	TS_Config.ad_left = TOUCH_AD_LEFT;
	TS_Config.ad_right = TOUCH_AD_RIGHT;
	TS_Config.ad_top = TOUCH_AD_TOP;
	TS_Config.ad_bottom = TOUCH_AD_BOTTOM;
	TS_Config.lcd_h_size = LCD_H_SIZE;
	TS_Config.lcd_v_size = LCD_V_SIZE;
	TS_Config.Priority = 31;

	// init timer
    TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
    TIM_ConfigStruct.PrescaleValue  = 1;
    // Set configuration for Tim_config and Tim_MatchConfig
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);

	GPIO_Init();
	_Set_TS_to_digital();												// set TS pins to digital mode

	// next, read IO0IntEnF register and set only desired bit.
	if (TS_X1_PORT == 0)
	{
		FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO0IntEnF | (1 << TS_X1_PIN), 1);			// set IRQ for X1 to Falling edge
	}
    else if(TS_X1_PORT == 2)
	{
    	FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO2IntEnF | (1 << TS_X1_PIN), 1);			// set IRQ for X1 to Falling edge
	}

	NVIC_SetPriority(GPIO_IRQn, TS_Config.Priority);
	NVIC_EnableIRQ(GPIO_IRQn);
}

// --------------------------------------------------
// freeing memory
void DeInit_TS(void)
{
	GPIO_Deinit();
}


// --------------------------------------------------
// conversion from ADC value to the screen resolution values
static int16_t ConvertCoord(int16_t Coord, int16_t MinVal, int16_t MaxVal, int16_t TrueSize)
{
	int16_t tmp;
	int16_t ret;
	uint8_t convert = 0;

	if (MinVal > MaxVal)        										// Swap value
	{
		tmp = MaxVal;
		MaxVal = MinVal;
		MinVal = tmp;
		convert = 1;
	}

	ret = (Coord - MinVal) * TrueSize / (MaxVal - MinVal);
	if (convert)
		ret = TrueSize - ret;

	return ret;
}

// --------------------------------------------------
// reconfigure appropriate TS pins to analog function
// and read ADC val;ue for X and Y coord.
void TS_Read(void)
{
	uint32_t i;

	NVIC_DisableIRQ(GPIO_IRQn);											// Important !

	//X2 pin - Output, without pull resistors - set to 0
	PINSEL_ConfigPin(TS_X2_PORT,TS_X2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_X2_PORT,TS_X2_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_X2_PORT, 1 << TS_X2_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_ClearValue(TS_X2_PORT, 1 << TS_X2_PIN);							// set to log.0

	//Y2 pin - Input, without pull resistors - set as floating
	PINSEL_ConfigPin(TS_Y2_PORT,TS_Y2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_Y2_PORT,TS_Y2_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_Y2_PORT, 1 << TS_Y2_PIN, GPIO_DIRECTION_INPUT);		// Set as Input

	//X1 pin - Output, with pull-up resistors - set to 1
	PINSEL_ConfigPin(TS_X1_PORT,TS_X1_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_X1_PORT,TS_X1_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_X1_PORT, 1 << TS_X1_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_SetValue(TS_X1_PORT, 1 << TS_X1_PIN);							// set to log.1

	//Y1 pin - connected to AD Converter
	PINSEL_ConfigPin(TS_Y1_PORT,TS_Y1_PIN, TS_Y1_FUNC_NO);				// switch alternate function no.
	PINSEL_SetAnalogPinMode(TS_Y1_PORT, TS_Y1_PIN, ENABLE);				// set to analog mode

	TIM_Waitms(TS_SETTLING_TIME);										// settling time for switching

	ADC_Init(LPC_ADC, 400000);
	for (i = 0; i < num_samples; i++)
	{
		ADC_ChannelCmd(LPC_ADC, TS_Y1_ADC_CH, ENABLE);
		ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		while (!(ADC_ChannelGetStatus(LPC_ADC, TS_Y1_ADC_CH, ADC_DATA_DONE)));
		ADC_ChannelCmd(LPC_ADC, TS_Y1_ADC_CH, DISABLE);
		x_values[i] = (ADC_ChannelGetData(LPC_ADC,TS_Y1_ADC_CH) >> 4 ) & TS_CONVERSION_MAX;			//mask for TS_CONVERSION BITS AD Convert result !
	}
	//ADC_DeInit(LPC_ADC);

	//Y2 pin - Output, without pull resistors - set to 0
	PINSEL_ConfigPin(TS_Y2_PORT,TS_Y2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_Y2_PORT,TS_Y2_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_Y2_PORT, 1 << TS_Y2_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_ClearValue(TS_Y2_PORT, 1 << TS_Y2_PIN);							// set to log.0

	//X2 pin - Input, without pull resistors - set as floating
	PINSEL_ConfigPin(TS_X2_PORT,TS_X2_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_X2_PORT,TS_X2_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_X2_PORT, 1 << TS_X2_PIN, GPIO_DIRECTION_INPUT);		// Set as Input

	//Y1 pin - Output, with pull-up resistors - set to 1
	PINSEL_SetAnalogPinMode(TS_Y1_PORT, TS_Y1_PIN, DISABLE);			// set back to digital mode
	PINSEL_ConfigPin(TS_Y1_PORT,TS_Y1_PIN, 0);							// Set default function no. - GPIO
	PINSEL_SetPinMode(TS_Y1_PORT,TS_Y1_PIN, PINSEL_BASICMODE_PLAINOUT);	// without pull resistors
	FIO_SetDir(TS_Y1_PORT, 1 << TS_Y1_PIN, GPIO_DIRECTION_OUTPUT);		// Set as Output
	FIO_SetValue(TS_Y1_PORT, 1 << TS_Y1_PIN);							// set to log.1

	//X1 pin - connected to AD Converter
	PINSEL_ConfigPin(TS_X1_PORT,TS_X1_PIN, TS_X1_FUNC_NO);				// switch alternate function no.
	PINSEL_SetAnalogPinMode(TS_X1_PORT, TS_X1_PIN, ENABLE);				// set to analog mode

	TIM_Waitms(TS_SETTLING_TIME); 					// settling time for switching

	ADC_Init(LPC_ADC, 400000);
	for (i = 0; i < num_samples; i++)
	{
		ADC_ChannelCmd(LPC_ADC, TS_X1_ADC_CH, ENABLE);
		ADC_StartCmd(LPC_ADC, ADC_START_NOW);;
		while (!(ADC_ChannelGetStatus(LPC_ADC, TS_X1_ADC_CH, ADC_DATA_DONE)));
		ADC_ChannelCmd(LPC_ADC, TS_X1_ADC_CH, DISABLE);
		y_values[i] = (ADC_ChannelGetData(LPC_ADC,TS_X1_ADC_CH) >> 4) & TS_CONVERSION_MAX;		//mask for TS_CONVERSION BITS AD Convert result !
	}
	PINSEL_SetAnalogPinMode(TS_X1_PORT, TS_X1_PIN, DISABLE);			// set back to digital mode
	ADC_DeInit(LPC_ADC);

	_Set_TS_to_digital(); 												// switch TS pins back to digital functions
	NVIC_EnableIRQ(GPIO_IRQn);											// Can be ...

	TS_x_value = 0;														// initial value
	for (i=0; i < num_samples; i++)	TS_x_value += x_values[i]; 			// add up the conversion results
	TS_x_value = TS_x_value /num_samples; 								// get average
	TS_y_value = 0;														// initial value
	for (i=0; i < num_samples; i++)	TS_y_value += y_values[i]; 			// add up conversion results
	TS_y_value = TS_y_value /num_samples; 								// get average
}



// --------------------------------------------------
// fill pointer to X and Y coord with newest values
void GetTouchCoord(int16_t *pX, int16_t* pY)
{
	uint16_t i, tmp;
	int16_t coord, x = -1, y = -1, z1 = -1, z2 = -1, z;

	TS_Read();

	if ((TS_x_value >= 0) && (TS_y_value >= 0))							// adjust to truly size of LCD
	{
		*pY = ConvertCoord(TS_y_value, TS_Config.ad_bottom, TS_Config.ad_top, TS_Config.lcd_v_size);
		*pX = ConvertCoord(TS_x_value, TS_Config.ad_left, TS_Config.ad_right, TS_Config.lcd_h_size);
	}
	TS_x_value = TS_y_value = -1;

}

// --------------------------------------------------
// enable IRQ from TS press event
void Enable_TS(void)
{
	// next, read IO0IntEnF register and set only desired bit.
	if (TS_X1_PORT == 0)
	{
		FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO0IntEnF | (1 << TS_X1_PIN), 1);			// set IRQ for X1 to Falling edge
	}
    else if(TS_X1_PORT == 2)
	{
    	FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO2IntEnF | (1 << TS_X1_PIN), 1);			// set IRQ for X1 to Falling edge
	}

}

// --------------------------------------------------
// disable IRQ from TS press event
void Disable_TS(void)
{
	// next, read IO0IntEnF register and clear only desired bit.
	if (TS_X1_PORT == 0)
	{
		FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO0IntEnF & ~(1 << TS_X1_PIN), 1);			// clear IRQ for X1 to Falling edge
	}
    else if(TS_X1_PORT == 2)
	{
    	FIO_IntCmd(TS_X1_PORT, LPC_GPIOINT->IO2IntEnF & ~(1 << TS_X1_PIN), 1);			// clear IRQ for X1 to Falling edge
	}

}

