/****************************************************************************
 *   $Id:: uart.c 9372 2014-07-19 22:56:24                        $
 *   Project: CANopen Application for LPC11C24
 *
 *   Description:
 *     This file contains UART code which include UART
 *     initialization, UART interrupt handler, and related APIs for
 *     UART access.
 *
 * Copyright(C) 2014, Mehmet Aksakal
 * All rights reserved.
 ****************************************************************************/
#include "LPC11xx.h"
#include "uart.h"

volatile uint32_t UARTStatus;
volatile uint8_t UARTTxEmpty = 1;
volatile uint8_t UARTBuffer[BUFSIZE];
volatile uint32_t UARTCount = 0;

#if AUTOBAUD_ENABLE
volatile uint32_t UARTAutoBaud = 0, AutoBaudTimeout = 0;
#endif

#if MODEM_TEST
/*****************************************************************************
 ** Function name:		ModemInit
 **
 ** Descriptions:		Initialize UART0 port as modem, setup pin select.
 **
 ** parameters:			None
 ** Returned value:		None
 **
 *****************************************************************************/
void ModemInit( void )
{
	LPC_IOCON->PIO2_0 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO2_0 |= 0x01; /* UART DTR */
	LPC_IOCON->PIO0_7 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO0_7 |= 0x01; /* UART CTS */
	LPC_IOCON->PIO1_5 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO1_5 |= 0x01; /* UART RTS */
#if 1
	LPC_IOCON->DSR_LOC = 0;
	LPC_IOCON->PIO2_1 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO2_1 |= 0x01; /* UART DSR */

	LPC_IOCON->DCD_LOC = 0;
	LPC_IOCON->PIO2_2 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO2_2 |= 0x01; /* UART DCD */

	LPC_IOCON->RI_LOC = 0;
	LPC_IOCON->PIO2_3 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO2_3 |= 0x01; /* UART RI */

#else
	LPC_IOCON->DSR_LOC = 1;
	LPC_IOCON->PIO3_1 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO3_1 |= 0x01; /* UART DSR */

	LPC_IOCON->DCD_LOC = 1;
	LPC_IOCON->PIO3_2 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO3_2 |= 0x01; /* UART DCD */

	LPC_IOCON->RI_LOC = 1;
	LPC_IOCON->PIO3_3 &= ~0x07; /* UART I/O config */
	LPC_IOCON->PIO3_3 |= 0x01; /* UART RI */
#endif
	LPC_UART->MCR = 0xC0; /* Enable Auto RTS and Auto CTS. */
	return;
}
#endif

/***********************************************************************
 *
 * Function: uart_set_divisors
 *
 * Purpose: Determines best dividers to get a target clock rate
 *
 * Processing:
 *     See function.
 *
 * Parameters:
 *     UARTClk    : UART clock
 *     baudrate   : Desired UART baud rate
 *
 * Outputs:
 *	  baudrate : Sets the estimated buadrate value in DLL, DLM, and FDR.
 *
 * Returns: Error status.
 *
 * Notes: None
 *
 **********************************************************************/
uint32_t uart_set_divisors(uint32_t UARTClk, uint32_t baudrate) {
	uint32_t uClk;
	uint32_t calcBaudrate = 0;
	uint32_t temp = 0;

	uint32_t mulFracDiv, dividerAddFracDiv;
	uint32_t diviser = 0;
	uint32_t mulFracDivOptimal = 1;
	uint32_t dividerAddOptimal = 0;
	uint32_t diviserOptimal = 0;

	uint32_t relativeError = 0;
	uint32_t relativeOptimalError = 100000;

	/* get UART block clock */
	uClk = UARTClk >> 4; /* div by 16 */
	/* In the Uart IP block, baud rate is calculated using FDR and DLL-DLM registers
	 * The formula is :
	 * BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * (DLL)
	 * It involves floating point calculations. That's the reason the formulae are adjusted with
	 * Multiply and divide method.*/
	/* The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
	 * 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15 */
	for (mulFracDiv = 1; mulFracDiv <= 15; mulFracDiv++) {
		for (dividerAddFracDiv = 0; dividerAddFracDiv <= 15;
				dividerAddFracDiv++) {
			temp = (mulFracDiv * uClk) / ((mulFracDiv + dividerAddFracDiv));
			diviser = temp / baudrate;
			if ((temp % baudrate) > (baudrate / 2))
				diviser++;

			if (diviser > 2 && diviser < 65536) {
				calcBaudrate = temp / diviser;

				if (calcBaudrate <= baudrate)
					relativeError = baudrate - calcBaudrate;
				else
					relativeError = calcBaudrate - baudrate;

				if ((relativeError < relativeOptimalError)) {
					mulFracDivOptimal = mulFracDiv;
					dividerAddOptimal = dividerAddFracDiv;
					diviserOptimal = diviser;
					relativeOptimalError = relativeError;
					if (relativeError == 0)
						break;
				}
			} /* End of if */
		} /* end of inner for loop */
		if (relativeError == 0)
			break;
	} /* end of outer for loop  */

	if (relativeOptimalError < (baudrate / 30)) {
		/* Set the `Divisor Latch Access Bit` and enable so the DLL/DLM access*/
		/* Initialise the `Divisor latch LSB` and `Divisor latch MSB` registers */
		LPC_UART->DLM = (diviserOptimal >> 8) & 0xFF;
		LPC_UART->DLL = diviserOptimal & 0xFF;

		/* Initialise the Fractional Divider Register */
		LPC_UART->FDR = ((mulFracDivOptimal & 0xF) << 4)
				| (dividerAddOptimal & 0xF);
		return ( true);
	}
	return ( false);
}

/*****************************************************************************
 ** Function name:		UARTInit
 **
 ** Descriptions:		Initialize UART0 port, setup pin select,
 **				clock, parity, stop bits, FIFO, etc.
 **
 ** parameters:			UART baudrate
 ** Returned value:		None
 **
 *****************************************************************************/
void UARTInit(uint32_t baudrate) {
#if !AUTOBAUD_ENABLE
	uint32_t Fdiv;
#endif
	volatile uint32_t regVal;

	UARTTxEmpty = 1;
	UARTCount = 0;
	(void) regVal;

	NVIC_DisableIRQ(UART_IRQn);

	LPC_IOCON->PIO1_6 &= ~0x07; /*  UART I/O config */
	LPC_IOCON->PIO1_6 |= 0x01; /* UART RXD */
	LPC_IOCON->PIO1_7 &= ~0x07;
	LPC_IOCON->PIO1_7 |= 0x01; /* UART TXD */

	/* Enable UART clock */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);
	LPC_SYSCON->UARTCLKDIV = 0x1; /* divided by 1 */

	LPC_UART->LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit */
#if !AUTOBAUD_ENABLE
#if FDR_CALIBRATION
	if ( uart_set_divisors(SystemCoreClock/LPC_SYSCON->UARTCLKDIV, baudrate) != TRUE )
	{
		Fdiv = ((SystemCoreClock/LPC_SYSCON->UARTCLKDIV)/16)/baudrate; /*baud rate */
		LPC_UART->DLM = Fdiv / 256;
		LPC_UART->DLL = Fdiv % 256;
		LPC_UART->FDR = 0x10; /* Default */
	}
#else
	Fdiv = ((SystemCoreClock / LPC_SYSCON->UARTCLKDIV) / 16) / baudrate; /*baud rate */
	LPC_UART->DLM = Fdiv / 256;
	LPC_UART->DLL = Fdiv % 256;
	LPC_UART->FDR = 0x10; /* Default */
#endif
#endif
	LPC_UART->LCR = 0x03; /* DLAB = 0 */
	LPC_UART->FCR = 0x07; /* Enable and reset TX and RX FIFO. */

	/* Read to clear the line status. */
	regVal = LPC_UART->LSR;

	/* Ensure a clean start, no data in either TX or RX FIFO. */
	while (( LPC_UART->LSR & (LSR_THRE | LSR_TEMT)) != (LSR_THRE | LSR_TEMT))
		;
	while ( LPC_UART->LSR & LSR_RDR) {
		regVal = LPC_UART->RBR; /* Dump data from RX FIFO */
	}

	/* Enable the UART Interrupt */
	NVIC_EnableIRQ(UART_IRQn);

#if TX_INTERRUPT
	LPC_UART->IER = IER_RBR | IER_THRE | IER_RLS; /* Enable UART interrupt */
#else
	LPC_UART->IER = IER_RBR | IER_RLS; /* Enable UART interrupt */
#endif
#if AUTOBAUD_ENABLE
	LPC_UART->IER |= IER_ABEO | IER_ABTO;
#endif
	return;
}

/* Read data through the UART peripheral (non-blocking) */
int UART_Read(void *data, int numBytes) {
	int readBytes = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((readBytes < numBytes) && ((LPC_UART->LSR & LSR_RDR) != 0)) {
		*p8 = UART_ReadByte();
		p8++;
		readBytes++;
	}

	return readBytes;
}

/* Copy data from a receive ring buffer */
int UART_ReadRB(RINGBUFF_T *pRB, void *data, int bytes) {
	return RingBuffer_PopMult(pRB, (uint8_t *) data, bytes);
}

/* Transmit a byte array through the UART peripheral (non-blocking) */
int UART_Send(const void *data, int numBytes) {
	int sent = 0;
	uint8_t *p8 = (uint8_t *) data;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((sent < numBytes) && ((LPC_UART->LSR & LSR_THRE) != 0)) {
		UART_SendByte(*p8);
		p8++;
		sent++;
	}

	return sent;
}

/* Populate a transmit ring buffer and start UART transmit */
uint32_t UART_SendRB(RINGBUFF_T *pRB, const void *data, int bytes) {
	uint32_t ret;
	uint8_t *p8 = (uint8_t *) data;

	/* Don't let UART transmit ring buffer change in the UART IRQ handler */
	UART_IntDisable(IER_THRE);

	/* Move as much data as possible into transmit ring buffer */
	ret = RingBuffer_InsertMult(pRB, p8, bytes);
	UART_TXIntHandlerRB(pRB);

	/* Add additional data to transmit ring buffer if possible */
	ret += RingBuffer_InsertMult(pRB, (p8 + ret), (bytes - ret));

	/* Enable UART transmit interrupt */
	UART_IntEnable(IER_THRE);

	return ret;
}

/* UART receive/transmit interrupt handler for ring buffers */
void UART_IRQRBHandler(RINGBUFF_T *pRXRB, RINGBUFF_T *pTXRB) {
	/* Handle transmit interrupt if enabled */
	if (LPC_UART->IER & IER_THRE) {
		UART_TXIntHandlerRB(pTXRB);

		/* Disable transmit interrupt if the ring buffer is empty */
		if (RingBuffer_IsEmpty(pTXRB)) {
			UART_IntDisable(IER_THRE);
		}
	}

	/* Handle receive interrupt */
	UART_RXIntHandlerRB(pRXRB);
}

/* UART receive-only interrupt handler for ring buffers */
void UART_RXIntHandlerRB(RINGBUFF_T *pRB) {
	/* New data will be ignored if data not popped in time */
	while (LPC_UART->LSR & LSR_RDR) {
		uint8_t ch = UART_ReadByte();
		RingBuffer_Insert(pRB, &ch);
	}
}

/* UART transmit-only interrupt handler for ring buffers */
void UART_TXIntHandlerRB(RINGBUFF_T *pRB) {
	uint8_t ch;

	/* Fill FIFO until full or until TX ring buffer is empty */
	while ((LPC_UART->LSR & LSR_THRE) != 0 && RingBuffer_Pop(pRB, &ch)) {
		UART_SendByte(ch);
	}
}

/******************************************************************************
 **                            End Of File
 ******************************************************************************/
