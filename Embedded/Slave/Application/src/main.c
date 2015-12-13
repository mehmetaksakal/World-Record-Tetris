/***********************************************************************
 * $Id:: main.c 1604 2012-04-24 11:34:47     $
 *
 * Project: CANopen Application for LPC11Cxx (slave node)
 *
 * Description:
 *   CANopen using on-chip CANopen drivers
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#include "LPC11xx.h"
#include "canopen_driver.h"
#include "CAN_Node_Def.h"
#include "gpio.h"
#include "leddriver.h"
#include "adc.h"

/* interrupts */
void TIMER16_0_IRQHandler(void);

/* CAN Callback function prototypes */
void CANopen_Init_SDO(void);								/* callback function for setting initial SDO */
void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID);	/* callback function for heartbeat consumer did not send heartbeat in time */
void CANopen_NMT_Reset_Node_Received(void);					/* callback function for reacting to NMT command Reset Node  */
void CANopen_NMT_Reset_Comm_Received(void);					/* callback function for reacting to NMT command Reset Communication */

/* Global Variables */
MY_LED_T led_obj;


/*****************************************************************************
** Function name:		main
**
** Description:			C entry. Initializes HW and starts application code
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
int main(void)
{
	SystemInit();
	ADCInit( ADC_CLK );
	CANopenInit();
	LED_Init(&led_obj);
	LED_Test(&led_obj);

	GPIOSetDir(PORT0, 11, 0);

	/* Timer16B0 */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);		/* Enable clock for 16-bit counter/timer 0 */
	LPC_TMR16B0->MCR = 3;						/* Interrupt and Reset on MR0 */
	LPC_TMR16B0->MR0 = SystemCoreClock/1000;	/* Interrupt and Reset on MR0 */
    NVIC_EnableIRQ(TIMER_16_0_IRQn);			/* Enable the Timer0 Interrupt */
    LPC_TMR16B0->TCR = 1;						/* Enable Timer0 */

    LED1 = 0x00;
    LED2 = 0x00;
    LED3 = 0x00;
    LED4 = 0x00;
    HighVoltage = 0x00;
    ADCValue_MSB = 0x00;
    ADCValue_LSB = 0x00;

	while(1)
	{

	}

	return 0;
}

/*****************************************************************************
** Function name:		TIMER16_0_IRQHandler
**
** Description:			Set to fire every 1ms
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void TIMER16_0_IRQHandler(void)
{
	uint16_t ADCValue;
	LPC_TMR16B0->IR = 1;			/* clear interrupt flag */

	/* CANopen 1ms tick */
	CANopen_1ms_tick();

	HighVoltage = GPIOGetValue(PORT0, 11);

	ADCValue = ADCRead(1);
	ADCValue_MSB = ((ADCValue & 0xFF00) >> 2);
	ADCValue_LSB =  (ADCValue & 0x00FF);



	/*PWMTick--;

	if( PWMTick == LED1_r)
	{
		LED_WriteValue(&led_obj, 1, led_obj.LED1 | 0x01);
	}


	if( PWMTick == LED1_g)
	{
		LED_WriteValue(&led_obj, 1, led_obj.LED1 & 0xFD);
	}


	if( PWMTick == LED1_b)
	{
		LED_WriteValue(&led_obj, 1, led_obj.LED1 & 0xFB);
	}



	if(PWMTick == 1)
	{
		PWMTick = 10;
		LED_WriteValue(&led_obj, 1, led_obj.LED1 & 0xFE);
		LED_WriteValue(&led_obj, 1, led_obj.LED1 | 0x02);
		LED_WriteValue(&led_obj, 1, led_obj.LED1 | 0x04);
	}*/



    /* display value of LEDs */
    LED_WriteValue(&led_obj, 1, LED1);
    LED_WriteValue(&led_obj, 2, LED2);
    LED_WriteValue(&led_obj, 3, LED3);
    LED_WriteValue(&led_obj, 4, LED4);


}

/*****************************************************************************
** Function name:		CANopen_Init_SDO
**
** Description:			Callback function for initializing SDO parameters
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_Init_SDO(void)
{
	uint32_t i;

	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;

	error_register = 0;
	for(i=0; i<WatchListLength; i++)
	{
		WatchList[i].value = 0;
		WatchList[i].counter = 0;
	}
	CANopen_Heartbeat_Producer_Value = 0;
	CANopen_Heartbeat_Producer_Counter = 0;
}

/*****************************************************************************
** Function name:		NMT_Reset_Node
**
** Description:			NMT Reset Node callback.
** 						Called upon receiving reset node NMT command.
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Reset_Node_Received(void)
{
    LED_WriteValue(&led_obj, 1, 0x00);
    LED_WriteValue(&led_obj, 2, 0x00);
    LED_WriteValue(&led_obj, 3, 0x00);
    LED_WriteValue(&led_obj, 4, 0x00);
}

/*****************************************************************************
** Function name:		NMT_Reset_Comm
**
** Description:			NMT Reset Communication.
** 						Called upon CanInit / receiving reset node/communication NMT command.
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Reset_Comm_Received(void)
{
    LED_WriteValue(&led_obj, 1, 0x00);
    LED_WriteValue(&led_obj, 2, 0x00);
    LED_WriteValue(&led_obj, 3, 0x00);
    LED_WriteValue(&led_obj, 4, 0x00);
}

/*****************************************************************************
** Function name:		CAN_Heartbeat_Fail
**
** Description:			CAN heartbeat fail callback.
** 						Function is executed when a heartbeat producer which
** 						is listed in the heartbeat consumer list did not
** 						send a heartbeat on time. Callback functions is executed
** 						after sending the NMT reset command.
**
** Parameters:			Node_ID. Contains the number of the Node_ID which did
** 						not respond on time.
** Returned value:		None
*****************************************************************************/
void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID)
{
    LED_WriteValue(&led_obj, 1, 0x00);
    LED_WriteValue(&led_obj, 2, 0x00);
    LED_WriteValue(&led_obj, 3, 0x00);
    LED_WriteValue(&led_obj, 4, 0x00);
}

/*****************************************************************************
** Function name:		CANopen_NMT_Consumer_Bootup_Received
**
** Description:			CAN consumer bootup received callback.
** 						Function is executed when a node which is listed in the
** 						watchlist send a boot-up message.
**
** Parameters:			Node_ID. Contains the number of the Node_ID which send
** 						the boot-up message
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Consumer_Bootup_Received(uint8_t Node_ID)
{
    LED_WriteValue(&led_obj, 1, 0x00);
    LED_WriteValue(&led_obj, 2, 0x00);
    LED_WriteValue(&led_obj, 3, 0x00);
    LED_WriteValue(&led_obj, 4, 0x00);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
