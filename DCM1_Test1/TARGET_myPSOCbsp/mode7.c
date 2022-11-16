/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode7program()
{
	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to OPTICAL ANNEALING");
	*printTelemetryFlag=true;
	check_countTime();
	for (int t = 0; t < *RTime; t++)
	{
		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		cyhal_system_delay_ms(countLoopDelay);
	}
	*printTelemetryFlag=false;
	mode1program();
}
