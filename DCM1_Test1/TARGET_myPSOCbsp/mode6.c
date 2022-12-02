

#include "modes.h"

void mode6program()
{
	Cy_SCB_UART_PutString(UART_HW, "SET MODE to Thermal Annealing");

	// CODE FOR RUNNING  MODE
	turnOFF_TECs();
	*printTelemetryFlag=true;

	// Annealing the selected detector to 91 C for the selected time

	if (*AnDET == 0)
	{
		TEC_controller0ActiveFlag = 1;
		TEC_controller1ActiveFlag = 0;
		TEC_SW0_Status(ON);
		TEC_Driver0_Status(ON);
		*targetTECFlag0 =false;
	}

	else if (*AnDET == 1)
	{
		TEC_controller0ActiveFlag = 1;
		TEC_controller1ActiveFlag = 0;
		TEC_SW1_Status(ON);
		TEC_Driver0_Status(ON);
		*targetTECFlag0=true;
	}
	else if (*AnDET == 2)
	{

		TEC_controller0ActiveFlag = 0;
		TEC_controller1ActiveFlag = 1;
		TEC_SW2_Status(ON);
		TEC_Driver1_Status(ON);
		*targetTECFlag1=false;
	}
	else if (*AnDET == 3)
	{
		TEC_controller0ActiveFlag = 0;
		TEC_controller1ActiveFlag = 1;
		TEC_SW3_Status(ON);
		TEC_Driver1_Status(ON);
		*targetTECFlag1=true;
	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "\r\nWrong anneal detector- Exit");
		//*printTelemetryFlag=false;
		mode1program();
		transition_modes_if_tec_start_global();
		return;
	}

	check_countTime();
	if(*Exit== false){
	cyhal_system_delay_ms(*TempStabilizationDlay);
	}

	for (int k = 0; k < *RTime; k++)
	{

		if (*Exit == true)
		{
			//Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		cyhal_system_delay_ms(countLoopDelay); // Must be kept for accumulating counts/sec
	}
	turnOFF_TECs();
	*printTelemetryFlag=true;
	*AnDET=5;
	mode1program();
	transition_modes_if_tec_start_global();
}
