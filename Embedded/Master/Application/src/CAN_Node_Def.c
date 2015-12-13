/***********************************************************************
 * $Id:: CAN_Node_Def.c 1604 2014-07-14 11:34:47     $
 *
 * Project: CANopen Application for LPC11C24 (entry node)
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
uint8_t Error_Register; /* variable for mandatory SDO entry 0x1001 */
uint32_t CANopen_Heartbeat_Producer_Value; /* variable for heartbeat producer entry */
WatchNode_t WatchList[NUM_CAN_NODES]; /* Watch 2 nodes for their NMT state / bootup message and heartbeat */
uint8_t WatchListLength = sizeof(WatchList) / sizeof(WatchList[0]); /* required so that number of nodes in watchlist is known */

/*	CANopen read-only (constant) Object Dictionary (OD) entries
 Used with Expedited SDO only. Lengths = 1/2/4 bytes */
CAN_ODCONSTENTRY myConstOD[] = {
/* index, subindex,	length,	value */
{ 0x1000, 0x00, 4, 0x00000000UL }, { 0x1018, 0x00, 1, 0x00000001UL }, /* only vendor ID is specified */
{ 0x1018, 0x01, 4, 0x000002DCUL }, /* NXP vendor ID for CANopen */
};
uint32_t NumberOfmyConstODEntries = sizeof(myConstOD) / sizeof(myConstOD[0]);

/*	CANopen list of variable Object Dictionary (OD) entries
 Expedited SDO with length=1/2/4 bytes and segmented SDO */
CAN_ODENTRY myOD[] = {
/* index, subindex,	access_type | length,	value_pointer */
{ 0x1001, 0x00, OD_EXP_RO | 1, (uint8_t *) &Error_Register }, { 0x1016, 0x00,
		OD_EXP_RO | 1, (uint8_t *) &WatchListLength }, { 0x1016, 0x01, OD_EXP_RW
		| 4, (uint8_t *) &WatchList[0].value }, { 0x1016, 0x02, OD_EXP_RW | 4,
		(uint8_t *) &WatchList[1].value }, { 0x1017, 0x00, OD_EXP_RW | 2,
		(uint8_t *) &CANopen_Heartbeat_Producer_Value }, };
uint32_t NumberOfmyODEntries = sizeof(myOD) / sizeof(myOD[0]);
