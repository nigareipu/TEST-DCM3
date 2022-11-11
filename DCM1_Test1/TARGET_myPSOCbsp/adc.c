/*
 * delay.c
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#include "adc.h"

int16_t HVMoni0Counts;
int16_t HVMoni3Counts;
int16_t THERM0;
int16_t THERM1;
int16_t THERM2;
int16_t THERM3;
float HVMoni0Volts;
float HVMoni3Volts;
//float ThermRead;
/*float HVMoni0;
float HVMoni3;
float ThermRead0;
float ThermRead1;
float ThermRead2;
float ThermRead3;*/

// Functions

/* @desc Initializes ADC
 * @returns Nothing
 */
void ADC_Init()
{

	cy_en_sysanalog_status_t status_aref;

	status_aref = Cy_SysAnalog_Init(&Cy_SysAnalog_Fast_Local);
	Cy_SysAnalog_Enable();
	// ADC Settings
	Cy_SAR_Init(SAR_ADC_HW, &SAR_ADC_config);
	Cy_SAR_Enable(SAR_ADC_HW);
}

/* @desc Read voltage from HV 0 feedback line. Value of HVMoni will be between 0 and Vref (2.048V) and must be converted to read
 * high voltage: Vconverted = HVMoni *(10039.2/39.2)
 * @returns Nothing
 */
void HV0_Monitor(void)
{
	//Cy_SAR_StopConvert(SAR_ADC_HW);
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);

	for (int j = 0; j < 10; j++)
	{

		HVMoni0Counts = Cy_SAR_GetResult16(SAR_ADC_HW, hvmoni0channel);
		HVMoni0Volts = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, hvmoni0channel, HVMoni0Counts);
		// This accounts for voltage divider, will print actual high voltage
		*HVMoni0 = HVMoni0Volts * 10039.2 / 39.2;
	}
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/* @desc Read voltage from HV 3 feedback line. Value of HVMoni will be between 0 and Vref (2.048V) and must be converted to read
 * high voltage: Vconverted = HVMoni *(10039.2/39.2)
 * @returns Nothing
 */
void HV3_Monitor(void)
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	for (int j = 0; j < 10; j++)
	{
		HVMoni3Counts = Cy_SAR_GetResult16(SAR_ADC_HW, hvmoni3channel);
		HVMoni3Volts = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, hvmoni3channel, HVMoni3Counts);
		// This accounts for voltage divider, will print actual high voltage
		*HVMoni3 = HVMoni3Volts * 10039.2 / 39.2;
	}
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets the voltage reading of thermistor 0
 * @returns Nothing
 */
void Therm0_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM0 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel);
	*ThermRead0 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread0channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets the voltage reading of thermistor 1
 * @returns Nothing
 */
void Therm1_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM1 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel);
	*ThermRead1 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread1channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets the voltage reading of thermistor 2
 * @returns Nothing
 */
void Therm2_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM2 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel);
	*ThermRead2 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread2channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets the voltage reading of thermistor 3
 * @returns Nothing
 */
void Therm3_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM3 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel);
	*ThermRead3 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread3channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets the voltage reading of all thermistors
 * @returns Nothing
 */
/*void GetAllThermRead(void)
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	ThermRead0 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread0channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel));
	ThermRead1 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread1channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel));
	ThermRead2 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread2channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel));
	ThermRead3 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread3channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}*/

/*
 * @desc Gets current for TEC 0
 * @returns Nothing
 */
void ITEC0_Read()
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	ITEC0_V = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, ITEC0channel, Cy_SAR_GetResult16(SAR_ADC_HW, ITEC0channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
 * @desc Gets current for TEC 1
 * @returns Nothing
 */
void ITEC1_Read()
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	ITEC1_V = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, ITEC1channel, Cy_SAR_GetResult16(SAR_ADC_HW, ITEC1channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}
