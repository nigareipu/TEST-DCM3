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

	else if (ConcidanceWindow == 3)
	{
		CoincidenceWindow_Set(1, 1);
		Cy_SCB_UART_PutString(UART_HW, "ConcidanceWindow = 3\r\n");
	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\n Input not valid ");

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

void startSinglesCounting()
{
	       GetSingles0Counts();
			GetSingles1Counts();
			GetSingles2Counts();
			GetSingles3Counts();
}

void startCoincidenceCounting()
{
	// Want 12, 01, 23, 03
			GetCoincidence1Counts();
			GetCoincidence0Counts();
			GetCoincidence3Counts();
			GetCoincidence2Counts();
}

void printFloat(float message)
{
	sprintf(confirmValue, "%f", message);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");
}
