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

void isr_timer(void *callback_arg, cyhal_timer_event_t event);
void cyhal_timer_event_interrupt();
void PID_loop(float tempSet);

extern volatile bool timer_interrupt_flag;
extern cyhal_timer_t timer_obj;




#endif /* TARGET_MYPSOCBSP_TIMERINTERRUPT_H_ */
