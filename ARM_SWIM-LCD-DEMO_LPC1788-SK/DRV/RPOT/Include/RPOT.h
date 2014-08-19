/*
 * RPOT.h
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#ifndef RPOT_H_
#define RPOT_H_

// ******************************************************************************************************
// ADC Input - Potentiometer - connection:
// ******************************************************************************************************
#define RPOT_ADC_PREPARED_CHANNEL		BSP_RPOT_ADC_PREPARED_CHANNEL
#define RPOT_ADC_PREPARED_INTR			BSP_RPOT_ADC_PREPARED_INTR
#define RPOT_ADC_PREPARED_CH_PORT		BSP_RPOT_ADC_PREPARED_CH_PORT
#define RPOT_ADC_PREPARED_CH_PIN		BSP_RPOT_ADC_PREPARED_CH_PIN
#define RPOT_ADC_PREPARED_CH_FUNC_NO	BSP_RPOT_ADC_PREPARED_CH_FUNC_NO

// ******************************************************************************************************
// Export
// ******************************************************************************************************
// Do NOT modify next lines !!!
void Init_RPOT(void);
uint16_t Get_RPOT_Value(void);

#endif /* RPOT_H_ */
