

#include "uartInterrupt.h"

void UART_Isr(void)
{
	Cy_SCB_UART_Interrupt(UART_HW, &uartContext);
}

void UART_Interrupt_Callback(uint32_t event)
{
	uint32_t   rx_num;
	switch (event)
	{
	case CY_SCB_UART_RECEIVE_NOT_EMTPY:

		/* Check Receive Data */
		//rx_num = Cy_SCB_UART_GetNumInRxFifo(UART_HW);
		if (rx_num != 0ul)
			//uint8_t uart_in_data[128];
		rx_num = Cy_SCB_UART_GetArray(UART_HW, rxBuffer, rx_num); //take input at the Rx buffer
		Cy_SCB_UART_PutArray(UART_HW, rxBuffer, rx_num); //echo at the emulator

		for(uint32_t i=0; i<rx_num; i++)
		{
		storeBuffer[i] = rxBuffer[i];
		//storeBuffer[count] = '\0';
		}

		if (rxBuffer[rx_num-1] == '\n' || rxBuffer[rx_num-1] == '\r')
		{
			// Divide incoming buffer into command and value sections (ex. first 4 bits are for command and last 4 are for value)
			// Will only work with terminal connected to it, although without it all default values should still go through

			uartRxCompleteFlag = 1;
			commandBuffer = strtok(storeBuffer, ";");
			valueBuffer = strtok(NULL, ";");
			update_node(table, TABLE_SIZE, commandBuffer, valueBuffer);
			break;
		}
		//Cy_SCB_UART_GetArray(UART_HW, rxBuffer, 32);


	}
}

void configureUART_Isr()
{
	(void)Cy_SCB_UART_Init(UART_HW, &UART_config, &uartContext);

	// Populate configuration structure (code specific for CM4)
	cy_stc_sysint_t uartIntrConfig =
	{
			.intrSrc = UART_IRQ,
			.intrPriority = 6u,
	};

	// Hook interrupt service routine and enable interrupt */
	(void)Cy_SysInt_Init(&uartIntrConfig, &UART_Isr);
	NVIC_EnableIRQ(uartIntrConfig.intrSrc);

	// Set the Transmission done interrupt for SCB
	Cy_SCB_SetTxInterruptMask(UART_HW, CY_SCB_TX_INTR_UART_DONE);

	// Set the Receive not empty interrupt for SCB
	Cy_SCB_SetRxInterruptMask(UART_HW, CY_SCB_RX_INTR_NOT_EMPTY);

	// Register the callback for the interrupt events
	Cy_SCB_UART_RegisterCallback(UART_HW, UART_Interrupt_Callback, &uartContext);
}
