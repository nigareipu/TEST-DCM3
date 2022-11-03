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
	mode = allocate_node(hash_table, table_size, sizeof(int), "mode");
	mode5Calibration = allocate_node(hash_table, table_size, sizeof(int), "mode5Calibration");
	VDET0 = allocate_node(hash_table, table_size, sizeof(float), "VDET0");
	VDET1 = allocate_node(hash_table, table_size, sizeof(float), "VDET1");
	VDET2 = allocate_node(hash_table, table_size, sizeof(float), "VDET2");
	VDET3 = allocate_node(hash_table, table_size, sizeof(float), "VDET3");
	TDET0 = allocate_node(hash_table, table_size, sizeof(float), "TDET0");
	TDET1 = allocate_node(hash_table, table_size, sizeof(float), "TDET1");
	TDET2 = allocate_node(hash_table, table_size, sizeof(float), "TDET2");
	TDET3 = allocate_node(hash_table, table_size, sizeof(float), "TDET3");
	RTime = allocate_node(hash_table, table_size, sizeof(int), "RTime");
	DThrs = allocate_node(hash_table, table_size, sizeof(float), "DThrs");
	DlayDET0 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET0");
	DlayDET1 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET1");
	DlayDET2 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET2");
	DlayDET3 = allocate_node(hash_table, table_size, sizeof(float), "DlayDET3");
	CoWin = allocate_node(hash_table, table_size, sizeof(int), "CoWin");
	AnDET = allocate_node(hash_table, table_size, sizeof(int), "AnDET"); // Choose Annealing DET for Mode6
	Di = allocate_node(hash_table, table_size, sizeof(int), "Di");
	DNum = allocate_node(hash_table, table_size, sizeof(int), "DNum");
	DthrEd = allocate_node(hash_table, table_size, sizeof(float), "DthrEd");
	DthrSt = allocate_node(hash_table, table_size, sizeof(float), "DthrSt");
	TempSt = allocate_node(hash_table, table_size, sizeof(float), "TempSt");
	TempEd = allocate_node(hash_table, table_size, sizeof(float), "TempEd");
	VoltSt = allocate_node(hash_table, table_size, sizeof(float), "VoltSt");
	VoltEd = allocate_node(hash_table, table_size, sizeof(float), "VoltEd");
	kp = allocate_node(hash_table, table_size, sizeof(float), "kp");
	ki = allocate_node(hash_table, table_size, sizeof(float), "ki");
	kd = allocate_node(hash_table, table_size, sizeof(float), "kd");
	countTime = allocate_node(hash_table, table_size, sizeof(int), "countTime");
	targetTECFlag0 = allocate_node(hash_table, table_size, sizeof(int), "targetTECFlag0");
	targetTECFlag1 = allocate_node(hash_table, table_size, sizeof(int), "targetTECFlag1");
	printMessageFlag = allocate_node(hash_table, table_size, sizeof(int), "printMessageFlag");
	printThermalFlag = allocate_node(hash_table, table_size, sizeof(int), "printThermalFlag");
	Exit = allocate_node(hash_table, table_size, sizeof(int), "Exit");

	*mode = 2;
	*mode5Calibration = 1;
	*VDET0 = 1;
	*VDET1 = 1;
	*VDET2 = 1;
	*VDET3 = 1;
	*TDET0 = 1.0;
	*TDET1 = 1.0;
	*TDET2 = 0.95;
	*TDET3 = 0.95;
	*RTime = 10000;
	*DThrs = 0.05;
	*DlayDET0 = 0;
	*DlayDET1 = 0;
	*DlayDET2 = 0;
	*DlayDET3 = 0;
	*CoWin = 3;
	*AnDET = 3; ////value-> 0 (for TEC0),  1 (for TEC1), 2 (for TEC2) & 3 (for TEC3)
	*targetTECFlag0 = 1;
	*targetTECFlag1 = 1;
	*DthrSt = 0.2;
	*DthrEd = 0.22;
	*TempSt = 0.85;
	*TempEd = 1.2;
	*VoltSt = 300;
	*VoltEd = 320;
	*Di = 0;
	*DNum = 4;	// value->1-4. How many detectors to scan, upperlimit
	*kp = 1.63; // PID Proportional Gain
	*ki = 0.45; // PID Integral Gain
	*kd = 0.15;
	*printMessageFlag=0;
	*printThermalFlag=0;
	*countTime = 1000; //In millisecond.
	*Exit=0;

}
