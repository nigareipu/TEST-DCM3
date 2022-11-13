

#include "uartInterrupt.h"

void UART_Isr(void)
{
	Cy_SCB_UART_Interrupt(UART_HW, &uartContext);
}

/*void UART_Interrupt_Callback(uint32_t event)
{
	uint32_t   rx_num;
	switch (event)
	{
	case CY_SCB_UART_RECEIVE_NOT_EMTPY:
		uartRxCompleteFlag = 1;
		Cy_SCB_UART_GetArray(UART_HW, rxBuffer, 32);
		break;

	}
}*/

void UART_Interrupt_Callback(uint32_t event) //test callback
{
	uint32_t character;
	char c_char;
	switch(event)
	{
	case CY_SCB_UART_RECEIVE_NOT_EMTPY:
		// Get single character
		character = Cy_SCB_UART_Get(UART_HW);
		// Get all characters in buffer
		while (character != CY_SCB_UART_RX_NO_DATA)
		{
			// Cast int return to char
			c_char = (char) character;
			// Echo character
			Cy_SCB_UART_Put(UART_HW, character);
			// If end of command, set flag
			if ( c_char == '\n' || c_char == '\r') //
			{
				uartRxCompleteFlag = true;
				commandBuffer = strtok(storeBuffer, ";");
				//int length_cb = strlen(commandBuffer);
				//sprintf(confirmValue, "\r\n storeBuffer, commandbuffer, valueBuffer : %s %s %s\n\r", storeBuffer, commandBuffer, valueBuffer);
								//Cy_SCB_UART_PutString(UART_HW, confirmValue);

				valueBuffer = strtok(NULL, ";");
				//sprintf(confirmValue, "\r\n storeBuffer, commandbuffer, valueBuffer : %s %s %s\n\r", storeBuffer, commandBuffer, valueBuffer);
				//Cy_SCB_UART_PutString(UART_HW, confirmValue);
				//if(strlen(commandBuffer)>0 && strlen(valueBuffer)>0)

				update_node(table, TABLE_SIZE, commandBuffer, valueBuffer);

				//Cy_SCB_UART_PutString(UART_HW, "\r\n");
				count = 0;

			}
			else{
				// Push character to buffer
				//fillBuffer(&c_char);
				char* char_buff=&c_char;
				storeBuffer[count++] = *char_buff;
				storeBuffer[count] = '\0';
			}


			character = Cy_SCB_UART_Get(UART_HW);
		}
		break;
	}
}



void configureUART_Isr()
{
	(void)Cy_SCB_UART_Init(UART_HW, &UART_config, &uartContext);

	// Populate configuration structure (code specific for CM4)
	cy_stc_sysint_t uartIntrConfig =
	{
			.intrSrc = UART_IRQ,
			.intrPriority = 6u,//was 6u
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
