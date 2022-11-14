
#include "modes.h"

/*
 * @desc For each detector 0-3, does a voltage scan and prints counts at a range of temps
 * @returns Nothing
 */

void calibrateBreakdownvTemp()
{

	float currentVoltage = 0;
	setParameters();
	// Turn on TECs

	unsigned int DET[] = {DET0, DET1, DET2, DET3};

	for (int d = *DetSt; d < *DetEd; d++)
	{

		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		// Set temperature loop.. make sure to print also what the temperature is.
		// Range should be 0.9-1.36 corresponds to 16 degrees to -20 degrees (celsius)
		for (float temp = *TempSt; temp <= *TempEd; temp = temp + 0.1)
		{

			if (*Exit == 1)
			{
				//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}

			// Set TEC for Therm feedback
			if (d == 0)
			{
				*TDET0 = temp;
				*targetTECFlag0 = 0;
			}
			else if (d == 1)
			{
				*TDET1 = temp;
				*targetTECFlag0 = 1;
			}
			else if (d == 2)
			{
				*TDET2 = temp;
				*targetTECFlag1 = 0;
			}
			else if (d == 3)
			{
				*TDET3 = temp;
				*targetTECFlag1 = 1;
			}
			/***************************************************************************
			 * *******************This is required to settle temperature before counting*************
			 **************************************************************************/
			if(*Exit== false){
				cyhal_system_delay_ms(*TempStabilizationDlay);
			}

			if (*Exit == 1)
			{
				//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
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
			VoltageScan(DET[d], *VoltSt, *VoltEd, temp);
		}
	}

	// Turn off TECs
	turnOFF_TECs();
	//mode1program();
}
/*
 * @desc At -20c and 20v above breakdown, prints counts for a range of discr thresh
 * @returns Nothing
 */

void calibrateCountsvDiscThresh()
{
	turnON_TECs();
	if (*Exit == 1)
	{
		//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		return;
	}
	check_countTime();
	if(*Exit== false){
		// Set voltage of detectors gradually
		setDetectorBias();
	}

	// Threshold less than 0.14 V can lead to double counting noisy falling edge of avalanche.
	for (float thresh = *DthrSt; thresh < *DthrEd; thresh = thresh + 0.01)
	{
		if (*Exit == 1)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		// Set discriminator thresholds
		setDiscr0Thresh(thresh);
		setDiscr1Thresh(thresh);
		setDiscr2Thresh(thresh);
		setDiscr3Thresh(thresh);

		// Single counts for each detector information

		// Print out singles counts for all detectors
		for (int i = 0; i < 10; i++)
		{
			if (*Exit == 1)
			{
				//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
				break;
			}
			ClockStamp0 = Cy_SysTick_GetValue();
			startSinglesCounting();
			SetCounters();
			sprintf(confirmValue, "\n\rClockStamp, DThrs, S0, S1, S2, S3:  %lu, %.2f, %lu, %lu, %lu, %lu\n\r", ClockStamp0, thresh, Singles0_CountRate, Singles1_CountRate, Singles2_CountRate, Singles3_CountRate);
			Cy_SCB_UART_PutString(UART_HW, confirmValue);
			cyhal_system_delay_ms(countLoopDelay);
		}
	}
	// Turn off TECs
	turnOFF_TECs();
	//mode1program();
}
