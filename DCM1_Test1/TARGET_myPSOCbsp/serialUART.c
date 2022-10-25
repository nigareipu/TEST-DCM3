/*
 * serialBufferInput.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include <serialUART.h>
#include "uartInterrupt.h"

void echoInput()
{

	// Echo what is written in the serial terminal
	sprintf(sendBuffer, "%s", rxBuffer);
	Cy_SCB_UART_Transmit(UART_HW, sendBuffer, strlen(sendBuffer), &uartContext);
}

void fillBuffer()
{

	uartRxCompleteFlag = 0; // reset the flag
	storeBuffer[count++] = *rxBuffer;
	storeBuffer[count] = '\0';
}

void UART_Init()
{

	cy_stc_scb_uart_context_t uartContext;

	(void)Cy_SCB_UART_Init(UART_HW, &UART_config, &uartContext);

	configureUART_Isr();

	// Enable UART to operate //
	Cy_SCB_UART_Enable(UART_HW);
}
