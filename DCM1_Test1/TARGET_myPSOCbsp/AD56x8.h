/*
 * AD56x8.h
 *
 *  Created on: Jan 12, 2022
 *      Author: cqtsuba
 */
// ****
// AD56x8 related DAC source file used by LCPR modules
// Developed by Subash Sachidananda
// Centre for Quantum Technologies, National University of Singapore, Singapore
// *****

#ifndef SRC_HAL_AD56X8_H_
#define SRC_HAL_AD56X8_H_

// DAC based constants
#define IS_AD5628_USED (1)
#define IS_AD5648_USED (0)
#define IS_AD5668_USED (0)
#define USE_INTERNAL_VREF (1) // 1.25 or 2.5 V
#define USE_EXTERNAL_VREF (0) // 1.25V

#define AD56x8_WRITER_INPUT_REG (0x00) // write to input register n
#define AD56x8_UPDATE_DAC_REG (0x01)   // update all register
#define AD56x8_WR_IN_UPD_ALL (0x02)    // write to input and update all
#define AD56x8_CLR_ALL (0x06)          // clear all DAC register
#define AD56x8_WR_UPD_CH (0x03)        // write to and update channel n
#define AD56x8_CMD_USE_INT_VREF (0x08) // use internal VREF

#define AD56x8_DAC_CH_A (0x00)
#define AD56x8_DAC_CH_B (0x01)
#define AD56x8_DAC_CH_C (0x02)
#define AD56x8_DAC_CH_D (0x03)
#define AD56x8_DAC_CH_E (0x04)
#define AD56x8_DAC_CH_F (0x05)
#define AD56x8_DAC_CH_G (0x06)
#define AD56x8_DAC_CH_H (0x07)
#define AD56x8_DAC_CH_ALL (0x0F)

#define AD56x8_DATA_SIZE (20)
#define AD56x8_COMMAND_SIZE (4)
#define AD56x8_ADDR_SIZE (4)

#define AD5628_DATA_SHIFT (8)
#define AD5648_DATA_SHIFT (6)
#define AD5668_DATA_SHIFT (4)

#define AD56x8_COMMAND_SHIFT (24)
#define AD56x8_ADDRESS_SHIFT (20)

#define AD56x8_DATA_MASK (0x000FFFFF)
#define AD56x8_COMMAND_MASK (0x0F000000)
#define AD56x8_ADDRESS_MASK (0x00F00000)

#if USE_INTERNAL_VREF
#define AD56x8_VREF_VALUE ((float)2.5) // 2 * 1.25V
#elif USE_EXTERNAL_VREF
#define AD56x8_VREF_VALUE ((float)2.5)
#endif

#if IS_AD5628_USED
#define AD56x8_DATA_SHIFT AD5628_DATA_SHIFT
#define AD56x8_NUM_STEPS (4096)
#define AD56x8_DAC_MIN (1)
#define AD56x8_DAC_MAX (4095)
#elif IS_AD5648_USED
#define AD56x8_DATA_SHIFT AD5648_DATA_SHIFT
#define AD56x8_NUM_STEPS (16383)
#define AD56x8_DAC_MIN (1000)
#define AD56x8_DAC_MAX (16382)
#elif IS_AD5668_USED
#define AD56x8_DATA_SHIFT AD5668_DATA_SHIFT
#define AD56x8_NUM_STEPS (65535)
#define AD56x8_DAC_MIN (1000)
#define AD56x8_DAC_MAX (65535)
#endif

#endif /* SRC_HAL_AD56X8_H_ */
