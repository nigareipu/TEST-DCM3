/*
 * timerInterrupt.c
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */
#include "timerInterrupt.h"
#include "tec.h"


void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{

	if(timer_interrupt_flag == true)
    {
		PID_loop(*TDET0);

		//Cy_SCB_UART_PutString(UART_HW, "1s Timer interrupt testing\n\r ");
    }


    else
    	{
    	*ki=0;
    	Cy_SCB_UART_PutString(UART_HW, "do nothing\n\r ");
    	}
}

void cyhal_timer_event_interrupt()

{
	//timer_interrupt_flag = false;
	//cy_rslt_t rslt;

    cyhal_timer_cfg_t timer_cfg =
        {
            .compare_value = 0,              // Timer compare value, not used
            .period = 9999,                  // Defines the timer period
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


void PID_loop(float tempSet)
{
	// Function for cooling down all detectors

	 k1 = *kp + *ki + *kd;
	 k2 = -*kp - 2 * (*kd);
	 k3 = *kd;

	Cy_SCB_UART_PutString(UART_HW, "thermRead0 (V), thermRead1 (V), thermRead2 (V), thermRead3 (V), TEC 0 Current (A), TEC 1 Current (A)\r\n");


		// Start ADC conversion measurements
		Therm0_Read();
		Therm1_Read();
		Therm2_Read();
		Therm3_Read();

		if (targetDetectorFlag == 0)
		{
			thermRead0 = ThermRead0;
		}
		else
		{
			thermRead0 = ThermRead1;
		}

		if (targetDetectorFlag2 == 0)
		{
			thermRead1 = ThermRead2;
		}
		else
		{
			thermRead1 = ThermRead3;
		}



		if (thermRead0 < 0)
		{
			thermRead0 = 0;
		}

		if (thermRead1 < 0)
		{
			thermRead1 = 0;
		}

		// THERM LOOP PARAMETER UPDATES
		// Process Variables for TEC Drive 0 (Error calculation for feedback)
		e2 = e1;
		e1 = e;
		e = tempSet - thermRead0;

		// Process Variables for TEC Drive 1
		e5 = e4;
		e4 = e3;
		e3 = tempSet - thermRead1;

		// Calculating the control function (output) for TEC 0 and TEC 2
		C_output0 = prev_output0 + k1 * e + k2 * e1 + k3 * e2;
		C_output1 = prev_output1 + k1 * e3 + k2 * e4 + k3 * e5;

		// Current limit for TEC Driver 0
		if (C_output0 > 1.95)
		{
			C_output0 = 1.95; // Cooling limit
		}
		else if (C_output0 < 1.2)
		{ // Heating limit
			C_output0 = 1.2;
		}

		// Current Limit for TEC Driver 1
		if (C_output1 > 1.95)
		{
			C_output1 = 1.95; // Cooling limit
		}
		else if (C_output1 < 1.2)
		{
			C_output1 = 1.2; // Heating limit
		}

		// Storing control function for feedback
		prev_output0 = C_output0;
		prev_output1 = C_output1;

		// Output of the loop updating the DAC for TEC_Driver0
		dacValue = convertTempSetVoltagetoDACVoltage(C_output0);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		// Output of the loop updating the DAC for TEC_Driver1
		dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
		transmitToHVDAC(dacDataPacket);

		if (printThermalInfo == 1)
		{
			sprintf(adcBuffer, "%f", ThermRead0);
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead1);
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead2);
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			Cy_SCB_UART_PutString(UART_HW, ",");

			sprintf(adcBuffer, "%f", ThermRead3);
			Cy_SCB_UART_PutArray(UART_HW, adcBuffer, 7);
			Cy_SCB_UART_PutString(UART_HW, ",");

			monitorITEC0();
			Cy_SCB_UART_PutString(UART_HW, ",");
			monitorITEC1();
			Cy_SCB_UART_PutString(UART_HW, ",\r\n");
		}

		Cy_SAR_StopConvert(SAR_ADC_HW);
		cyhal_system_delay_ms(*PIDLoopDlay);//do we need this delay as our timer also waits for 1000ms

}

