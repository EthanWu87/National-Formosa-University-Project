#ifndef _SIM7600X_H_
#define _SIM7600X_H_

#include "ht32.h"
#include "usart.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sim7600x_Configuration();
void sim7600x_UpdateBoxData(float *eepromData);
void sim7600x_UpdateRcvData(float *eepromData);
void sim7600x_BeeBoxSend();
void sim7600x_RcvSend();
void sim7600x_Receive();
void sim7600x_GetGPS();
float sim7600x_GPSToDec(float coordinate);

#endif
