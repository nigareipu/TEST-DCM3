/******************************************************************************
 * File Name:   function.c
 *
 * Description: Contains all functions for operation of SEAQUE DCM
 *
 * Author: Joanna Krynski
 *
 * Date: April 20, 2022
 *
 *******************************************************************************/

#include "functions.h"

/*
 * @desc Initializes the board and peripherals
 * @returns Nothing
 */
void Board_Init()
{
	cy_rslt_t result;

	/* Initialize the device and board peripherals */
	result = cybsp_init();
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	__enable_irq();
}

