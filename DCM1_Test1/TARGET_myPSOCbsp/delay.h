/*
 * delays.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_DELAYS_H_
#define TARGET_MYPSOCBSP_DELAYS_H_

extern volatile bool delay0SetFlag, delay1SetFlag, delay2SetFlag, delay3SetFlag;

//Functions
void Delays_Init();
void Delay0_Set(bool Delay0Bit1, bool Delay0Bit2);
void Delay1_Set(bool Delay1Bit1, bool Delay1Bit2);
void Delay2_Set(bool Delay2Bit1, bool Delay2Bit2);
void Delay3_Set(bool Delay3Bit1, bool Delay3Bit2);



#endif /* TARGET_MYPSOCBSP_DELAYS_H_ */
