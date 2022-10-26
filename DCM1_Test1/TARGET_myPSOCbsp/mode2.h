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
#include "serialUART.h"
#include "uartInterrupt.h"
#include "functions.h"
#include "AD56x8.h"
#include "discr.h"
#include "mode1.h"

extern volatile bool coincWindowSetFlag, uartRxCompleteFlag, warningFlag, printfeedbackFlag;
extern volatile int count;
extern char confirmValue[32];
extern float discrThresh;

extern float *mode;
extern float *VDET0, *VDET1, *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
extern float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin, *Exit;
extern float *AnDET;

void mode2program();
void mode3program();
void mode4program();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE2_H_ */
