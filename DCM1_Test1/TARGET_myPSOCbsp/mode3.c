/*
 * mode3.c
 *
 *  Created on: May 19, 2022
 *      Author: jkrynski1
 */

#include "mode2.h"

void mode3program()
{

    float DET_gradual_increase[] = {0, 0, 0, 0};
    float DET_bias[] = {*VDET0, *VDET1, *VDET2, *VDET3};
    unsigned int DET[] = {DET0, DET1, DET2, DET3};

    Cy_SCB_UART_PutString(UART_HW, "SET MODE to ACCIDENTAL COUNTING\r\n");
    printThermalInfo = 1;

    /*****************************Test Pritning*************************/
    // if (printfeedbackFlag == 1){
    Cy_SCB_UART_PutString(UART_HW, "*VDET0: ");
    printFloat(*VDET0);

    Cy_SCB_UART_PutString(UART_HW, "*VDET1: ");
    printFloat(*VDET1);

    Cy_SCB_UART_PutString(UART_HW, "*VDET2: ");
    printFloat(*VDET2);

    Cy_SCB_UART_PutString(UART_HW, "*VDET3: ");
    printFloat(*VDET3);

    Cy_SCB_UART_PutString(UART_HW, "TDET0: ");
    printFloat(*TDET0);

    Cy_SCB_UART_PutString(UART_HW, "Runtime :");
    printFloat(*RTime);

    Cy_SCB_UART_PutString(UART_HW, "\r\n discriminator threshold:  ");
    printFloat(*DThrs);

    /*****************************TEst printing***************************/
    // sets discriminator threshold
    setDiscr0Thresh(*DThrs);
    setDiscr1Thresh(*DThrs);
    setDiscr2Thresh(*DThrs);
    setDiscr3Thresh(*DThrs);

    // Turns on TEC driver and switches

    TEC_SW0_Status(ON);
    TEC_SW1_Status(ON);
    TEC_SW2_Status(ON);
    TEC_SW3_Status(ON);
    TEC_Driver0_Status(ON); // 0 OFF, 1 ON; changes status of tecStatusFlag
    TEC_Driver1_Status(ON);

    // sets coincidence channel, window and delay
    SingleSide_Set(1, 1); // sets coin0-> 0&1 and coin1->2&3; but Want 12, 01, 23, 03
    setCoincidenceWindowCommand(*CoWin);
    setDelay0Command(*DlayDET0);
    setDelay1Command(*DlayDET1);
    setDelay2Command(*DlayDET2);
    setDelay3Command(*DlayDET3);

    StabilizeAllTemp(*TDET0);

    if (*rxBuffer == 'q')
    {
        Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
        uartRxCompleteFlag = 0;
        count = 0;
        return;
    }

    // Slowly ramp up voltages
    // Set voltage of detectors gradually

    for (int i = 0; i <= 3; i++)
    {
        while (DET_gradual_increase[i] < DET_bias[i])
        {

            SetDetectorVoltage(DET[i], DET_gradual_increase[i]);
            DET_gradual_increase[i] = DET_gradual_increase[i] + 10;
            cyhal_system_delay_ms(1);
        }
        Cy_SCB_UART_PutString(UART_HW, "detector voltage :");
        printFloat(DET_bias[i]);
        SetDetectorVoltage(DET[i], DET_bias[i]);
    }

    HV0_Monitor();
    cyhal_system_delay_ms(500); // required delay
    HV3_Monitor();
    cyhal_system_delay_ms(500); // required delay

    Cy_SCB_UART_PutString(UART_HW, "\r\nSingle Count Rate 0, 1, 2, 3, Coincidence 1&2, 0&1, 2&3, 0&3\r\n");


    //Starts counting
    for (int k = 0; k < *RTime; k++)
    {
    	if (*Exit == 1)
		{
			Cy_SCB_UART_PutString(UART_HW, "Exiting\r\n");
			break;
		}

        UpdateAllTemp(*TDET0);
        startCounting();
        cyhal_system_delay_ms(1000);
    }

    mode1program();
}
