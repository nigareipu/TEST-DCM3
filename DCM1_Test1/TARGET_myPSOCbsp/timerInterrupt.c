/*
 * timerInterrupt.c
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */
#include "timerInterrupt.h"
#include "adc.h"
#include "det_bias.h"


double e_0 = 0; // Error = (SetPoint - Feedback)
double e1_0 = 0;
double e2_0 = 0;
double e_1 = 0;
double e1_1 = 0;
double e2_1 = 0;

void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{
	//First TEC controller
	if (PID_Select==0)
	{
		if(printThermalInfo==1)
		{
			Cy_SCB_UART_PutString(UART_HW, "\n\rTherm0, Therm1, Therm2, Therm3, ITEC0, ITEC1: ");
			Therm0_Read();
			Therm1_Read();
			Therm2_Read();
			Therm3_Read();
			monitorITEC0();
			monitorITEC1();

			//printFloat(*TDET0);
			printFloat(ThermRead0);
			printFloat(ThermRead1);
			printFloat(ThermRead2);
			printFloat(ThermRead3);
			printFloat(ITEC0);
			printFloat(ITEC1);
			Cy_SCB_UART_PutString(UART_HW, "\n\r");
		}



		PID_Select=1;

		if(TEC_controller0ActiveFlag == 1)
		{
			PID_loop0();
		}


		else
		{
			e_0 = 0; // Error = (SetPoint - Feedback)
			e1_0 = 0;
			e2_0 = 0;

			prev_output0 = 1.5;
			C_output0 = 1.5;
			//Cy_SCB_UART_PutString(UART_HW, "Loop 0 Deactivated\n\r ");
		}

		dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}

	else
	{
		PID_Select=0;

		//Second TEC controller
		if(TEC_controller1ActiveFlag == 1)
		{
			PID_loop1();
			//Cy_SCB_UART_PutString(UART_HW, "1s Timer interrupt testing\n\r ");
		}

		else
		{
			e_1 = 0;
			e1_1 = 0;
			e2_1 = 0;
			prev_output1 = 1.5;
			C_output1 = 1.5;
			//Cy_SCB_UART_PutString(UART_HW, "do nothing\n\r ");
		}
		dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);
	}
}

void cyhal_timer_event_interrupt()

{
	cyhal_timer_cfg_t timer_cfg =
	{
			.compare_value = 0,              // Timer compare value, not used
			.period = 4999,                  // Defines the timer period
			.direction = CYHAL_TIMER_DIR_UP, // Timer counts up
			.is_compare = false,             // Don't use compare mode
			.is_continuous = true,           // Run the timer indefinitely
			.value = 0                       // Initial value of counter
	};

	// Initialize the timer object. Does not use pin output ('pin' is NC) and does not use a
	// pre-configured clock source ('clk' is NULL).
	cyhal_timer_init(&timer_obj, NC, NULL);


	// Apply timer configuration such as period, count direction, run mode, etc.
	cyhal_timer_configure(&timer_obj, &timer_cfg);

	// Set the frequency of timer to 10000 Hz
	cyhal_timer_set_frequency(&timer_obj, 10000);

	// Assign the ISR to execute on timer interrupt
	cyhal_timer_register_callback(&timer_obj, isr_timer, NULL);

	// Set the event on which timer interrupt occurs and enable it
	cyhal_timer_enable_event(&timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 3, true);

	// Start the timer with the configured settings
	cyhal_timer_start(&timer_obj);
}


void PID_loop0()
{
	// Function for cooling down all detectors
	float tempSet;

	float k1 = *kp + *ki + *kd;
	float k2 = -*kp -  2* (*kd);
	float k3 = *kd;

	Therm0_Read();
	Therm1_Read();

	if (*targetTECFlag0 == 0)
	{
		tempSet = *TDET0;
		thermRead0 = ThermRead0;
	}
	else
	{
		tempSet = *TDET1;
		thermRead0 = ThermRead1;
	}

	if (thermRead0 < 0)
	{
		thermRead0 = 0;
	}

	/*printFloat(tempSet);
	sprintf(confirmValue, "%f", thermRead0);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);*/

	e2_0 = e1_0;
	e1_0 = e_0;
	e_0 = tempSet - thermRead0;							 // Calculating the error
	C_output0 = prev_output0 + k1 * e_0 + k2 * e1_0 + k3 * e2_0; // Adjusting Correction Value

	if (C_output0 > 1.95)
	{
		C_output0 = 1.95; // Cooling Limit on current
	}
	else if (C_output0 < 1.2)
	{
		C_output0 = 1.2; // Heating Limit on current
	}

	prev_output0 = C_output0; // Correction value stored in prev_output
	/*Cy_SCB_UART_PutString(UART_HW, "prev_output0: \n\r ");
	printFloat(prev_output0);*/

	// Applying correction to minimize error
	/*dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
	transmitToHVDAC(dacDataPacket);*/

	//monitorITEC0();
	//Cy_SCB_UART_PutString(UART_HW, ",\r\n");
	//Cy_SCB_UART_PutString(UART_HW, " PID loop1 ends\n\r ");
}

void PID_loop1()
{
	float tempSet;
	float k1 = *kp + *ki + *kd;
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	// Start ADC conversion measurements
	Therm2_Read();
	Therm3_Read();

	if (*targetTECFlag1 == 0)
	{
		tempSet = *TDET2;
		thermRead1 = ThermRead2;
	}
	else
	{
		tempSet = *TDET3;
		thermRead1 = ThermRead3;
	}


	if (thermRead1 < 0)
	{
		thermRead1 = 0;
	}

	//printFloat(tempSet);

	// THERM LOOP PARAMETER UPDATES
	e2_1 = e1_1;
	e1_1 = e_1;
	e_1 = tempSet - thermRead1;
	C_output1 = prev_output1 + k1 * e_1 + k2 * e1_1 + k3 * e2_1;
	if (C_output1 > 1.95)
	{
		C_output1 = 1.95;
	}
	else if (C_output1 < 1.2)
	{
		C_output1 = 1.2;
	}

	prev_output1 = C_output1;

	/*dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
	transmitToHVDAC(dacDataPacket);*/

	/*printFloat(thermRead1);
	Cy_SCB_UART_PutString(UART_HW, ",");*/
	//monitorITEC1();
	//Cy_SCB_UART_PutString(UART_HW, ",\r\n");
	//Cy_SCB_UART_PutString(UART_HW, " PID loop2 ends\n\r ");
}
