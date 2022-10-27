/******************************************************************************
 * File Name:   main.c
  Author: Nigar Sultana*
 * Date: October 24th 2022
 *
 *******************************************************************************/


#include "dcmmain.h"



int main(void)
{

	Init_Hardware();
	configureUART_Isr();
	Cy_SCB_UART_Enable(UART_HW); // Enable UART to operate

	// enable all interrupts
	__enable_irq();


	 /* ***********Timer code******************************
	 ************************************************** */

	cyhal_timer_event_interrupt();

  // Read the current timer value, which should be close to the amount of delay in ms * 10 (5000)

  //Cy_SCB_UART_PutString(UART_HW, "Timer interrupt testing\n ");


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


				// Divide incoming buffer into command and value sections (ex. first 4 bits are for command and last 4 are for value)
				// Will only work with terminal connected to it, without it tho all default values should still go through
				commandBuffer = strtok(storeBuffer, ";");
				valueBuffer = strtok(NULL, ";");
			    //fvalue = atof(valueBuffer);
				//*command = fvalue;
				// update_table(commandBuffer, fvalue);


				if (*mode == 1)
				{
					// CODE RUNNING IDLE MODE
					mode1program();
				}
				else if (*mode == 2)
				{
					// CODE RUNNING TWO SIDE COINCIDENCE COUNTING MODE
					mode2program();
				}
				else if (*mode == 3)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					mode3program();
				}
				else if (*mode == 4)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					mode4program();
				}
				else if (*mode == 5)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					mode5program();
				}
				else if (*mode == 6)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					mode6program();
				}
				else if (*mode == 7)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					mode7program();
				}

				else
				{
					mode1program();
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
