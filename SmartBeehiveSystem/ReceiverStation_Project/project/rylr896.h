#ifndef _RYLR896_H_
#define _RYLR896_H_

#include "ht32.h"
#include "usart.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rylr896_Configuration();
void rylr896_Send(u8 boxID, u8 *method);
void rylr896_Receive();

#endif
