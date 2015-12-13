/***********************************************************************
 *   $Id:: gpio.h 9365 2014-07-15 22:51:19                        $
 *
 * Project: CANopen Application for LPC11C24 (slave node)
 *
 *   Description:
 *     This file contains definition and prototype for GPIO.
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#ifndef __GPIO_H
#define __GPIO_H

#define PORT0		0
#define PORT1		1
#define PORT2		2
#define PORT3		3
static LPC_GPIO_TypeDef (* const LPC_GPIO[4]) = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3 };
void PIOINT0_IRQHandler(void);
void PIOINT1_IRQHandler(void);
void PIOINT2_IRQHandler(void);
void PIOINT3_IRQHandler(void);
void GPIOInit( void );
void GPIOSetInterrupt( uint32_t portNum, uint32_t bitPosi, uint32_t sense,
		uint32_t single, uint32_t event );
void GPIOIntEnable( uint32_t portNum, uint32_t bitPosi );
void GPIOIntDisable( uint32_t portNum, uint32_t bitPosi );
uint32_t GPIOIntStatus( uint32_t portNum, uint32_t bitPosi );
void GPIOIntClear( uint32_t portNum, uint32_t bitPosi );
uint32_t GPIOGetValue( uint32_t portNum, uint32_t bitPosi );
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal );
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir );

#endif /* end __GPIO_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
