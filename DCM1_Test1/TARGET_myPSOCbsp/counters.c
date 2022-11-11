#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "counters.h"

// External variables defined

uint32_t Singles0_CountRate;
uint32_t Singles1_CountRate;
uint32_t Singles2_CountRate;
uint32_t Singles3_CountRate;

uint32_t Coincidence0_CountRate;
uint32_t Coincidence1_CountRate;
uint32_t Coincidence2_CountRate;
uint32_t Coincidence3_CountRate;

/*
 * @desc Initialize and start Singles 0 counter
 * @returns Nothing
 */
void SinglesCounter0_Init(void)
{
    // Initialize Singles_0 created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Singles_0_HW, Singles_0_NUM, &Singles_0_config);
	Cy_TCPWM_Counter_Enable(Singles_0_HW, Singles_0_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_0_HW, Singles_0_NUM);
}

/*
 * @desc Initialize and start Singles 1 counter
 * @returns Nothing
 */
void SinglesCounter1_Init(void)
{
	/*Initialize Singles_0 created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Singles_1_HW, Singles_1_NUM, &Singles_1_config);
	Cy_TCPWM_Counter_Enable(Singles_1_HW, Singles_1_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_1_HW, Singles_1_NUM);
}

/*
 * @desc Initialize and start Singles 2 counter
 * @returns Nothing
 */
void SinglesCounter2_Init(void)
{

	/*Initialize Singles_1 created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Singles_2_HW, Singles_2_NUM, &Singles_2_config);
	Cy_TCPWM_Counter_Enable(Singles_2_HW, Singles_2_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_2_HW, Singles_2_NUM);
}

/*
 * @desc Initialize and start Singles 3 counter
 * @returns Nothing
 */
void SinglesCounter3_Init(void)
{
	/*Initialize Singles_1 created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Singles_3_HW, Singles_3_NUM, &Singles_3_config);
	Cy_TCPWM_Counter_Enable(Singles_3_HW, Singles_3_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_3_HW, Singles_3_NUM);
}

/*
 * @desc Initialize and start coincidence counter 0
 * @returns Nothing
 */
void CoincidenceCounter0_Init(void)
{
	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Coinc_0_HW, Coinc_0_NUM, &Coinc_0_config);
	Cy_TCPWM_Counter_Enable(Coinc_0_HW, Coinc_0_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_0_HW, Coinc_0_NUM);
}

/*
 * @desc Initialize and start coincidence counter 1
 * @returns Nothing
 */
void CoincidenceCounter1_Init(void)
{
	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Coinc_1_HW, Coinc_1_NUM, &Coinc_1_config);
	Cy_TCPWM_Counter_Enable(Coinc_1_HW, Coinc_1_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_1_HW, Coinc_1_NUM);
}

/*
 * @desc Initialize and start coincidence counter 2
 * @returns Nothing
 */
void CoincidenceCounter2_Init(void)
{
	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Coinc_2_HW, Coinc_2_NUM, &Coinc_2_config);
	Cy_TCPWM_Counter_Enable(Coinc_2_HW, Coinc_2_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_2_HW, Coinc_2_NUM);
}

/*
 * @desc Initialize and start coincidence counter 3
 * @returns Nothing
 */
void CoincidenceCounter3_Init(void)
{
	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	Cy_TCPWM_Counter_Init(Coinc_3_HW, Coinc_3_NUM, &Coinc_3_config);
	Cy_TCPWM_Counter_Enable(Coinc_3_HW, Coinc_3_NUM);

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_3_HW, Coinc_3_NUM);
}

/*
 * @desc Initializes SysTick driver with an interval of 10000000
 * @returns Nothing
 */
void SysTick_Init()
{
	Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU, 10000000);
	Cy_SysTick_Enable();
}
