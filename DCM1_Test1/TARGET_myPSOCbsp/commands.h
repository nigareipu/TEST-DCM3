/*
 * commands.h
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#ifndef LIBS_TARGET_CY8CPROTO_062S3_4343W_COMMANDS_H_
#define LIBS_TARGET_CY8CPROTO_062S3_4343W_COMMANDS_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "det_bias.h"
#include "coin_window.h"
#include "tec.h"
#include "discr.h"
#include "modes.h"
#include "allocate.h"


extern float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
extern volatile bool delay0SetFlag, delay1SetFlag, delay2SetFlag, delay3SetFlag;

void Init_Hardware();
void setCoincidenceWindowCommand(int ConcidanceWindow);
void setDelay0Command(int DelayValue);
void setDelay1Command(int DelayValue);
void setDelay2Command(int DelayValue);
void setDelay3Command(int DelayValue);
void startSinglesCounting();
void startCoincidenceCounting();
void printFloat(float message);
void setParameters();
void setDetectorBias();
void turnON_TECs();
void turnOFF_TECs();
void SetCounters();
void check_countTime();

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_COMMANDS_H_ */
