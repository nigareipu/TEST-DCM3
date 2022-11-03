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
void VoltageScan(uint16_t detector, float startVoltage, float endVoltage, float temp)
{

	printThermalInfo = *printThermalFlag;

	// Voltage scan loop for each temperature
	for (float voltage = startVoltage; voltage < endVoltage + 0.5; voltage = voltage + 0.5)
	{
		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		/*Cy_SCB_UART_PutString(UART_HW, "\n\rDET, Tset, DBias, DCount: ");
		sprintf(voltStep, "%i, %.4f, %.3f, ", detector, temp, voltage);
		Cy_SCB_UART_PutString(UART_HW, voltStep);*/

		SetDetectorVoltage(detector, voltage);
		ClockStamp0 = Cy_SysTick_GetValue();
		for (int j = 0; j < 1; j++)
		{
			// should be an if statement dependent on det chosen
			if (detector == DET0)
			{
				//TEC0_updateTemp(DET0_temp);
				Singles0_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_0_HW, Singles_0_NUM);
				sprintf(confirmValue, "\n\rClockStamp, DET, Tset, DBias, S0: %lu, 0, %.4f, %.2f, %lu", ClockStamp0, temp, voltage, Singles0_CountRate);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
			}
			if (detector == DET1)
			{
				//TEC0_updateTemp(DET0_temp);
				Singles1_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_1_HW, Singles_1_NUM);
				sprintf(confirmValue, "\n\rClockStamp, DET, Tset, DBias, S1: %lu, 1, %.4f, %.2f, %lu", ClockStamp0, temp, voltage, Singles1_CountRate);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
			}
			if (detector == DET2)
			{
				//TEC1_updateTemp(DET0_temp);
				Singles2_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_2_HW, Singles_2_NUM);
				sprintf(confirmValue, "\n\rClockStamp, DET, Tset, DBias, S2: %lu, 2, %.4f, %.2f, %lu", ClockStamp0, temp, voltage, Singles2_CountRate);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
			}
			if (detector == DET3)
			{
				//TEC1_updateTemp(DET0_temp);
				Singles3_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_3_HW, Singles_3_NUM);
				sprintf(confirmValue, "\n\rClockStamp, DET, Tset, DBias, S3: %lu, 3, %.4f, %.2f, %lu", ClockStamp0, temp, voltage, Singles3_CountRate);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
			}
			SetCounters();
			cyhal_system_delay_ms(*countTime);
		}
	}
}
