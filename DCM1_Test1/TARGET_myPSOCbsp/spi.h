/*
 * spi.h
 *
 *  Created on: Apr. 28, 2022
 *      Author: jkrynski1
 */

#ifndef TARGET_MYPSOCBSP_SPI_H_
#define TARGET_MYPSOCBSP_SPI_H_

//#include "functions.h"

#define SPI_BUFFER_SIZE 4

// Globals
extern cyhal_spi_t DiscrDAC_obj;
extern cyhal_spi_t HVDAC_obj;
extern uint8_t spi_buf[SPI_BUFFER_SIZE];
extern int8_t bufIndex;
extern uint8_t shift;

// functions
void DiscrDAC_SPI_Init();
void HVDAC_SPI_Init();
void transmitToDiscrDAC(uint32_t dacDataPacket);
void transmitToHVDAC(uint32_t dacDataPacket);
void transmitToTDAC(uint32_t dacDataPacket);

#endif /* TARGET_MYPSOCBSP_SPI_H_ */
