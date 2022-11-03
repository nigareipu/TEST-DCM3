/*
 * mode2.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

/*
 * @desc Checks all settings are correct for mode 2 and prints error messages if they are not. Runs in
 * mode 2 and prints coincidence counts
 * @returns Nothing
 */

void mode2program()
{

	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to COINCIDENCE COUNTING\r\n");
	printThermalInfo = 1;


	/*****************************Test values for printing*************************/
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

	/*****************************End of test values for printing***************************/

	/********settings for MODE2***********************/

	//check if countTime is acceptable
	check_countTime();
	SingleSide_Set(1, 1); //sets coin0-> 0&1 and coin1->2&3; but  Want 12, 01, 23, 03
	setParameters();
	setDetectorBias();

	printThermalInfo=*printThermalFlag;

	for (int k = 0; k < *RTime; k++)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		ClockStamp0 = Cy_SysTick_GetValue();
		startSinglesCounting();
		startCoincidenceCounting();
		SetCounters();

		//ClockStamp1 = Cy_SysTick_GetValue();

		sprintf(confirmValue, "\n\rClockStamp, S0, S1, S2, S3, C12, C01, C23, C03 : %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\r\n ",
				ClockStamp0, Singles0_CountRate, Singles1_CountRate, Singles2_CountRate, Singles3_CountRate, Coincidence0_CountRate, Coincidence1_CountRate,
				Coincidence2_CountRate, Coincidence3_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, strlen(confirmValue));


		cyhal_system_delay_ms(countLoopDelay);//Must be kept for accumulating counts/sec
	}
	mode1program();
}
