/*
 * mode2.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE2_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE2_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "coin_window.h"
#include "delay.h"
#include "dac.h"
#include "spi.h"
#include "det_bias.h"
#include "counters.h"
#include "tec.h"
#include "adc.h"
#include "uartInterrupt.h"
#include "AD56x8.h"
#include "discr.h"
#include "allocate.h"
#define ON (1u)
#define OFF (0u)


//extern volatile bool uartRxCompleteFlag;
//extern volatile int count;
extern volatile bool TEC_controller0ActiveFlag;
extern volatile bool TEC_controller1ActiveFlag;
extern char confirmValue[200];
extern uint32_t ClockStamp0;
extern int countLoopDelay;
extern bool tec_started_locally;
extern int count_tec_stabile_loop;
extern bool monitor_die_temp;

void mode1program();
void mode2program();
void mode3program();
void mode4program();
void mode5program();
void calibrateBreakdownvTemp();    // Mode5 functions
void calibrateCountsvDiscThresh(); // Mode5 functions
void mode6program();
void mode7program();
#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE2_H_ */
