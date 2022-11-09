/*
 * mode5.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode5program()
{

	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to CALIBRATION\r\n");
	printThermalInfo = *InitialTempInfo;

	if (*mode5Calibration == 0)
	{

		Cy_SCB_UART_PutString(UART_HW, "\r\nDET_Vb vs T\r\n");

		calibrateBreakdownvTemp();

		if (*Exit == 1)
		{
			mode1program();
		}
	}

	else if (*mode5Calibration == 1)
	{

		Cy_SCB_UART_PutString(UART_HW, "\r\nDETCounts vs DThrs\r\n");

		calibrateCountsvDiscThresh();

		if (*Exit == 1)
		{
			mode1program();
		}
	}

	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nALL CALIBRATION\r\n");
		Cy_SCB_UART_PutString(UART_HW, "\r\nDET_Vb vs T\r\n");
		calibrateBreakdownvTemp();
		Cy_SCB_UART_PutString(UART_HW, "\r\nDETCounts vs DThrs\r\n");
		calibrateCountsvDiscThresh();
	}
	mode1program();
}
