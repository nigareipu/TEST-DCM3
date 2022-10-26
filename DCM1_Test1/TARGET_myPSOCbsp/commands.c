/*
 * commands.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "commands.h"

char* command;

/*
 * @desc Command that sets the length of time modes run for
 * @returns nothing
 *
 */
void Init_Hardware()
{
	cy_rslt_t rslt;
	count = 0;
	rslt = cybsp_init();
	if (rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
}


/*void setLengthCommand() // don't need this command
{

	// Storing the temperature value
	for (idx = 0; idx < 4; idx++)
	{
		lengthArray[idx] = valueBuffer[idx];
	}

	length = atof(lengthArray);

	// Check that value is a valid length
	if (length > 0)
	{
		sprintf(confirmValue, "%f", length);
		Cy_SCB_UART_PutString(UART_HW, "The measurement length = ");
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0; // check flaging values with @KatieCurvelo
	}

	else
	{
		length = 0;
		Cy_SCB_UART_PutString(UART_HW, "Not permissible measurement length; permissible values are 0001-9999");
		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
}*/

/*
void setMasterTEC(){

	//Storing the temperature value
	for(idx=0;idx<2;idx++){
		confirmValue[idx] = valueBuffer[idx];
	}

	detector = atof(confirmValue);

	if (detector == 0 ){
		targetDetectorFlag = 0;
	}
	else if(detector == 1){
		targetDetectorFlag = 1;
	}

	if(detector == 0){
		targetDetectorFlag2 = 0;
	}
	else if (detector == 1){
		targetDetectorFlag2  = 1;
	}

}*/

/*void setTECCommand() //don't need it, a
{

	// Storing the temperature value
	for (idx = 0; idx < 2; idx++)
	{
		confirmValue[idx] = valueBuffer[idx];
	}

	detector = atof(confirmValue);

	// To check which of the four detectors is selected, only compare first elements of value buffer
	if (strncmp(valueBuffer, "0", 1) == 0)
	{

		// store detector variable (DAC channel to set HV for appropriate detector)
		detector = DET0;

		// check that detector variable was correctly filed
		if (detector == DET0)
		{
			Cy_SCB_UART_PutString(UART_HW, "Set to Anneal: TEC0\r\n");
			DetectorSetFlag = 1;
			uartRxCompleteFlag = 0;
			count = 0;
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			DetectorSetFlag = 0;
			uartRxCompleteFlag = 0;
			count = 0;
		}
	}

	else if (strncmp(valueBuffer, "1", 1) == 0)
	{

		detector = DET1;

		// check that detector variable was correctly filed
		if (detector == DET1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Set to Anneal: TEC1\r\n");
			DetectorSetFlag = 1;
			uartRxCompleteFlag = 0;
			count = 0;
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			DetectorSetFlag = 0;
			uartRxCompleteFlag = 0;
			count = 0;
		}
	}

	else if (strncmp(valueBuffer, "2", 1) == 0)
	{

		detector = DET2;

		// check that detector variable was correctly filed
		if (detector == DET2)
		{
			Cy_SCB_UART_PutString(UART_HW, "Set to Anneal: TEC2\r\n");
			DetectorSetFlag = 1;
			uartRxCompleteFlag = 0;
			count = 0;
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			DetectorSetFlag = 0;
			uartRxCompleteFlag = 0;
			count = 0;
		}
	}

	else if (strncmp(valueBuffer, "3", 1) == 0)
	{

		detector = DET3;

		// check that detector variable was correctly filed
		if (detector == DET3)
		{
			Cy_SCB_UART_PutString(UART_HW, "Set to Anneal: TEC3\r\n");
			DetectorSetFlag = 1;
			uartRxCompleteFlag = 0;
			count = 0;
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			DetectorSetFlag = 0;
			uartRxCompleteFlag = 0;
			count = 0;
		}
	}

	else
	{
		Cy_SCB_UART_PutString(UART_HW, "Not permissible DET number; permissible numbers are 0, 1, 2, 3");
		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
}*/

/*
 * @desc Stores detector voltage variable.  DOES NOT SET VOLTAGE ITSELF.
 * @returns Nothing
 */
/*void setVoltageCommand()
{

	// To check which detector, only compare first elements of value buffer
	if (strncmp(valueBuffer, "0", 1) == 0)
	{

		// store detector variable (DAC channel to set HV for appropriate detector)
		detector = DET0;

		Cy_SCB_UART_PutString(UART_HW, "Detector voltage to be modified:");
		// check that detector variable was correctly filed
		if (detector == DET0)
		{
			Cy_SCB_UART_PutString(UART_HW, "DET0\r\n");
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			uartRxCompleteFlag = 0;
			count = 0;
		}

		// set element which corresponds to detector number to zero
		for (idx = 0; idx <= 2; idx++)
		{

			voltageArray[idx] = valueBuffer[idx + 1];
		}

		// Change remaining array into float and set detector voltage
		/*Since only can PutArray into serial buffer, must do trick of sprintf the float value
		into confirmValue and then print the confirmValue array*/
/*
		DET0_voltage = atof(voltageArray);
		if (DET0_voltage > 500)
		{
			Cy_SCB_UART_PutString(UART_HW, "\r\n Not a valid value, must be 000-500 \r\n ");
		}
		else
		{
			sprintf(confirmValue, "%f", DET0_voltage);
			Cy_SCB_UART_PutString(UART_HW, "DET 0 voltage = ");
			Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
			Cy_SCB_UART_PutString(UART_HW, "V");
		}

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}

	else if (strncmp(valueBuffer, "1", 1) == 0)
	{

		detector = DET1;
		Cy_SCB_UART_PutString(UART_HW, "Detector voltage to be modified:");
		// check that detector variable was correctly filed
		if (detector == DET1)
		{
			Cy_SCB_UART_PutString(UART_HW, "DET1\r\n");
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			uartRxCompleteFlag = 0;
			count = 0;
		}

		// set element which corresponds to detector number to zero
		for (idx = 0; idx <= 2; idx++)
		{

			voltageArray[idx] = valueBuffer[idx + 1];
		}
		DET1_voltage = atof(voltageArray);
		if (DET1_voltage > 500)
		{
			Cy_SCB_UART_PutString(UART_HW, "\r\n Not a valid value, must be 000-500 \r\n ");
		}
		else
		{
			sprintf(confirmValue, "%f", DET1_voltage);
			Cy_SCB_UART_PutString(UART_HW, "DET 1 voltage = ");
			Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
			Cy_SCB_UART_PutString(UART_HW, "V");
		}

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
	else if (strncmp(valueBuffer, "2", 1) == 0)
	{

		detector = DET2;
		Cy_SCB_UART_PutString(UART_HW, "Detector voltage to be modified:");
		// check that detector variable was correctly filed
		if (detector == DET2)
		{
			Cy_SCB_UART_PutString(UART_HW, "DET2\r\n");
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			uartRxCompleteFlag = 0;
			count = 0;
		}

		// set element which corresponds to detector number to zero
		for (idx = 0; idx <= 2; idx++)
		{

			voltageArray[idx] = valueBuffer[idx + 1];
		}
		DET2_voltage = atof(voltageArray);
		if (DET2_voltage > 500)
		{
			Cy_SCB_UART_PutString(UART_HW, "\r\n Not a valid value, must be 000-500 \r\n ");
		}
		else
		{
			sprintf(confirmValue, "%f", DET2_voltage);
			Cy_SCB_UART_PutString(UART_HW, "DET 2 voltage = ");
			Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
			Cy_SCB_UART_PutString(UART_HW, "V");
		}

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
	else if (strncmp(valueBuffer, "3", 1) == 0)
	{

		detector = DET3;
		Cy_SCB_UART_PutString(UART_HW, "Detector voltage to be modified:");
		// check that detector variable was correctly filed
		if (detector == DET3)
		{
			Cy_SCB_UART_PutString(UART_HW, "DET3\r\n");
		}
		else
		{
			Cy_SCB_UART_PutString(UART_HW, "None");
			Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
			uartRxCompleteFlag = 0;
			count = 0;
		}

		// set element which corresponds to detector number to zero
		for (idx = 0; idx <= 2; idx++)
		{

			voltageArray[idx] = valueBuffer[idx + 1];
		}
		DET3_voltage = atof(voltageArray);
		if (DET3_voltage > 500)
		{
			Cy_SCB_UART_PutString(UART_HW, "\r\n Not a valid value, must be 000-500 \r\n ");
		}
		else
		{
			sprintf(confirmValue, "%f", DET3_voltage);
			Cy_SCB_UART_PutString(UART_HW, "DET 3 voltage = ");
			Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
			Cy_SCB_UART_PutString(UART_HW, "V");
		}

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "Not permissible DET number; permissible numbers are 0, 1, 2, 3");
		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
}*/

/*
 * @desc Command that checks if value for coincidence window is valid
 * @returns Nothing
 */
void setCoincidenceWindowCommand(float ConcidanceWindow)
{

	if (ConcidanceWindow == 0)

	{
		CoincidenceWindow_Set(0, 0);
		Cy_SCB_UART_PutString(UART_HW, "ConcidanceWindow = 0\r\n");
	}

	else if (ConcidanceWindow == 1)
	{

		CoincidenceWindow_Set(0, 1);
		Cy_SCB_UART_PutString(UART_HW, "ConcidanceWindow = 1\r\n");
	}

	else if (ConcidanceWindow == 2)
	{

		CoincidenceWindow_Set(1, 0);
		Cy_SCB_UART_PutString(UART_HW, "ConcidanceWindow = 2\r\n");

	}
	//else if (strncmp(valueBuffer, "0011", sizeof(valueBuffer)) == 0)
	else if (ConcidanceWindow == 3)
	{

		CoincidenceWindow_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "ConcidanceWindow = 3\r\n");

	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\n Not permissible value");
		//Cy_SCB_UART_PutString(UART_HW, "\r\n Possible values are 0000, 0010, 0001, 0011 \r\n");
		//coincWindowSetFlag = 0;
		uartRxCompleteFlag = 0;
		count = 0;
	}
}

/*
 * @desc Command that checks whether the length of delay is valid
 * @returns Nothing
 */
void setDelay0Command(float DelayValue)
{

	if (DelayValue == 0)
	{

		Delay0_Set(0, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET0 Delay = 0\r\n");

	}
	else if (DelayValue == 1)
	{

		Delay0_Set(0, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET0 Delay = 1\r\n");

	}
	else if (DelayValue == 2)
	{

		Delay0_Set(1, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET0 Delay = 2\r\n");

	}
	else if (DelayValue == 3)
	{

		Delay0_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET0 Delay = 3\r\n");

	}
}

void setDelay1Command(float DelayValue)
{
	if (DelayValue == 0)
	{
		Delay1_Set(0, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET1 Delay = 0\r\n");
	}
	else if (DelayValue == 1)
	{
		Delay1_Set(0, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET1 Delay = 1\r\n");
	}
	else if (DelayValue == 2)
	{

		Delay1_Set(1, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET1 Delay = 2\r\n");

	}
	else if (DelayValue == 3)
	{
		Delay1_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET1 Delay = 3\r\n");

	}
}

void setDelay2Command(float DelayValue)
{
	if (DelayValue == 0)
	{
		Delay2_Set(0, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET2 Delay = 0\r\n");
	}
	else if (DelayValue == 1)
	{
		Delay2_Set(0, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET2 Delay = 1\r\n");
	}
	else if (DelayValue == 2)
	{

		Delay2_Set(1, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET2 Delay = 2\r\n");

	}
	else if (DelayValue == 3)
	{
		Delay2_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET2 Delay = 3\r\n");

	}
}

void setDelay3Command(float DelayValue)
{
	if (DelayValue == 0)
	{
		Delay3_Set(0, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET3 Delay = 0\r\n");
	}
	else if (DelayValue == 1)
	{
		Delay3_Set(0, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET3 Delay = 1\r\n");
	}
	else if (DelayValue == 2)
	{

		Delay3_Set(1, 0);
		Cy_SCB_UART_PutString(UART_HW, "DET3 Delay = 2\r\n");

	}
	else if (DelayValue == 3)
	{
		Delay3_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "DET3 Delay = 3\r\n");

	}
}



/*
 * @desc Checks the temperature value is valid and stores it
 * @returns Nothing
 */
/*void setTempCommand()
{

	// Storing the temperature value
	for (idx = 0; idx <= 2; idx++)
	{
		temperatureArray[idx] = valueBuffer[idx + 1];
	}
	DET0_temp = atof(temperatureArray);

	// Check that value is a valid tempset
	if (DET0_temp < 137 && DET0_temp > 14)
	{
		DET0_temp = atof(temperatureArray);
		// Convert from character buffer format to thermistor voltage decimal value
		DET0_temp = DET0_temp / 100;
		DET1_temp = DET0_temp;
		DET2_temp = DET0_temp;
		DET3_temp = DET0_temp;
		sprintf(confirmValue, "%f", DET0_temp);
		Cy_SCB_UART_PutString(UART_HW, "Temperature of all detectors = ");
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));

		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}

	else
	{
		DET0_temp = 0.85;
		Cy_SCB_UART_PutString(UART_HW, "Not permissible temperature; permissible values are 0015-0136");
		Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
		uartRxCompleteFlag = 0;
		count = 0;
	}
}*/

/*
 * @desc Gets discriminator threshold value and sets all discriminators
 * @returns Nothing
 */
/*void setDiscrThreshCommand()
{

	float discrThresh;

	// Storing the threshold value
	for (idx = 0; idx <= 3; idx++)
	{
		discrThreshArray[idx] = valueBuffer[idx];
	}

	// Check threshold value is valid? Maybe not necessary

	// Store threshold values
	discrThresh = atof(discrThreshArray);
	if (discrThresh < 50 || discrThresh > 1200)
	{
		Cy_SCB_UART_PutString(UART_HW, "Not a valid value, must be between 0050-0120\r\n");
	}
	else
	{
		discrThresh = discrThresh / 1000;
		sprintf(confirmValue, "%f", discrThresh);
		Cy_SCB_UART_PutString(UART_HW, "Discriminator threshold = ");
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
		Cy_SCB_UART_PutString(UART_HW, "V\r\n");
	}

	Cy_SCB_UART_PutString(UART_HW, "\r\n Choose another command and value \r\n ");
	uartRxCompleteFlag = 0;
	count = 0;
}*/

void settingParameters()
   {
    setDiscr0Thresh(*DThrs);
    setDiscr1Thresh(*DThrs);
    setDiscr2Thresh(*DThrs);
    setDiscr3Thresh(*DThrs);

    // Turns on TEC driver and switches

    TEC_SW0_Status(ON);
    TEC_SW1_Status(ON);
    TEC_SW2_Status(ON);
    TEC_SW3_Status(ON);
    TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
    TEC_Driver1_Status(ON);


    StabilizeAllTemp(*TDET0);

    if (*Exit == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
		mode1program();
	}

    // Slowly ramp up voltages
    // Set voltage of detectors gradually

    float DET_gradual_increase[] = {0, 0, 0, 0};
    float DET_bias[] = {*VDET0, *VDET1, *VDET2, *VDET3};
    unsigned int DET[] = {DET0, DET1, DET2, DET3};
    for (int i = 0; i <= 3; i++)
    {
        while (DET_gradual_increase[i] < DET_bias[i])
        {

            SetDetectorVoltage(DET[i], DET_gradual_increase[i]);
            DET_gradual_increase[i] = DET_gradual_increase[i] + 10;
            cyhal_system_delay_ms(1);
        }
        Cy_SCB_UART_PutString(UART_HW, "detector voltage :");
        printFloat(DET_bias[i]);
        SetDetectorVoltage(DET[i], DET_bias[i]);
    }

    HV0_Monitor();
    cyhal_system_delay_ms(500); // required delay
    HV3_Monitor();
    cyhal_system_delay_ms(500); // required delay

   }

void startCounting()
{
	       GetSingles0Counts();
			GetSingles1Counts();
			GetSingles2Counts();
			GetSingles3Counts();
			// Want 12, 01, 23, 03
			GetCoincidence1Counts();
			GetCoincidence0Counts();
			GetCoincidence3Counts();
			GetCoincidence2Counts();
			Cy_SCB_UART_PutString(UART_HW, "\r\n");
}

void printFloat(float message)
{
	sprintf(confirmValue, "%f", message);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");
}
