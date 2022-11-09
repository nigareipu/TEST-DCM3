/*
 * mainheader.h
 *
 *  Created on: Oct. 25, 2022
 *      Author: n6sultan
 */

#ifndef MAINHEADER_H_
#define MAINHEADER_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "serialUART.h"
#include "uartInterrupt.h"
#include "AD56x8.h"
#include "dac.h"
#include "spi.h"
#include "tec.h"
#include "adc.h"//Not touching up to here
#include "det_bias.h"
#include "discr.h"
#include "coin_window.h"
#include "delay.h"
#include "modes.h"
#include "table.h"
#include "commands.h"
#include "allocate.h"
#include "timerInterrupt.h"

/************************  FUNCTION DECLARATIONS  *********************************/
uint8_t rxBuffer[32];
uint8_t sendBuffer[32];
char storeBuffer[BUF_LEN];
char *commandBuffer;
char *valueBuffer;
char confirmValue[200];

volatile int count;
volatile bool uartRxCompleteFlag; // flag for notifying that the rx buffer is not empty
volatile bool printThermalInfo = 1;	  // option to print all thermread data
volatile bool TEC_controller0ActiveFlag;	  // flag for timer interrupt
volatile bool TEC_controller1ActiveFlag;
volatile bool PID_Select = 0; // flag for alternating PID loops
float tecDriver0StatusFlag;
float tecDriver1StatusFlag;

cyhal_spi_t DiscrDAC_obj;
cyhal_spi_t HVDAC_obj;
uint8_t spi_buf[SPI_BUFFER_SIZE];
uint32_t dacDataPacket;
uint16_t dacValue;
uint32_t ClockStamp, ClockStamp0, ClockStamp1, ClockStamp2, ClockStamp3;

cy_stc_scb_uart_context_t uartContext;
cyhal_timer_t timer_obj;


/*****************hash table variables************************************************/
/* Integer parameters include:
 * setting the mode
 * choosing the number of detectors to calibrate using DetST and DetEd
 * setting the delay time between each counting using countTime
 * choosing the upper limit for delay time to be set (default value is 5000ms)
 * choosing the detector via AnDET to be annealed
 * Choosing loop time using RTime
 * setting coincidence window size by setting CoWin
 * Setting the Bias voltage and Temperature for each detector using VDET0-3 and TDET0-3
 * selecting the discriminator threshhold using DThrs
 * setting the path delay for each detector using DlayDET0-3
 * setting the discriminator threshhold, voltage and temperature range for calibration using DthrEd, DthrSt, VoltSt, VoltEd, TempSt, TempEd.
 * setting PID coefficient kp, ki, kd
 * setting targetTECFlag0 = 0 sets TEC 0 as master, setting targetTECFlag0 = 1 sets TEC 1 as master for the TEC Driver 0
 * setting targetTECFlag1 = 0 sets TEC 0 as master, setting targetTECFlag1 = 1 sets TEC 1 as master for the TEC Driver 1
 * Turning feedback off by setting printMessageFlag = 0, On by setting printMessageFlag = 1
 * Get thermal information by setting printThermalFlag = 1 otherwise 0
 * Selecting calibration sub mode: mode5Calibration = 0 -> BreakdownvsTemp or mode5Calibration = 1 -> CountsvDiscThresh and BiasTempvsCounts
 * Exit mode by setting Exit = 1, default value is 0
 */
uint16_t *countTime, *maxcountTime;
uint8_t *mode, *DetSt, *DetEd, *AnDET,  *RTime, *CoWin;
float *VDET0, *VDET1, *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *DThrs, *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *DthrEd, *DthrSt,*TempSt, *TempEd, *VoltSt, *VoltEd, *kp, *ki, *kd;
bool *targetTECFlag1, *targetTECFlag0, *printMessageFlag, *printThermalFlag, *Exit, *mode5Calibration, *InitialTempInfo;
/*****************End of hash table variables declaration*****************************/

//Local flags used in functions
volatile bool coincWindowSetFlag = 0;
volatile bool delay0SetFlag = 0, delay1SetFlag = 0, delay2SetFlag = 0,delay3SetFlag = 0;
float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
int countLoopDelay;

#endif /* MAINHEADER_H_ */
