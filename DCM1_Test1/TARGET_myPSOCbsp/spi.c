/*
 * spi.c
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#include "spi.h"

int8_t bufIndex;
uint8_t shift;

void DiscrDAC_SPI_Init(void)
{
	cy_rslt_t result;
	/*Define data transfer frequency*/
	uint32_t spi_master_frequency = 1000000;

	// Initialize CLR pin to high so DAC registers can be updated
	result = cyhal_gpio_init(P6_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUP, 1);
	/*Configure the SPI Master settings*/
	result = cyhal_spi_init(&DiscrDAC_obj, P2_0, NC, P2_2, P2_3, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
	/*Set the SPI frequency*/
	result = cyhal_spi_set_frequency(&DiscrDAC_obj, spi_master_frequency);
}

void HVDAC_SPI_Init(void)
{
	cy_rslt_t result;
	/*Define data transfer frequency*/
	uint32_t spi_master_frequency = 1000000;
	// Initialize CLR pin to high so DAC registers can be updated
	result = cyhal_gpio_init(P6_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUP, 1);
	/*Configure the SPI Master settings*/
	result = cyhal_spi_init(&HVDAC_obj, P11_0, NC, P11_2, P11_3, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
	/*Set the SPI frequency*/
	result = cyhal_spi_set_frequency(&HVDAC_obj, spi_master_frequency);
}

void transmitToTDAC(uint32_t dacDataPacket)
{
	// char confirmValue[32];
	for (bufIndex = (SPI_BUFFER_SIZE - 1), shift = 0; bufIndex >= 0; bufIndex--, shift++)
	{
		// Cy_SCB_UART_PutString(UART_HW, "inside transmitToHVDAC  loop\n\r ");
		spi_buf[bufIndex] = (uint8_t)(dacDataPacket >> (8 * shift));
	}
	cy_rslt_t result;
	// Define placehold variable to receive
	uint8_t receive_data[4];
	for (int i = 0; i < 1; i++)
	{
		cyhal_spi_transfer_async(&HVDAC_obj, spi_buf, 4, receive_data, 4);
	}
}

void transmitToHVDAC(uint32_t dacDataPacket)
{
	// char confirmValue[32];
	for (bufIndex = (SPI_BUFFER_SIZE - 1), shift = 0; bufIndex >= 0; bufIndex--, shift++)
	{
		// Cy_SCB_UART_PutString(UART_HW, "inside transmitToHVDAC  loop\n\r ");
		spi_buf[bufIndex] = (uint8_t)(dacDataPacket >> (8 * shift));
	}
	cy_rslt_t result;
	// Define placehold variable to receive
	uint8_t receive_data[4];
	for (int i = 0; i < 1; i++)
	{
		cyhal_spi_transfer_async(&HVDAC_obj, spi_buf, 4, receive_data, 4);
		//cyhal_spi_transfer(&HVDAC_obj, spi_buf, 4, receive_data, 4, 0xFF);
	}
}

void transmitToDiscrDAC(uint32_t dacDataPacket)
{

	for (bufIndex = (SPI_BUFFER_SIZE - 1), shift = 0; bufIndex >= 0; bufIndex--, shift++)
	{
		spi_buf[bufIndex] = (uint8_t)(dacDataPacket >> (8 * shift));
	}

	cy_rslt_t result;
	// Define placehold variable to receive
	uint8_t receive_data[4];
	for (int i = 0; i < 1; i++)
	{
		result = cyhal_spi_transfer(&DiscrDAC_obj, spi_buf, 4u, receive_data, 4u, 0XFF);
	}
}
