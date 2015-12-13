/***********************************************************************
 * $Id:: main.c 1604 2014-07-14 11:34:47     $
 *
 * Project: CANopen Application for LPC11C24 (entry node)
 *
 * Description:
 *   CANopen using on-chip CANopen drivers
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/
#include "LPC11xx.h"
#include "ring_buffer.h"
#include "uart.h"
#include "canopen_driver.h"
#include "CAN_Node_Def.h"
#include "CAN_Node_cmd.h"

/* Transmit and receive ring buffers */
static RINGBUFF_T txring, rxring;

/* Transmit and receive ring buffer sizes */
#define UART_SRB_SIZE 128	/* Send */
#define UART_RRB_SIZE 32	/* Receive */

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

/* interrupts */
void TIMER16_0_IRQHandler(void);
void UART_IRQHandler(void);

/* CAN Callback function prototypes */
void CANopen_Init_SDO(void); /* callback function for setting initial SDO */
void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID); /* callback function for heartbeat consumer did not send heartbeat in time */
void CANopen_NMT_Reset_Node_Received(void); /* callback function for reacting to NMT command Reset Node  */
void CANopen_NMT_Reset_Comm_Received(void); /* callback function for reacting to NMT command Reset Communication */

/* used by application */
void Print_SDO_SEG_Entry(uint8_t node_id, uint16_t index, uint8_t subindex); /* prints SDO segmented entry */
void Print_SDO_EXP_Entry(uint8_t node_id, uint16_t index, uint8_t subindex); /* prints SDO expedited entry */

/* Global Variables */
char buffer[64]; /* general purpose buffer for application */

/*****************************************************************************
 ** Function name:		main
 **
 ** Description:			C entry. Initializes HW and starts application code
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
int main(void) {
	uint8_t cmd[4]; /* UART command buffer */
	//uint8_t Value_MSB, Value_LSB;	/* return value when reading */

	cmd[0] = 0x00;
	cmd[1] = 0x00;
	cmd[2] = 0x00;
	cmd[3] = 0x00;

	//Value_MSB = 0x00;
	//Value_LSB = 0x00;

	RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

	SystemInit();
	CANopenInit();
	UARTInit(115200);

	CANnode_Init_Watchlist();

	/* Timer16B0 */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7); /* Enable clock for 16-bit counter/timer 0 */
	LPC_TMR16B0->MCR = 3; /* Interrupt and Reset on MR0 */
	LPC_TMR16B0->MR0 = SystemCoreClock / 1000; /* Interrupt and Reset on MR0 */
	NVIC_EnableIRQ(TIMER_16_0_IRQn); /* Enable the Timer0 Interrupt */
	LPC_TMR16B0->TCR = 1; /* Enable Timer0 */

	LPC_GPIO0->DIR |= 1<<7;
	LPC_GPIO0->MASKED_ACCESS[(1<<7)] = (0<<7);

	while (1) {

		//CANnode_Read_HighVoltage_Value(CAN_SLAVE1_NODE, &cmd[2]);

		if (RingBuffer_GetCount(&rxring) > 3)
		{
			UART_ReadRB(&rxring, cmd, 4);

			LPC_GPIO0->MASKED_ACCESS[(1<<7)] = (1<<7);

			switch (cmd[0]) {
			case 0x01:
				if (CANnode_Send_Config(cmd[1]) != CANopen_SDOC_Fail)
					UARThost_Send_Ack(&txring, cmd[1]);
				else
					UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE,
							cmd[1]);

				break;

			case 0x02:
				if (CANnode_Write_LED_Value(cmd[1], cmd[2],
						cmd[3]) != CANopen_SDOC_Fail)
					UARThost_Send_Ack(&txring, cmd[1]);
				else
					UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE,
							cmd[1]);

				break;

			case 0x04:
				if (CANnode_Read_HighVoltage_Value(cmd[1],
						&cmd[2]) != CANopen_SDOC_Fail)
					UARThost_Send_HighVoltage_Value(&txring, cmd[1], cmd[2]);
				else
					UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE,
							cmd[1]);

				break;

			case 0x08:
				UARThost_Comm_Test(&txring);

				break;

			case 0x10:
				if (CANnode_Read_LowVoltage_Value(cmd[1], &cmd[2],
						&cmd[3]) != CANopen_SDOC_Fail)
					UARThost_Send_LowVoltage_Value(&txring, cmd[1], cmd[2],
							cmd[3]);
				else
					UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE,
							cmd[1]);

				break;

			default:
				UARThost_Send_Error(&txring, APP_ERROR_UNKOWN_COMMAND, cmd[1]);
				break;
			}


			LPC_GPIO0->MASKED_ACCESS[(1<<7)] = (0<<7);

		}


		__WFI();
	}
	return 0;
}

/*****************************************************************************
 ** Function name:		UART_IRQHandler
 **
 ** Descriptions:		UART interrupt handler
 **
 ** parameters:			None
 ** Returned value:		None
 **
 *****************************************************************************/
void UART_IRQHandler(void) {
	/* Want to handle any errors? Do it here. */

	/* Use default ring buffer handler. Override this with your own
	 code if you need more capability. */
	UART_IRQRBHandler(&rxring, &txring);
	return;
}

/*****************************************************************************
 ** Function name:		TIMER16_0_IRQHandler
 **
 ** Description:			Set to fire every 1ms
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
void TIMER16_0_IRQHandler(void) {
	LPC_TMR16B0->IR = 1; /* clear interrupt flag */

	/* CANopen 1ms tick */
	CANopen_1ms_tick();
}

/*****************************************************************************
 ** Function name:		CANopen_Init_SDO
 **
 ** Description:			Callback function for initializing SDO parameters
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
void CANopen_Init_SDO(void) {
	uint32_t i;

	Error_Register = 0;
	for (i = 0; i < WatchListLength; i++) {
		WatchList[i].value = 0;
		WatchList[i].counter = 0;
	}
	CANopen_Heartbeat_Producer_Value = HEARTBEAT_PRODUCER_TIME;
	CANopen_Heartbeat_Producer_Counter = 0;
}

/*****************************************************************************
 ** Function name:		CANopen_NMT_Reset_Node_Received
 **
 ** Description:			NMT Reset Node callback.
 ** 						Called upon receiving reset node NMT command.
 ** 						Can be added by user
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
void CANopen_NMT_Reset_Node_Received(void) {
	UARThost_Send_Error(&txring, APP_ERROR_NODE_RESET, 0x00);
}

/*****************************************************************************
 ** Function name:		CANopen_NMT_Reset_Comm_Received
 **
 ** Description:			NMT Reset Communication.
 ** 						Called upon CanInit / receiving reset node/communication NMT command.
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
void CANopen_NMT_Reset_Comm_Received(void) {
	UARThost_Send_Error(&txring, APP_ERROR_COMM_RESET, 0x00);
}

/*****************************************************************************
 ** Function name:		CANopen_Heartbeat_Consumer_Failed
 **
 ** Description:			CAN heartbeat fail callback.
 ** 						Function is executed when a heartbeat producer which
 ** 						is listed in the watchlist did not
 ** 						send a heartbeat on time. Callback functions is executed
 ** 						after sending the NMT reset command.
 **
 ** Parameters:			Node_ID. Contains the number of the Node_ID which did
 ** 						not respond on time.
 ** Returned value:		None
 *****************************************************************************/
void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID) {
	UARThost_Send_Error(&txring, APP_ERROR_HEARTBEAT_FAILURE, Node_ID);
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
void CANopen_NMT_Consumer_Bootup_Received(uint8_t Node_ID) {
	UARThost_Bootup_Received(&txring, Node_ID);
}

/*****************************************************************************
 ** Function name:		Print_SDO_SEG_Entry
 **
 ** Description:			used for printing a segmented SDO entry
 **
 ** Parameters:			node_id: node-id of node to read.
 ** 						index: index to read
 ** 						subindex: subindex to read
 ** Returned value:		None
 *****************************************************************************/
void Print_SDO_SEG_Entry(uint8_t node_id, uint16_t index, uint8_t subindex) {
	CANopen_SDOC_Seg_Read(node_id, index, subindex, buffer, sizeof(buffer));
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;
	if (CANopen_SDOC_State == CANopen_SDOC_Succes)
		UARThost_Send_Ack(&txring, node_id);
	//printf("0x%02X\t%04XH\t%02XH\t\tSEG\t-\t%s\r\n", node_id, index, subindex, buffer);
	else
		// Error: Failed while executing command!
		UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE, node_id);
}

/*****************************************************************************
 ** Function name:		Print_SDO_EXP_Entry
 **
 ** Description:			used for printing a expedited SDO entry
 **
 ** Parameters:			node_id: node-id of node to read.
 ** 						index: index to read
 ** 						subindex: subindex to read
 ** Returned value:		None
 *****************************************************************************/
void Print_SDO_EXP_Entry(uint8_t node_id, uint16_t index, uint8_t subindex) {
	uint8_t i;

	buffer[0] = 0x00;
	buffer[1] = 0x00;
	buffer[2] = 0x00;
	buffer[3] = 0x00;

	CANopen_SDOC_Exp_Read(node_id, index, subindex, (uint8_t*) buffer, &i);
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;
	if (CANopen_SDOC_State == CANopen_SDOC_Succes)
		UARThost_Send_Ack(&txring, node_id);
	//printf("0x%02X\t%04XH\t%02XH\t\tEXP\t%d\t0x%02X 0x%02X 0x%02X 0x%02X\r\n", node_id, index, subindex, i, buffer[0], buffer[1], buffer[2], buffer[3]);
	else
		// Error: Failed while executing command!
		UARThost_Send_Error(&txring, APP_ERROR_GENERAL_FAILURE, node_id);
}

/******************************************************************************
 **                            End Of File
 ******************************************************************************/
