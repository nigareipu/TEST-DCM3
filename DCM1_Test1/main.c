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
	turnOFF_TECs();
	mode1program();
	int count_global_loop=0;

	for (;;)
	{
		// loop will run only once when *tec_enableFlag=true
		if (*tec_enableFlag==true && count_global_loop<1)
		{
			turnON_TECs();
			//cyhal_system_delay_ms(*TempStabilizationDlay);
			count_global_loop++;
		}
		else if (*tec_enableFlag==false){
			turnOFF_TECs();
			count_global_loop=0;
		}

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

	}
}
