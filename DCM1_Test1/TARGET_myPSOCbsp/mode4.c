/*
 * mode4.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode4.h"

void mode4program()
{

	float DET0_volt = 0;
	float DET1_volt = 0;
	float DET2_volt = 0;
	float DET3_volt = 0;

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to SINGLE SIDE COINCIDENCE COUNTING\r\n");

	// CODE FOR RUNNING  MODE

	SingleSide_Set(0, 0);

	printThermalInfo = 1;

	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

	/*****************************Test Pritning*************************/
	Cy_SCB_UART_PutString(UART_HW, "*VDET0: ");
	sprintf(confirmValue, "%f", *VDET0);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");

	Cy_SCB_UART_PutString(UART_HW, "*VDET1: ");
	sprintf(confirmValue, "%f", *VDET1);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");

	Cy_SCB_UART_PutString(UART_HW, "*VDET2: ");
	sprintf(confirmValue, "%f", *VDET2);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");


	Cy_SCB_UART_PutString(UART_HW, "*VDET3: ");
	sprintf(confirmValue, "%f", *VDET3);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");


	Cy_SCB_UART_PutString(UART_HW, "TDET0: ");
	sprintf(confirmValue, "%f", *TDET0);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");


	Cy_SCB_UART_PutString(UART_HW, "Runtime :");
	sprintf(confirmValue, "%f", *RTime);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");

	Cy_SCB_UART_PutString(UART_HW, "\r\n discriminator threshold:  ");
	sprintf(confirmValue, "%f\r\n", *DThrs);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");

	/*****************************TEst printing***************************/

	TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
	TEC_Driver1_Status(ON);
	cyhal_system_delay_ms(2000);

	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	StabilizeAllTemp(*TDET0);

	if (*rxBuffer == 'q')
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		uartRxCompleteFlag = 0;
		count = 0;
		return;
	}

	// Slowly ramp up voltages
	while (DET0_volt < *VDET0)
	{
		SetDetectorVoltage(DET0, DET0_volt);
		DET0_volt = DET0_volt + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET0, *VDET0);

	while (DET1_volt < *VDET1)
	{
		SetDetectorVoltage(DET1, DET1_volt);
		DET1_volt = DET1_volt + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET1, *VDET1);

	while (DET2_volt < *VDET2)
	{
		SetDetectorVoltage(DET2, DET2_volt);
		DET2_volt = DET2_volt + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET2, *VDET2);

	while (DET3_volt < *VDET3)
	{
		SetDetectorVoltage(DET3, DET3_volt);
		DET3_volt = DET3_volt + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET3, *VDET3);



	HV0_Monitor();
	cyhal_system_delay_ms(500);//required delay
	HV3_Monitor();
	cyhal_system_delay_ms(500);//required delay


	Cy_SCB_UART_PutString(UART_HW, "\r\nSingles 0, Singles 1, Singles 2,  Singles 3, Coincidence 0&2, Coincidence 1&3\r\n");
	//////Noura: Does this need to be commented out
	StartCounters();

	for (int k = 0; k < *RTime; k++)
	{
		if (*rxBuffer == 'q')
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			uartRxCompleteFlag = 0;
			count = 0;
			break;
		}

		UpdateAllTemp(*TDET0);
		GetSingles0Counts();
		GetSingles1Counts();
		GetSingles2Counts();
		GetSingles3Counts();
		// Want coin between 0&2 and 1&3
		GetCoincidence0Counts();
		GetCoincidence3Counts();
		Cy_SCB_UART_PutString(UART_HW, "\r\n");
		cyhal_system_delay_ms(1000);
	}

	mode1program();
}
