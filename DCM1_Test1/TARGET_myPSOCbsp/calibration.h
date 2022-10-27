/*
 * calibration.h
 *
 *  Created on: May 20, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_CALIBRATION_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_CALIBRATION_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "det_bias.h"
#include "discr.h"
#include "serialUART.h"
#include "spi.h"
#define ON (1u)
#define OFF (0u)


extern float *VDET0,*VDET1,*VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
extern float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin;
extern float *AnDET;
extern float *DthrEd, *DthrSt;
extern float *TempSt,*TempEd;
extern float *VoltSt, *VoltEd;
extern float *Exit;

void calibrateBreakdownvTemp();
void calibrateCountsvDiscrThresh();
void calibrateCountsvBiasVolt();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_CALIBRATION_H_ */
