/****************************************************************************
 *   $Id:: rom_drivers.h 1604 2014-07-14 11:34:47             $
 *   Project: NXP LPC11xx CAN
 *
 *   Description:
 *     This file is part of the CAN and CANopen on-chip driver.
 ***************************************************************************/
#ifndef ROM_DRIVERS_H_
#define ROM_DRIVERS_H_

#define CAN	0
#define USB	1

#define PERIPHERAL		CAN

#if (PERIPHERAL == CAN)
	#include "rom_driver_CAN.h"
#endif /* (PERIPHERAL == CAN) */

#if (PERIPHERAL == USB)
	#include "usb.h" 
	typedef	struct _USB {
	  void (*init_clk_pins)(void);
	  void (*isr)(void);
	  void (*init)( USB_DEV_INFO * DevInfoPtr ); 
	  void (*connect)(BOOL  con);
	}USB;
#endif /* (PERIPHERAL == USB) */

typedef	struct _ROM {
   const unsigned p_usbd;
   const unsigned p_clib;
#if (PERIPHERAL == CAN)
   const CAND *pCAND;
#else
   const unsigned pCAND;
#endif /* (PERIPHERAL == CAN) */
   const unsigned p_pwrd;
   const unsigned p_dev1;
   const unsigned p_dev2;
   const unsigned p_dev3;
   const unsigned p_dev4; 
}  ROM;

#endif /* ROM_DRIVERS_H_ */
