/*
 * discr.h
 *
 *  Created on: Jun. 10, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_DISCR_H_
#define TARGET_MYPSOCBSP_DISCR_H_

#include "AD56x8.h"
#include "dac.h"
#include "spi.h"
#include "mode1.h"

void setDiscr0Thresh(float discrThresh);
void setDiscr1Thresh(float discrThresh);
void setDiscr2Thresh(float discrThresh);
void setDiscr3Thresh(float discrThresh);

extern char discrThreshArray[4];

#endif /* TARGET_MYPSOCBSP_DISCR_H_ */
