/****************************************************************************
 *   $Id:: uart.h 8216 2014-07-06 17:50:47                        $
 *   Project: CANopen Application for LPC11C24
 *
 *   Description:
 *     This file contains definition and prototype for UART configuration.
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 ****************************************************************************/
#ifndef __UART_H
#define __UART_H

#include "ring_buffer.h"

#define AUTOBAUD_ENABLE 0
#define FDR_CALIBRATION 0
#define RS485_ENABLED   0
#define TX_INTERRUPT    1		/* 0 if TX uses polling, 1 interrupt driven. */
#define MODEM_TEST      0

#define IER_RBR         (0x01<<0)
#define IER_THRE        (0x01<<1)
#define IER_RLS         (0x01<<2)
#define IER_ABEO        (0x01<<8)
#define IER_ABTO        (0x01<<9)

#define IIR_PEND        0x01
#define IIR_RLS         0x03
#define IIR_RDA         0x02
#define IIR_CTI         0x06
#define IIR_THRE        0x01
#define IIR_ABEO        (0x01<<8)
#define IIR_ABTO        (0x01<<9)

#define LSR_RDR         (0x01<<0)
#define LSR_OE          (0x01<<1)
#define LSR_PE          (0x01<<2)
#define LSR_FE          (0x01<<3)
#define LSR_BI          (0x01<<4)
#define LSR_THRE        (0x01<<5)
#define LSR_TEMT        (0x01<<6)
#define LSR_RXFE        (0x01<<7)

#define RBR_MASKBIT		(0xFF)

#define BUFSIZE         0x40

/* RS485 mode definition. */
#define RS485_NMMEN		(0x1<<0)
#define RS485_RXDIS		(0x1<<1)
#define RS485_AADEN		(0x1<<2)
#define RS485_SEL             (0x1<<3)
#define RS485_DCTRL		(0x1<<4)
#define RS485_OINV		(0x1<<5)

void ModemInit(void);
void UARTInit(uint32_t Baudrate);

int UART_Send(const void *data, int numBytes);
uint32_t UART_SendRB(RINGBUFF_T *pRB, const void *data, int bytes);
int UART_Read(void *data, int numBytes);
int UART_ReadRB(RINGBUFF_T *pRB, void *data, int bytes);

void UART_IRQRBHandler(RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB);
void UART_RXIntHandlerRB(RINGBUFF_T *pRB);
void UART_TXIntHandlerRB(RINGBUFF_T *pRB);

static inline uint8_t UART_ReadByte() {
	return (uint8_t) (LPC_UART->RBR & RBR_MASKBIT);
}

static inline void UART_SendByte(uint8_t data) {
	LPC_UART->THR = (uint32_t) data;
}

static inline void UART_IntEnable(uint32_t intMask) {
	LPC_UART->IER |= intMask;
}

static inline void UART_IntDisable(uint32_t intMask) {
	LPC_UART->IER &= ~intMask;
}

#endif /* end __UART_H */
/*****************************************************************************
 **                            End Of File
 ******************************************************************************/
