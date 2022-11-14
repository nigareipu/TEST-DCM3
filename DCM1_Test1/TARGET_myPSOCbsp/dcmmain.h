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
uint8_t rxBuffer[32]={0};
uint8_t sendBuffer[32];
char storeBuffer[200];
char *commandBuffer;
char *valueBuffer;
char confirmValue[200];

volatile int count_uartbuffer; //uart buffer index
volatile bool printThermalInfo = 1;	  // option to print all thermread data
volatile bool TEC_controller0ActiveFlag;	  // flag for choosing PIDloop0() in timer interrupt
volatile bool TEC_controller1ActiveFlag;	// flag for choosing PIDloop1() in timer interrupt
volatile bool PID_Select = 0; // flag for alternating PID loops
float tecDriver0StatusFlag; // flag used in initializing TEC Driver 0
float tecDriver1StatusFlag; // flag used in initializing TEC Driver 1

cyhal_spi_t DiscrDAC_obj;
cyhal_spi_t HVDAC_obj;
uint8_t spi_buf[SPI_BUFFER_SIZE];
uint32_t dacDataPacket;
uint16_t dacValue;
uint32_t ClockStamp0; //read sys_clock

cy_stc_scb_uart_context_t uartContext;
cyhal_timer_t timer_obj;


/*****************hash table variables************************************************/

uint16_t *countTime; 					//set delay between each counting
uint16_t *maxcountTime;					//set upper limit for *countTime
uint16_t *TempStabilizationDlay;		// time for thermal stabilization before each counting mode
uint8_t *mode; 							//set mode
uint8_t *DetSt, *DetEd;					//choose number of detectors to calibrate
uint8_t *AnDET;							//choose the detector to be annealed
uint8_t *RTime;							//Choose number of loop to execute during each counting mode
uint8_t *CoWin; 						//set coincidence window size
float *VDET0, *VDET1, *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3;  //Set the Bias voltage and Temperature for each detector
float *DThrs; 							//select discriminator threshhold
float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3;  //set path delay for each detector
float *DthrSt, *DthrEd, *TempSt, *TempEd, *VoltSt, *VoltEd;  // set range of discriminator threshhold, voltage and temperature for calibration
float *kp, *ki, *kd;					//set PID coefficient kp, ki, kd
float *HVMoni0, *HVMoni3, *ThermRead0, *ThermRead1, *ThermRead2, *ThermRead3, *ITEC0, *ITEC1; //keep high voltage, thermistor  voltage and current info
bool *targetTECFlag0, *targetTECFlag1;  // choose thermistor feedback for PID loops. targetTECFlag0->thermistor0 or thermistor1, targetTECFlag1->thermistor2 or thermistor3
bool *printMessageFlag;					//turn on/off intro debug value messages
bool *printThermalFlag ;
bool *Exit; 							//for exiting any mode
uint8_t *mode5Calibration;					//Select calibration sub mode: mode5Calibration = 0 -> BreakdownvsTemp, mode5Calibration = 1 -> CountsvDiscThresh and BiasTempvsCounts
bool *InitialTempInfo;
/*****************End of hash table variables declaration*****************************/

//Local Variables
int countLoopDelay;

#endif /* MAINHEADER_H_ */
