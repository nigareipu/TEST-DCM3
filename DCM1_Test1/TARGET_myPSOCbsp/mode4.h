/*
 * mode4.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE4_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE4_H_

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

extern float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
extern float DET0_temp, DET1_temp, DET2_temp, DET3_temp;
extern float length;
extern float discrThresh;

extern float *mode;
extern float *VDET0;
extern float *VDET1;
extern float *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
extern float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin;

extern volatile bool coincWindowSetFlag, uartRxCompleteFlag;

extern volatile int count;

extern char confirmValue[32];

extern int coincWindowValue;

extern volatile bool delay0SetFlag, delay1SetFlag, delay2SetFlag, delay3SetFlag;

extern int delay0Value, delay1Value, delay2Value, delay3Value;

void mode4program();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE4_H_ */
