/*
 * mode5.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode5program()
{
	TEC_controller0ActiveFlag = 1;
	TEC_controller1ActiveFlag = 1;


	Cy_SCB_UART_PutString(UART_HW, "SET MODE to CALIBRATION\r\n");

	if (*mode5Calibration==0)
	{

		Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Breakdown Voltage versus Temperature test\r\n");

		calibrateBreakdownvTemp();

		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			mode1program();
		}
	}

	else if (*mode5Calibration==1)
	{

		Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Detector Counts versus Discriminator Threshold test\r\n");

		calibrateCountsvDiscThresh();

		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			mode1program();
		}
	}

	else if (*mode5Calibration==1)
	{

		Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Detector Counts versus Bias Voltage test\r\n");

		calibrateCountsvBiasVolt();

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			mode1program();
		}
	}

	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nRunning ALL calibration\r\n");
		calibrateBreakdownvTemp();
		calibrateCountsvDiscThresh();
		calibrateCountsvBiasVolt();

	}


	mode1program();
}
