/*
 * mode3.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode3program()
{

	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to ACCIDENTAL COUNTING\r\n");
	printThermalInfo = 1;

	/*****************************Test Printing*************************/
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
	SingleSide_Set(1, 1); // sets coin0-> 0&1 and coin1->2&3; but Want 12, 01, 23, 03
	setCoincidenceWindowCommand(*CoWin);
	setDelay0Command(*DlayDET0);
	setDelay1Command(*DlayDET1);
	setDelay2Command(*DlayDET2);
	setDelay3Command(*DlayDET3);

	// sets discriminator threshold, turns on switches and bias voltages
	setParameters();
	setDetectorBias();

	printThermalInfo=*printThermalFlag;

	// Starts counting
	for (int k = 0; k < *RTime; k++)
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nS0, S1, S2, S3, C12, C01, C23, C03: ");
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		startSinglesCounting();
		startCoincidenceCounting();
		Cy_SCB_UART_PutString(UART_HW, "\r\n");
		cyhal_system_delay_ms(*countTime);//Must be kept for accumulating counts/sec
	}

	mode1program();
}
