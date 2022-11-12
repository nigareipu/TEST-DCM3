/*
 * serialBufferInput.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_SERIALUART_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_SERIALUART_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define BUF_LEN 200

extern cy_stc_scb_uart_context_t uartContext;

extern volatile bool uartRxCompleteFlag;

extern volatile int count;

extern uint8_t rxBuffer[32], sendBuffer[32];
extern char storeBuffer[BUF_LEN], *commandBuffer, *valueBuffer;

void echoInput();
void fillBuffer(char* char_buff);
void UART_Init();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_SERIALUART_H_ */
