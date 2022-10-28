/*
 * mode1.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode1.h"

void mode1program(void)
{
	TEC_controller0ActiveFlag = 0;
	TEC_controller1ActiveFlag = 0;


	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to IDLE");

	// CODE FOR RUNNING IDLE MODE
	Cy_SCB_UART_PutString(UART_HW, "\r\nCurrently in IDLE MODE.\r\n");
	Cy_SCB_UART_PutString(UART_HW, "High voltage OFF\r\n");

	DET0_voltage = 0;
	DET1_voltage = 0;
	DET2_voltage = 0;
	DET3_voltage = 0;

	SetDetectorVoltage(DET0, DET0_voltage);
	SetDetectorVoltage(DET1, DET1_voltage);
	SetDetectorVoltage(DET2, DET2_voltage);
	SetDetectorVoltage(DET3, DET3_voltage);

	Cy_SCB_UART_PutString(UART_HW, "Thermoelectric cooler OFF\r\n");

	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	Cy_SCB_UART_PutString(UART_HW, "Counters OFF\r\n");
	// Do we need code here?

	length = 100;
	CoincidenceWindow_Set(0, 0);
	Delay0_Set(0, 0);
	Delay1_Set(0, 0);
	Delay2_Set(0, 0);
	Delay3_Set(0, 0);

	// timer_interrupt_flag = false;

	// Threshold chosen to be low, but above noisy falling edge of avalanche.
	discrThresh = 0.20;
	// Change DEFAULT TEMPERATURE here. Vtherm = 0.85 is about room temperature.
	DET0_temp = 0.85;

	Cy_SCB_UART_PutString(UART_HW, "Choose another command and value \r\n ");
	uartRxCompleteFlag = 0;
	count = 0;
}
