
#include "modes.h"

/*
 * @desc For each detector 0-3, does a voltage scan and prints counts at a range of temps
 * @returns Nothing
 */

void calibrateBreakdownvTemp()
{

	float currentVoltage = 0;
	printThermalInfo = 1;
	setParameters();
	// Turn on TECs

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
			/***************************************************************************
			 * *******************This is required to settle temperature before counting*************
			 **************************************************************************/
			cyhal_system_delay_ms(10000);

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
			printThermalInfo=0;
			// Do a voltage scan at each temperature
			VoltageScan(DET[d], *VoltSt, *VoltEd);

		}
	}

	//SetDetectorVoltage(DET3, 0);
	// Turn off TECs
    turnOFF_TECs();

	uartRxCompleteFlag = 0;
	count = 0;
}
/*
 * @desc At -20c and 20v above breakdown, prints counts for a range of discr thresh
 * @returns Nothing
 */

void calibrateCountsvDiscThresh()
{
	// Set temp and stabilize
	turnON_TECs();
	//StabilizeAllTemp(*TDET0);

	if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}

	// Set voltage of detectors gradually
	setDetectorBias();

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
		printThermalInfo=0;

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
	turnOFF_TECs();
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

	setParameters();

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
		printThermalInfo=0;
		VoltageScan(DET[d], *VoltSt, *VoltEd);
	}

	turnOFF_TECs();
}

