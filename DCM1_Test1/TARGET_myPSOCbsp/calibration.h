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

extern float discrThresh;

void calibrateBreakdownvTemp();
void calibrateCountsvDiscrThresh();
void calibrateCountsvBiasVolt();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_CALIBRATION_H_ */
