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

uint8_t txBuffer[20];
uint8_t rxBuffer[20];
uint8_t sendBuffer[8];
char storeBuffer[BUF_LEN];
char str[20];
char interpBuffer[8];
char *commandBuffer;
char *valueBuffer;
char confirmValue[32];


int idx;
volatile int count;
volatile bool uartRxCompleteFlag; // flag for notifying that the rx buffer is not empty
volatile bool flag_1;			  // flag for notifying that the rx buffer is full and receiving is complete.
volatile bool printThermalInfo=1;	  // option to print all thermread data
volatile bool ThermStabilize;	  // option to do 30 s thermal stabilization. Must be set to 1 initially during first measurements.
volatile bool TEC_controller0ActiveFlag;// flag for timer interrupt
volatile bool TEC_controller1ActiveFlag;
volatile bool warningFlag = 1; // flag for printing warnings before mode is set. Must be set to 1 to print information.
volatile bool PID_Select=0; // flag for alternating PID loops
float tecDriver0StatusFlag;
float tecDriver1StatusFlag;
float targetDetectorFlag;
float targetDetectorFlag2;

cyhal_spi_t DiscrDAC_obj;
cyhal_spi_t HVDAC_obj;
uint8_t spi_buf[SPI_BUFFER_SIZE];
uint32_t dacDataPacket;
uint16_t dacValue;
uint32_t ClockStamp;

float inputVoltage;

uint8_t receive_data[SPI_BUFFER_SIZE];
cy_stc_scb_uart_context_t uartContext;
cy_rslt_t result;
cyhal_timer_t timer_obj;
cyhal_adc_t adc_obj;// ADC and channel object//

char adcBuffer[10];
char adcBuffer0[16];

uint16_t detector;

float discrThresh;
float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
float DET0_temp, DET1_temp, DET2_temp, DET3_temp;
float length;
float fvalue;


/*hashtable variables*/
float* mode;
float *mode5Calibration;
float* VDET0;
float* VDET1;
float *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin;
float *TECcntr, *AnDET;
float *DthrEd, *DthrSt;
float *TempSt,*TempEd;
float *VoltSt, *VoltEd, *DNum;
float *kp, *ki, *kd; //PID coefficients
float *countTime;
float *targetTECFlag0;
float *targetTECFlag1, *printMessageFlag, *printThermalFlag;
float *Exit;

/*end of hashtable variable declaration*/

volatile bool coincWindowSetFlag = 0;
int coincWindowValue;
volatile bool TerminalCommunicationFlag = 1;
float startVoltage, endVoltage;
volatile bool delay0SetFlag = 0, delay1SetFlag = 0, delay2SetFlag = 0, delay3SetFlag = 0;
int delay0Value, delay1Value, delay2Value, delay3Value;

char voltageArray[3];
char temperatureArray[3];
char discrThreshArray[4];
char lengthArray[4];

unsigned int table_size = 50;
struct node *hash_table;
char HashValue[20];


#endif /* MAINHEADER_H_ */
