/*
 * calibration.c
 *
 *  Created on: May 20, 2022
 *      Author: jkrynski1
 */

#include "modes.h"

/*
 * @desc For each detector 0-3, does a voltage scan and prints counts at a range of temps
 * @returns Nothing
 */

void calibrateBreakdownvTemp()
{

	float currentVoltage = 0;
	printThermalInfo = 1;

	// Turn on TECs
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

    unsigned int DET[] = {DET0, DET1, DET2, DET3};

    for (int d = 0; d < 4; d++)
	{

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;//should it be break or return
		}

		// Set temperature loop.. make sure to print also what the temperature is.
		// Range should be 0.9-1.36 corresponds to 16 degrees to -20 degrees (celsius)
		for (float temp = *TempSt; temp <= *TempEd; temp = temp + 0.1)
		{

			if (*Exit == 1)
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}

			Cy_SCB_UART_PutString(UART_HW, "SetTemp = ");
			sprintf(txBuffer, "%f", temp);
			Cy_SCB_UART_Transmit(UART_HW, txBuffer, 8, &uartContext);
			Cy_SCB_UART_PutString(UART_HW, "\r\n\r\n");

			if (d==0)
			{
				*TDET0 = temp;
				*targetTECFlag0=0;
			}
			else if (d==1)
			{
				*TDET1 = temp;
				*targetTECFlag0=1;
			}
			else if (d==1)
			{
				*TDET2 = temp;
				*targetTECFlag1=0;
			}
			else {
				*TDET3 = temp;
				*targetTECFlag1=1;
			}
			cyhal_system_delay_ms(10000);


			// stabilize temperature



			if (*Exit == 1)
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}

			while (currentVoltage < *VoltSt)
			{
				SetDetectorVoltage(DET[d], currentVoltage);
				currentVoltage = currentVoltage + 10;
				cyhal_system_delay_ms(10);
			}


			SetDetectorVoltage(DET[d], *VoltSt);
			// Do a voltage scan at each temperature
			VoltageScan(DET[d], *VoltSt, *VoltEd);

		}
	}

	//SetDetectorVoltage(DET3, 0);
	// Turn off TECs
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);

	uartRxCompleteFlag = 0;
	count = 0;
}
/*
 * @desc At -20c and 20v above breakdown, prints counts for a range of discr thresh
 * @returns Nothing
 */

void calibrateCountsvDiscThresh()
{

	float volt0 = 0;
	float volt1 = 0;
	float volt2 = 0;
	float volt3 = 0;

	printThermalInfo = 1;

	// Set temp and stabilize
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	//StabilizeAllTemp(*TDET0);

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}

	// Set voltage of detectors gradually
	while (volt0 < *VDET0)
	{
		SetDetectorVoltage(DET0, volt0);
		volt0 = volt0 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET0, *VDET0);

	while (volt1 < *VDET1)
	{
		SetDetectorVoltage(DET1, volt1);
		volt1 = volt1 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET1, *VDET1);

	while (volt2 < *VDET2)
	{
		SetDetectorVoltage(DET2, volt2);
		volt2 = volt2 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET2, *VDET2);

	while (volt3 < *VDET3)
	{
		SetDetectorVoltage(DET3, volt3);
		volt3 = volt3 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET3, *VDET3);

	// Threshold less than 0.14 V can lead to double counting noisy falling edge of avalanche.
	for (float thresh = *DthrSt; thresh < *DthrEd; thresh = thresh + 0.01)
	{

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		// Set discriminator thresholds
		setDiscr0Thresh(thresh);
		setDiscr1Thresh(thresh);
		setDiscr2Thresh(thresh);
		setDiscr3Thresh(thresh);

		// Print information
		Cy_SCB_UART_PutString(UART_HW, "\r\n thresholds =  ");
		sprintf(txBuffer, "%.3f", thresh);
		Cy_SCB_UART_Transmit(UART_HW, txBuffer, 4, &uartContext);
		Cy_SCB_UART_PutString(UART_HW, "\r\n ");
		Cy_SCB_UART_PutString(UART_HW, "Singles 0, Singles 1, Singles 2, Singles 3 s\r\n");

		// Print out singles counts for all detectors
		for (int i = 0; i < 10; i++)
		{
			if (*Exit == 1)
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}
			startSinglesCounting();
			//UpdateAllTemp(*TDET0);
			Cy_SCB_UART_PutString(UART_HW, "\r\n");
			cyhal_system_delay_ms(1000);
		}
	}

	// Turn off TECs
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);
}

/*
 * @desc For each detector 0-3, does a voltage scan starting at breakdown at 0c
 * @returns Nothing
 */

void calibrateCountsvBiasVolt()
{

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		return;
	}


	float currentVoltage = 0;


	// Cy_SCB_UART_Enable(UART_HW);

	printThermalInfo = 1;

	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

	Cy_SCB_UART_PutString(UART_HW, "\r\nTurning on TEC Drivers\r\n");
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);

	Cy_SCB_UART_PutString(UART_HW, "Turning on all TECs\r\n");
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

    unsigned int DET[] = {DET0, DET1, DET2, DET3};

	for (int d = 0; d < 4; d = d + 1)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		currentVoltage = 0;

		// Slowly ramp up bias voltage
		while (currentVoltage < *VoltSt)
		{
			SetDetectorVoltage(DET[d], currentVoltage);
			currentVoltage = currentVoltage + 10;
			cyhal_system_delay_ms(10);
		}

		SetDetectorVoltage(DET[d], *VoltSt);

		// Stabilize temperature for 30 s to -1?
		//Cy_SCB_UART_PutString(UART_HW, "Stabilizing temperatures for 30 s\r\n");
		//StabilizeAllTemp(temp);

		VoltageScan(DET[d], *VoltSt, *VoltEd);
	}

	Cy_SCB_UART_PutString(UART_HW, "Turning off all TECs\r\n\r\n");
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	Cy_SCB_UART_PutString(UART_HW, "Turning off TEC Drivers\r\n\r\n");
	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);
}

