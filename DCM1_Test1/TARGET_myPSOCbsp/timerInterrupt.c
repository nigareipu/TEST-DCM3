/*
 * timerInterrupt.c
 *
 *  Created on: Oct. 21, 2022
 *      Author: n6sultan
 */
#include <timerInterrupt.h>


void isr_timer(void *callback_arg, cyhal_timer_event_t event)
{
    Cy_SCB_UART_PutString(UART_HW, "1s Timer interrupt testing\n\r ");

    // Set the interrupt flag and process it from the application
    timer_interrupt_flag = true;
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
