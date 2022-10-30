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

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to COINCIDENCE COUNTING\r\n");
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

	SingleSide_Set(1, 1); //sets coin0-> 0&1 and coin1->2&3; but  Want 12, 01, 23, 03
	setParameters();
	setDetectorBias();
	//printThermalInfo=0;

	/********counting loop*****************************/

	Cy_SCB_UART_PutString(UART_HW, "\r\nSingle Count Rate 0, 1, 2, 3, Coincidence 1&2, 0&1, 2&3, 0&3\r\n");
	for (int k = 0; k < *RTime; k++)
	{

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		startSinglesCounting();
		startCoincidenceCounting();
		Cy_SCB_UART_PutString(UART_HW, "\r\n");

		/*dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);*/

		cyhal_system_delay_ms(*countTime);//Must be kept for accumulating counts/sec
	}
	mode1program();
}
