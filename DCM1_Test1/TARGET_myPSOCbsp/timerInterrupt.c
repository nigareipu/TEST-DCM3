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

//double C_output = 0.0;
//double prev_output = 1.5;
/*double prev_output0 = 1.5;
double prev_output1 = 1.5;
double C_output0 = 0.0;
double C_output1 = 0.0;

float thermRead = 0.0;
float thermRead0 = 0.0; // System output temperature in voltage for Tec 0
float thermRead1 = 0.0; // System output temperature in voltage for Tec 1
float thermRead2 = 0.0; // System output temperature in voltage for Tec 2
float thermRead3 = 0.0;*/


void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{
 //First TEC controller

	Therm0_Read();
	 Therm1_Read();
	 Therm2_Read();
	 Therm3_Read();

	 printFloat(*TDET0);
	 printFloat(ThermRead0);
	 printFloat(ThermRead1);
	 printFloat(ThermRead2);
	 printFloat(ThermRead3);


	if(TEC_controller0ActiveFlag == 1)
    {
	Cy_SCB_UART_PutString(UART_HW, "TDET0: ");
			    printFloat(*TDET0);
		PID_loop0();

		Cy_SCB_UART_PutString(UART_HW, "1s Timer interrupt testing\n\r ");
    }


    else
    	{
    		 e_0 = 0; // Error = (SetPoint - Feedback)
    	 e1_0 = 0;
    	 e2_0 = 0;


    	prev_output0 = 1.5;
    	C_output0 = 0.0;

    	Cy_SCB_UART_PutString(UART_HW, "do nothing\n\r ");
    	}

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
	    	 C_output1 = 0.0;
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


void PID_loop0()
{
	// Function for cooling down all detectors
   float tempSet;
	Cy_SCB_UART_PutString(UART_HW, "inside PID loop1 start\n\r ");


	 float k1 = *kp + *ki + *kd;
	 float k2 = -*kp -  2* (*kd);
	 float k3 = *kd;

	 printFloat(k1);
	 printFloat(k2);
	 printFloat(k3);

	 Therm0_Read();
	 Therm1_Read();

	 printFloat(*TDET0);
	 printFloat(ThermRead0);
	 printFloat(ThermRead1);

	 //Cy_SCB_UART_PutString(UART_HW, "read therm value \n\r ");

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

	 		printFloat(tempSet);
	 		sprintf(confirmValue, "%f", thermRead0);
	 		Cy_SCB_UART_PutString(UART_HW, confirmValue);


            //printFloat(targetDetectorFlag0);
	 		//Cy_SCB_UART_PutString(UART_HW, "passed thermRead selection \n\r ");

	 		// PID Controller
	 		e2_0 = e1_0;
	 		e1_0 = e_0;
	 		e_0 = tempSet - thermRead0;							 // Calculating the error
	 		C_output0 = prev_output0 + k1 * e_0 + k2 * e1_0 + k3 * e2_0; // Adjusting Correction Value

	 		//printFloat(C_output0);
	 		//Cy_SCB_UART_PutString(UART_HW, "passed thermRead selection \n\r ");

	 		if (C_output0 > 1.95)
	 		{
	 			C_output0 = 1.95; // Cooling Limit on current
	 		}
	 		else if (C_output0 < 1.2)
	 		{ // Heating Limit on current
	 			C_output0 = 1.2;
	 		}

	 		prev_output0 = C_output0; // Correction value stored in prev_output
	 		Cy_SCB_UART_PutString(UART_HW, "prev_output0: \n\r ");
	 		printFloat(prev_output0);

	 		// Applying correction to minimize error
	 		dacValue = convertTempSetVoltagetoDACVoltage(C_output0);

	 		//sprintf(confirmValue, "%d", dacValue);
	 		//Cy_SCB_UART_PutString(UART_HW, confirmValue);

	 		dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_C, AD56x8_WR_IN_UPD_ALL);
	 		//sprintf(confirmValue, "%ld", dacDataPacket);
	 		//Cy_SCB_UART_PutString(UART_HW, confirmValue);
	 		transmitToHVDAC(dacDataPacket);

	 		//Cy_SCB_UART_PutString(UART_HW, "after packet transmit\n\r ");


	 		// TEC Driver Current reading
	 		monitorITEC0();
	 		Cy_SCB_UART_PutString(UART_HW, ",\r\n");
	 		 Cy_SCB_UART_PutString(UART_HW, " PID loop1 ends\n\r ");
	 		//cyhal_system_delay_ms(1000);

}

void PID_loop1()
{
	float tempSet;
	float k1 = *kp + *ki + *kd;
		 float k2 = -*kp - 2 * (*kd);
		 float k3 = *kd;

		 Cy_SCB_UART_PutString(UART_HW, "inside PID loop2 start\n\r ");


		Cy_SCB_UART_PutString(UART_HW, "thermRead2 (V), thermRead3 (V), TEC 1 Current (A)\r\n");


			// Start ADC conversion measurements
			Therm2_Read();
			Therm3_Read();

			 //printFloat(*TDET0);
				 printFloat(ThermRead2);
				 printFloat(ThermRead3);
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

			printFloat(tempSet);

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

			dacValue = convertTempSetVoltagetoDACVoltage(C_output1);
			dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_D, AD56x8_WR_IN_UPD_ALL);
			transmitToHVDAC(dacDataPacket);

			printFloat(thermRead1);
			Cy_SCB_UART_PutString(UART_HW, ",");



			monitorITEC1();
			Cy_SCB_UART_PutString(UART_HW, ",\r\n");
			Cy_SCB_UART_PutString(UART_HW, " PID loop2 ends\n\r ");
		}
