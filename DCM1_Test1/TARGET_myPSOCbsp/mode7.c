/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode7.h"

void mode7program()
{

	// Want to print thermistor readings for specified time
	Cy_SCB_UART_PutString(UART_HW, "SET MODE to OPTICAL ANNEALING\r\n");

	Cy_SCB_UART_PutString(UART_HW, "thermRead0, thermRead1, thermRead2, thermRead3\r\n ");
	for (int t = 0; t < *RTime; t++)
	{
		if (*rxBuffer == 'q')
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		Therm0_Read();
		Therm1_Read();
		Therm2_Read();
		Therm3_Read();

		sprintf(adcBuffer, "%f", ThermRead0);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", ThermRead1);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", ThermRead2);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", ThermRead3);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V");
		Cy_SCB_UART_PutString(UART_HW, "\r\n");
		cyhal_system_delay_ms(1000);
	}
	mode1program();
}
