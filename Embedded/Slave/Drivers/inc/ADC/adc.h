/****************************************************************************
 *   $Id:: adc.h 9359 2014-07-19 22:30:24                          $
 *
 * Project: CANopen Application for LPC11Cxx
 *
 *   Description:
 *     This file contains ADC code header definition.
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 ****************************************************************************/

#ifndef __ADC_H
#define __ADC_H

#define ADC_INTERRUPT_FLAG    0	/* 1 is interrupt driven, 0 is polling */
#define BURST_MODE            0 /* Burst mode works in interrupt driven mode only. */
#define SINGLE_BURST_MODE     0 /* Single burst mode works in interrupt driven mode only. */
#define ADGINTEN              0	/* global DONE flag generate interrupt */
#define INTERNAL_VOLT         0	/* If this flag is on, it measures interval voltage,
                                   core voltage, internal Vref, and temperature. */
#define ADC_DEBUG             0
#define ADC_DEBUG_CLEAR_CNT   (100) /* Number of samples until statistics are cleared */
#define ADC_DEBUG_UPDATE_CNT  (5000) /* Number of samples until statistics are cleared */

#define ADC_OFFSET            0x10
#define ADC_INDEX             4

#define ADC_DONE              0x80000000
#define ADC_OVERRUN           0x40000000
#define ADC_ADINT             0x00010000

#define ADC_NUM               4			/* for LPC11xx */
#define ADC_CLK               4400000		/* set to 4.4Mhz */


extern void ADC_IRQHandler( void );
extern void ADCInit( uint32_t ADC_Clk );
extern uint32_t ADCRead( uint8_t channelNum );
extern void ADCBurstRead( void );
#endif /* end __ADC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
