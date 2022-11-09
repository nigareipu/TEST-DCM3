/*
 * tec.c
 *
 *  Created on: Jun. 8, 2022
 *      Author: jkrynski1
 * 		Commented July 28, 2022: Noura-B
 *
 */

/*This Program is written based on the Z-Transform of PID loop for digital implementation.
It has e as loop input and u at loop output  */

#include "tec.h"
#include "adc.h"
#include "det_bias.h"

// Defining global variables
// PID tuning parameters

double prev_output0 = 1.5;
double prev_output1 = 1.5;
double C_output0 = 0.0;
double C_output1 = 0.0;

float thermRead0 = 0.0; // System output temperature in voltage for Tec 0
float thermRead1 = 0.0; // System output temperature in voltage for Tec 1
float thermRead2 = 0.0; // System output temperature in voltage for Tec 2
float thermRead3 = 0.0;

float ITEC0_V, ITEC1_V, ITEC0, ITEC1;

void TEC_Driver0_Init(uint8 status)
{
	// Function initializing TEC Driver 0

	cyhal_gpio_init(P5_6, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);

	if (status == 1)
	{
		tecDriver0StatusFlag = 1;
	}
	else
	{
		tecDriver0StatusFlag = 0;
	}
}

void TEC_Driver0_Status(uint8 status)
{
	// Function for turning TEC Driver 0 ON and OFF

	cyhal_gpio_write(P5_6, status);

	if (status == 1)
	{
		tecDriver0StatusFlag = 1;
	}
	else
	{
		tecDriver0StatusFlag = 0;
	}
}

void TEC_Driver1_Init(uint8 status)
{
	// Function initializing TEC Driver 1

	cyhal_gpio_init(P5_7, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);

	if (status == 1)
	{
		tecDriver1StatusFlag = 1;
	}
	else
	{
		tecDriver1StatusFlag = 0;
	}
}

void TEC_Driver1_Status(uint8 status)
{
	// Function for turning TEC Driver 0 ON and OFF

	cyhal_gpio_write(P5_7, status);

	if (status == 1)
	{
		tecDriver1StatusFlag = 1;
	}
	else
	{
		tecDriver1StatusFlag = 0;
	}
}

void TEC_SW0_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_init(P6_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW0_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P6_4, status);
}

void TEC_SW1_Init(uint8 status)
{ // ON/OFF Switch function for TEC 1

	cyhal_gpio_init(P6_5, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW1_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P6_5, status);
}

void TEC_SW2_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 2

	cyhal_gpio_init(P7_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW2_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P7_2, status);
}

void TEC_SW3_Init(uint8 status)
{
	// ON/OFF Switch function for TEC 2

	cyhal_gpio_init(P7_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, status);
}

void TEC_SW3_Status(uint8 status)
{
	// ON/OFF Switch function for TEC 0

	cyhal_gpio_write(P7_3, status);
}

void monitorITEC0()
{
	ITEC0_Read();
	ITEC0 = (ITEC0_V - 1.5) / (8 * 0.05);
}

void monitorITEC1()
{
	ITEC1_Read();
	ITEC1 = (ITEC1_V - 1.5) / (8 * 0.05);
}
