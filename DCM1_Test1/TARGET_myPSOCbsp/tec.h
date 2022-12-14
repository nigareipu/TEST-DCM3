/*
 * tec.h
 *
 *  Created on: Jun. 8, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_TEC_H_
#define TARGET_MYPSOCBSP_TEC_H_

#include <stdint.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "AD56x8.h"
#include "dac.h"
#include "spi.h"
#include "adc.h"
#include "allocate.h"

// declaration of global PID Coeficients
// extern float  k1, k2, k3;
extern float *kp, *ki, *kd; // PID coefficients
extern float *PIDLoopDlay;

// Error parameters
extern double e_1, e1_1, e2_1, e_1, e1_1, e2_1; // Error = (SetPoint - Feedback)
extern double prev_output0, prev_output1, C_output0, C_output1;

// System output temperature in voltage for Tec 0, 1, 2, 3
extern float thermRead0, thermRead1, thermRead2, thermRead3;

extern float ITEC0_V, ITEC1_V; // Current Reading as voltage for TEC Driver 0 and 1
//extern float *ITEC0, *ITEC1;     // TEC Driver 0 and 1 Current = (ITEC#_V-REF)/(8*R_SENSE),  Center point 1.5V = REF (no current)

extern uint32_t dacDataPacket;
extern uint16_t dacValue;

extern float tecDriver0StatusFlag;
extern float tecDriver1StatusFlag;

extern volatile bool printThermalInfo;

void TEC_Driver0_Status(uint8 status);
void TEC_Driver0_Init(uint8 status);
void TEC_Driver1_Status(uint8 status);
void TEC_Driver1_Init(uint8 status);
void TEC_SW0_Status(uint8 status);
void TEC_SW1_Status(uint8 status);
void TEC_SW2_Status(uint8 status);
void TEC_SW3_Status(uint8 status);
void TEC_SW0_Init(uint8 status);
void TEC_SW1_Init(uint8 status);
void TEC_SW2_Init(uint8 status);
void TEC_SW3_Init(uint8 status);
void monitorITEC0();
void monitorITEC1();
void GetAllTECCurrent();


#endif /* TARGET_MYPSOCBSP_TEC_H_ */
