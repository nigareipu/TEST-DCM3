/******************************************************************************
 * File Name:   function.h
 *
 * Description: Contains all function declarations for operation of SEAQUE DCM
 *
 * Author: Joanna Krynski
 *
 * Date: April 20, 2022
 *
 *******************************************************************************/

#include <stdint.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

/*************************  MACROS  *******************************************/

#define DATA_BITS_8 8
#define STOP_BITS_1 1
#define BAUD_RATE 115200
#define UART_DELAY 10u
#define RX_BUF_SIZE 255
#define TX_BUF_SIZE 255

#define ON (1u)
#define OFF (0u)

/*************************  GLOBAL FUNCTION  **********************************/
void print();
void Board_Init();
