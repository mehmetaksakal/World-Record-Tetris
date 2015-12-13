/***********************************************************************
 * $Id:: CAN_Node_cmd.c 1604 2014-07-18 12:33:26     $
 *
 * Project: CANopen Application for LPC11C24 (entry node)
 *
 * Description:
 *   CANopen definition source file
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#include "CAN_Node_cmd.h"
#include "CAN_Node_Def.h"
#include "uart.h"

char buffer[255]; /* general purpose buffer for application */
uint8_t cmd[4]; /* uart command buffer */
//extern uint8_t Value_MSB, Value_LSB;	/* return value when reading */

void CANnode_Init_Watchlist() {
	uint8_t i;

	for (i = 0; i < NUM_CAN_NODES; i++) {
		WatchList[i].NodeID = i + 1; /* Slave node in watchlist */
		WatchList[i].ConsumerTime = HEARTBEAT_CONSUMER_TIME; /* Consumer time for watch node. This will restore the consumer heartbeat when the slave node resets after heartbeat failure */
		WatchList[i].ProducerTime = HEARTBEAT_PRODUCER_TIME; /* Producer time for watch node. This will restore the producer heartbeat when the slave node resets after heartbeat failure */
	}
}

uint8_t CANnode_Send_Config(uint8_t Node_ID) {
	uint8_t Node_Index;
	Node_Index = Node_ID - 1;

	WatchList[0].value = 0x00; /* Disable heartbeat while configuring */

	buffer[0] = (WatchList[Node_Index].ProducerTime >> 8) & 0xFF;
	buffer[1] = (WatchList[Node_Index].ProducerTime >> 0) & 0xFF;

	CANopen_SDOC_Exp_Write(Node_Index, 0x1017, 0x00, (uint8_t*) buffer, 2);
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;

	if (CANopen_SDOC_State == CANopen_SDOC_Succes)
		WatchList[Node_Index].value = (WatchList[Node_Index].NodeID) << 16
				| WatchList[Node_Index].ConsumerTime;
	else
		return CANopen_SDOC_State;

	buffer[0] = 0x00;
	buffer[1] = CAN_NODE_ID;
	buffer[2] = (WatchList[Node_Index].ConsumerTime >> 8) & 0xFF;
	buffer[3] = (WatchList[Node_Index].ConsumerTime >> 0) & 0xFF;
	CANopen_SDOC_Exp_Write(Node_ID, 0x1016, 0x01, (uint8_t*) buffer, 4);
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;

	/*if(CANopen_SDOC_State == CANopen_SDOC_Fail)
	 printf("Error: Failed while executing command!\r\n");*/
	return CANopen_SDOC_State;
}

uint8_t CANnode_Write_LED_Value(uint8_t Node_ID, uint8_t LED_ID, uint8_t Value) {
	CANopen_SDOC_Exp_Write(Node_ID, 0x2000, LED_ID - 1, &Value, 1);

	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;

	return CANopen_SDOC_State;
}

uint8_t CANnode_Read_HighVoltage_Value(uint8_t Node_ID, uint8_t *Value) {
	uint8_t tmpValue;
	tmpValue = 0x00;

	CANopen_SDOC_Exp_Read(Node_ID, 0x1900, 0x00, (uint8_t *) &tmpValue, NULL);

	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail));

	*Value = tmpValue;

	return CANopen_SDOC_State;
}

uint8_t CANnode_Read_LowVoltage_Value(uint8_t Node_ID, uint8_t *Value_MSB, uint8_t *Value_LSB) {
	uint8_t MSB, LSB;
	MSB = 0x00;
	LSB = 0x00;

	CANopen_SDOC_Exp_Read(Node_ID, 0x1910, 0x00, (uint8_t *) &MSB, NULL);
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;
	*Value_MSB = MSB;

	CANopen_SDOC_Exp_Read(Node_ID, 0x1910, 0x01, (uint8_t *) &LSB, NULL);
	while (!(CANopen_SDOC_State == CANopen_SDOC_Succes
			|| CANopen_SDOC_State == CANopen_SDOC_Fail))
		;
	*Value_LSB = LSB;

	return CANopen_SDOC_State;
}

void UARThost_Send_Error(RINGBUFF_T *pTXRB, uint8_t Error, uint8_t Node_ID) {
	cmd[0] = 0x08;
	cmd[1] = Node_ID;
	cmd[2] = Error;
	cmd[3] = 0x01;

	UART_SendRB(pTXRB, cmd, 4);
}

void UARThost_Send_Ack(RINGBUFF_T *pTXRB, uint8_t Node_ID) {
	cmd[0] = 0x04;
	cmd[1] = Node_ID;
	cmd[2] = 0x01;
	cmd[3] = 0x01;

	UART_SendRB(pTXRB, cmd, 4);
}

void UARThost_Comm_Test(RINGBUFF_T *pTXRB) {
	cmd[0] = 0x10;
	cmd[1] = 0x01;
	cmd[2] = 0x01;
	cmd[3] = 0x01;

	UART_SendRB(pTXRB, cmd, 4);
}

void UARThost_Send_HighVoltage_Value(RINGBUFF_T *pTXRB, uint8_t Node_ID,
		uint8_t Value) {
	cmd[0] = 0x02;
	cmd[1] = Node_ID;
	cmd[2] = Value;
	cmd[3] = 0x01;

	UART_SendRB(pTXRB, cmd, 4);
}

void UARThost_Send_LowVoltage_Value(RINGBUFF_T *pTXRB, uint8_t Node_ID,
		uint8_t Value_MSB, uint8_t Value_LSB) {
	cmd[0] = 0x20;
	cmd[1] = Node_ID;
	cmd[2] = Value_MSB;
	cmd[3] = Value_LSB;

	UART_SendRB(pTXRB, cmd, 4);
}

void UARThost_Bootup_Received(RINGBUFF_T *pTXRB, uint8_t Node_ID) {
	cmd[0] = 0x01;
	cmd[1] = Node_ID;
	cmd[2] = 0x01;
	cmd[3] = 0x01;

	UART_SendRB(pTXRB, cmd, 4);
}
