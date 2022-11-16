/*
 * allocate.c *
 *  Created on: Oct. 25, 2022
 *  Author: n6sultan
 */

#include "allocate.h"

struct TNODE table[TABLE_SIZE];

void default_hashtable()
{
	struct TNODE* n_node;
	memset(table, '\0', TABLE_SIZE); // Ensure all fields are 0, including data pointer is set to NULL


	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "mode");
	mode = n_node->data;
	*mode = 1;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "DThrs");
	DThrs = n_node->data;
	*DThrs = 0.05;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "mode5Calibration");
	mode5Calibration = n_node->data;
	*mode5Calibration = 2;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VDET0");
	VDET0 = n_node->data;
	*VDET0 = 294;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VDET1");
	VDET1 = n_node->data;
	*VDET1 = 290;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VDET2");
	VDET2 = n_node->data;
	*VDET2 = 295;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VDET3");
	VDET3 = n_node->data;
	*VDET3 = 310;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TDET0");
	TDET0 = n_node->data;
	*TDET0 = 0.85;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TDET1");
	TDET1 = n_node->data;
	*TDET1 = 0.85;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TDET2");
	TDET2 = n_node->data;
	*TDET2 = 0.85;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TDET3");
	TDET3 = n_node->data;
	*TDET3 = 0.85;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint16_t), "TempStabilizationDlay");//need before each counting
	TempStabilizationDlay = n_node->data;
	*TempStabilizationDlay = 30000; //ms
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT16;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "RTime");
	RTime = n_node->data;
	*RTime = 60;  //seconds
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DlayDET0");
	DlayDET0 = n_node->data;
	*DlayDET0 = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DlayDET1");
	DlayDET1 = n_node->data;
	*DlayDET1 = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DlayDET2");
	DlayDET2 = n_node->data;
	*DlayDET2 = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DlayDET3");
	DlayDET3 = n_node->data;
	*DlayDET3 = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "CoWin");
	CoWin = n_node->data;
	*CoWin = 3;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;


	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "AnDET");
	AnDET = n_node->data;
	*AnDET = 5;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "targetTECFlag0");
	targetTECFlag0 = n_node->data;
	*targetTECFlag0 = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "targetTECFlag1");
	targetTECFlag1 = n_node->data;
	*targetTECFlag1 = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "DthrSt");
	DthrSt = n_node->data;
	*DthrSt = 0.02;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT ;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "DthrEd");
	DthrEd = n_node->data;
	*DthrEd = 1.3;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;


	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TempSt");
	TempSt = n_node->data;
	*TempSt = 0.85;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "TempEd");
	TempEd = n_node->data;
	*TempEd = 1.36;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VoltSt");
	VoltSt = n_node->data;
	*VoltSt = 260;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "VoltEd");
	VoltEd = n_node->data;
	*VoltEd = 370;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DetSt");
	DetSt = n_node->data;
	*DetSt = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint8_t), "DetEd");
	DetEd = n_node->data;
	*DetEd = 3;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT8;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "kp");
	kp = n_node->data;
	*kp = 1.63;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ki");
	ki = n_node->data;
	*ki = 0.45;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "kd");
	kd = n_node->data;
	*kd = 0.15;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "printMessageFlag");
	printMessageFlag = n_node->data;
	*printMessageFlag = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "printTelemetryFlag");
	printTelemetryFlag = n_node->data;								//print thermal info after boot
	*printTelemetryFlag = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "echo_uartmessageFlag");
	echo_uartmessageFlag = n_node->data;								//print thermal info after boot
	*echo_uartmessageFlag = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(_Bool), "Exit");
	Exit = n_node->data;
	*Exit = false;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_BOOLEAN;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint16_t), "countTime");
	countTime = n_node->data;
	*countTime = 1000; //ms
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT16;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint16_t), "maxcountTime");
	maxcountTime = n_node->data;
	*maxcountTime = 5000;  //ms
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = true;
	n_node->executable = false;
	n_node->data_type = T_UINT16;



	/******************Telemetry variable******************/

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ThermRead0");
	ThermRead0 = n_node->data;
	*ThermRead0=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ThermRead1");
	ThermRead1 = n_node->data;
	*ThermRead1=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ThermRead2");
	ThermRead2 = n_node->data;
	*ThermRead2=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ThermRead3");
	ThermRead3 = n_node->data;
	*ThermRead3=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ITEC0");
	ITEC0 = n_node->data;
	*ITEC0=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "ITEC1");
	ITEC1 = n_node->data;
	*ITEC1=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "HVMoni0");
	HVMoni0 = n_node->data;
	*HVMoni0=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(float), "HVMoni3");
	HVMoni3 = n_node->data;
	*HVMoni3=0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_FLOAT;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint32_t), "count_timerInterruptEvent");
	count_timerInterruptEvent = n_node->data;
	*count_timerInterruptEvent = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_UINT32;

	n_node = allocate_node(table, TABLE_SIZE, sizeof(uint32_t), "timer_sysclock");
	timer_sysclock = n_node->data;
	*timer_sysclock = 0;
	n_node->is_array = false;
	n_node->readable = true;
	n_node->writeable = false;
	n_node->executable = false;
	n_node->data_type = T_UINT32;

}


