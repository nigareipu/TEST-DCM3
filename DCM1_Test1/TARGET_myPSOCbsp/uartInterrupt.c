

#include "uartInterrupt.h"

void UART_Isr(void)
{
	Cy_SCB_UART_Interrupt(UART_HW, &uartContext);
}

void UART_Interrupt_Callback(uint32_t event)
{
	switch (event)
	{
	case CY_SCB_UART_RECEIVE_NOT_EMTPY:
		uartRxCompleteFlag = 1;
		Cy_SCB_UART_GetArray(UART_HW, rxBuffer, 32);
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
