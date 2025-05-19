#ifndef _HX711_H_
#define _HX711_H_

#include "twowire.h"
#include "delay.h"

void hx711_Configuration();

void hx711_0_Calibration();
int hx711_0_ReadData();
int hx711_0_GetWeight();
long hx711_0_DataAverage(u8 times);

void hx711_1_Calibration();
int hx711_1_ReadData();
int hx711_1_GetWeight();
long hx711_1_DataAverage(u8 times);

#endif