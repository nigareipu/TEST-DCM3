/*
 * mode5.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode5.h"

void mode5program()
{
	// Need to check the delays
	Cy_SCB_UART_PutString(UART_HW, "SET MODE to CALIBRATION\r\n");

	cyhal_system_delay_ms(3000);

	Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Breakdown Voltage versus Temperature test\r\n");

	calibrateBreakdownvTemp();

	cyhal_system_delay_ms(3000);

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}

	Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Detector Counts versus Discriminator Threshold test\r\n");

	calibrateCountsvDiscThresh();

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}

	cyhal_system_delay_ms(3000);

	Cy_SCB_UART_PutString(UART_HW, "\r\nRunning Detector Counts versus Bias Voltage test\r\n");

	calibrateCountsvBiasVolt();

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}


	mode1program();
}
