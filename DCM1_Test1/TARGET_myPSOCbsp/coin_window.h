/*
 * coin_window.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_COIN_WINDOW_H_
#define TARGET_MYPSOCBSP_COIN_WINDOW_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>

extern volatile bool coincWindowSetFlag;

// Functions
void CoincidenceWindow_Init();
void CoincidenceWindow_Set(bool Bit1, bool bit2);
void SingleSide_Init();
void SingleSide_Set(bool Bit1, bool Bit2);

#endif /* TARGET_MYPSOCBSP_COIN_WINDOW_H_ */
