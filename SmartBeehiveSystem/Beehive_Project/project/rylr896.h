#ifndef _RYLR896_H_
#define _RYLR896_H_

#include "ht32.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rylr896_Configuration();
void rylr896_UpdateData(int fsrValue1, u32 hx711_0_Value, u32 hx711_1_Value, float temperature, float humidity);
void rylr896_Receive();
void rylr896_Send();

#endif
