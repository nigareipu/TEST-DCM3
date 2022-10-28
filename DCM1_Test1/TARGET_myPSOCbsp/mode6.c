/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 * 		Modified: Noura-B August 9th
 */

#include "modes.h"
//volatile bool DetectorSetFlag;

// should we have an emergency shutdown button??

void mode6program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to Thermal Annealing\r\n");

	// CODE FOR RUNNING  MODE
	turnOFF_TECs();
	//printThermalInfo = 1;

	// Confirm selected TEC is on and set to anneal to the temperature #
	Cy_SCB_UART_PutString(UART_HW, "Thermoelectric cooler number ");
	sprintf(adcBuffer, "%f", *AnDET);
	Cy_SCB_UART_PutString(UART_HW, " is ON and set to anneal to temperature ");
	sprintf(confirmValue, "%f", *TDET0);
	Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
	Cy_SCB_UART_PutString(UART_HW, " for ");
	sprintf(confirmValue, "%f", *RTime);
	Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
	Cy_SCB_UART_PutString(UART_HW, " seconds:\r\n");

	// Annealing the selected detector to 91 C for the selected time
	//Annealing setup

	if(*AnDET==0)
	{
		TEC_SW0_Status(ON);
	}

	else if (*AnDET==1){
		TEC_SW1_Status(ON);
	}
	else if (*AnDET==2){
		TEC_SW2_Status(ON);
	}
	else {
		TEC_SW3_Status(ON);
	}

	if(*CntTEC==0)
	{
		TEC_controller0ActiveFlag = 1;
		TEC_controller1ActiveFlag = 0;
		TEC_Driver0_Status(ON);
	}
	else
	{
		TEC_controller0ActiveFlag = 0;
		TEC_controller1ActiveFlag = 1;
		TEC_Driver1_Status(ON);
	}


	Cy_SCB_UART_PutString(UART_HW, "\r\nSingle Count Rate 0, 1, 2, 3, Coincidence 1&2, 0&1, 2&3, 0&3\r\n");
	for (int k = 0; k < *RTime; k++)
	{

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}


		cyhal_system_delay_ms(1000);//Must be kept for accumulating counts/sec
	}
	turnOFF_TECs();
	mode1program();
}



// Turn the selected detector OFF == 0


