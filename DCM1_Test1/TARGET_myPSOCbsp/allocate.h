/*
 * allocate.h
 *
 *  Created on: Oct. 25, 2022
 *      Author: n6sultan
 */

#ifndef TARGET_MYPSOCBSP_ALLOCATE_H_
#define TARGET_MYPSOCBSP_ALLOCATE_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
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
#include "functions.h"
#include "tec.h"
#include "table.h"

extern volatile bool coincWindowSetFlag, uartRxCompleteFlag, warningFlag, printfeedbackFlag;
extern volatile int count;
extern char confirmValue[32];
extern float* mode;
extern float* VDET0;
extern float* VDET1;
extern float *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
extern float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin;
extern float *AnDET;
extern float *DthrEd, *DthrSt;
extern float *TempSt,*TempEd;
extern float *VoltSt, *VoltEd, *Exit;
extern float *kp; // PID Proportional Gain
extern float *ki;// PID Integral Gain
extern float *kd;

extern struct node *hash_table;
extern unsigned int table_size;
void default_hashtable();


#endif /* TARGET_MYPSOCBSP_ALLOCATE_H_ */
