/*
 * counters.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_COUNTERS_H_
#define TARGET_MYPSOCBSP_COUNTERS_H_

//#include "functions.h"
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

#include <stdio.h>
#include "string.h"
#include <stdlib.h>

extern char lengthArray[4];

// External variables declared
extern uint32_t Singles0_CountRate;
extern uint32_t Singles1_CountRate;
extern uint32_t Singles2_CountRate;
extern uint32_t Singles3_CountRate;

extern uint32_t Coincidence0_CountRate;
extern uint32_t Coincidence1_CountRate;
extern uint32_t Coincidence2_CountRate;
extern uint32_t Coincidence3_CountRate;

extern uint32_t prevCount0;
extern uint32_t prevCount1;
extern uint32_t prevCount2;
extern uint32_t prevCount3;

extern uint32_t prevCoinCount0;
extern uint32_t prevCoinCount1;
extern uint32_t prevCoinCount2;
extern uint32_t prevCoinCount3;

extern uint32_t deltaTick;
extern uint32_t sysTick;
extern uint32_t prevTick;

// Functions

void SinglesCounter0_Init();
void SinglesCounter1_Init();
void SinglesCounter2_Init();
void SinglesCounter3_Init();
void CoincidenceCounter0_Init();
void CoincidenceCounter1_Init();
void CoincidenceCounter2_Init();
void CoincidenceCounter3_Init();

void SinglesCounter0_Read(uint32_t *prevCount0);
void SinglesCounter1_Read(uint32_t *prevCount1);
void SinglesCounter2_Read(uint32_t *prevCount2);
void SinglesCounter3_Read(uint32_t *prevCount3);

void CoincidenceCounter0_Read(uint32_t *CoinCount0);
void CoincidenceCounter1_Read(uint32_t *CoinCount1);
void CoincidenceCounter2_Read(uint32_t *CoinCount2);
void CoincidenceCounter3_Read(uint32_t *CoinCount3);

void SysTick_Init();
void getSysTick(uint32_t *prevTick);

void GetSingles0Counts();
void GetSingles1Counts();
void GetSingles2Counts();
void GetSingles3Counts();
void GetCoincidence0Counts();
void GetCoincidence1Counts();
void GetCoincidence2Counts();
void GetCoincidence3Counts();
void GetAllSinglesCounts();
void GetAllCounts();
void StartCounters();
// void GetCoincidence0Counts();

#endif /* TARGET_MYPSOCBSP_COUNTERS_H_ */
