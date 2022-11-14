/*
 * commands.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "commands.h"

/*
 * @desc Command that sets the length of time modes run for
 * @returns nothing
 *
 */
void Init_Hardware()
{
	cy_rslt_t rslt;
	count_uartbuffer = 0;
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
void setCoincidenceWindowCommand(int ConcidanceWindow)
{
	if (ConcidanceWindow == 0)
	{
		CoincidenceWindow_Set(0, 0);
	}
	else if (ConcidanceWindow == 1)
	{
		CoincidenceWindow_Set(0, 1);
	}
	else if (ConcidanceWindow == 2)
	{
		CoincidenceWindow_Set(1, 0);
	}
	else if (ConcidanceWindow == 3)
	{
		CoincidenceWindow_Set(1, 1);
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
void setDelay0Command(int DelayValue)
{

	if (DelayValue == 0)
	{
		Delay0_Set(0, 0);
	}
	else if (DelayValue == 1)
	{
		Delay0_Set(0, 1);
	}
	else if (DelayValue == 2)
	{
		Delay0_Set(1, 0);
	}
	else if (DelayValue == 3)
	{
		Delay0_Set(1, 1);
	}
}

void setDelay1Command(int DelayValue)
{
	if (DelayValue == 0)
	{
		Delay1_Set(0, 0);
	}
	else if (DelayValue == 1)
	{
		Delay1_Set(0, 1);
	}
	else if (DelayValue == 2)
	{

		Delay1_Set(1, 0);
	}
	else if (DelayValue == 3)
	{
		Delay1_Set(1, 1);
	}
}

void setDelay2Command(int DelayValue)
{
	if (DelayValue == 0)
	{
		Delay2_Set(0, 0);
	}
	else if (DelayValue == 1)
	{
		Delay2_Set(0, 1);
	}
	else if (DelayValue == 2)
	{
		Delay2_Set(1, 0);
	}
	else if (DelayValue == 3)
	{
		Delay2_Set(1, 1);
	}
}

void setDelay3Command(int DelayValue)
{
	if (DelayValue == 0)
	{
		Delay3_Set(0, 0);
	}
	else if (DelayValue == 1)
	{
		Delay3_Set(0, 1);
	}
	else if (DelayValue == 2)
	{
		Delay3_Set(1, 0);
	}
	else if (DelayValue == 3)
	{
		Delay3_Set(1, 1);
	}
}

void setParameters()
{
	setDiscr0Thresh(*DThrs);
	setDiscr1Thresh(*DThrs);
	setDiscr2Thresh(*DThrs);
	setDiscr3Thresh(*DThrs);

	// Turns on TEC driver and switches
	TEC_controller0ActiveFlag = 1;
	TEC_controller1ActiveFlag = 1;

	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);
	TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
	TEC_Driver1_Status(ON);
}

// Slowly ramp up voltages
// Set voltage of detectors gradually
void setDetectorBias()
{
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
		SetDetectorVoltage(DET[i], DET_bias[i]);
	}

	cyhal_system_delay_ms(3000);
	HV0_Monitor();
	cyhal_system_delay_ms(3000);
	HV3_Monitor();
	sprintf(confirmValue, "\r\nHV0, HV3: %.3f, %.3f", *HVMoni0, *HVMoni3);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
}

void turnOFF_TECs()
{
	TEC_controller0ActiveFlag = 0;
	TEC_controller1ActiveFlag = 0;
	TEC_SW0_Status(OFF);
	TEC_SW1_Status(OFF);
	TEC_SW2_Status(OFF);
	TEC_SW3_Status(OFF);

	TEC_Driver0_Status(OFF);
	TEC_Driver1_Status(OFF);
}

void turnON_TECs()
{
	TEC_controller0ActiveFlag = 1;
	TEC_controller1ActiveFlag = 1;
	TEC_SW0_Status(ON);
	TEC_SW1_Status(ON);
	TEC_SW2_Status(ON);
	TEC_SW3_Status(ON);
	TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
	TEC_Driver1_Status(ON);
}
void startSinglesCounting()
{
	Singles0_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_0_HW, Singles_0_NUM);
	Singles1_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_1_HW, Singles_1_NUM);
	Singles2_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_2_HW, Singles_2_NUM);
	Singles3_CountRate = Cy_TCPWM_Counter_GetCounter(Singles_3_HW, Singles_3_NUM);
}

void startCoincidenceCounting()
{
	Coincidence0_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_0_HW, Coinc_0_NUM);
	Coincidence1_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_1_HW, Coinc_1_NUM);
	Coincidence2_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_2_HW, Coinc_2_NUM);
	Coincidence3_CountRate = Cy_TCPWM_Counter_GetCounter(Coinc_3_HW, Coinc_3_NUM);
	// Want 12, 01, 23, 03
}

void SetCounters()
{
	Cy_TCPWM_Counter_SetCounter(Singles_0_HW, Singles_0_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Singles_1_HW, Singles_1_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Singles_2_HW, Singles_2_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Singles_3_HW, Singles_3_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Coinc_0_HW, Coinc_0_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Coinc_1_HW, Coinc_1_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Coinc_2_HW, Coinc_2_NUM, 0);
	Cy_TCPWM_Counter_SetCounter(Coinc_3_HW, Coinc_3_NUM, 0);
}


void check_countTime()
{
	if (*countTime>*maxcountTime)  //MAX Counting loop delay is 5000 millisecond
	{
		countLoopDelay=*maxcountTime;
	}
	else
	{
		countLoopDelay=*countTime;
	}
}



void printFloat(float message)
{
	sprintf(confirmValue, "%f", message);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, ",");
}
