/*
 * mode3.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

void mode3program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to ACCIDENTAL COUNTING");


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
	//check if countTime is acceptable
	check_countTime();
	//check if tec starts locally
	check_inside_mode_tec_start();


	if(*Exit== false){
		// sets coincidence channel, window and delay
		SingleSide_Set(1, 1); // sets coin0-> 0&1 and coin1->2&3; but Want 12, 01, 23, 03
		setCoincidenceWindowCommand(*CoWin);
		setDelay0Command(*DlayDET0);
		setDelay1Command(*DlayDET1);
		setDelay2Command(*DlayDET2);
		setDelay3Command(*DlayDET3);
		// sets bias voltages
		setDetectorBias();
	}

	// Starts counting
	for (int k = 0; k < *RTime; k++)
	{
		if (*Exit == true)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		ClockStamp0 = Cy_SysTick_GetValue();

		SetCounters();
		cyhal_system_delay_ms(*msTime);//change it by a variable

		startSinglesCounting();
		startCoincidenceCounting();

		sprintf(confirmValue, "\n\rClk, S0, S1, S2, S3, C01, C12, C03, C23: %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu",
				ClockStamp0, Singles0_CountRate, Singles1_CountRate, Singles2_CountRate, Singles3_CountRate, Coincidence0_CountRate, Coincidence1_CountRate,
				Coincidence2_CountRate, Coincidence3_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, strlen(confirmValue));


		cyhal_system_delay_ms(countLoopDelay-*msTime);//Must be kept for accumulating counts/sec
	}
	//check if TEC to turn off
	check_mode_tec_end();
	mode1program();
	//*printTelemetryFlag=true;
}
