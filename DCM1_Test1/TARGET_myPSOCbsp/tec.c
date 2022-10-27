/*
 * tec.c
 *
 *  Created on: Jun. 8, 2022
 *      Author: jkrynski1
 * 		Commented July 28, 2022: Noura-B
 *
 */

/*This Program is written based on the Z-Transform of PID loop for digital implementation.
It has e as loop input and u at loop output  */

#include "tec.h"
#include "adc.h"
#include "det_bias.h"

// Defining global variables
// PID tuning parameters

double e = 0; // Error = (SetPoint - Feedback)
double e1 = 0;
double e2 = 0;
double e3 = 0;
double e4 = 0;
double e5 = 0;
double C_output = 0.0;
double prev_output = 1.5;
double prev_output0 = 1.5;
double prev_output1 = 1.5;
double C_output0 = 0.0;
double C_output1 = 0.0;

float thermRead = 0.0;
float thermRead0 = 0.0; // System output temperature in voltage for Tec 0
float thermRead1 = 0.0; // System output temperature in voltage for Tec 1
float thermRead2 = 0.0; // System output temperature in voltage for Tec 2
float thermRead3 = 0.0;

float ITEC0_V, ITEC1_V, ITEC0, ITEC1;



void TEC_Driver0_Init(uint8 status)
{
	// Function initializing TEC Driver 0

	cyhal_gpio_init(P5_6, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);

	if (status == 1)
	{
		tecDriver0StatusFlag = 1;
	}
	else
	{
		tecDriver0StatusFlag = 0;
	}
}

void TEC_Driver0_Status(uint8 status)
{
	// Function for turning TEC Driver 0 ON and OFF

	cyhal_gpio_write(P5_6, status);

	if (status == 1)
	{
		tecDriver0StatusFlag = 1;
	}
	else
	{
		tecDriver0StatusFlag = 0;
	}
}

void TEC_Driver1_Init(uint8 status)
{
	// Function initializing TEC Driver 1

	cyhal_gpio_init(P5_7, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);

	if (status == 1)
	{
		tecDriver1StatusFlag = 1;
	}
	else
	{
		tecDriver1StatusFlag = 0;
	}
}

void TEC_Driver1_Status(uint8 status)
{
	// Function for turning TEC Driver 0 ON and OFF

	cyhal_gpio_write(P5_7, status);

	if (status == 1)
	{
		tecDriver1StatusFlag = 1;
	}
	else
	{
		tecDriver1StatusFlag = 0;
	}
}

void TEC_SW0_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_init(P6_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW0_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P6_4, status);
}

void TEC_SW1_Init(uint8 status)
{ // ON/OFF Switch function for TEC 1

	cyhal_gpio_init(P6_5, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW1_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P6_5, status);
}

void TEC_SW2_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 2

	cyhal_gpio_init(P7_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW2_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P7_2, status);
}

void TEC_SW3_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 2

	cyhal_gpio_init(P7_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW3_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P7_3, status);
}

void TEC0_StabilizeTemp(float tempSet)
{

	// EXPLAIN the function

	// PID Loop Coefficeints
	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	Cy_SCB_UART_PutString(UART_HW, "time (s), thermRead0 (V), thermRead1 (V), TEC 0 Current (A)\r\n");

	for (int i = 0; i < 30; i++)
	{
		// Start ADC conversion measurements
		Therm0_Read();
		Therm1_Read();

		if (targetDetectorFlag == 0)
		{
			thermRead = ThermRead0;
		}
		else
		{
			thermRead = ThermRead1;
		}

		// Initialize Loop to start feedback from second thermread value onwards (avoid overshooting due to false initial reading)
		if (i == 0)
		{
			continue;
		}

		if (thermRead < 0)
		{
			thermRead = 0;
		}

		// PID Controller
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead;							 // Calculating the error
		C_output = prev_output + k1 * e + k2 * e1 + k3 * e2; // Adjusting Correction Value

		if (C_output > 1.95)
		{
			C_output = 1.95; // Cooling Limit on current
		}
		else if (C_output < 1.2)
		{ // Heating Limit on current
			C_output = 1.2;
		}

		prev_output = C_output; // Correction value stored in prev_output

		// Applying correction to minimize error
		dacValue = convertTempSetVoltagetoDACVoltage(C_output);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		sprintf(adcBuffer, "%i", i);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 2);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", thermRead0);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", thermRead1);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		// TEC Driver Current reading
		monitorITEC0();
		Cy_SCB_UART_PutString(UART_HW, ",\r\n");

		cyhal_system_delay_ms(1000);
	}
}

void TEC1_StabilizeTemp(float tempSet)
{

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	Cy_SCB_UART_PutString(UART_HW, "time (s), thermRead2 (V), thermRead3 (V), TEC 1 Current (A)\r\n");

	for (int i = 0; i < 30; i++)
	{
		// Start ADC conversion measurements
		Therm2_Read();
		Therm3_Read();

		if (targetDetectorFlag == 0)
		{
			thermRead = ThermRead2;
		}
		else
		{
			thermRead = ThermRead3;
		}

		// Initializing PID Loop
		if (i == 0)
		{
			continue;
		}

		if (thermRead < 0)
		{
			thermRead = 0;
		}

		// THERM LOOP PARAMETER UPDATES
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead;
		C_output = prev_output + k1 * e + k2 * e1 + k3 * e2;
		if (C_output > 1.95)
		{
			C_output = 1.95;
		}
		else if (C_output < 1.2)
		{
			C_output = 1.2;
		}

		prev_output = C_output;

		dacValue = convertTempSetVoltagetoDACVoltage(C_output);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		sprintf(adcBuffer, "%i", i);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 2);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", thermRead2);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		sprintf(adcBuffer, "%f", thermRead3);
		// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
		Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
		// Cy_SCB_UART_PutString(UART_HW," V\r\n");
		Cy_SCB_UART_PutString(UART_HW, ",");

		monitorITEC1();
		Cy_SCB_UART_PutString(UART_HW, ",\r\n");

		cyhal_system_delay_ms(1000);
	}
}

void monitorITEC0()
{

	ITEC0_Read();
	ITEC0 = (ITEC0_V - 1.5) / (8 * 0.05);
	sprintf(adcBuffer, "%f", ITEC0);
	// Cy_SCB_UART_PutString(UART_HW,"ITEC0 = ");
	Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
	// Cy_SCB_UART_PutString(UART_HW," A\r\n");
}

void monitorITEC1()
{

	ITEC1_Read();
	ITEC1 = (ITEC1_V - 1.5) / (8 * 0.05);
	sprintf(adcBuffer, "%f", ITEC1);
	// Cy_SCB_UART_PutString(UART_HW,"ITEC1 = ");
	Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
	// Cy_SCB_UART_PutString(UART_HW," A\r\n");
}

void GetAllTECCurrent(void)
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	ITEC0_V = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, ITEC0channel, Cy_SAR_GetResult16(SAR_ADC_HW, ITEC0channel));
	ITEC1_V = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, ITEC1channel, Cy_SAR_GetResult16(SAR_ADC_HW, ITEC1channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

void TEC0_updateTemp(float tempSet)
{

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	// Cy_SCB_UART_PutString(UART_HW,"thermRead0 (V), thermRead1 (V), TEC 0 Current (A)\r\n");

	for (int i = 0; i < 1; i++)
	{
		// Start ADC conversion measurements
		Therm0_Read();
		Therm1_Read();

		// Initializing PID Loop
		if (i == 0)
		{
			continue;
		}

		if (targetDetectorFlag == 0)
		{
			thermRead = ThermRead0;
		}
		else
		{
			thermRead = thermRead1;
		}

		if (thermRead < 0)
		{
			thermRead = 0;
		}

		// THERM LOOP PARAMETER UPDATES
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead;
		C_output = prev_output + k1 * e + k2 * e1 + k3 * e2;
		if (C_output > 1.95)
		{
			C_output = 1.95;
		}
		else if (C_output < 1.2)
		{
			C_output = 1.2;
		}

		prev_output = C_output;

		dacValue = convertTempSetVoltagetoDACVoltage(C_output);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		if (printThermalInfo == 1)
		{
			sprintf(adcBuffer, "%f", ThermRead0);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead1);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			monitorITEC0();
			Cy_SCB_UART_PutString(UART_HW, ",");
		}

		Cy_SAR_StopConvert(SAR_ADC_HW);
	}
}

void TEC1_updateTemp(float tempSet)
{

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	// Cy_SCB_UART_PutString(UART_HW,"time (s), thermRead2 (V), thermRead3 (V), TEC 1 Current (A)\r\n");

	for (int i = 0; i < 1; i++)
	{
		// Start ADC conversion measurements
		Therm2_Read();
		Therm3_Read();

		if (targetDetectorFlag == 0)
		{
			thermRead = ThermRead2;
		}
		else
		{
			thermRead = ThermRead3;
		}

		// Initializing PID Loop
		if (i == 0)
		{
			continue;
		}

		if (thermRead < 0)
		{
			thermRead = 0;
		}

		// THERM LOOP PARAMETER UPDATES
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead;
		C_output = prev_output + k1 * e + k2 * e1 + k3 * e2;
		if (C_output > 1.95)
		{
			C_output = 1.95;
		}
		else if (C_output < 1.2)
		{
			C_output = 1.2;
		}

		prev_output = C_output;

		dacValue = convertTempSetVoltagetoDACVoltage(C_output);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		if (printThermalInfo == 1)
		{
			sprintf(adcBuffer, "%f", ThermRead2);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead3);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			monitorITEC1();
			Cy_SCB_UART_PutString(UART_HW, ",");
		}

		Cy_SAR_StopConvert(SAR_ADC_HW);
	}
}

void StabilizeAllTemp(float tempSet)
{
	// Function for cooling down all detectors

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	Cy_SCB_UART_PutString(UART_HW, "thermRead0 (V), thermRead1 (V), thermRead2 (V), thermRead3 (V), TEC 0 Current (A), TEC 1 Current (A)\r\n");

	for (int i = 0; i < 30; i++)
	{

		if (*rxBuffer == 'q')
		{
			break;
		}

		// Start ADC conversion measurements
		Therm0_Read();
		Therm1_Read();
		Therm2_Read();
		Therm3_Read();

		if (targetDetectorFlag == 0)
		{
			thermRead0 = ThermRead0;
		}
		else
		{
			thermRead0 = ThermRead1;
		}

		if (targetDetectorFlag2 == 0)
		{
			thermRead1 = ThermRead2;
		}
		else
		{
			thermRead1 = ThermRead3;
		}

		// Initializing PID Loop
		if (i == 0)
		{
			continue;
		}

		if (thermRead0 < 0)
		{
			thermRead0 = 0;
		}

		if (thermRead1 < 0)
		{
			thermRead1 = 0;
		}

		// THERM LOOP PARAMETER UPDATES
		// Process Variables for TEC Drive 0 (Error calculation for feedback)
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead0;

		// Process Variables for TEC Drive 1
		e5 = e4;
		e4 = e3;
		e3 = tempSet - thermRead1;

		// Calculating the control function (output) for TEC 0 and TEC 2
		C_output0 = prev_output0 + k1 * e + k2 * e1 + k3 * e2;
		C_output1 = prev_output1 + k1 * e3 + k2 * e4 + k3 * e5;

		// Current limit for TEC Driver 0
		if (C_output0 > 1.95)
		{
			C_output0 = 1.95; // Cooling limit
		}
		else if (C_output0 < 1.2)
		{ // Heating limit
			C_output0 = 1.2;
		}

		// Current Limit for TEC Driver 1
		if (C_output1 > 1.95)
		{
			C_output1 = 1.95; // Cooling limit
		}
		else if (C_output1 < 1.2)
		{
			C_output1 = 1.2; // Heating limit
		}

		// Storing control function for feedback
		prev_output0 = C_output0;
		prev_output1 = C_output1;

		// Output of the loop updating the DAC for TEC_Driver0
		dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		// Output of the loop updating the DAC for TEC_Driver1
		dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		if (printThermalInfo == 1)
		{
			sprintf(adcBuffer, "%f", ThermRead0);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead1);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead2);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead2 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead3);
			// Cy_SCB_UART_PutString(UART_HW,"thermRead3 = ");
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			// Cy_SCB_UART_PutString(UART_HW," V\r\n");
			Cy_SCB_UART_PutString(UART_HW, ",");

			monitorITEC0();
			Cy_SCB_UART_PutString(UART_HW, ",");
			monitorITEC1();
			Cy_SCB_UART_PutString(UART_HW, ",\r\n");
		}

		Cy_SAR_StopConvert(SAR_ADC_HW);
		cyhal_system_delay_ms(1000);
	}
}

// change settime to length (command setl) and choosedetector to DET_0 in bias code
// make sure the detectors are off and only on is on
// ranges can be found in prompt.h for set l and set det

void Annealing(uint16_t detector, float length, float DET0_temp)
{

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	Cy_SCB_UART_PutString(UART_HW, "Thermistor (V), TEC Current (A)\r\n");

	for (int i = 0; i < length; i++)
	{
		if (*rxBuffer == 'q')
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}
		if (detector == DET0 || detector == DET1)
		{

			// Selecting detectors on TEC Driver 0 for ADC conversion
			if (detector == DET0)
			{
				Therm0_Read();
				thermRead = ThermRead0;
			}

			else if (detector == DET1)
			{
				Therm1_Read();
				thermRead = ThermRead1;
			}

			// Initializing PID Loop
			if (i == 0)
			{
				continue;
			}

			if (thermRead < 0)
			{
				thermRead = 0;
			}

			// Annealing the detector to (0.12 V == 91 celsius)
			e2 = e1;
			e1 = e;
			e = DET0_temp - thermRead;

			// Calculating the control function (output) for TEC 0 and TEC 2
			C_output = prev_output + k1 * e + k2 * e1 + k3 * e2;

			// Current limit for TEC Driver 0
			if (C_output > 1.95)
			{
				C_output = 1.95; // Cooling limit
			}
			else if (C_output < 1.2)
			{ // Heating limit
				C_output = 1.2;
			}

			// Storing control function for feedback
			prev_output = C_output;

			// Output of the loop updating the DAC for TEC Driver 0
			dacValue = convertTempSetVoltagetoDACVoltage(C_output);
			dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
			transmitToHVDAC(dacDataPacket);

			if (printThermalInfo == 1)
			{
				if (detector == DET0)
				{
					sprintf(adcBuffer, "%f", ThermRead0);
					// Cy_SCB_UART_PutString(UART_HW,"thermRead0 = ");
					Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
					// Cy_SCB_UART_PutString(UART_HW," V\r\n");
					Cy_SCB_UART_PutString(UART_HW, ",");
				}
				else if (detector == DET1)
				{
					sprintf(adcBuffer, "%f", ThermRead1);
					// Cy_SCB_UART_PutString(UART_HW,"thermRead1 = ");
					Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
					// Cy_SCB_UART_PutString(UART_HW," V\r\n");
					Cy_SCB_UART_PutString(UART_HW, ",");
				}

				monitorITEC0();
				Cy_SCB_UART_PutString(UART_HW, "\r\n");
				Cy_SAR_StopConvert(SAR_ADC_HW);
				cyhal_system_delay_ms(1000);
			}
		}

		else if (detector == DET2 || detector == DET3)
		{

			// Selecting TECs on TEC Driver 1
			if (detector == DET2)
			{
				Therm2_Read();
				thermRead = ThermRead2;
			}

			else if (detector == DET3)
			{
				Therm3_Read();
				thermRead = ThermRead3;
			}

			// Ignoring flaky thermread terms
			if (i == 0)
			{
				continue;
			}

			if (thermRead < 0)
			{
				thermRead = 0;
			}

			// Annealing the detector to (0.22 = 70C to 0.12 V == 91 C)
			e2 = e1;
			e1 = e;
			e = DET0_temp - thermRead;

			// Calculating the control function (output) for TEC 0 and TEC 2
			C_output = prev_output + k1 * e + k2 * e1 + k3 * e2;

			// Current limit for TEC Driver 0 to avoid overshooting
			if (C_output > 1.95)
			{
				C_output = 1.95;
			}
			else if (C_output < 1.2)
			{
				C_output = 1.2;
			}

			// Storing control function for feedback
			prev_output = C_output;

			// Output of the loop updating the DAC for TEC_Driver1
			dacValue = convertTempSetVoltagetoDACVoltage(C_output);
			dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
			transmitToHVDAC(dacDataPacket);

			if (printThermalInfo == 1)
			{
				if (detector == DET2)
				{
					sprintf(adcBuffer, "%f", ThermRead2);
					// Cy_SCB_UART_PutString(UART_HW,"thermRead2 = ");
					Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
					// Cy_SCB_UART_PutString(UART_HW," V\r\n");
					Cy_SCB_UART_PutString(UART_HW, ",");
				}
				else if (detector == DET3)
				{
					sprintf(adcBuffer, "%f", ThermRead3);
					// Cy_SCB_UART_PutString(UART_HW,"thermRead3 = ");
					Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
					// Cy_SCB_UART_PutString(UART_HW," V\r\n");
					Cy_SCB_UART_PutString(UART_HW, ",");
				}

				monitorITEC1();
				Cy_SCB_UART_PutString(UART_HW, "\r\n");
				Cy_SAR_StopConvert(SAR_ADC_HW);
				cyhal_system_delay_ms(1000);
			}
		}
	}
}

// add print statements saying which detector is on
void TurnTEC_ON(uint16_t detector)
{

	if (detector == DET0)
	{
		TEC_Driver0_Status(ON);
		cyhal_system_delay_ms(2000);
		TEC_SW0_Status(ON);
	}
	else if (detector == DET1)
	{
		TEC_Driver0_Status(ON);
		cyhal_system_delay_ms(2000);
		TEC_SW1_Status(ON);
	}
	else if (detector == DET2)
	{
		TEC_Driver1_Status(ON);
		cyhal_system_delay_ms(2000);
		TEC_SW2_Status(ON);
	}
	else if (detector == DET3)
	{
		TEC_Driver1_Status(ON);
		cyhal_system_delay_ms(2000);
		TEC_SW3_Status(ON);
	}
}

void TurnTEC_OFF(uint16_t detector)
{

	if (detector == DET0)
	{
		TEC_Driver0_Status(OFF);
		cyhal_system_delay_ms(2000);
		TEC_SW0_Status(OFF);
	}
	else if (detector == DET1)
	{
		TEC_Driver0_Status(OFF);
		cyhal_system_delay_ms(2000);
		TEC_SW1_Status(OFF);
	}
	else if (detector == DET2)
	{
		TEC_Driver1_Status(OFF);
		cyhal_system_delay_ms(2000);
		TEC_SW2_Status(OFF);
	}
	else if (detector == DET3)
	{
		TEC_Driver1_Status(OFF);
		cyhal_system_delay_ms(2000);
		TEC_SW3_Status(OFF);
	}
}

void UpdateAllTemp(float tempSet)
{
	// Updating Detector 0 and 1 simultanously

	TEC0_updateTemp(tempSet);
	TEC1_updateTemp(tempSet);
}
