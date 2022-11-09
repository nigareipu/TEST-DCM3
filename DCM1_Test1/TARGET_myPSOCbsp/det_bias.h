/*
 * det_bias.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_DET_BIAS_H_
#define TARGET_MYPSOCBSP_DET_BIAS_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "dac.h"
#include "AD56x8.h"
#include "spi.h"
#include "counters.h"
#include "commands.h"
#include "modes.h"

#define DET0 (0x00)
#define DET1 (0x01)
#define DET2 (0x04)
#define DET3 (0x05)

extern uint16_t dacValue;
extern uint32_t dacDataPacket;

// Functions
void SetDetectorVoltage(uint16_t detector, float voltage);
void VoltageScan(uint16_t detector, float startVoltage, float endVoltage, float temp);

#endif /* TARGET_MYPSOCBSP_DET_BIAS_H_ */
