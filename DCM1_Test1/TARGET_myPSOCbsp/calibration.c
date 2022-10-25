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
/*
void calibrateBreakdownvTemp()
{

	float startVoltage;
	float endVoltage;
	float currentVoltage = 0;

	// Threshold chosen here to be 50 mV because it reflects closer breakdown voltage as compared with oscilloscope.
	discrThresh = 0.05;

	printThermalInfo = 1;

	// Turn on TECs
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	setDiscr0Thresh(discrThresh);
	setDiscr1Thresh(discrThresh);
	setDiscr2Thresh(discrThresh);
	setDiscr3Thresh(discrThresh);

	for (int d = 0; d <= 3; d++)
	{

		if (*rxBuffer == 'q' || *rxBuffer == 'a')
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			return;
		}

		// Pick a detector
		if (d == 0)
		{
			detector = DET0;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 0 Calibration\r\n");
			startVoltage = 340; // DCM1: 240; DCM2:
			endVoltage = 370;	// DCM1:290;
			currentVoltage = 0;
		}
		else if (d == 1)
		{

			detector = DET1;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 1 Calibration\r\n");
			startVoltage = 340; // DCM1: 240; DCM2:
			endVoltage = 370;	// DCM1:290;
			currentVoltage = 0;
			SetDetectorVoltage(DET0, 0);
		}
		else if (d == 2)
		{
			detector = DET2;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 2 Calibration\r\n");
			startVoltage = 300; // DCM1: 238; DCM2:
			endVoltage = 330;	// DCM1:288;
			currentVoltage = 0;
			SetDetectorVoltage(DET1, 0);
		}
		else if (d == 3)
		{

			detector = DET3;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 3 Calibration\r\n");
			startVoltage = 270; // DCM1: 247; DCM2:
			endVoltage = 300;	// DCM1: 297; DCM2:
			currentVoltage = 0;
			SetDetectorVoltage(DET2, 0);
		}

		// Set temperature loop.. make sure to print also what the temperature is.
		// Range should be 0.9-1.36 corresponds to 16 degrees to -20 degrees (celsius)
		for (float temp = 0.9; temp <= 1.35 + 0.01; temp = temp + 0.1)
		{

			if (*rxBuffer == 'q' || *rxBuffer == 'a')
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				return;
			}

			Cy_SCB_UART_PutString(UART_HW, "SetTemp = ");
			sprintf(txBuffer, "%f", temp);
			Cy_SCB_UART_Transmit(UART_HW, txBuffer, 8, &uartContext);
			Cy_SCB_UART_PutString(UART_HW, "\r\n\r\n");

			DET0_temp = temp;

			Cy_SCB_UART_PutString(UART_HW, "Stabilizing temperatures for 30 s\r\n");

			// stabilize temperature
			StabilizeAllTemp(temp);

			if (*rxBuffer == 'q' || *rxBuffer == 'a')
			{
				return;
			}
			//	if (d == 0 || d == 1){
			//		TEC0_StabilizeTemp(temp);
			//	}
			//	else{
			//		TEC1_StabilizeTemp(temp);
			//	}

			// Slowly ramp up bias voltage
			while (currentVoltage < startVoltage)
			{
				SetDetectorVoltage(detector, currentVoltage);
				currentVoltage = currentVoltage + 10;
				cyhal_system_delay_ms(10);
			}
			SetDetectorVoltage(detector, startVoltage);

			// Do a voltage scan at each temperature
			VoltageScan(detector, startVoltage, endVoltage);
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
*/
/*
 * @desc At -20c and 20v above breakdown, prints counts for a range of discr thresh
 * @returns Nothing
 */

/*
void calibrateCountsvDiscThresh()
{

	float volt0 = 0;
	float volt1 = 0;
	float volt2 = 0;
	float volt3 = 0;
	// Should be 20v above breakdown, see datasheet for approx breakdown
	float DET0_voltage = 381.5;
	float DET1_voltage = 379.5;
	float DET2_voltage = 344;
	float DET3_voltage = 315.5;
	// Temperature at -12
	float temp = 0.9;

	printThermalInfo = 1;

	// Set temp and stabilize
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	StabilizeAllTemp(temp);

	if (*rxBuffer == 'q' || *rxBuffer == 'b')
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		return;
	}

	// Set voltage of detectors gradually
	while (volt0 < DET0_voltage)
	{
		SetDetectorVoltage(DET0, volt0);
		volt0 = volt0 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET0, DET0_voltage);

	while (volt1 < DET1_voltage)
	{
		SetDetectorVoltage(DET1, volt1);
		volt1 = volt1 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET1, DET1_voltage);

	while (volt2 < DET2_voltage)
	{
		SetDetectorVoltage(DET2, volt2);
		volt2 = volt2 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET2, DET2_voltage);

	while (volt3 < DET3_voltage)
	{
		SetDetectorVoltage(DET3, volt3);
		volt3 = volt3 + 10;
		cyhal_system_delay_ms(10);
	}
	SetDetectorVoltage(DET3, DET3_voltage);

	// Threshold less than 0.14 V can lead to double counting noisy falling edge of avalanche.
	for (float thresh = 0.20; thresh < 1.10; thresh = thresh + 0.01)
	{

		if (*rxBuffer == 'q' || *rxBuffer == 'b')
		{
			return;
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
			if (*rxBuffer == 'q' || *rxBuffer == 'b')
			{
				Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				return;
			}
			GetSingles0Counts();
			GetSingles1Counts();
			GetSingles2Counts();
			GetSingles3Counts();
			UpdateAllTemp(temp);
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
*/
/*
 * @desc For each detector 0-3, does a voltage scan starting at breakdown at 0c
 * @returns Nothing
 */
/*
void calibrateCountsvBiasVolt()
{

	if (*rxBuffer == 'q' || *rxBuffer == 'c')
	{
		return;
	}

	// choose start at previously found Breakdown
	float startVoltage = 0;
	float endVoltage = 0;
	float currentVoltage = 0;
	float temp = 1.15;
	discrThresh = 0.20;

	// Cy_SCB_UART_Enable(UART_HW);

	printThermalInfo = 1;

	setDiscr0Thresh(discrThresh);
	setDiscr1Thresh(discrThresh);
	setDiscr2Thresh(discrThresh);
	setDiscr3Thresh(discrThresh);

	Cy_SCB_UART_PutString(UART_HW, "\r\nTurning on TEC Drivers\r\n");
	TEC_Driver0_Status(ON);
	TEC_Driver1_Status(ON);

	Cy_SCB_UART_PutString(UART_HW, "Turning on all TECs\r\n");
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);

	for (int d = 0; d < 4; d = d + 1)
	{
		if (*rxBuffer == 'q' || *rxBuffer == 'c')
		{
			return;
		}

		currentVoltage = 0;

		if (d == 0)
		{

			detector = DET0;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 0 Calibration\r\n");

			startVoltage = 360;
			endVoltage = 365;
			// startVoltage = 350; //Vbr = 354
			// endVoltage = 380;
		}
		else if (d == 1)
		{

			detector = DET1;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 1 Calibration\r\n");

			startVoltage = 375;
			endVoltage = 380;

			// startVoltage = 347; // Vbr=351.5
			// endVoltage = 377;
		}
		else if (d == 2)
		{

			detector = DET2;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 2 Calibration\r\n");

			startVoltage = 330;
			endVoltage = 335;

			// startVoltage = 310;//Vbr=314
			// endVoltage = 340;
		}
		else if (d == 3)
		{

			detector = DET3;
			Cy_SCB_UART_PutString(UART_HW, "\r\nDetector 3 Calibration\r\n");

			startVoltage = 314;
			endVoltage = 320;

			// startVoltage = 288;//Vbr = 291
			// endVoltage = 318;
		}

		// Slowly ramp up bias voltage
		while (currentVoltage < startVoltage)
		{
			SetDetectorVoltage(detector, currentVoltage);
			currentVoltage = currentVoltage + 10;
			cyhal_system_delay_ms(10);
		}

		SetDetectorVoltage(detector, startVoltage);

		// Stabilize temp for 30 s
		Cy_SCB_UART_PutString(UART_HW, "Stabilizing temperatures for 30 s\r\n");
		StabilizeAllTemp(temp);

		VoltageScan(detector, startVoltage, endVoltage);
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
*/
