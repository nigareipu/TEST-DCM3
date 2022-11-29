/*
 * mode4.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode4program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to SINGLE SIDE COINCIDENCE COUNTING");

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

	/*****************************TEst printing done ***************************/

	check_countTime();
	if(*Exit== false){
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
	cyhal_system_delay_ms(*TempStabilizationDlay);
	}

	// Starts counting

	for (int k = 0; k < *RTime; k++)
	{

		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		ClockStamp0 = Cy_SysTick_GetValue();
		startSinglesCounting();
		// Want coin between 0&2 and 1&3
		Coincidence0_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_0_HW, Coinc_0_NUM);
		Coincidence3_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_3_HW, Coinc_3_NUM);
		SetCounters();

		sprintf(confirmValue, "\n\rClk, S0, S1, S2, S3, C02, C13: %lu, %lu, %lu, %lu, %lu, %lu, %lu",
				ClockStamp0, Singles0_CountRate, Singles1_CountRate, Singles2_CountRate, Singles3_CountRate, Coincidence0_CountRate,
				Coincidence3_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, strlen(confirmValue));

		cyhal_system_delay_ms(countLoopDelay);//Must be kept for accumulating counts/sec
	}
	mode1program();
}
