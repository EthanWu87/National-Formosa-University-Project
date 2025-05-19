#ifndef _AM2320_H_
#define _AM2320_H_

#include "ht32.h"
#include "i2c.h"
#include "delay.h"

#define AM2320_ADDRESS 0x5C

void am2320_Configuration();
void am2320_Wake();
void am2320_ReadData(u8 *data, u8 length);
void am2320_GetTemperatureHumidity(float *temperature, float *humidity);

#endif
