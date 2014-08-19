/*
 * RPOT.c
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#include "global.h"
#include "../Chip/Drivers/Include/lpc177x_8x_pinsel.h"
#include "../Chip/Drivers/Include/lpc177x_8x_adc.h"

// ******************************************************************************************************
// Function prototypes
// ******************************************************************************************************
void Init_RPOT(void);

// ******************************************************************************************************
// Globals
// ******************************************************************************************************

// --------------------------------------------------
// First HW initialization
void Init_RPOT(void)
{
	PINSEL_ConfigPin (RPOT_ADC_PREPARED_CH_PORT, RPOT_ADC_PREPARED_CH_PIN, RPOT_ADC_PREPARED_CH_FUNC_NO);
	PINSEL_SetAnalogPinMode(RPOT_ADC_PREPARED_CH_PORT, RPOT_ADC_PREPARED_CH_PIN,ENABLE);

	ADC_Init(LPC_ADC, 400000);
	//ADC_IntConfig(LPC_ADC, RPOT_ADC_PREPARED_INTR, DISABLE);
	ADC_ChannelCmd(LPC_ADC, RPOT_ADC_PREPARED_CHANNEL, ENABLE);
}

// --------------------------------------------------
// Freeing memory
void DeInit_RPOT(void)
{

}

// --------------------------------------------------
// Get fresh value.
uint16_t Get_RPOT_Value(void)
{
	uint16_t res;

	ADC_Init(LPC_ADC, 400000);
	ADC_ChannelCmd(LPC_ADC, RPOT_ADC_PREPARED_CHANNEL, ENABLE);

	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	do
	{
		if ((LPC_ADC->CR & (1 << RPOT_ADC_PREPARED_CHANNEL))==0)		// if current channel is another then selected -> exit
		{
			ADC_ChannelCmd(LPC_ADC, RPOT_ADC_PREPARED_CHANNEL, DISABLE);
			ADC_DeInit(LPC_ADC);
			return (-1);
		}
	}
	while (!(ADC_ChannelGetStatus(LPC_ADC, RPOT_ADC_PREPARED_CHANNEL, ADC_DATA_DONE)));
	res = ADC_ChannelGetData(LPC_ADC, RPOT_ADC_PREPARED_CHANNEL);
	ADC_DeInit(LPC_ADC);
	return(res);
}
