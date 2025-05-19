#ifndef _I2C_H_
#define _I2C_H_

#include "ht32.h"

#define I2C_MASTER_CLK(ck)  (ck.Bit.I2C1)
#define I2C_MASTER_ADDRESS  0x0A
#define ClockSpeed          10000
#define I2C_MASTER_PORT     HT_I2C1
#define I2C_GPIO_GROUP      (GPIO_PA)
#define I2C_GPIO_PORT       (HT_GPIOA)
#define I2C_SCL_AFIO_PIN    (AFIO_PIN_0)
#define I2C_SDA_AFIO_PIN    (AFIO_PIN_1)

void i2c_Configuration();

#endif
