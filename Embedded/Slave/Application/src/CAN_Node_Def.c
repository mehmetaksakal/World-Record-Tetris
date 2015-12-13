/***********************************************************************
 * $Id:: CAN_Node_Def.c 1604 2012-04-24 11:34:47     $
 *
 * Project: CANopen Application for LPC11Cxx (slave)
 *
 * Description:
 *   CANopen definition source file
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
  **********************************************************************/

#include "CAN_Node_Def.h"
#include <stdint.h>

/* Application variables used in variable OD */
uint8_t  error_register;
uint8_t  LED1;
uint8_t  LED2;
uint8_t  LED3;
uint8_t  LED4;
uint8_t HighVoltage;
uint8_t ADCValue_MSB;
uint8_t ADCValue_LSB;
volatile SDOS_Buffer_t SDOS_2200 =
{
	(uint8_t*)SDOS_2200_Data,
	sizeof(SDOS_2200_Data),
};
volatile uint8_t SDOS_2200_Data[255] = "Boot-up value of SDO 2200h";
uint32_t CANopen_Heartbeat_Producer_Value;
WatchNode_t WatchList[1];
uint8_t WatchListLength = sizeof(WatchList)/sizeof(WatchList[0]);



/*	CANopen read-only (constant) Object Dictionary (OD) entries
	Used with Expedited SDO only. Lengths = 1/2/4 bytes */
CAN_ODCONSTENTRY myConstOD [] =
{
	/* index, subindex,	length,	value */
	{ 0x1000, 0x00, 	4, 		0x00000000UL },
	{ 0x1018, 0x00, 	1, 		0x00000001UL },		/* only vendor ID is specified */
	{ 0x1018, 0x01, 	4, 		0x000002DCUL },		/* NXP vendor ID for CANopen */
};
uint32_t NumberOfmyConstODEntries = sizeof(myConstOD)/sizeof(myConstOD[0]);

/*	CANopen list of variable Object Dictionary (OD) entries
	Expedited SDO with length=1/2/4 bytes and segmented SDO */
CAN_ODENTRY myOD [] =
{
	/* index, subindex,	access_type | length,	value_pointer */
	{ 0x1001, 0x00, 	OD_EXP_RO | 1,			(uint8_t *)&error_register },
	{ 0x1016, 0x00,     OD_EXP_RO | 1,          (uint8_t *)&WatchListLength},
	{ 0x1016, 0x01,     OD_EXP_RW | 4,          (uint8_t *)&WatchList[0].value},
	{ 0x1017, 0x00,     OD_EXP_RW | 2,          (uint8_t *)&CANopen_Heartbeat_Producer_Value},
	{ 0x1900, 0x00,     OD_EXP_RO | 1,          (uint8_t *)&HighVoltage},
	{ 0x1910, 0x00,     OD_EXP_RO | 1,          (uint8_t *)&ADCValue_MSB},
	{ 0x1910, 0x01,     OD_EXP_RO | 1,          (uint8_t *)&ADCValue_LSB},
	{ 0x2000, 0x00,     OD_EXP_RW | 1,          (uint8_t *)&LED1},
	{ 0x2000, 0x01,     OD_EXP_RW | 1,          (uint8_t *)&LED2},
	{ 0x2000, 0x02,     OD_EXP_RW | 1,          (uint8_t *)&LED3},
	{ 0x2000, 0x03,     OD_EXP_RW | 1,          (uint8_t *)&LED4},
	{ 0x2200, 0x00,		OD_SEG_RW,				(uint8_t *)&SDOS_2200},
};
uint32_t NumberOfmyODEntries = sizeof(myOD)/sizeof(myOD[0]);
