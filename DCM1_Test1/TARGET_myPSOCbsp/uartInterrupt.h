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
#include "serialUART.h"

void UART_Isr(void);
void UART_Interrupt_Callback(uint32_t event);
void configureUART_Isr(void);

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_UARTINTERRUPT_H_ */
