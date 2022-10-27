/*
 * calibration.c
 *
 *  Created on: May 20, 2022
 *      Author: jkrynski1
 */

#include "calibration.h"

// FOR CALIBRATION IT IS IMPORTANT TO CHANGE THESE VALUES TO MATCH YOUR BOARD
// In lines 29-30, the start and end voltage should be a range to encompass the approx breakdown voltages from
// the datasheets.
// In lines 134-137 the voltages should be 20v above breakdown for each detector at -20c
// In lines 255-256, 264-265, 271-271, 279-280 want to start at breakdown and end at 30v above breakdown at -20c

/*From Excelitas data sheet, breakdown voltage for at - 10C (+/- 3C) were:
DCM1: Det 0 - 252
	  Det 1 - 252
	  Det 2 - 250
	  Det 3 - 259

DCM2: Det 0 - 260
	  Det 1 - 258
	  Det 2 - 262
	  Det 3 - 273
*/
/*
 * @desc For each detector 0-3, does a voltage scan and prints counts at a range of temps
 * @returns Nothing
 */

void calibrateBreakdownvTemp()
{

	float currentVoltage = 0;

	// Threshold chosen here to be 50 mV because it reflects closer breakdown voltage as compared with oscilloscope.
	//Set discrThresh to = 0.05 to find the breakdown voltage

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

		//Now one voltage set for all detectors

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

			DET0_temp = temp;

			Cy_SCB_UART_PutString(UART_HW, "Stabilizing temperatures for 30 s\r\n");

			// stabilize temperature
			StabilizeAllTemp(temp);

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

			Cy_SCB_UART_PutString(UART_HW, "\r\n\r\n");

			SetDetectorVoltage(DET[d], *VoltSt);
			// Do a voltage scan at each temperature
			VoltageScan(DET[d], *VoltSt, *VoltEd);

		}
	}

	SetDetectorVoltage(DET3, 0);
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

	StabilizeAllTemp(*TDET0);

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
		Cy_SCB_UART_PutString(UART_HW, "\r\nDiscriminator thresholds set to: ");
		sprintf(txBuffer, "%.3f", thresh);
		Cy_SCB_UART_Transmit(UART_HW, txBuffer, 4, &uartContext);
		Cy_SCB_UART_PutString(UART_HW, "\r\n\r\n ");
		Cy_SCB_UART_PutString(UART_HW, "Singles 0, Singles 1, Singles 2, Singles 3 s\r\n");

		// Print out singles counts for all detectors
		for (int i = 0; i < 10; i++)
		{
			if (*Exit == 1)
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}
			GetSingles0Counts();
			GetSingles1Counts();
			GetSingles2Counts();
			GetSingles3Counts();
			UpdateAllTemp(*TDET0);
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
	float temp = 1.15;

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
		Cy_SCB_UART_PutString(UART_HW, "Stabilizing temperatures for 30 s\r\n");
		StabilizeAllTemp(temp);

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

