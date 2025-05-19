#ifndef _TWOWIRE_H_
#define _TWOWIRE_H_

#include "ht32.h"

#define TWO_WIRE0_GPIO_GROUP  (GPIO_PD)
#define TWO_WIRE0_GPIO_PORT   (HT_GPIOD)
#define TWO_WIRE0_SCL_PIN     (GPIO_PIN_2)
#define TWO_WIRE0_SDA_PIN     (GPIO_PIN_3)
#define TWO_WIRE0_SDA_Read()  GPIO_ReadInBit(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN)

#define TWO_WIRE1_GPIO_GROUP  (GPIO_PB)
#define TWO_WIRE1_GPIO_PORT   (HT_GPIOB)
#define TWO_WIRE1_SCL_PIN     (GPIO_PIN_2)
#define TWO_WIRE1_SDA_PIN     (GPIO_PIN_3)
#define TWO_WIRE1_SDA_Read()  GPIO_ReadInBit(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN)

void twowire_Configuration();

void twowire0_SDA_In();
void twowire0_SDA_High();
void twowire0_SCL_High();
void twowire0_SCL_Low();

void twowire1_SDA_In();
void twowire1_SDA_High();
void twowire1_SCL_High();
void twowire1_SCL_Low();

#endif
