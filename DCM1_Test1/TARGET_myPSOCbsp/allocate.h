
#ifndef TARGET_MYPSOCBSP_ALLOCATE_H_
#define TARGET_MYPSOCBSP_ALLOCATE_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>
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
#include "table.h"


///Testing new table
#define TABLE_SIZE 200
extern struct TNODE table[TABLE_SIZE];

//extern volatile bool coincWindowSetFlag, uartRxCompleteFlag, warningFlag, printfeedbackFlag;
extern volatile int count;
extern char confirmValue[200];
extern uint8_t *mode, *RTime, *DetSt, *DetEd, *CoWin, *AnDET;
extern uint16_t *maxcountTime, *countTime;
extern float *VDET0;
extern float *VDET1;
extern float *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *DThrs;
extern float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3;
extern float *DthrEd, *DthrSt;
extern float *TempSt, *TempEd;
extern float *VoltSt, *VoltEd;
extern float *kp; // PID Proportional Gain
extern float *ki; // PID Integral Gain
extern float *kd;
extern float *HVMoni0, *HVMoni3, *ThermRead0, *ThermRead1, *ThermRead2, *ThermRead3, *ITEC0, *ITEC1;
extern bool *targetTECFlag0, *targetTECFlag1, *printMessageFlag,*mode5Calibration, *printThermalFlag, *Exit, *InitialTempInfo;

void default_hashtable();

#endif /* TARGET_MYPSOCBSP_ALLOCATE_H_ */
