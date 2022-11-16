/*
 * mode1.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage; //Local voltage variables in mode 1

void mode1program()
{
	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to IDLE\r\n");

	// SETTINGS FOR RUNNING IDLE MODE


	TEC_controller0ActiveFlag = 0;
	TEC_controller1ActiveFlag = 0;

	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

	DET0_voltage = 0;
	DET1_voltage = 0;
	DET2_voltage = 0;
	DET3_voltage = 0;

	SetDetectorVoltage(DET0, DET0_voltage);
	SetDetectorVoltage(DET1, DET1_voltage);
	SetDetectorVoltage(DET2, DET2_voltage);
	SetDetectorVoltage(DET3, DET3_voltage);

	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	CoincidenceWindow_Set(0, 0);
	Delay0_Set(0, 0);
	Delay1_Set(0, 0);
	Delay2_Set(0, 0);
	Delay3_Set(0, 0);

	*Exit = false;
	*count_timerInterruptEvent=0;
	*mode = 0;
}
