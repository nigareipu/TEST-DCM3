	/*
 * mode3.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode2.h"

void mode3program()
{

	float volt0 = 0;
	float volt1 = 0;
	float volt2 = 0;
	float volt3 = 0;

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to ACCIDENTAL COUNTING\r\n");
	printThermalInfo = 1;

	/*****************************Test Pritning*************************/
	// if (printfeedbackFlag == 1){
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

	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

	TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
	TEC_Driver1_Status(ON);

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
	// Set voltage of detectors gradually
	while (volt0 < *VDET0)
	{
		SetDetectorVoltage(DET0, volt0);
		volt0 = volt0 + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET0, *VDET0);

	while (volt1 < *VDET1)
	{
		SetDetectorVoltage(DET1, volt1);
		volt1 = volt1 + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET1, *VDET1);

	while (volt2 < *VDET2)
	{
		SetDetectorVoltage(DET2, volt2);
		volt2 = volt2 + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET2, *VDET2);

	while (volt3 < *VDET3)
	{
		SetDetectorVoltage(DET3, volt3);
		volt3 = volt3 + 10;
		cyhal_system_delay_ms(1);
	}
	SetDetectorVoltage(DET3, *VDET3);

	HV0_Monitor();
	cyhal_system_delay_ms(500);//required delay
	HV3_Monitor();
	cyhal_system_delay_ms(500);//required delay

	Cy_SCB_UART_PutString(UART_HW, "\r\nSingle Count Rate 0, 1, 2, 3, Coincidence 1&2, 0&1, 2&3, 0&3\r\n");

	SingleSide_Set(1, 1);

	for (int k = 0; k < *RTime; k++)
	{
		if (*rxBuffer == 'q')
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		UpdateAllTemp(*TDET0);
		GetSingles0Counts();
		GetSingles1Counts();
		GetSingles2Counts();
		GetSingles3Counts();
		// Want 12, 01, 23, 03
		GetCoincidence1Counts();
		GetCoincidence0Counts();
		GetCoincidence3Counts();
		GetCoincidence2Counts();
		Cy_SCB_UART_PutString(UART_HW, "\r\n");
		cyhal_system_delay_ms(1000);
	}


	mode1program();
}
