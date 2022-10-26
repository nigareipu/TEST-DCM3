/******************************************************************************
 * File Name:   main.c
  Author: Nigar Sultana*
 * Date: October 24th 2022
 *
 *******************************************************************************/


#include "mainheader.h"

/*
 * Check if all the header declaration in a separate .h file. does it make any difference?
 */

/***************************  DEFINITIONS  *************************************/


int main(void)
{

	Init_Hardware();
	configureUART_Isr();
	Cy_SCB_UART_Enable(UART_HW); // Enable UART to operate

	// enable all interrupts
	__enable_irq();


	 /* ***********Timer code******************************
	 ************************************************** */

	//cyhal_timer_event_interrupt();

  // Read the current timer value, which should be close to the amount of delay in ms * 10 (5000)

  Cy_SCB_UART_PutString(UART_HW, "Timer interrupt testing\n ");


	/*****************************************************************
	 * Initialize all peripherals
	 * ***************************************************************
	 */


	DiscrDAC_SPI_Init();
	setDiscrDACInternalRef();
	HVDAC_SPI_Init();
	setHVDACInternalRef();
	CoincidenceWindow_Init();
	SingleSide_Init();
	Delays_Init();
	ADC_Init();
	TEC_Driver0_Init(0);
	TEC_Driver1_Init(0);
	TEC_SW0_Init(0);
	TEC_SW1_Init(0);
	TEC_SW2_Init(0);
	TEC_SW3_Init(0);
	SinglesCounter0_Init();
	SinglesCounter1_Init();
	SinglesCounter2_Init();
	SinglesCounter3_Init();
	CoincidenceCounter0_Init();
	CoincidenceCounter1_Init();
	CoincidenceCounter2_Init();
	CoincidenceCounter3_Init();

	//StartCounters();

	// Upon RESET, re-iterate that in IDLE MODE
	// Should probably check in actuality if in Idle mode..

	/***********************************Table Allocation********************************/
	//Cy_SCB_UART_PutString(UART_HW, "\r\nCurrently in IDLE MODE.\r\n ");
	mode1program();


	Cy_SCB_UART_PutString(UART_HW, "\r\nRight Before allocation function");
	default_hashtable();

	Cy_SCB_UART_PutString(UART_HW, "I'm here after table\r\n");
	Cy_SCB_UART_PutString(UART_HW, "\r\n About to go into modes = ");
	sprintf(confirmValue, "%f\r\n", *mode);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");


	// Setting the Communication Input Mode to Automated or Manual

	for (;;)
	{

		// If something has been typed, show that character on the terminal
		if (uartRxCompleteFlag == 1)
		{
			echoInput();


			// If the user starts a new line, process the command
			if (*rxBuffer == '\n' || *rxBuffer == '\r')
			{

				Cy_SCB_UART_PutString(UART_HW, "*VDET0: \r\n");
				sprintf(confirmValue, "%f", *VDET0);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
				Cy_SCB_UART_PutString(UART_HW, " V\r\n");

				Cy_SCB_UART_PutString(UART_HW, "DiscrThresh: \r\n");
								sprintf(confirmValue, "%f", discrThresh);
								Cy_SCB_UART_PutString(UART_HW, confirmValue);
								Cy_SCB_UART_PutString(UART_HW, " V\r\n");

				// Divide incoming buffer into command and value sections (ex. first 4 bits are for command and last 4 are for value)
				// Will only work with terminal connected to it, without it tho all default values should still go through
				// commandBuffer = strtok(storeBuffer, ";");
				// valueBuffer = strtok(NULL, ";");
				// fvalue = atof(valueBuffer);
				//*command = fvalue;
				// update_table(commandBuffer, fvalue);
				// String comparison. List of possible commands and values are compared to invoke the proper function and arguments.
				// float* mode = allocate_node(hash_table, table_size, sizeof(float), "mode");

				if (*mode == 1)
				{
					// CODE RUNNING IDLE MODE
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to 1\r\n");
					mode1program();
				}
				else if (*mode == 2)
				{
					// CODE RUNNING TWO SIDE COINCIDENCE COUNTING MODE
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 2\r\n");
					mode2program();
				}
				else if (*mode == 3)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 3\r\n");
					mode3program();
				}
				else if (*mode == 4)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 4\r\n");
					mode4program();
				}
				else if (*mode == 5)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 5\r\n");
					mode5program();
				}
				else if (*mode == 6)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 6\r\n");
					mode6program();
				}
				else if (*mode == 7)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 7\r\n");
					mode7program();
				}

				else
				{
					//mode1program();
					Cy_SCB_UART_PutString(UART_HW, "\r\n Not valid value\r\n");
					Cy_SCB_UART_PutString(UART_HW, "Choose command and value\r\n");
					uartRxCompleteFlag = 0;
					count = 0;
				}
			}

			// If user types something other than newline or return, put the chars into the buffer
			else
			{
				fillBuffer();
			}
		}

		// Occaisionally, if nothing incoming in buffer, then send temperature data.
	}
}
