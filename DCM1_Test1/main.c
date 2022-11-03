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

	/*****************************************************************
	 * Initialize all peripherals
	 * ***************************************************************/

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
	SysTick_Init();
	Cy_SysTick_Enable();

	/* ***********Timer setup******************************/
	cyhal_timer_event_interrupt();

	/************Set default values*********************/
	default_hashtable();
	mode1program();

	for (;;)
	{
		if (uartRxCompleteFlag == 1)
		{
			echoInput();
			// If the user starts a new line, process the command
			if (*rxBuffer == '\n' || *rxBuffer == '\r')
			{
				// Divide incoming buffer into command and value sections (ex. first 4 bits are for command and last 4 are for value)
				// Will only work with terminal connected to it, although without it all default values should still go through
				commandBuffer = strtok(storeBuffer, ";");
				valueBuffer = strtok(NULL, ";");

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
					// CODE RUNNING SET MODE to SINGLE SIDE COINCIDENCE COUNTING
					mode4program();
				}
				else if (*mode == 5)
				{
					// CODE RUNNING SET MODE to CALIBRATION MODE
					mode5program();
				}
				else if (*mode == 6)
				{
					// CODE RUNNING SET MODE to THERMAL ANNEALING
					mode6program();
				}
				else if (*mode == 7)
				{
					// CODE RUNNING SET MODE to LASER ANNEALING
					mode7program();
				}

				else
				{
					mode1program();
					Cy_SCB_UART_PutString(UART_HW, "\r\n Not valid input\r\n");
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
	}
}
