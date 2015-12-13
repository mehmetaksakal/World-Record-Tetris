/***********************************************************************
 *   $Id:: leddriver.c 9365 2014-07-15 22:51:19                        $
 *
 * Project: CANopen Application for LPC11C24 (slave node)
 *
 *   Description:
 *     This file contains RGB LED driver code which include GPIO
 *     initialization and related APIs
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#include "leddriver.h"


/* Initialize GPIO block */
void LED_Init(MY_LED_T *my_led)
{
	GPIOInit();

	my_led->LED1 = 0x00;

	GPIOSetDir(PORT0, 3, 1);
	GPIOSetDir(PORT1, 10, 1);
	GPIOSetDir(PORT1, 11, 1);

	GPIOSetValue(PORT0, 3, 0);
	GPIOSetValue(PORT1, 10, 0);
	GPIOSetValue(PORT1, 11, 0);

	my_led->LED2 = 0x00;
	GPIOSetDir(PORT2, 0, 1);
	GPIOSetDir(PORT2, 1, 1);
	GPIOSetDir(PORT2, 2, 1);

	GPIOSetValue(PORT2, 0, 0);
	GPIOSetValue(PORT2, 1, 0);
	GPIOSetValue(PORT2, 2, 0);

	my_led->LED3 = 0x00;
	GPIOSetDir(PORT1, 4, 1);
	GPIOSetDir(PORT1, 5, 1);
	GPIOSetDir(PORT1, 8, 1);

	GPIOSetValue(PORT1, 4, 0);
	GPIOSetValue(PORT1, 5, 0);
	GPIOSetValue(PORT1, 8, 0);

	my_led->LED4 = 0x00;
	GPIOSetDir(PORT3, 0, 1);
	GPIOSetDir(PORT3, 1, 1);
	GPIOSetDir(PORT3, 2, 1);

	GPIOSetValue(PORT3, 0, 0);
	GPIOSetValue(PORT3, 1, 0);
	GPIOSetValue(PORT3, 2, 0);

	return;
}

void LED_Test(MY_LED_T *my_led)
{
	uint32_t i;
	i = 0;

	LED_WriteValue(my_led, 1, 0x01);
	LED_WriteValue(my_led, 2, 0x01);
	LED_WriteValue(my_led, 3, 0x01);
	LED_WriteValue(my_led, 4, 0x01);

	for(i = 0; i < 2000000; i++);

	LED_WriteValue(my_led, 1, 0x02);
	LED_WriteValue(my_led, 2, 0x02);
	LED_WriteValue(my_led, 3, 0x02);
	LED_WriteValue(my_led, 4, 0x02);

	for(i = 0; i < 2000000; i++);

	LED_WriteValue(my_led, 1, 0x04);
	LED_WriteValue(my_led, 2, 0x04);
	LED_WriteValue(my_led, 3, 0x04);
	LED_WriteValue(my_led, 4, 0x04);

	for(i = 0; i < 2000000; i++);

	LED_WriteValue(my_led, 1, 0x00);
	LED_WriteValue(my_led, 2, 0x00);
	LED_WriteValue(my_led, 3, 0x00);
	LED_WriteValue(my_led, 4, 0x00);
}

void LED_WriteValue(MY_LED_T *my_led, char LEDn, char val)
{
	switch(LEDn)
	{
	case 0x01:
		my_led->LED1 = val;

		GPIOSetValue(PORT0, 3, (val & 0x01) );
		GPIOSetValue(PORT1, 10, (val & 0x02) >> 1);
		GPIOSetValue(PORT1, 11, (val & 0x04) >> 2);

		break;

	case 0x02:

		my_led->LED2 = val;

		GPIOSetValue(PORT3, 0, (val & 0x01) );
		GPIOSetValue(PORT3, 1, (val & 0x02) >> 1);
		GPIOSetValue(PORT3, 2, (val & 0x04) >> 2);

		break;

	case 0x03:

		my_led->LED3 = val;

		GPIOSetValue(PORT2, 0, (val & 0x01) );
		GPIOSetValue(PORT2, 1, (val & 0x02) >> 1);
		GPIOSetValue(PORT2, 2, (val & 0x04) >> 2);

		break;

	case 0x04:

		my_led->LED4 = val;

		GPIOSetValue(PORT1, 4, (val & 0x01) );
		GPIOSetValue(PORT1, 5, (val & 0x02) >> 1);
		GPIOSetValue(PORT1, 8, (val & 0x04) >> 2);

		break;
	default:
		break;
	}
}


