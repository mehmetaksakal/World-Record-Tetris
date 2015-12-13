/***********************************************************************
 * $Id:: CAN_Node_cmd.h 1604 2014-07-18 12:34:29     $
 *
 * Project: CANopen Application for LPC11C24 (entry node)
 *
 * Description:
 *   CANopen definition header file
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#ifndef CAN_NODE_CMD_H_
#define CAN_NODE_CMD_H_

#define HEARTBEAT_PRODUCER_TIME		4000		/* in ms */
#define HEARTBEAT_CONSUMER_TIME		4500		/* in ms */

#define APP_ERROR_GENERAL_FAILURE	0x01		/* General read/write failure to CAN node */
#define APP_ERROR_UNKOWN_COMMAND	0x02		/* Unkown command received */
#define APP_ERROR_HEARTBEAT_FAILURE	0x03		/* Heartbeat failure */
#define APP_ERROR_COMM_RESET		0x04		/* Comm reset requested by node */
#define APP_ERROR_NODE_RESET		0x05		/* Node reset requested by node */

//#include <stdint.h>
#include "ring_buffer.h"
#include "canopen_driver.h"

void CANnode_Init_Watchlist();
uint8_t CANnode_Send_Config(uint8_t Node_ID);
uint8_t CANnode_Write_LED_Value(uint8_t Node_ID, uint8_t LED_ID, uint8_t Value);
uint8_t CANnode_Read_HighVoltage_Value(uint8_t Node_ID, uint8_t *Value);
uint8_t CANnode_Read_LowVoltage_Value(uint8_t Node_ID, uint8_t *Value_MSB, uint8_t *Value_LSB);

void UARThost_Send_Error(RINGBUFF_T *pTXRB, uint8_t Error, uint8_t Node_ID);
void UARThost_Send_HighVoltage_Value(RINGBUFF_T *pTXRB, uint8_t Node_ID, uint8_t Value);
void UARThost_Send_LowVoltage_Value(RINGBUFF_T *pTXRB, uint8_t Node_ID, uint8_t Value_MSB, uint8_t Value_LSB);
void UARThost_Bootup_Received(RINGBUFF_T *pTXRB, uint8_t Node_ID);
void UARThost_Send_Ack(RINGBUFF_T *pTXRB, uint8_t Node_ID);
void UARThost_Comm_Test(RINGBUFF_T *pTXRB);

#endif /* CAN_NODE_CMD_H_ */
