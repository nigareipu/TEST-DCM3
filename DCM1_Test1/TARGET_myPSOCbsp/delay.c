/*
 * delay.c
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
#include "delay.h"

/*
 * @desc Initializes relevant delay pins as bidirectional output pins
 * with a starting value of 0
 * @returns Nothing
 */
void Delays_Init()
{

	// Delay 0, bit 1
	cyhal_gpio_init(P11_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay  0, bit 2
	cyhal_gpio_init(P11_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 1, bit 1
	cyhal_gpio_init(P0_0, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 1, bit 2
	cyhal_gpio_init(P0_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 2, bit 1 CHANGE PIN HERE
	cyhal_gpio_init(P0_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 2, bit 2 CHANGE PIN HERE
	cyhal_gpio_init(P0_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 3, bit 1 CHANGE PIN HERE
	cyhal_gpio_init(P0_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

	// Delay 3, bit 2 CHANGE PIN HERE
	cyhal_gpio_init(P2_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);
}

/*
 * @desc Writes to P11_1 and P11_4 the first two bits of delay setting
 * @param bool Delay0Bit1 - Value to be written to P11_1 (first bit of delay setting)
 * @param bool Delay0Bit2 - Value to be written to P11_4 (second bit of delay setting)
 * @returns Nothing
 */
void Delay0_Set(bool Delay0Bit1, bool Delay0Bit2)
{

	// Initialize GPIO for first bit of Delay setting
	cyhal_gpio_write(P11_1, Delay0Bit1);

	// initialize GPIO for second bit of Delay setting
	cyhal_gpio_write(P11_4, Delay0Bit2);

	delay0SetFlag = 1;
}

/*
 * @desc Writes to P0_0 and P0_1 two bits of delay setting
 * @param bool Delay1Bit1 - Value to be written to P0_0
 * @param bool Delay1Bit2 - Value to be written to P0_1
 * @returns Nothing
 */
void Delay1_Set(bool Delay1Bit1, bool Delay1Bit2)
{

	delay1SetFlag = 1;

	cyhal_gpio_write(P0_0, Delay1Bit1); // change last value to 0 or 1
	cyhal_gpio_write(P0_1, Delay1Bit2); // change last value to 0 or 1
}

/*
 * @desc Writes to P2_2 and P2_3 two bits of delay setting
 * @param bool Delay2Bit1 - Value to be written to P2_2
 * @param bool Delay2Bit2 - Value to be written to P2_3
 * @returns Nothing
 */
void Delay2_Set(bool Delay2Bit1, bool Delay2Bit2)
{

	delay2SetFlag = 1;

	cyhal_gpio_write(P2_2, Delay2Bit1); // change last value to 0 or 1
	cyhal_gpio_write(P2_3, Delay2Bit2); // change last value to 0 or 1
}

/*
 * @desc Writes to P0_4 and P2_1 two bits of delay setting
 * @param bool Delay3Bit1 - Value to be written to P0_4
 * @param bool Delay3Bit2 - Value to be written to P2_1
 * @returns Nothing
 */
void Delay3_Set(bool Delay3Bit1, bool Delay3Bit2)
{

	delay3SetFlag = 1;

	cyhal_gpio_write(P0_4, Delay3Bit1); // change last value to 0 or 1
	cyhal_gpio_write(P2_1, Delay3Bit2); // change last value to 0 or 1
}
