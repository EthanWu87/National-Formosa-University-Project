#ifndef _JGB37_H_
#define _JGB37_H_

#include "ht32.h"

#define JGB37_GPIO_GROUP  (HT_GPIOC)
#define JGB37_GPIO_PIN    (GPIO_PIN_10)

void jgb37_Configuration();
void jgb37_Start();
void jgb37_Stop();

#endif