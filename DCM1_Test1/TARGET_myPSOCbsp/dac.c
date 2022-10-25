/*
 * dac.c
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#include "dac.h"

/*
 * @desc Sets internal reference voltage of DAC
 * @returns Nothing
 */
void setDiscrDACInternalRef(void)
{

	cy_rslt_t result;

	// Cy_SCB_UART_PutString(UART_HW,"Created result \r\n");

	/*Define placehold variable to receive */
	uint8_t receive_data[4];
	// Cy_SCB_UART_PutString(UART_HW,"Created receive data \r\n");

	spi_buf[0] = 0x08;
	spi_buf[1] = 0x00;
	spi_buf[2] = 0x00;
	spi_buf[3] = 0x01;

	Cy_SCB_UART_PutArray(UART_HW, spi_buf, 4);

	for (int i = 0; i < 1; i++)
	{
		result = cyhal_spi_transfer(&DiscrDAC_obj, spi_buf, 4u, receive_data, 4u, 0XFF);
		/*if( result != CY_RSLT_SUCCESS)
		{
			Cy_SCB_UART_PutString(UART_HW,"\r\n DAC Discr internal ref Setting FAILED \r\n");
			CY_ASSERT(0);


		}
		else Cy_SCB_UART_PutString(UART_HW,"\r\nDAC Discr internal reference voltage set\r\n");*/
	}
}

/*
 * @desc Sets internal reference voltage of HVDAC
 * @returns Nothing
 */
void setHVDACInternalRef(void)
{
	char confirmValue[8];

	uint16_t error_code;

	char error_codeArray[10];

	// Cy_SCB_UART_PutString(UART_HW,"Created nothing \r\n");

	cy_rslt_t result;
	// Cy_SCB_UART_PutString(UART_HW,"Created result \r\n");

	/*Define placehold variable to receive */
	uint8_t receive_data[4];
	// Cy_SCB_UART_PutString(UART_HW,"Created receive data \r\n");

	spi_buf[0] = 0x08;
	spi_buf[1] = 0x00;
	spi_buf[2] = 0x00;
	spi_buf[3] = 0x01;

	/*Cy_SCB_UART_PutString(UART_HW,"spi buf = ");
	sprintf(confirmValue,"%x",spi_buf);
	Cy_SCB_UART_PutArray(UART_HW,confirmValue,4);
	Cy_SCB_UART_PutString(UART_HW," \r\n");*/

	for (int i = 0; i < 1; i++)
	{
		result = cyhal_spi_transfer(&HVDAC_obj, spi_buf, 4u, receive_data, 4u, 0XFF);
		/*	if( result != CY_RSLT_SUCCESS)
			{
				Cy_SCB_UART_PutString(UART_HW,"\r\nHV DAC internal ref Setting FAILED \r\n");

				 error_code = CY_RSLT_GET_CODE(result);
				 Cy_SCB_UART_PutString(UART_HW,"Error code =  ");
				 sprintf(error_codeArray,"%u",error_code);
				 Cy_SCB_UART_PutArray(UART_HW,error_codeArray,10);
				 Cy_SCB_UART_PutString(UART_HW," V\r\n");
				CY_ASSERT(0);


			}
			Cy_SCB_UART_PutString(UART_HW,"\r\nHV DAC internal reference voltage set\r\n");*/
	}
}

/*
 * @desc Takes a voltage and converts it using a voltage divider factor for the DAC
 * @param float inputVoltage - The voltage to be converted
 * @returns uint16_t dacValue - The converted voltage value for the DAC
 */
uint16_t convertHighVoltagetoDACVoltage(float inputVoltage)
{

	float inputVoltageConverted;
	int32_t tempDacValue;
	uint16_t dacValue;
	float voltageDividerFactor = 0.003904693601084;
	char confirmdacValue[32];

	tempDacValue = 0;
	dacValue = 0;

	inputVoltageConverted = inputVoltage * voltageDividerFactor;

	/*Cy_SCB_UART_PutString(UART_HW,"Converted voltage = ");
   sprintf(confirmdacValue,"%f",inputVoltageConverted);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	// get DAC decimal value (from data sheet: D = 2^(resolution) * V/2*VrefInternal = 2^12 * V/2(1.25V) = 4096 *V/2.5. V is the voltage you want the DAC to output.
	tempDacValue = (uint32_t)((inputVoltageConverted * AD56x8_NUM_STEPS) / (AD56x8_VREF_VALUE));

	// In case the chosen value is too large or too small, limit to the first or last step of DAC
	if (tempDacValue >= AD56x8_DAC_MAX)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MAX);
	}
	else if (tempDacValue < AD56x8_DAC_MIN)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MIN);
	}
	else
	{
		dacValue = (uint16_t)tempDacValue;
	}

	/*Cy_SCB_UART_PutString(UART_HW,"dacValue = ");
	sprintf(confirmdacValue,"%i",dacValue);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	return (dacValue);
}

/*
 * @desc Converts a given voltage to a value for DAC
 * @param float inputVoltage - Voltage to be converted
 * @returns uint16_t dacValue - The converted voltage for the DAC
 */
uint16_t convertDiscrThreshtoDACVoltage(float inputVoltage)
{

	float inputVoltageConverted;
	int32_t tempDacValue;
	uint16_t dacValue;

	char confirmdacValue[32];

	tempDacValue = 0;
	dacValue = 0;

	/*Cy_SCB_UART_PutString(UART_HW,"Converted voltage = ");
   sprintf(confirmdacValue,"%f",inputVoltageConverted);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	// get DAC decimal value (from data sheet: D = 2^(resolution) * V/2*VrefInternal = 2^12 * V/2(1.25V) = 4096 *V/2.5. V is the voltage you want the DAC to output.
	tempDacValue = (uint32_t)((inputVoltage * AD56x8_NUM_STEPS) / (AD56x8_VREF_VALUE));

	// In case the chosen value is too large or too small, limit to the first or last step of DAC
	if (tempDacValue >= AD56x8_DAC_MAX)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MAX);
	}
	else if (tempDacValue < AD56x8_DAC_MIN)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MIN);
	}
	else
	{
		dacValue = (uint16_t)tempDacValue;
	}

	/*Cy_SCB_UART_PutString(UART_HW,"dacValue = ");
	sprintf(confirmdacValue,"%i",dacValue);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	return (dacValue);
}

/*
 * @desc Converts a given voltage to a value for DAC
 * @param float inputVoltage - Voltage to be converted
 * @returns uint16_t dacValue - The converted voltage for the DAC
 */
uint16_t convertTempSetVoltagetoDACVoltage(float inputVoltage)
{

	float inputVoltageConverted;
	int32_t tempDacValue;
	uint16_t dacValue;

	char confirmdacValue[32];

	tempDacValue = 0;
	dacValue = 0;

	inputVoltageConverted = inputVoltage;

	/*Cy_SCB_UART_PutString(UART_HW,"Converted voltage = ");
   sprintf(confirmdacValue,"%f",inputVoltageConverted);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	// get DAC decimal value (from data sheet: D = 2^(resolution) * V/2*VrefInternal = 2^12 * V/2(1.25V) = 4096 *V/2.5. V is the voltage you want the DAC to output.
	tempDacValue = (uint32_t)((inputVoltageConverted * AD56x8_NUM_STEPS) / (AD56x8_VREF_VALUE));

	// In case the chosen value is too large or too small, limit to the first or last step of DAC
	if (tempDacValue >= AD56x8_DAC_MAX)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MAX);
	}
	else if (tempDacValue < AD56x8_DAC_MIN)
	{
		dacValue = (uint16_t)(AD56x8_DAC_MIN);
	}
	else
	{
		dacValue = (uint16_t)tempDacValue;
	}

	/*Cy_SCB_UART_PutString(UART_HW,"dacValue = ");
	sprintf(confirmdacValue,"%i",dacValue);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,3);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	return (dacValue);
}

/*
 * @desc Prepares a DAC data packet
 * @param uint16_t data -
 * @param uint16_t channel - The channel packet is sent to
 * @param uint16_t command -
 * @returns uint32_t dacDataPacket - The data packet ready to send to DAC
 */
uint32_t prepareDACDataPacket(uint16_t data, uint16_t channel, uint16_t command)
{

	uint32_t tempDACPacket;
	uint32_t dacDataPacket;
	char confirmdacValue[32];

	dacDataPacket = 0;

	// Command
	tempDACPacket = 0;
	tempDACPacket = command;
	tempDACPacket = tempDACPacket << AD56x8_COMMAND_SHIFT; // shift by 24?
	tempDACPacket &= AD56x8_COMMAND_MASK;
	dacDataPacket &= (~AD56x8_COMMAND_MASK);
	dacDataPacket += tempDACPacket;

	// Address
	tempDACPacket = 0;
	tempDACPacket = channel;
	tempDACPacket = tempDACPacket << AD56x8_ADDRESS_SHIFT; // shift by 20?
	tempDACPacket &= AD56x8_ADDRESS_MASK;
	dacDataPacket &= (~AD56x8_ADDRESS_MASK);
	dacDataPacket += tempDACPacket;

	// Data
	tempDACPacket = 0;
	if ((command == AD56x8_CMD_USE_INT_VREF) && (data == 1))
	{
		tempDACPacket = 1;
	}
	else
	{
		tempDACPacket = data;
		tempDACPacket = tempDACPacket << AD56x8_DATA_SHIFT;
	}
	tempDACPacket &= AD56x8_DATA_MASK;
	dacDataPacket &= (~AD56x8_DATA_MASK);
	dacDataPacket += tempDACPacket;

	/*Cy_SCB_UART_PutString(UART_HW,"dacDataPacket = ");
	sprintf(confirmdacValue,"%lu",dacDataPacket);
	Cy_SCB_UART_PutArray(UART_HW,confirmdacValue,8);
	Cy_SCB_UART_PutString(UART_HW,"\r\n");*/

	return dacDataPacket;
}
