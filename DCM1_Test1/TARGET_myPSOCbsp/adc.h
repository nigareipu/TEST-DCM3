
#ifndef TARGET_MYPSOCBSP_ADC_H_
#define TARGET_MYPSOCBSP_ADC_H_

#include <stdint.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "modes.h"

// ADC channels
#define hvmoni0channel 0UL
#define hvmoni3channel 1UL
#define thermread0channel 2UL
#define thermread1channel 3UL
#define thermread2channel 4UL
#define thermread3channel 5UL
#define ITEC0channel 6UL
#define ITEC1channel 7UL

// Globals

/*extern float HVMoni0;
extern float HVMoni3;
extern float ThermRead0;
extern float ThermRead1;
extern float ThermRead2;
extern float ThermRead3;*/
extern float ITEC0_V;
extern float ITEC1_V;
extern float *HVMoni0, *HVMoni3, *ThermRead0, *ThermRead1, *ThermRead2, *ThermRead3, *ITEC0, *ITEC1;

extern cy_stc_scb_uart_context_t uartContext;

// Functions
void ADC_Init();
void HV0_Monitor(void);
void HV3_Monitor(void);
void Therm0_Read(void);
void Therm1_Read(void);
void Therm2_Read(void);
void Therm3_Read(void);
void GetAllThermRead(void);
void ITEC0_Read(void);
void ITEC1_Read(void);

#endif /* TARGET_MYPSOCBSP_ADC_H_ */
