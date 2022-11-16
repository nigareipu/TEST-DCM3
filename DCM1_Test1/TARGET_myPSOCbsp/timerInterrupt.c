/*
 * timerInterrupt.c
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */
#include "timerInterrupt.h"
//#define DEBUG


double e_0 = 0; // Error = (SetPoint - Feedback)
double e1_0 = 0;
double e2_0 = 0;
double e_1 = 0;
double e1_1 = 0;
double e2_1 = 0;
uint32_t count_timerevents=0;

void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{
	// First TEC controller
	if (PID_Select == 0)
	{
		Therm0_Read();
		Therm1_Read();
		Therm2_Read();
		Therm3_Read();
		monitorITEC0();
		monitorITEC1();
		HV0_Monitor();
		HV3_Monitor();
		*timer_sysclock = Cy_SysTick_GetValue();
		count_timerevents++;
		*count_timerInterruptEvent=count_timerevents;


		if(*printTelemetryFlag==true){

			sprintf(confirmValue, "\n\rclk, #Tmr, T0, T1, T2, T3, IT0, IT1: %ld, %ld, %.4f, %.4f, %.4f, %.4f,%.4f, %.4f",
					*timer_sysclock, *count_timerInterruptEvent, *ThermRead0, *ThermRead1, *ThermRead2, *ThermRead3, *ITEC0, *ITEC1);
			Cy_SCB_UART_PutArray(UART_HW, confirmValue, strlen(confirmValue));
		}


		PID_Select = 1;

		if (TEC_controller0ActiveFlag == true)
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
		}

		dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToTDAC(dacDataPacket);
	}

	else
	{
		PID_Select = 0;

		// Second TEC controller
		if (TEC_controller1ActiveFlag == true)
		{
			PID_loop1();
		}

		else
		{
			e_1 = 0;
			e1_1 = 0;
			e2_1 = 0;
			prev_output1 = 1.5;
			C_output1 = 1.5;
		}
		dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToTDAC(dacDataPacket);
	}
}

void cyhal_timer_event_interrupt()

{
	cyhal_timer_cfg_t timer_cfg =
	{
			.compare_value = 0,				 // Timer compare value, not used
			.period = 4999,					 // Defines the timer period
			.direction = CYHAL_TIMER_DIR_UP, // Timer counts up
			.is_compare = false,			 // Don't use compare mode
			.is_continuous = true,			 // Run the timer indefinitely
			.value = 0						 // Initial value of counter
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
	float k2 = -*kp - 2 * (*kd);
	float k3 = *kd;

	Therm0_Read();
	Therm1_Read();

	if (*targetTECFlag0 == false)
	{
		tempSet = *TDET0;
		thermRead0 = *ThermRead0;
	}
	else
	{
		tempSet = *TDET1;
		thermRead0 = *ThermRead1;
	}

	if (thermRead0 < 0)
	{
		thermRead0 = 0;
	}

	e2_0 = e1_0;
	e1_0 = e_0;
	e_0 = tempSet - thermRead0;									 // Calculating the error
	C_output0 = prev_output0 + k1 * e_0 + k2 * e1_0 + k3 * e2_0; // Adjusting Correction Value

	if (C_output0 > 1.95)
	{
		C_output0 = 1.95; // Cooling Limit on current
	}
	else if (C_output0 < 1.2)
	{
		C_output0 = 1.2; // Heating Limit on current
	}

	prev_output0 = C_output0;
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

	if (*targetTECFlag1 == false)
	{
		tempSet = *TDET2;
		thermRead1 = *ThermRead2;
	}
	else
	{
		tempSet = *TDET3;
		thermRead1 = *ThermRead3;
	}

	if (thermRead1 < 0)
	{
		thermRead1 = 0;
	}

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
}
