/*
 * det_bias.c
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#include "det_bias.h"
#include "dac.h"
#include "spi.h"
#include "counters.h"

float voltage;
float voltStart, voltFinish;

// uint16_t dacValue;
// uint32_t dacDataPacket;

/*
 * @desc Sets the given detector's voltage to the given voltage
 * @param uint16_t detector - The detector whose voltage will be set (DET_0, DET_1, DET_2, DET_3)
 * @param float voltage - The voltage that the chosen detector will be set to
 * @returns Nothing
 */
void SetDetectorVoltage(uint16_t detector, float voltage)
{

	float inputVoltage;

	char confirmValue[32];

	inputVoltage = voltage;

	if (detector == DET0)
	{

		dacValue = convertHighVoltagetoDACVoltage(inputVoltage);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_A, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}

	else if (detector == DET1)
	{
		dacValue = convertHighVoltagetoDACVoltage(inputVoltage);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_B, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}

	else if (detector == DET2)
	{
		dacValue = convertHighVoltagetoDACVoltage(inputVoltage);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_E, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}

	else if (detector == DET3)
	{
		dacValue = convertHighVoltagetoDACVoltage(inputVoltage);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_F, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}
}

/*
 * @desc Sets the given detector to voltages ranging from startVoltage to endVoltage in steps of 0.5.
 * After setting a new voltage it waits 1s before printing information including counts once a second
 * for 4 seconds
 * @param uint16_t detector - The detector whose voltage will be altered (DET_0, DET_1, DET_2, DET_3)
 * @param float startVoltage - The voltage the scan will start at
 * @param float endVoltage - The voltage the scan will end at
 * @returns Nothing
 */
void VoltageScan(uint16_t detector, float startVoltage, float endVoltage)
{

	char voltStep[5];

	Cy_SCB_UART_PutString(UART_HW, "Detector Bias Voltage, Count Rate\r\n");
	// Voltage scan loop for each temperature
	for (float voltage = startVoltage; voltage < endVoltage + 0.5; voltage = voltage + 0.5)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		SetDetectorVoltage(detector, voltage);

		for (int j = 0; j < 1; j++)
		{
			sprintf(voltStep, "%f", voltage);
			Cy_SCB_UART_PutArray(UART_HW, voltStep, 5);
			Cy_SCB_UART_PutString(UART_HW, ",");
			// should be an if statement dependent on det chosen
			if (detector == DET0)
			{
				//TEC0_updateTemp(DET0_temp);
				GetSingles0Counts();
			}
			if (detector == DET1)
			{
				//TEC0_updateTemp(DET0_temp);
				GetSingles1Counts();
			}
			if (detector == DET2)
			{
				//TEC1_updateTemp(DET0_temp);
				GetSingles2Counts();
			}
			if (detector == DET3)
			{
				//TEC1_updateTemp(DET0_temp);
				GetSingles3Counts();
			}
			Cy_SCB_UART_PutString(UART_HW, "\r\n");
			cyhal_system_delay_ms(1000);
		}
	}
}
