/*
 * uartInterrupt.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_UARTINTERRUPT_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_UARTINTERRUPT_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "allocate.h"
#define BUF_LEN 200

extern cy_stc_scb_uart_context_t uartContext;
extern volatile int count_uartbuffer;
extern uint8_t rxBuffer[32], sendBuffer[32];
extern char storeBuffer[BUF_LEN], *commandBuffer, *valueBuffer;



void UART_Init();
void UART_Isr(void);
void UART_Interrupt_Callback(uint32_t event);
void configureUART_Isr(void);


#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_UARTINTERRUPT_H_ */
