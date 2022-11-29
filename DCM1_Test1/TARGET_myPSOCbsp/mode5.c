/*
 * mode5.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode5program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to CALIBRATION");

	if (*mode5Calibration == 0)
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nDET_Vb vs T");
		calibrateBreakdownvTemp();
	}

	else if (*mode5Calibration == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nDETCounts vs DThrs");
		calibrateCountsvDiscThresh();
	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nALL CALIBRATION");
		Cy_SCB_UART_PutString(UART_HW, "\r\nDET_Vb vs T");
		calibrateBreakdownvTemp();
		Cy_SCB_UART_PutString(UART_HW, "\r\nDETCounts vs DThrs");
		calibrateCountsvDiscThresh();
	}
	mode1program();
}
