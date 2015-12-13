/***********************************************************************
 * $Id:: CAN_Node_Def.h 1604 2014-07-14 11:34:47     $
 *
 * Project: CANopen Application for LPC11C24 (entry node)
 *
 * Description:
 *   CANopen definition header file
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 **********************************************************************/

#ifndef _CAN_NODE_DEF_H
#define _CAN_NODE_DEF_H

#include <stdint.h>
#include "canopen_driver.h"

#define NUM_CAN_NODES			50		/* Number of total nodes */

#define CAN_MASTER_NODE			0x7D		/* 125 */
#define CAN_SLAVE1_NODE			0x01		/* 1 */
#define CAN_SLAVE2_NODE			0x02		/* 2 */
#define CAN_SLAVE3_NODE			0x03		/* 3 */
#define CAN_SLAVE4_NODE			0x04		/* 4 */
#define CAN_SLAVE5_NODE			0x05		/* 5 */
#define CAN_SLAVE6_NODE			0x06		/* 6 */
#define CAN_SLAVE7_NODE			0x07		/* 7 */
#define CAN_SLAVE8_NODE			0x08		/* 8 */
#define CAN_SLAVE9_NODE			0x09		/* 9 */
#define CAN_SLAVE10_NODE		0x0A		/* 10 */
#define CAN_SLAVE11_NODE		0x0B		/* 11 */
#define CAN_SLAVE12_NODE		0x0C		/* 12 */
#define CAN_SLAVE13_NODE		0x0D		/* 13 */
#define CAN_SLAVE14_NODE		0x0E		/* 14 */
#define CAN_SLAVE15_NODE		0x0F		/* 15 */
#define CAN_SLAVE16_NODE		0x10		/* 16 */
#define CAN_SLAVE17_NODE		0x11		/* 17 */
#define CAN_SLAVE18_NODE		0x12		/* 18 */
#define CAN_SLAVE19_NODE		0x13		/* 19 */
#define CAN_SLAVE20_NODE		0x14		/* 20 */
#define CAN_SLAVE21_NODE		0x15		/* 21 */
#define CAN_SLAVE22_NODE		0x16		/* 22 */
#define CAN_SLAVE23_NODE		0x17		/* 23 */
#define CAN_SLAVE24_NODE		0x18		/* 24 */
#define CAN_SLAVE25_NODE		0x19		/* 25 */
#define CAN_SLAVE26_NODE		0x1A		/* 26 */
#define CAN_SLAVE27_NODE		0x1B		/* 27 */
#define CAN_SLAVE28_NODE		0x1C		/* 28 */
#define CAN_SLAVE29_NODE		0x1D		/* 29 */
#define CAN_SLAVE30_NODE		0x1E		/* 30 */
#define CAN_SLAVE31_NODE		0x1F		/* 31 */
#define CAN_SLAVE32_NODE		0x20		/* 32 */
#define CAN_SLAVE33_NODE		0x21		/* 33 */
#define CAN_SLAVE34_NODE		0x22		/* 34 */
#define CAN_SLAVE35_NODE		0x23		/* 35 */
#define CAN_SLAVE36_NODE		0x24		/* 36 */
#define CAN_SLAVE37_NODE		0x25		/* 37 */
#define CAN_SLAVE38_NODE		0x26		/* 38 */
#define CAN_SLAVE39_NODE		0x27		/* 39 */
#define CAN_SLAVE40_NODE		0x28		/* 40 */
#define CAN_SLAVE41_NODE		0x29		/* 41 */
#define CAN_SLAVE42_NODE		0x2A		/* 42 */
#define CAN_SLAVE43_NODE		0x2B		/* 43 */
#define CAN_SLAVE44_NODE		0x2C		/* 44 */
#define CAN_SLAVE45_NODE		0x2D		/* 45 */
#define CAN_SLAVE46_NODE		0x2E		/* 46 */
#define CAN_SLAVE47_NODE		0x2F		/* 47 */
#define CAN_SLAVE48_NODE		0x30		/* 48 */
#define CAN_SLAVE49_NODE		0x31		/* 49 */
#define CAN_SLAVE50_NODE		0x32		/* 50 */

#define CAN_NODE_ID				CAN_MASTER_NODE
#define CANOPEN_TIMEOUT_VAL		10		/* in ms */

/* Application variables used in variable OD */
extern uint8_t Error_Register; /* CANopen error register */
extern uint32_t CANopen_Heartbeat_Producer_Value; /* heartbeat producer value */

extern WatchNode_t WatchList[]; /* Watch 2 nodes for their NMT state / bootup message and heartbeat */
extern uint8_t WatchListLength; /* required so that number of nodes in watchlist is known */
extern CAN_ODCONSTENTRY myConstOD[]; /* OD for constant values, e.g. vendor ID */
extern uint32_t NumberOfmyConstODEntries; /* required so that the number of entries in the variable OD is known */
extern CAN_ODENTRY myOD[]; /* OD for variable values, e.g. for controlling LEDs */
extern uint32_t NumberOfmyODEntries; /* required so that the number of entries in the variable OD is known */

#endif /* _CAN_NODE_DEF_H */
