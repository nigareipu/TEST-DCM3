/*
 * dac.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_DAC_H_
#define TARGET_MYPSOCBSP_DAC_H_

#include <stdint.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "AD56x8.h"
#include "spi.h"

// Globals
extern uint32_t dacDataPacket;
extern uint16_t dacValue;

// Functions
uint16_t convertHighVoltagetoDACVoltage(float inputVoltage);
uint16_t convertDiscrThreshtoDACVoltage(float inputVoltage);
uint16_t convertTempSetVoltagetoDACVoltage(float inputVoltage);

uint32_t prepareDACDataPacket(uint16_t data, uint16_t channel, uint16_t command);
void setDiscrDACInternalRef();
void setHVDACInternalRef();

#endif /* TARGET_MYPSOCBSP_DAC_H_ */
