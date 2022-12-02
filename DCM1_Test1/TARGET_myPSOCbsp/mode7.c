/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode7program()
{
	Cy_SCB_UART_PutString(UART_HW, "SET MODE to OPTICAL ANNEALING");
	turnOFF_TECs();
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
	transition_modes_if_tec_start_global();
}
