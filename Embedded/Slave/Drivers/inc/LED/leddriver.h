/***********************************************************************
 *   $Id:: leddriver.h 9365 2014-07-15 22:51:19                        $
 *
 * Project: CANopen Application for LPC11C24 (slave node)
 *
 *   Description:
 *     This file contains definition and prototype for driving RGB LEDs.
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "LPC11xx.h"
#include "gpio.h"

typedef struct {				/*!< LED_PORT Structure */
	char LED1;
	char LED2;
	char LED3;
	char LED4;

	char LED1_R;
	char LED1_G;
	char LED1_B;

	char LED2_R;
	char LED2_G;
	char LED2_B;

	char LED3_R;
	char LED3_G;
	char LED3_B;

	char LED4_R;
	char LED4_G;
	char LED4_B;

} MY_LED_T;

void LED_WriteValue(MY_LED_T *my_led, char LEDn, char val);
void LED_Init(MY_LED_T *my_led);
void LED_Test(MY_LED_T *my_led);

#endif /* LED_DRIVER_H_ */
