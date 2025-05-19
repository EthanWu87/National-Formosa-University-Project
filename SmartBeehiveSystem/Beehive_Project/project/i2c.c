#include "i2c.h"
#include "delay.h"

void i2c_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  I2C_MASTER_CLK(CKCUClock) = 1;
  CKCUClock.Bit.AFIO  = 1;
  CKCUClock.Bit.PA = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(I2C_GPIO_GROUP, I2C_SCL_AFIO_PIN, AFIO_FUN_I2C);
  AFIO_GPxConfig(I2C_GPIO_GROUP, I2C_SDA_AFIO_PIN, AFIO_FUN_I2C);

  I2C_InitTypeDef  I2C_InitStructure;
  I2C_InitStructure.I2C_GeneralCall = DISABLE;
  I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
  I2C_InitStructure.I2C_Acknowledge = DISABLE;
  I2C_InitStructure.I2C_OwnAddress = I2C_MASTER_ADDRESS;
  I2C_InitStructure.I2C_Speed = ClockSpeed;
  I2C_InitStructure.I2C_SpeedOffset = 0;
  I2C_Init(I2C_MASTER_PORT, &I2C_InitStructure);

  I2C_Cmd(I2C_MASTER_PORT, ENABLE);
}