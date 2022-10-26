/*
 * mode1.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE1_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE1_H_

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

extern volatile int count;
extern volatile bool uartRxCompleteFlag;

extern float discrThresh;
extern float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
extern float DET0_temp, DET1_temp, DET2_temp, DET3_temp;
extern float length;
// extern volatile bool timer_interrupt_flag;

/*
 *
 * This mode goes into automated turning off all active device
 *
 */
void mode1program(void);

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_MODE1_H_ */
