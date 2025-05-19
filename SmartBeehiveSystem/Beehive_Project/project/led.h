#ifndef _LED_H_
#define _LED_H_

#include "ht32.h"

#define LED_GPIO_GROUP  (HT_GPIOC)
#define LED1_GPIO_PIN   (GPIO_PIN_14)
#define LED2_GPIO_PIN   (GPIO_PIN_15)

void led_Configuration();
void led1_On();
void led1_Off();
void led2_On();
void led2_Off();

#endif
