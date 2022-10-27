/*
 * timerInterrupt.h
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */

#ifndef TARGET_MYPSOCBSP_TIMERINTERRUPT_H_
#define TARGET_MYPSOCBSP_TIMERINTERRUPT_H_

#include "uartInterrupt.h"
#include "mode2.h"
#include "tec.h"

void isr_timer(void *callback_arg, cyhal_timer_event_t event);
void cyhal_timer_event_interrupt();
void PID_loop1(float tempSet);
void PID_loop2(float tempSet);

extern volatile bool TEC_controller1ActiveFlag;
extern volatile bool TEC_controller2ActiveFlag;
extern float targetDetectorFlag0;
extern float targetDetectorFlag1;
extern cyhal_timer_t timer_obj;
extern double e_0, e1_0, e2_0, e_1, e1_1, e2_1;




#endif /* TARGET_MYPSOCBSP_TIMERINTERRUPT_H_ */
