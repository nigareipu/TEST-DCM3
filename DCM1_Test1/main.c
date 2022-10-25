/******************************************************************************
 * File Name:   main.c
  Author: Nigar Sultana*
 * Date: October 24th 2022
 *
 *******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "serialUART.h"
#include "uartInterrupt.h"
#include "functions.h"
#include "AD56x8.h"
#include "dac.h"
#include "spi.h"
#include "tec.h"
#include "adc.h"//Not touching up to here
#include "det_bias.h"
#include "discr.h"
#include "coin_window.h"
#include "delay.h"
#include "mode1.h"
#include "mode2.h"
#include "mode3.h"
#include "mode4.h"
#include "mode6.h"
#include "mode7.h"
#include "table.h"
#include "commands.h"
//#include "allocate.h"


/***************************  DEFINITIONS  *************************************/

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
char confirmInputValue[32];
char confirmConvertedValue[32];
char confirmdacValue[32];
char *ptr;
uint32_t value;

int idx;
volatile int count;
volatile bool uartRxCompleteFlag; // flag for notifying that the rx buffer is not empty
volatile bool flag_1;			  // flag for notifying that the rx buffer is full and receiving is complete.
volatile bool printThermalInfo;	  // option to print all thermread data
volatile bool ThermStabilize;	  // option to do 30 s thermal stabilization. Must be set to 1 initially during first measurements.
//volatile bool timer_interrupt_flag = false;// flag for timer interrupt
volatile bool warningFlag = 1; // flag for printing warnings before mode is set. Must be set to 1 to print information.

cyhal_spi_t DiscrDAC_obj;
cyhal_spi_t HVDAC_obj;
uint8_t spi_buf[SPI_BUFFER_SIZE];
uint32_t dacDataPacket;
uint16_t dacValue;

float inputVoltage;

uint8_t receive_data[SPI_BUFFER_SIZE];

cy_stc_scb_uart_context_t uartContext;

cy_rslt_t result;
cyhal_timer_t timer_obj;

// ADC and channel object//
cyhal_adc_t adc_obj;

char adcBuffer[10];
char adcBuffer0[16];

uint16_t detector;

float discrThresh;
float DET0_voltage, DET1_voltage, DET2_voltage, DET3_voltage;
float DET0_temp, DET1_temp, DET2_temp, DET3_temp;
float length;
float fvalue;


/*New hashtable variables*/
float* mode;
float* VDET0;
float* VDET1;
float *VDET2, *VDET3, *TDET0, *TDET1, *TDET2, *TDET3, *RTime, *DThrs;
float *DlayDET0, *DlayDET1, *DlayDET2, *DlayDET3, *CoWin;
float* AnDET;
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

int main(void)
{

	Init_Hardware();
	configureUART_Isr();
	Cy_SCB_UART_Enable(UART_HW); // Enable UART to operate

	// enable all interrupts
	__enable_irq();


	 /* ***********Timer code******************************
	 ************************************************** */

	//cyhal_timer_event_interrupt();

  // Read the current timer value, which should be close to the amount of delay in ms * 10 (5000)

  Cy_SCB_UART_PutString(UART_HW, "Timer interrupt testing\n ");


	/*****************************************************************
	 * Initialize all peripherals
	 * ***************************************************************
	 */


	DiscrDAC_SPI_Init();
	setDiscrDACInternalRef();
	HVDAC_SPI_Init();
	setHVDACInternalRef();
	CoincidenceWindow_Init();
	SingleSide_Init();
	Delays_Init();
	ADC_Init();
	TEC_Driver0_Init(0);
	TEC_Driver1_Init(0);
	TEC_SW0_Init(0);
	TEC_SW1_Init(0);
	TEC_SW2_Init(0);
	TEC_SW3_Init(0);
	SinglesCounter0_Init();
	SinglesCounter1_Init();
	SinglesCounter2_Init();
	SinglesCounter3_Init();
	CoincidenceCounter0_Init();
	CoincidenceCounter1_Init();
	CoincidenceCounter2_Init();
	CoincidenceCounter3_Init();

	StartCounters();

	// Upon RESET, re-iterate that in IDLE MODE
	// Should probably check in actuality if in Idle mode..

	/***********************************Table Allocation********************************/
	//Cy_SCB_UART_PutString(UART_HW, "\r\nCurrently in IDLE MODE.\r\n ");
	mode1program();


	Cy_SCB_UART_PutString(UART_HW, "\r\nRight Before allocation function");
	default_hashtable();

	Cy_SCB_UART_PutString(UART_HW, "I'm here after table\r\n");
	Cy_SCB_UART_PutString(UART_HW, "\r\n About to go into modes = ");
	sprintf(confirmValue, "%f\r\n", *mode);
	Cy_SCB_UART_PutString(UART_HW, confirmValue);
	Cy_SCB_UART_PutString(UART_HW, "V\r\n");


	// Setting the Communication Input Mode to Automated or Manual

	for (;;)
	{

		// If something has been typed, show that character on the terminal
		if (uartRxCompleteFlag == 1)
		{
			echoInput();


			// If the user starts a new line, process the command
			if (*rxBuffer == '\n' || *rxBuffer == '\r')
			{

				Cy_SCB_UART_PutString(UART_HW, "*VDET0: \r\n");
				sprintf(confirmValue, "%f", *VDET0);
				Cy_SCB_UART_PutString(UART_HW, confirmValue);
				Cy_SCB_UART_PutString(UART_HW, " V\r\n");

				Cy_SCB_UART_PutString(UART_HW, "DiscrThresh: \r\n");
								sprintf(confirmValue, "%f", discrThresh);
								Cy_SCB_UART_PutString(UART_HW, confirmValue);
								Cy_SCB_UART_PutString(UART_HW, " V\r\n");


				// Divide incoming buffer into command and value sections (ex. first 4 bits are for command and last 4 are for value)
				// Will only work with terminal connected to it, without it tho all default values should still go through
				// commandBuffer = strtok(storeBuffer, ";");
				// valueBuffer = strtok(NULL, ";");
				// fvalue = atof(valueBuffer);
				//*command = fvalue;
				// update_table(commandBuffer, fvalue);

				// String comparison. List of possible commands and values are compared to invoke the proper function and arguments.

				// float* mode = allocate_node(hash_table, table_size, sizeof(float), "mode");

				if (*mode == 1)
				{
					// CODE RUNNING IDLE MODE
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to 1\r\n");
					mode1program();
				}
				else if (*mode == 2)
				{
					// CODE RUNNING TWO SIDE COINCIDENCE COUNTING MODE
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 2\r\n");
					mode2program();
				}
				else if (*mode == 3)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 3\r\n");
					mode3program();
				}
				else if (*mode == 4)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 4\r\n");
					mode4program();
				}
				else if (*mode == 6)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 6\r\n");
					mode6program();
				}
				else if (*mode == 5)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 6\r\n");
					mode5program();
				}
				else if (*mode == 7)
				{
					// CODE RUNNING SET MODE to ACCIDENTAL COUNTING
					Cy_SCB_UART_PutString(UART_HW, "I was able to pass to mode 7\r\n");
					mode7program();
				}



				else
				{
					//mode1program();
					Cy_SCB_UART_PutString(UART_HW, "\r\n Not valid value\r\n");
					Cy_SCB_UART_PutString(UART_HW, "Choose command and value\r\n");
					uartRxCompleteFlag = 0;
					count = 0;
				}
			}

			// If user types something other than newline or return, put the chars into the buffer
			else
			{
				fillBuffer();
			}
		}

		// Occaisionally, if nothing incoming in buffer, then send temperature data.
	}
}
