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
#include "serialUART.h"
#include "det_bias.h"
#include "coin_window.h"
#include "tec.h"
#include "discr.h"

extern int idx;
extern char voltageArray[3];
extern char confirmValue[32];
extern char lengthArray[4];

extern volatile bool coincWindowSetFlag;
extern int coincWindowValue;

extern float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
extern float DET0_temp, DET1_temp, DET2_temp, DET3_temp;
extern float length;
extern float Annealing_temp;

extern volatile bool delay0SetFlag, delay1SetFlag, delay2SetFlag, delay3SetFlag;
extern volatile bool DetectorSetFlag;

extern int delay0Value, delay1Value, delay2Value, delay3Value;
extern float fvalue;
extern char* command;

void Init_Hardware();
//void setTECCommand();// actually not sure
//void setLengthCommand();
//void setVoltageCommand();
void setCoincidenceWindowCommand(float ConcidanceWindow);
void setDelay0Command(float DelayValue);
void setDelay1Command(float DelayValue);
void setDelay2Command(float DelayValue);
void setDelay3Command(float DelayValue);
void startCounting();
void printFloat(float message);
//void setTempCommand();
//void setAnnealingTempCommand();
//void setDiscrThreshCommand();

// Updating Hash Table Values
//void* inout();
//void update_table(char* command, float value);

#endif /* LIBS_TARGET_CY8CPROTO_062S3_4343W_COMMANDS_H_ */
