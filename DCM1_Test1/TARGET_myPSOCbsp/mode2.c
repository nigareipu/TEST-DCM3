/*
 * mode2.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode2.h"

/*
 * @desc Checks all settings are correct for mode 2 and prints error messages if they are not. Runs in
 * mode 2 and prints coincidence counts
 * @returns Nothing
 */

void mode2program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to COINCIDENCE COUNTING\r\n");
	printThermalInfo = 1;


	/*****************************Test values for printing*************************/
	// if (printfeedbackFlag == 1){
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


	/*****************************End of test values for printing***************************/

	SingleSide_Set(1, 1); //sets coin0-> 0&1 and coin1->2&3; but  Want 12, 01, 23, 03
	settingParameters();
	TEC_controller1ActiveFlag = 1;
	TEC_controller2ActiveFlag = 1;
	targetDetectorFlag0 = 0;
	targetDetectorFlag1 =0;

	Cy_SCB_UART_PutString(UART_HW, "\r\nSingle Count Rate 0, 1, 2, 3, Coincidence 1&2, 0&1, 2&3, 0&3\r\n");



			//UpdateAllTemp(*TDET0);

			for (int k = 0; k < *RTime; k++)
			{
				// Press q to exit; must exist within a loop to function.

				if (*Exit == 1)
				{
					Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
					break;
				}

				UpdateAllTemp(*TDET0); //

				startCounting();
				cyhal_system_delay_ms(1000);//Must be kept for accumulating counts/sec
			}



	mode1program();
}
