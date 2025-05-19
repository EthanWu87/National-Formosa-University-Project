#ifndef _HT24LC64_H_
#define _HT24LC64_H_

#include "ht32.h"
#include "i2c.h"
#include "delay.h"
#include <string.h>

#define HT24LC64_ADDRESS    0x50
#define HT24LC64_TOTAL_SIZE 8192
#define HT24LC64_PAGE_SIZE  32   //32pages of 256bytes each

void ht24lc64_Configuration();
void ht24lc64_ClearData();
void ht24lc64_WriteData(float *floatData, u16 address, u16 floatLength);
void ht24lc64_ReadData(float *floatData, u16 address, u16 floatLength);

#endif
