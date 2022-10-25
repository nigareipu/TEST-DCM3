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

uint32_t prevCount0;
uint32_t prevCount1;
uint32_t prevCount2;
uint32_t prevCount3;

uint32_t prevCoinCount0;
uint32_t prevCoinCount1;
uint32_t prevCoinCount2;
uint32_t prevCoinCount3;

/*
 * @desc Initialize and start Singles 0 counter
 * @returns Nothing
 */
void SinglesCounter0_Init(void)
{

	cy_en_tcpwm_status_t SinglesCounter0_Status;

	// Initialize Singles_0 created in PDL, see code in device configurator for appropriate values*/
	SinglesCounter0_Status = Cy_TCPWM_Counter_Init(Singles_0_HW, Singles_0_NUM, &Singles_0_config);
	if (SinglesCounter0_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Singles0 Counter Initialized\r\n");
	}
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

	cy_en_tcpwm_status_t SinglesCounter1_Status;
	/*Initialize Singles_0 created in PDL, see code in device configurator for appropriate values*/
	SinglesCounter1_Status = Cy_TCPWM_Counter_Init(Singles_1_HW, Singles_1_NUM, &Singles_1_config);
	Cy_TCPWM_Counter_Enable(Singles_1_HW, Singles_1_NUM);
	if (SinglesCounter1_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Singles1 Counter Initialized\r\n");
	}

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_1_HW, Singles_1_NUM);
}

/*
 * @desc Initialize and start Singles 2 counter
 * @returns Nothing
 */
void SinglesCounter2_Init(void)
{
	cy_en_tcpwm_status_t SinglesCounter2_Status;
	/*Initialize Singles_1 created in PDL, see code in device configurator for appropriate values*/
	SinglesCounter2_Status = Cy_TCPWM_Counter_Init(Singles_2_HW, Singles_2_NUM, &Singles_2_config);
	Cy_TCPWM_Counter_Enable(Singles_2_HW, Singles_2_NUM);
	if (SinglesCounter2_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Singles2 Counter Initialized\r\n");
	}

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_2_HW, Singles_2_NUM);
}

/*
 * @desc Initialize and start Singles 3 counter
 * @returns Nothing
 */
void SinglesCounter3_Init(void)
{
	cy_en_tcpwm_status_t SinglesCounter3_Status;
	/*Initialize Singles_1 created in PDL, see code in device configurator for appropriate values*/
	SinglesCounter3_Status = Cy_TCPWM_Counter_Init(Singles_3_HW, Singles_3_NUM, &Singles_3_config);
	Cy_TCPWM_Counter_Enable(Singles_3_HW, Singles_3_NUM);
	if (SinglesCounter3_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Singles3 Counter Initialized\r\n");
	}

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Singles_3_HW, Singles_3_NUM);
}

/*
 * @desc Initialize and start coincidence counter 0
 * @returns Nothing
 */
void CoincidenceCounter0_Init(void)
{

	cy_en_tcpwm_status_t CoincidenceCounter0_Status;

	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	CoincidenceCounter0_Status = Cy_TCPWM_Counter_Init(Coinc_0_HW, Coinc_0_NUM, &Coinc_0_config);

	if (CoincidenceCounter0_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Coincidence0 Counter Initialized\r\n");
	}
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
	cy_en_tcpwm_status_t CoincidenceCounter1_Status;

	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	CoincidenceCounter1_Status = Cy_TCPWM_Counter_Init(Coinc_1_HW, Coinc_1_NUM, &Coinc_1_config);
	if (CoincidenceCounter1_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Coincidence1 Counter Initialized\r\n");
	}
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
	cy_en_tcpwm_status_t CoincidenceCounter2_Status;

	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	CoincidenceCounter2_Status = Cy_TCPWM_Counter_Init(Coinc_2_HW, Coinc_2_NUM, &Coinc_2_config);
	Cy_TCPWM_Counter_Enable(Coinc_2_HW, Coinc_2_NUM);
	if (CoincidenceCounter2_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Coincidence2 Counter Initialized\r\n");
	}

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_2_HW, Coinc_2_NUM);
}

/*
 * @desc Initialize and start coincidence counter 3
 * @returns Nothing
 */
void CoincidenceCounter3_Init(void)
{
	cy_en_tcpwm_status_t CoincidenceCounter3_Status;

	/*Initialize Coincidence counter created in PDL, see code in device configurator for appropriate values*/
	CoincidenceCounter3_Status = Cy_TCPWM_Counter_Init(Coinc_3_HW, Coinc_3_NUM, &Coinc_3_config);
	Cy_TCPWM_Counter_Enable(Coinc_3_HW, Coinc_3_NUM);
	if (CoincidenceCounter3_Status == 0)
	{
		// Cy_SCB_UART_PutString(UART_HW,"Coincidence0 Counter Initialized\r\n");
	}

	/*Start counter*/
	Cy_TCPWM_TriggerStart_Single(Coinc_3_HW, Coinc_3_NUM);
}

/*
 * @desc Reads the current singles count at counter 0 and subtracts previous counts. So finds the
 * number of counts between the last reading and the current reading
 * @param uint32_t* prevCount0 - The number of counts prior to performing this read
 * @returns Nothing
 */
void SinglesCounter0_Read(uint32_t *prevCount0)
{

	uint32_t readcount0 = Cy_TCPWM_Counter_GetCounter(Singles_0_HW, Singles_0_NUM);
	Singles0_CountRate = readcount0 - *prevCount0;

	*prevCount0 = readcount0;

	// Cy_SCB_UART_PutString(UART_HW,"SinglesCounter0_Read = ");
	// sprintf(confirmValue,"%lu",Singles0_CountRate);
	// Cy_SCB_UART_PutArray(UART_HW,confirmValue,10);
}

/*
 * @desc Reads the current singles count at counter 1 and subtracts previous counts. So finds the
 * number of counts between the last reading and the current reading
 * @param uint32_t* prevCount1 - The number of counts prior to performing this read
 * @returns Nothing
 */
void SinglesCounter1_Read(uint32_t *prevCount1)
{

	// printf("prevCount0 = %lu\r\n",*prevCount0);
	uint32_t readcount1 = Cy_TCPWM_Counter_GetCounter(Singles_1_HW, Singles_1_NUM);
	// printf("readcount0 = %lu\r\n",readcount0);
	Singles1_CountRate = readcount1 - *prevCount1;
	// printf("Singles 0 count rate = %lu\r\n",Singles0_CountRate);
	*prevCount1 = readcount1;
	// printf("new prevCount0 = %lu\r\n",*prevCount0);

	// return Singles1_CountRate;
}

/*
 * @desc Reads the current singles count at counter 2 and subtracts previous counts. So finds the
 * number of counts between the last reading and the current reading
 * @param uint32_t* prevCount2 - The number of counts prior to performing this read
 * @returns Nothing
 */
void SinglesCounter2_Read(uint32_t *prevCount2)
{

	uint32_t readcount2 = Cy_TCPWM_Counter_GetCounter(Singles_2_HW, Singles_2_NUM);

	Singles2_CountRate = readcount2 - *prevCount2;

	*prevCount2 = readcount2;

	// return Singles2_CountRate;
}

/*
 * @desc Reads the current singles count at counter 3 and subtracts previous counts. So finds the
 * number of counts between the last reading and the current reading
 * @param uint32_t* prevCount3 - The number of counts prior to performing this read
 * @returns Nothing
 */
void SinglesCounter3_Read(uint32_t *prevCount3)
{

	uint32_t readcount3 = Cy_TCPWM_Counter_GetCounter(Singles_3_HW, Singles_3_NUM);

	Singles3_CountRate = readcount3 - *prevCount3;

	*prevCount3 = readcount3;

	// return Singles3_CountRate;
}

/*
 * @desc Reads the current coincidence count at counter 0 and subtracts previous coincidence counts.
 * So finds the number of coincidence counts between the last reading and the current reading
 * @param uint32_t* prevCoinCount0 - The number of coincidence counts prior to performing this read
 * @returns Nothing
 */
void CoincidenceCounter0_Read(uint32_t *prevCoinCount0)
{

	uint32_t readCoincount0 = Cy_TCPWM_Counter_GetCounter(Coinc_0_HW, Coinc_0_NUM);

	Coincidence0_CountRate = readCoincount0 - *prevCoinCount0;

	*prevCoinCount0 = readCoincount0;

	/*char coin0_readArray[10] = {0,0,0,0,0,0,0,0,0,0};
	sprintf(coin0_readArray,",%lu,",readCoincount0);
	Cy_SCB_UART_PutArray(UART_HW,coin0_readArray,5);*/

	// return Coincidence0_CountRate;
}

/*
 * @desc Reads the current coincidence count at counter 1 and subtracts previous coincidence counts.
 * So finds the number of coincidence counts between the last reading and the current reading
 * @param uint32_t* prevCoinCount1 - The number of coincidence counts prior to performing this read
 * @returns Nothing
 */
void CoincidenceCounter1_Read(uint32_t *prevCoinCount1)
{

	uint32_t readCoincount1 = Cy_TCPWM_Counter_GetCounter(Coinc_1_HW, Coinc_1_NUM);

	Coincidence1_CountRate = readCoincount1 - *prevCoinCount1;

	*prevCoinCount1 = readCoincount1;

	/*char coin1_readArray[10] = {0,0,0,0,0,0,0,0,0,0};
	sprintf(coin1_readArray,",%lu,",readCoincount1);
	Cy_SCB_UART_PutArray(UART_HW,coin1_readArray,5);*/

	// return Coincidence1_CountRate;
}

/*
 * @desc Reads the current coincidence count at counter 2 and subtracts previous coincidence counts.
 * So finds the number of coincidence counts between the last reading and the current reading
 * @param uint32_t* prevCoinCount2 - The number of coincidence counts prior to performing this read
 * @returns Nothing
 */
void CoincidenceCounter2_Read(uint32_t *prevCoinCount2)
{

	uint32_t readCoincount2 = Cy_TCPWM_Counter_GetCounter(Coinc_2_HW, Coinc_2_NUM);

	Coincidence2_CountRate = readCoincount2 - *prevCoinCount2;

	*prevCoinCount2 = readCoincount2;

	/*char coin2_readArray[10] = {0,0,0,0,0,0,0,0,0,0};
	sprintf(coin2_readArray,",%lu,",readCoincount2);
	Cy_SCB_UART_PutArray(UART_HW,coin2_readArray,5);*/

	// return Coincidence2_CountRate;
}

/*
 * @desc Reads the current coincidence count at counter 3 and subtracts previous coincidence counts.
 * So finds the number of coincidence counts between the last reading and the current reading
 * @param uint32_t* prevCoinCount3 - The number of coincidence counts prior to performing this read
 * @returns Nothing
 */
void CoincidenceCounter3_Read(uint32_t *prevCoinCount3)
{

	uint32_t readCoincount3 = Cy_TCPWM_Counter_GetCounter(Coinc_3_HW, Coinc_3_NUM);

	Coincidence3_CountRate = readCoincount3 - *prevCoinCount3;

	*prevCoinCount3 = readCoincount3;

	/*char coin3_readArray[10] = {0,0,0,0,0,0,0,0,0,0};
	sprintf(coin3_readArray,",%lu,",readCoincount3);
	Cy_SCB_UART_PutArray(UART_HW,coin3_readArray,5);*/

	// return Coincidence3_CountRate;
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

/*
 * @desc Prints previous and current SysTick value, and the difference between them
 * @param uint32_t* prevTick - Previous value of SysTick
 * @returns Nothing
 */
void getSysTick(uint32_t *prevTick)
{

	// printf("prevTick = %lu\r\n",*prevTick);
	sysTick = Cy_SysTick_GetValue();
	// printf("sysTick = %lu\r\n",sysTick);
	deltaTick = sysTick - *prevTick + 10000000;
	// printf("deltaTick = %lu\r\n", deltaTick);
	*prevTick = sysTick;
	// printf("new prevTick = %lu\r\n",*prevTick);
}

/*
 * @desc Gets an initial count and coincidence count from each counter
 * @returns Nothing
 */
void StartCounters()
{

	/*char prevCount0Array[10];
	char prevCount1Array[10];
	char prevCount2Array[10];
	char prevCount3Array[10];

	char prevCoinCount0Array[10];
	char prevCoinCount1Array[10];
	char prevCoinCount2Array[10];
	char prevCoinCount3Array[10];*/

	// uint8_t test[5] = {1,2,3,4,5};

	// char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	//next four lines added by Nigar to see if the initial random counts goes to zero
	Cy_TCPWM_Counter_Init(Singles_0_HW, Singles_0_NUM, &Singles_0_config);
	Cy_TCPWM_Counter_Init(Singles_1_HW, Singles_1_NUM, &Singles_1_config);
	Cy_TCPWM_Counter_Init(Singles_2_HW, Singles_2_NUM, &Singles_2_config);
	Cy_TCPWM_Counter_Init(Singles_3_HW, Singles_3_NUM, &Singles_3_config);



	prevCount0 = Cy_TCPWM_Counter_GetCounter(Singles_0_HW, Singles_0_NUM);
	prevCount1 = Cy_TCPWM_Counter_GetCounter(Singles_1_HW, Singles_1_NUM);
	prevCount2 = Cy_TCPWM_Counter_GetCounter(Singles_2_HW, Singles_2_NUM);
	prevCount3 = Cy_TCPWM_Counter_GetCounter(Singles_3_HW, Singles_3_NUM);

	prevCoinCount0 = Cy_TCPWM_Counter_GetCounter(Coinc_0_HW, Coinc_0_NUM);
	prevCoinCount1 = Cy_TCPWM_Counter_GetCounter(Coinc_1_HW, Coinc_1_NUM);
	prevCoinCount2 = Cy_TCPWM_Counter_GetCounter(Coinc_2_HW, Coinc_2_NUM);
	prevCoinCount3 = Cy_TCPWM_Counter_GetCounter(Coinc_3_HW, Coinc_3_NUM);

	if (prevCoinCount0 == 0)
	{

		// Cy_SCB_UART_PutString(UART_HW,"prevCoinCount0 =");
		// sprintf(prevCount0Array,"%lu",prevCount0);
		// Cy_SCB_UART_PutArray(UART_HW,prevCount0Array,10);
	}
}

/*
 * @desc Prints the current singles 0 counts
 * @returns Nothing
 */
void GetSingles0Counts()
{

	char Singles0_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	SinglesCounter0_Read(&prevCount0);
	sprintf(Singles0_CountRateArray, "%lu,", Singles0_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles0_CountRateArray, strlen(Singles0_CountRateArray));
}

/*
 * @desc Prints the current singles 1 counts
 * @returns Nothing
 */
void GetSingles1Counts()
{

	char Singles1_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	SinglesCounter1_Read(&prevCount1);
	sprintf(Singles1_CountRateArray, "%lu,", Singles1_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles1_CountRateArray, strlen(Singles1_CountRateArray));
}

/*
 * @desc Prints the current singles 2 counts
 * @returns Nothing
 */
void GetSingles2Counts()
{

	char Singles2_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	SinglesCounter2_Read(&prevCount2);
	sprintf(Singles2_CountRateArray, "%lu,", Singles2_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles2_CountRateArray, strlen(Singles2_CountRateArray));
}

/*
 * @desc Prints the current singles 3 counts
 * @returns Nothing
 */
void GetSingles3Counts()
{

	char Singles3_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	SinglesCounter3_Read(&prevCount3);
	sprintf(Singles3_CountRateArray, "%lu,", Singles3_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles3_CountRateArray, strlen(Singles3_CountRateArray));
}

/*
 * @desc Prints the current coincidence 0 counts
 * @returns Nothing
 */
void GetCoincidence0Counts()
{

	char Coincidence0_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	CoincidenceCounter0_Read(&prevCoinCount0);
	sprintf(Coincidence0_CountRateArray, "%lu,", Coincidence0_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Coincidence0_CountRateArray, strlen(Coincidence0_CountRateArray));
}

/*
 * @desc Prints the current coincidence 1 counts
 * @returns Nothing
 */
void GetCoincidence1Counts()
{

	char Coincidence1_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	CoincidenceCounter1_Read(&prevCoinCount1);
	sprintf(Coincidence1_CountRateArray, "%lu,", Coincidence1_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Coincidence1_CountRateArray,strlen(Coincidence1_CountRateArray));
}

/*
 * @desc Prints the current coincidence 2 counts
 * @returns Nothing
 */
void GetCoincidence2Counts()
{

	char Coincidence2_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	CoincidenceCounter2_Read(&prevCoinCount2);
	sprintf(Coincidence2_CountRateArray, "%lu,", Coincidence2_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Coincidence2_CountRateArray, strlen(Coincidence2_CountRateArray));
}

/*
 * @desc Prints the current coincidence 3 counts
 * @returns Nothing
 */
void GetCoincidence3Counts()
{

	char Coincidence3_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	CoincidenceCounter3_Read(&prevCoinCount3);
	sprintf(Coincidence3_CountRateArray, "%lu,", Coincidence3_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Coincidence3_CountRateArray, strlen(Coincidence3_CountRateArray));
}

/*
 * @desc Prints all the current singles counts
 * @returns Nothing
 */
void GetAllSinglesCounts()
{

	char Singles0_CountRateArray[10];
	char Singles1_CountRateArray[10];
	char Singles2_CountRateArray[10];
	char Singles3_CountRateArray[10];

	SinglesCounter0_Read(&prevCount0);
	sprintf(Singles0_CountRateArray, "%lu,", Singles0_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles0_CountRateArray, 2);

	SinglesCounter1_Read(&prevCount1);
	sprintf(Singles1_CountRateArray, "%lu,", Singles1_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles1_CountRateArray, 2);

	SinglesCounter2_Read(&prevCount2);
	sprintf(Singles2_CountRateArray, "%lu,", Singles2_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles2_CountRateArray, 2);

	SinglesCounter3_Read(&prevCount3);
	sprintf(Singles3_CountRateArray, "%lu,", Singles3_CountRate);
	Cy_SCB_UART_PutArray(UART_HW, Singles3_CountRateArray, 2);
}

/*
 * @desc Prints all of the current single and coincidence counts
 * @returns Nothing
 */
void GetAllCounts()
{

	char Singles0_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Singles1_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Singles2_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Singles3_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Coincidence0_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Coincidence1_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Coincidence2_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char Coincidence3_CountRateArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cyhal_system_delay_ms(1000);

	for (int i = 0; i <= 100; i++)
	{

		SinglesCounter0_Read(&prevCount0);
		sprintf(Singles0_CountRateArray, "%lu,", Singles0_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Singles0_CountRateArray, 2);

		SinglesCounter1_Read(&prevCount1);
		sprintf(Singles1_CountRateArray, "%lu,", Singles1_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Singles1_CountRateArray, 2);

		SinglesCounter2_Read(&prevCount2);
		sprintf(Singles2_CountRateArray, "%lu,", Singles2_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Singles2_CountRateArray, 2);

		SinglesCounter3_Read(&prevCount3);
		sprintf(Singles3_CountRateArray, "%lu,", Singles3_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Singles3_CountRateArray, 2);

		CoincidenceCounter0_Read(&prevCoinCount0);
		sprintf(Coincidence0_CountRateArray, "%lu,", Coincidence0_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Coincidence0_CountRateArray, 2);

		CoincidenceCounter1_Read(&prevCoinCount1);
		sprintf(Coincidence1_CountRateArray, "%lu,", Coincidence1_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Coincidence1_CountRateArray, 2);

		CoincidenceCounter2_Read(&prevCoinCount2);
		sprintf(Coincidence2_CountRateArray, "%lu,", Coincidence2_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Coincidence2_CountRateArray, 2);

		CoincidenceCounter3_Read(&prevCoinCount3);
		sprintf(Coincidence3_CountRateArray, "%lu,", Coincidence3_CountRate);
		Cy_SCB_UART_PutArray(UART_HW, Coincidence3_CountRateArray, 2);

		Cy_SCB_UART_PutString(UART_HW, "\r\n");

		cyhal_system_delay_ms(1000);
	}
}
