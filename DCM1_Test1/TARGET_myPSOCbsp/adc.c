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
float ThermRead;
float HVMoni0ConvertedVolts;
float HVMoni3ConvertedVolts;
float ThermRead0;
float ThermRead1;
float ThermRead2;
float ThermRead3;

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

	// Cy_SCB_UART_PutString(UART_HW,"ADC Initalized \r\n");
}

/* @desc Read voltage from HV 0 feedback line. Value of HVMoni will be between 0 and Vref (2.048V) and must be converted to read
 * high voltage: Vconverted = HVMoni *(10039.2/39.2)
 * @returns Nothing
 */
void HV0_Monitor(void)
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);

	for (int j = 0; j < 10; j++)
	{

		HVMoni0Counts = Cy_SAR_GetResult16(SAR_ADC_HW, hvmoni0channel);
		HVMoni0Volts = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, hvmoni0channel, Cy_SAR_GetResult16(SAR_ADC_HW, hvmoni0channel));
		// This accounts for voltage divider, will print actual high voltage
		HVMoni0ConvertedVolts = HVMoni0Volts * 10039.2 / 39.2;
	}
	Cy_SAR_StopConvert(SAR_ADC_HW);

	/*sprintf(adcBuffer0,"%lu",HVMoni0Counts);
	//Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0Counts = ");
	Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	Cy_SCB_UART_PutString(UART_HW,", ");

	sprintf(adcBuffer0,"%f",HVMoni0Volts);
	//Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0Volts = ");
	Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	Cy_SCB_UART_PutString(UART_HW,", ");*/

	sprintf(adcBuffer0, "%f", HVMoni0ConvertedVolts);
	Cy_SCB_UART_PutString(UART_HW, "\r\nHVMoni_0 = ");
	Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	Cy_SCB_UART_PutString(UART_HW, "\r\n");
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
		HVMoni3ConvertedVolts = HVMoni3Volts * 10039.2 / 39.2;
	}
	Cy_SAR_StopConvert(SAR_ADC_HW);

	// sprintf(adcBuffer0,"%f",HVMoni3Counts);
	// Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_3Counts = ");
	// Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	// Cy_SCB_UART_PutString(UART_HW,"\r\n");

	/*sprintf(adcBuffer0,"%f",HVMoni3Volts);
	Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_3Volts = ");
	Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 10, &uartContext);*/

	sprintf(adcBuffer0, "%f", HVMoni3ConvertedVolts);
	Cy_SCB_UART_PutString(UART_HW, "\r\nHVMoni_3 = ");
	Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 10, &uartContext);
}

/*
 * @desc Gets the voltage reading of thermistor 0
 * @returns Nothing
 */
void Therm0_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM0 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel);
	ThermRead0 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread0channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);

	// sprintf(adcBuffer0,"%lu",THERM0);
	// Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0ConvertedVolts = ");
	// Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	// Cy_SCB_UART_PutString(UART_HW,"\r\n");
}

/*
 * @desc Gets the voltage reading of thermistor 1
 * @returns Nothing
 */
void Therm1_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM1 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel);
	ThermRead1 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread1channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
	// sprintf(adcBuffer0,"%lu",THERM1);
	// Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0ConvertedVolts = ");
	// Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	// Cy_SCB_UART_PutString(UART_HW,"\r\n");
}

/*
 * @desc Gets the voltage reading of thermistor 2
 * @returns Nothing
 */
void Therm2_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM2 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel);
	ThermRead2 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread2channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
	// sprintf(adcBuffer0,"%lu",THERM2);
	// Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0ConvertedVolts = ");
	// Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	// Cy_SCB_UART_PutString(UART_HW,"\r\n");
}

/*
 * @desc Gets the voltage reading of thermistor 3
 * @returns Nothing
 */
void Therm3_Read(void)
{
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	THERM3 = Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel);
	ThermRead3 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread3channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
	// sprintf(adcBuffer0,"%lu",THERM3);
	// Cy_SCB_UART_PutString(UART_HW,"\r\nHVMoni_0ConvertedVolts = ");
	// Cy_SCB_UART_Transmit(UART_HW, adcBuffer0, 16, &uartContext);
	// Cy_SCB_UART_PutString(UART_HW,"\r\n");
}

/*
 * @desc Gets the voltage reading of all thermistors
 * @returns Nothing
 */
void GetAllThermRead(void)
{

	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT);
	ThermRead0 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread0channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread0channel));
	ThermRead1 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread1channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread1channel));
	ThermRead2 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread2channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread2channel));
	ThermRead3 = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, thermread3channel, Cy_SAR_GetResult16(SAR_ADC_HW, thermread3channel));
	Cy_SAR_StopConvert(SAR_ADC_HW);
}

/*
void AnnealingThermRead(int ChooseDetector){
	//Write a
	Cy_SAR_StartConvert(SAR_ADC_HW, CY_SAR_START_CONVERT_SINGLE_SHOT );
	static therm_channel = (thermread0channel,thermread1channel,thermread2channel,thermread3channel);
	ThermRead = Cy_SAR_CountsTo_Volts(SAR_ADC_HW, therm_channel[ChooseDetector], Cy_SAR_GetResult16(SAR_ADC_HW, therm_channel[ChooseDetector]));
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

/*
void HVMoni_0_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};

	//Initialize ADC channel 0//
	result  = cyhal_adc_channel_init_diff(&adc_chan_0_obj, &adc_obj, P9_0, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 0 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {Cy_SCB_UART_PutString(UART_HW,"ADC channel 0 initialized ! \r\n");}

}

void HVMoni_3_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_1_obj, &adc_obj, P9_1, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 1 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void Thermread_0_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_2_obj, &adc_obj, P10_0, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 2 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void Thermread_1_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_3_obj, &adc_obj, P10_1, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 3 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void Thermread_2_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_4_obj, &adc_obj, P10_2, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 4 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void Thermread_3_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_5_obj, &adc_obj, P10_3, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 5 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void ITEC_0_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_7_obj, &adc_obj, P10_5, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 7 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

void ITEC_1_ADC_Channel_Init(void){
	cy_rslt_t result;
	//ADC channel configuration structure//
	const cyhal_adc_channel_config_t channel_config = {
			.enable_averaging = false,
			.min_acquisition_ns = 220,
			.enabled = true
	};
	//Initialize ADC channel 1//
	result  = cyhal_adc_channel_init_diff(&adc_chan_7_obj, &adc_obj, P10_5, CYHAL_ADC_VNEG, &channel_config);
	if (result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"ADC channel 7 initialization failed\r\n");
				CY_ASSERT(0);
			}
	else {}//printf("ADC channel 1 initialized ! \r\n");
}

float HVMoni_0_ADC_Channel_Read(){

	adc_out_0 = cyhal_adc_read_uv(&adc_chan_0_obj);
	float channel_0_output_V = adc_out_0/((float)(1000000));

	return channel_0_output_V;
}

float HVMoni_3_ADC_Channel_Read(){

	adc_out_1 = cyhal_adc_read_uv(&adc_chan_1_obj);
	float channel_1_output_V = adc_out_1/((float)(1000000));

	return channel_1_output_V;
}

float Thermread_0_ADC_Channel_Read() {

	adc_out_2 = cyhal_adc_read_uv(&adc_chan_2_obj);
	float channel_2_output_V = adc_out_2/((float)(1000000));

	return channel_2_output_V;
}

float Thermread_1_ADC_Channel_Read() {

	adc_out_3 = cyhal_adc_read_uv(&adc_chan_3_obj);
	float channel_3_output_V = adc_out_3/((float)(1000000));

	return channel_3_output_V;
}

float Thermread_2_ADC_Channel_Read() {

	adc_out_4 = cyhal_adc_read_uv(&adc_chan_4_obj);
	float channel_4_output_V = adc_out_4/((float)(1000000));

	return channel_4_output_V;
}

float Thermread_3_ADC_Channel_Read() {

	adc_out_5 = cyhal_adc_read_uv(&adc_chan_5_obj);
	float channel_5_output_V = adc_out_5/((float)(1000000));

	return channel_5_output_V;
}

float ITEC_0_ADC_Channel_Read() {

	adc_out_6 = cyhal_adc_read_uv(&adc_chan_6_obj);
	float channel_6_output_V = adc_out_6/((float)(1000000));

	return channel_6_output_V;
}

float ITEC_1_ADC_Channel_Read() {

	adc_out_7 = cyhal_adc_read_uv(&adc_chan_7_obj);
	float channel_7_output_V = adc_out_7/((float)(1000000));

	return channel_7_output_V;
}


*/
