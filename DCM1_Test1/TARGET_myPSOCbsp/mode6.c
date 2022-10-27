/*
 * mode6.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 * 		Modified: Noura-B August 9th
 */

#include "mode6.h"
volatile bool DetectorSetFlag;

// should we have an emergency shutdown button??

void mode6program()
{

	Cy_SCB_UART_PutString(UART_HW, "SET MODE to Thermal Annealing\r\n");

	// CODE FOR RUNNING  MODE
		printThermalInfo = 1;

		//TurnTEC_ON(detector);
		cyhal_system_delay_ms(1000);

		// Confirm selected TEC is on and set to anneal to the temperature #
		Cy_SCB_UART_PutString(UART_HW, "Thermoelectric cooler number ");
		sprintf(adcBuffer, "%i", *AnDET);
		Cy_SCB_UART_PutString(UART_HW, " is ON and set to anneal to temperature ");
		sprintf(confirmValue, "%f", *TDET0);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
		Cy_SCB_UART_PutString(UART_HW, " for ");
		sprintf(confirmValue, "%f", *RTime);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
		Cy_SCB_UART_PutString(UART_HW, " seconds:\r\n");

		// Annealing the selected detector to 91 C for the selected time
		Annealing(*AnDET, *RTime, *TDET0);
		cyhal_system_delay_ms(1000);

		// Turn the selected detector OFF == 0
		TurnTEC_OFF(*AnDET);
		Cy_SCB_UART_PutString(UART_HW, "Thermoelectric cooler turned OFF \r\n");
		cyhal_system_delay_ms(1000);

		// TEC0_updateTemp(0.85);

		Cy_SCB_UART_PutString(UART_HW,"Monitor thermistor3  for 90 seconds\r\n");
		for(int j=0; j<100; j++){
			cyhal_system_delay_ms(1000);
			Therm3_Read();
			thermRead = ThermRead3;
			sprintf(adcBuffer,"%f",thermRead);
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			Cy_SCB_UART_PutString(UART_HW,",\r\n");
		}

		mode1program();

}
