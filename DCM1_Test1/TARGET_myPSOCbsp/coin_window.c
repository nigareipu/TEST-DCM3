
#include "coin_window.h"

/*
 * @desc Initializes the pins used to change to single side coincidences
 * @returns Nothing
 */
void SingleSide_Init()
{

	// Initialize GPIO pins
	cy_rslt_t result;
	result = cyhal_gpio_init(P9_2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);
	result = cyhal_gpio_init(P9_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

}

/*
 * @desc If Bit1 is 1 Coin0 is 0&1 if 0 then Coin0 is 0&2, if Bit2 is 1 then
 * Coin1 is 2&3 if 0 then Coin1 is 1&2
 * @param bool Bit1 changes Coincidence 0
 * @param bool Bit2 changes Coincidence 1
 * @returns Nothing
 */
void SingleSide_Set(bool Bit1, bool Bit2)
{
	cyhal_gpio_write(P9_2, Bit1);
	cyhal_gpio_write(P9_3, Bit2);
}

/*
 * @desc Initialize P2_4 and P11_5 to value of 0, as bidirectional output pins.
 * For each pin will print whether initialization was successful or not.
 * @returns Nothing
 */
void CoincidenceWindow_Init()
{
	cy_rslt_t result;
	result = cyhal_gpio_init(P2_4, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);
	result = cyhal_gpio_init(P11_5, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_PULLUPDOWN, 0);

}

/*
 * @desc Writes input values to pins P2_4 and P11_5
 * @param bool Bit1 - Value given to P2_4
 * @param bool Bit2 - Value given to P11_5
 * @returns Nothing
 */
void CoincidenceWindow_Set(bool Bit1, bool Bit2)
{

	coincWindowSetFlag = 1;
	cyhal_gpio_write(P2_4, Bit1);
	cy_rslt_t setWindowBit2;
	cyhal_gpio_write(P11_5, Bit2);

}
