/*
 * mode4.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode4program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to SINGLE SIDE COINCIDENCE COUNTING\r\n");
	printThermalInfo = 1;

	/*****************************Test Pritning*************************/
	if (*printMessageFlag == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "*VDET0: ");
		printFloat(*VDET0);

		Cy_SCB_UART_PutString(UART_HW, "*VDET1: ");
		printFloat(*VDET1);

		Cy_SCB_UART_PutString(UART_HW, "*VDET2: ");
		printFloat(*VDET2);

		Cy_SCB_UART_PutString(UART_HW, "*VDET3: ");
		printFloat(*VDET3);

		Cy_SCB_UART_PutString(UART_HW, "TDET0: ");
		printFloat(*TDET0);

		Cy_SCB_UART_PutString(UART_HW, "Runtime :");
		printFloat(*RTime);

		Cy_SCB_UART_PutString(UART_HW, "\r\n discriminator threshold:  ");
		printFloat(*DThrs);
	}

	/*****************************TEst printing***************************/

	// sets coincidence channel, window and delay
	SingleSide_Set(0, 0); // sets coin0-> 0&2 and coin1->1&2; but // Want coin between 0&2 and 1&3
	setCoincidenceWindowCommand(*CoWin);
	setDelay0Command(*DlayDET0);
	setDelay1Command(*DlayDET1);
	setDelay2Command(*DlayDET2);
	setDelay3Command(*DlayDET3);

	// sets discriminator threshold, turns on switches and bias voltages
	setParameters();
	setDetectorBias();



	Cy_SCB_UART_PutString(UART_HW, "\r\nSingles 0, Singles 1, Singles 2,  Singles 3, Coincidence 0&2, Coincidence 1&3\r\n");
	// Starts counting

	for (int k = 0; k < *RTime; k++)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		startSinglesCounting();
		// Want coin between 0&2 and 1&3
		GetCoincidence0Counts();
		GetCoincidence3Counts();
		Cy_SCB_UART_PutString(UART_HW, "\r\n");
		cyhal_system_delay_ms(*countTime);//Must be kept for accumulating counts/sec
	}

	mode1program();
}


