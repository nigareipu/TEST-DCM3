/*
 * Common.h
 *
 *  Created on: Jan 12, 2022
 *      Author: cqtsuba
 */
// ****
// Common source file used by all modules
// Developed by Subash Sachidananda
// Centre for Quantum Technologies, National University of Singapore, Singapore
// *****

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/***************************** Include Files *********************************/
//#include "stm32f4xx.h"
//#include "HAL_spi.h"
//#include "HAL_dac.h"
//#include "HAL_common.h"
#include "AD56x8.h"
//#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************** Include Files *********************************/
/************************** Constant Definitions *****************************/

#define YES (2)
#define NO (1)
#define ENABLE (1)
#define DISABLE (0)
#define MANUAL (1)
#define AUTO (2)
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#define USER_INPUT_WAIT_TIME (20000) // in sec
#define USER_INPUT_UNDEFINED (0)
#define USER_INPUT_VOLTAGE_SIZE (4)
#define USER_INPUT_CHOOSE_SIZE (1)
#define UART_BUFFER_SIZE (255)
#define SPI_BUFFER_SIZE (4)
#define MANUAL_MODE (1)
#define AUTO_MODE (0)
#define LAB_MODE (0)
//#define DEBUG_MODE				(0)

#define MULTI_TIER_MENU (1)

#define OPTO_DAC_ENABLED (1)

#ifdef MULTI_TIER_MENU
#define LCPR_PARAM_LIMIT 1
#endif

// All values between 81-96 is for LCPR
#define LCPR1_INDEX 1
#define LCPR2_INDEX 2
#define ENABLE_DISABLE_LCPR 0
//#define CHANGE_LCPR_DUTY_CYCLE		1
//#define CHANGE_LCPR_FREQUENCY		2
#define CHANGE_LCPR_ANGLE 3
#define CHANGE_LCPR_VOLTAGE 4
//#define ENABLE_DISABLE_LCPR2		6
//#define CHANGE_LCPR2_DUTY_CYCLE		2
//#define CHANGE_LCPR3_DUTY_CYCLE		3
//#define CHANGE_LCPR3_FREQUENCY		9
//#define ENABLE_DISABLE_LCPR3		7

/**************************** Type Definitions *******************************/
/***************** Macros (Inline Functions) Definitions *********************/
#ifdef MULTI_TIER_MENU
#define isLCPRRelated(x) ((((x) == (LCPR_PARAM_LIMIT))) ? 1 : 0)
#endif

// Application specific mapping
// Opto - SPI
#define OPTO_DAC_DEVICE 0 // SPI0_DEVICE_ID
#define OPTO_DAC_SELECT SPI_SELECT_0

// Hardware mappings
// Opto - DAC
#define OPTO_DAC_MIN_VOLT (10)
#define OPTO_DAC_MAX_VOLT (2500)
#define OPTO_DAC_MIN DAC_MIN
#define OPTO_DAC_MAX DAC_MAX
#define OPTO_DAC_CMD_WR_CH DAC_CMD_WR_CH
#define OPTO_DAC_NUM_STEPS DAC_NUM_STEPS
#define OPTO_DAC_VREF_VALUE DAC_VREF_VALUE
#define OPTO_DAC_ALL_CHANNELS DAC_ALL_CHANNELS

// LCPR related
#define NUM_LCPRS (2)
#define LCPR_DAC_DEVICE OPTO_DAC_DEVICE
#define LCPR_1_DAC_CHANNEL DAC_CHANNEL_B
#define LCPR_2_DAC_CHANNEL DAC_CHANNEL_A
#define LCPR_POPULATED (TRUE)
#define LCPR_NOT_POPULATED (FALSE)
#define LCPR_1_POPULATED (LCPR_POPULATED)
#define LCPR_2_POPULATED (LCPR_POPULATED)

/************************** Global Variable Definitions **********************/
/************************** Function Prototypes ******************************/
void initializeCommonModules();
float readNumUserInput(UART_HandleTypeDef *huart2, uint8_t numChars, uint32_t timeOut);
uint16_t convertLCPRVoltageToDACVoltage(int32_t inputVoltage);
uint32_t prepareDACDataPacket(uint16_t data, uint16_t channel, uint16_t command);
/************************** Function Definitions *****************************/
#endif /* SRC_COMMON_H_ */
