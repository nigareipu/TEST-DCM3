/*
 * counters.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_COUNTERS_H_
#define TARGET_MYPSOCBSP_COUNTERS_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "modes.h"

// External variables declared
extern uint32_t Singles0_CountRate;
extern uint32_t Singles1_CountRate;
extern uint32_t Singles2_CountRate;
extern uint32_t Singles3_CountRate;

extern uint32_t Coincidence0_CountRate;
extern uint32_t Coincidence1_CountRate;
extern uint32_t Coincidence2_CountRate;
extern uint32_t Coincidence3_CountRate;

// Functions
void SinglesCounter0_Init();
void SinglesCounter1_Init();
void SinglesCounter2_Init();
void SinglesCounter3_Init();
void CoincidenceCounter0_Init();
void CoincidenceCounter1_Init();
void CoincidenceCounter2_Init();
void CoincidenceCounter3_Init();

void SysTick_Init();

#endif /* TARGET_MYPSOCBSP_COUNTERS_H_ */
