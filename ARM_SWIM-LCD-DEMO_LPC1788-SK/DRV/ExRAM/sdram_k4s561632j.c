/*
 * sdram_k4s561632l.c
 *
 *  Created on: 11.8.2014
 *      Author: peterj
 */

#include "global.h"
#define _EMC				1

#include "../Chip/Drivers/Include/lpc177x_8x_emc.h"
#include "../Chip/Drivers/Include/lpc177x_8x_clkpwr.h"
#include "../Chip/Drivers/Include/lpc177x_8x_pinsel.h"
#include "../Chip/Drivers/Include/lpc177x_8x_timer.h"
//#include "./Include/sdram_k4s561632j.h"


// --------------------------------------------------
// Initialize external SDRAM memory Micron K4S561632J, 256Mbit(8M x 32)
 void Init_SDRAM( void )
{
    volatile uint32_t i;
    volatile unsigned long Dummy;
    EMC_DYN_MEM_Config_Type config;
    TIM_TIMERCFG_Type TIM_ConfigStruct;
      
    TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
    TIM_ConfigStruct.PrescaleValue  = 1;
      
    // Set configuration for Tim_config and Tim_MatchConfig
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
      
    config.ChipSize = 256;
    config.AddrBusWidth = 32;
    config.AddrMap = EMC_ADD_MAP_ROW_BANK_COL;
    config.CSn = 0;
    config.DataWidth = 16;
    config.TotalSize = SDRAM_SIZE;

    config.CASLatency= 3;
    config.RASLatency= 3;
    config.Active2ActivePeriod =EMC_NS2CLK( SDRAM_TRC);
    config.ActiveBankLatency =EMC_NS2CLK( SDRAM_TRRD);
    config.AutoRefrehPeriod = EMC_NS2CLK( SDRAM_TRFC);
    config.DataIn2ActiveTime = SDRAM_TDAL + EMC_NS2CLK( SDRAM_TRP);
    config.DataOut2ActiveTime = SDRAM_TAPR;
    config.WriteRecoveryTime = SDRAM_TWR;
    config.ExitSelfRefreshTime = EMC_NS2CLK( SDRAM_TXSR);
    config.LoadModeReg2Active = SDRAM_TMRD;
    config.PrechargeCmdPeriod = EMC_NS2CLK( SDRAM_TRP);
    config.ReadConfig = 1;  								// Command delayed strategy, using EMCCLKDELAY
    config.RefreshTime = EMC_NS2CLK( SDRAM_REFRESH) >> 4;
    config.Active2PreChargeTime = EMC_NS2CLK( SDRAM_TRAS);
    config.SeftRefreshExitTime = EMC_NS2CLK( SDRAM_TXSR);
    DynMem_Init(&config);
   
    EMC_DynCtrlSDRAMInit(EMC_DYNAMIC_CTRL_SDRAM_NOP); 		// Issue NOP command

    TIM_Waitms(100);                  						// wait 200ms
    EMC_DynCtrlSDRAMInit(EMC_DYNAMIC_CTRL_SDRAM_PALL); 		// Issue Pre-charge command

    for(i = 0; i < 0x80; i++);         						// wait 128 AHB clock cycles
    
    TIM_Waitms(100);    
    EMC_DynCtrlSDRAMInit(EMC_DYNAMIC_CTRL_SDRAM_MODE); 		// Issue MODE command
    Dummy = *((volatile uint32_t *)(SDRAM_BASE_ADDR | (0x32<<13)));  // Mode Register Setting

    //Timing for 48/60/72MHZ Bus
    EMC_DynCtrlSDRAMInit(EMC_DYNAMIC_CTRL_SDRAM_NORMAL); 	// Issue NORMAL command

    //enable buffers
    EMC_DynMemConfigB(0, EMC_DYNAMIC_CFG_BUFF_ENABLED);
    for(i = 100000; i;i--);
    
    TIM_DeInit(LPC_TIM0);
}
