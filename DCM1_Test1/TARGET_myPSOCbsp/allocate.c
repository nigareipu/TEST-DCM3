/*
 * allocate.c *
 *  Created on: Oct. 25, 2022
 *  Author: n6sultan
 */

#include "allocate.h"

void default_hashtable()
{

	hash_table = initialize_table(table_size);
	Cy_SCB_UART_PutString(UART_HW, "\r\ninside hash table\r\n");
	// Allocating space to each Key
    mode = allocate_node(hash_table, table_size, sizeof(float), "mode");
    VDET0 = allocate_node(hash_table, table_size, sizeof(float), "VDET0");
    VDET1 = allocate_node(hash_table, table_size, sizeof(float), "VDET1");
    VDET2 = allocate_node(hash_table, table_size, sizeof(float), "VDET2");
	VDET3 = allocate_node(hash_table, table_size, sizeof(float), "VDET3");
    TDET0 = allocate_node(hash_table, table_size, sizeof(float), "TDET0");
	TDET1 = allocate_node(hash_table, table_size, sizeof(float), "TDET1");
	TDET2 = allocate_node(hash_table, table_size, sizeof(float), "TDET2");
	TDET3 = allocate_node(hash_table, table_size, sizeof(float), "TDET3");
	RTime = allocate_node(hash_table, table_size, sizeof(float), "length");
	DThrs = allocate_node(hash_table, table_size, sizeof(float), "DThrs");
	DlayDET0 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET0");
	DlayDET1 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET1");
	DlayDET2 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET2");
	DlayDET3 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET3");
	CoWin = allocate_node(hash_table, table_size, sizeof(float), "CoWin");
	AnDET = allocate_node(hash_table, table_size, sizeof(float), "AnDET");
	DthrEd = allocate_node(hash_table, table_size, sizeof(float), "DthrEd");
	DthrSt = allocate_node(hash_table, table_size, sizeof(float), "DthrSt");
	TempSt = allocate_node(hash_table, table_size, sizeof(float), "TempSt");
	TempEd = allocate_node(hash_table, table_size, sizeof(float), "TempEd");
	VoltSt = allocate_node(hash_table, table_size, sizeof(float), "VoltSt");
	VoltEd = allocate_node(hash_table, table_size, sizeof(float), "VoltEd");
	Exit = allocate_node(hash_table, table_size, sizeof(float), "Exit");

	Cy_SCB_UART_PutString(UART_HW, "\r\n after allocation \r\n");

	*mode = 5;
	*VDET0 = 312;
	*VDET1 = 337;
	*VDET2 = 376;
	*VDET3 = 373;
	*TDET0 = 0.85;
	*TDET1 = 0.85;
	*TDET2 = 0.85;
	*TDET3 = 0.85;
	*RTime = 120;
	*DThrs = 0.05;
	*DlayDET0 = 0;
	*DlayDET1= 3;
	*DlayDET2= 2;
	*DlayDET3= 1;
	*CoWin = 3;
	*AnDET = 0;
	*DthrEd = 1.10;
	*DthrSt = 0.2;
	*TempSt = 0.85 ;
	*TempEd = 1.05;
	*Exit=0;
	*VoltSt = 300;
	*VoltEd = 310;
	Cy_SCB_UART_PutString(UART_HW, "\r\n after value assignement \r\n");

}

