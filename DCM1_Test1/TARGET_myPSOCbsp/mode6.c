

#include "modes.h"

void mode6program()
{
	printThermalInfo = *InitialTempInfo;
	Cy_SCB_UART_PutString(UART_HW, "\r\nSET MODE to Thermal Annealing\r\n");

	// CODE FOR RUNNING  MODE
	turnOFF_TECs();

	// Confirm selected TEC is on and set to anneal to the temperature
	if (*printMessageFlag == 1)
	{
		Cy_SCB_UART_PutString(UART_HW, "Thermoelectric cooler number ");

		sprintf(confirmValue, "%i", *AnDET);

		Cy_SCB_UART_PutString(UART_HW, " is ON and set to anneal to temperature ");
		sprintf(confirmValue, "%f", *TDET0);
		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
		Cy_SCB_UART_PutString(UART_HW, " for ");

		sprintf(confirmValue, "%i", *RTime);

		Cy_SCB_UART_PutArray(UART_HW, confirmValue, sizeof(confirmValue));
		Cy_SCB_UART_PutString(UART_HW, " seconds:\r\n");
	}

	// Annealing the selected detector to 91 C for the selected time

	if (*AnDET == 0)
	{
		TEC_controller0ActiveFlag = 1;
		TEC_controller1ActiveFlag = 0;
		TEC_SW0_Status(ON);
		TEC_Driver0_Status(ON);
		// also set *targetTECFlag0 == 0;
	}

	else if (*AnDET == 1)
	{

		TEC_controller0ActiveFlag = 1;
		TEC_controller1ActiveFlag = 0;
		TEC_SW1_Status(ON);
		TEC_Driver0_Status(ON);
		// also set *targetTECFlag0 == 1;
	}
	else if (*AnDET == 2)
	{

		TEC_controller0ActiveFlag = 0;
		TEC_controller1ActiveFlag = 1;
		TEC_SW2_Status(ON);
		TEC_Driver1_Status(ON);
		// also set *targetTECFlag1 == 0;
	}
	else if (*AnDET == 3)
	{
		TEC_controller0ActiveFlag = 0;
		TEC_controller1ActiveFlag = 1;
		TEC_SW3_Status(ON);
		TEC_Driver1_Status(ON);
		// also set *targetTECFlag1 == 1;
	}
	else
	{
		Cy_SCB_UART_PutString(UART_HW, "Wrong anneal detector- Exit\r\n");
		mode1program();
		return;
	}

	cyhal_system_delay_ms(*TempStabilizationDlay);

	for (int k = 0; k < *RTime; k++)
	{

		if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

		cyhal_system_delay_ms(1000); // Must be kept for accumulating counts/sec
	}
	turnOFF_TECs();
	mode1program();
}
