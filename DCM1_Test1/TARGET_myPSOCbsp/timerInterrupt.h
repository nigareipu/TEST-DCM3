/*
 * timerInterrupt.h
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */

#ifndef TARGET_MYPSOCBSP_TIMERINTERRUPT_H_
#define TARGET_MYPSOCBSP_TIMERINTERRUPT_H_

#include "uartInterrupt.h"
#include "modes.h"


void isr_timer(void *callback_arg, cyhal_timer_event_t event);
void cyhal_timer_event_interrupt();
void PID_loop0();
void PID_loop1();

extern volatile bool TEC_controller0ActiveFlag;
extern volatile bool TEC_controller1ActiveFlag;
extern float targetDetectorFlag0;
extern float targetDetectorFlag1;
extern cyhal_timer_t timer_obj;
extern double e_0, e1_0, e2_0, e_1, e1_1, e2_1;
extern double prev_output0, prev_output1, C_output0, C_output1;
extern volatile bool PID_Select;






#endif /* TARGET_MYPSOCBSP_TIMERINTERRUPT_H_ */
