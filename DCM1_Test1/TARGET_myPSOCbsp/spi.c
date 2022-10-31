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
	// Cy_SCB_UART_PutString(UART_HW,"\r\nInitializing Discr DAC\r\n");

	cy_rslt_t result;

	/*Define data transfer frequency*/
	uint32_t spi_master_frequency = 1000000;

	// Initialize CLR pin to high so DAC registers can be updated
	result = cyhal_gpio_init(P6_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUP, 1);
	/*if (result != CY_RSLT_SUCCESS)
	   {

		   Cy_SCB_UART_PutString(UART_HW,"DAC Discr CLR pin not initialized\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"DAC Discr CLR pin Initialized \r\n");}*/

	/*Configure the SPI Master settings*/
	result = cyhal_spi_init(&DiscrDAC_obj, P2_0, NC, P2_2, P2_3, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
	/*if (result != CY_RSLT_SUCCESS)
	   {

		   Cy_SCB_UART_PutString(UART_HW,"DAC Discr SPI initialization failed\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"DAC Discr SPI Master Initialized \r\n");}*/

	/*Set the SPI frequency*/
	result = cyhal_spi_set_frequency(&DiscrDAC_obj, spi_master_frequency);
	/*if (result != CY_RSLT_SUCCESS)
	   {

			 Cy_SCB_UART_PutString(UART_HW,"DAC DiscrSPI set frequency failed\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"DAC Discr SPI Master Frequency Set \r\n");}*/

	// Cy_SCB_UART_PutString(UART_HW,"\r\nInitialized Discr DAC\r\n");
}

void HVDAC_SPI_Init(void)
{
	// Cy_SCB_UART_PutString(UART_HW,"\r\nInitializing HV DAC\r\n");

	cy_rslt_t result;

	/*Define data transfer frequency*/
	uint32_t spi_master_frequency = 1000000;

	// Initialize CLR pin to high so DAC registers can be updated
	result = cyhal_gpio_init(P6_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUP, 1);
	/*if (result != CY_RSLT_SUCCESS)
	   {

		   Cy_SCB_UART_PutString(UART_HW,"HV DAC CLR pin not initialized\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"HV DAC CLR pin Initialized \r\n");}*/

	/*Configure the SPI Master settings*/
	result = cyhal_spi_init(&HVDAC_obj, P11_0, NC, P11_2, P11_3, NULL, 8, CYHAL_SPI_MODE_00_MSB, false);
	/*if (result != CY_RSLT_SUCCESS)
	   {

		   Cy_SCB_UART_PutString(UART_HW,"HV DAC SPI initialization failed\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"HV DAC SPI Master Initialized \r\n");}*/

	/*Set the SPI frequency*/
	result = cyhal_spi_set_frequency(&HVDAC_obj, spi_master_frequency);
	/*if (result != CY_RSLT_SUCCESS)
	   {

			Cy_SCB_UART_PutString(UART_HW,"HV DAC SPI set frequency failed\r\n");

	   }
	else { Cy_SCB_UART_PutString(UART_HW,"HV DAC SPI Master Frequency Set \r\n");}(*/

	// Cy_SCB_UART_PutString(UART_HW,"\r\nInitialized HV DAC\r\n");
}

void transmitToHVDAC(uint32_t dacDataPacket)
{
	//Cy_SCB_UART_PutString(UART_HW, "inside transmitToHVDAC  start\n\r ");
	char confirmValue[32];
	/*sprintf(confirmValue, "%ld %d", dacDataPacket, SPI_BUFFER_SIZE );
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
				Cy_SCB_UART_PutString(UART_HW, "\n\r");*/

	for (bufIndex = (SPI_BUFFER_SIZE - 1), shift = 0; bufIndex >= 0; bufIndex--, shift++)
	{
		//Cy_SCB_UART_PutString(UART_HW, "inside transmitToHVDAC  loop\n\r ");
		spi_buf[bufIndex] = (uint8_t)(dacDataPacket >> (8 * shift));

	}
	//Cy_SCB_UART_PutString(UART_HW, "outside transmitToHVDAC  loop\n\r ");
	cy_rslt_t result;

	// Define placehold variable to receive
	uint8_t receive_data[4];

	for (int i = 0; i < 1; i++)
	{
		cyhal_spi_transfer_async(&HVDAC_obj, spi_buf, 4, receive_data, 4);
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

		/*if( result != CY_RSLT_SUCCESS)
		{
			//Cy_SCB_UART_PutString(UART_HW,"Discr DAC SPI data transferred FAILED \r\n");
			CY_ASSERT(0);


		}
		else { Cy_SCB_UART_PutString(UART_HW,"Discr DAC SPI data byte transferred\r\n");}*/
	}
}
