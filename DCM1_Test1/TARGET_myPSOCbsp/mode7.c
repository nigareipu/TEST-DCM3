/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode7program()
{
	Cy_SCB_UART_PutString(UART_HW, "SET MODE to OPTICAL ANNEALING\r\n");
	printThermalInfo=1;

	for (int t = 0; t < *RTime; t++)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		cyhal_system_delay_ms(1000);
	}
	mode1program();
}
