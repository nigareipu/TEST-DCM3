/*
 * allocate.c *
 *  Created on: Oct. 25, 2022
 *  Author: n6sultan
 */

#include "allocate.h"

void default_hashtable()
{

	hash_table = initialize_table(table_size);

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

	*mode = 2;
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
	*DlayDET0 = 1;
	*DlayDET1= 1;
	*DlayDET2= 1;
	*DlayDET3= 1;
	*CoWin = 1;
	*AnDET = 0;
	*DthrEd = 0.2;
	*DthrSt = 1.10;
	*TempSt = 0.9 ;
	*TempEd = 1.35 + 0.01;
	*VoltSt = 260;
	*VoltEd = 370;

}

