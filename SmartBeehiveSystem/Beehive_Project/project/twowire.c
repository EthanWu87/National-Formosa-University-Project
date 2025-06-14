#include "twowire.h"

void twowire_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.PB = 1;
  CKCUClock.Bit.PD = 1;
  CKCUClock.Bit.AFIO = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  //wire0
  AFIO_GPxConfig(TWO_WIRE0_GPIO_GROUP, TWO_WIRE0_SDA_PIN, AFIO_FUN_GPIO);
  AFIO_GPxConfig(TWO_WIRE0_GPIO_GROUP, TWO_WIRE0_SCL_PIN, AFIO_FUN_GPIO);
  
	GPIO_PullResistorConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, GPIO_DV_8MA);
  GPIO_OpenDrainConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, ENABLE);
	GPIO_DirectionConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, GPIO_DIR_OUT);

	GPIO_PullResistorConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, GPIO_DV_8MA);
	GPIO_OpenDrainConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, ENABLE);
	GPIO_DirectionConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, GPIO_DIR_OUT);

  //wire1
  AFIO_GPxConfig(TWO_WIRE1_GPIO_GROUP, TWO_WIRE1_SDA_PIN, AFIO_FUN_GPIO);
  AFIO_GPxConfig(TWO_WIRE1_GPIO_GROUP, TWO_WIRE1_SCL_PIN, AFIO_FUN_GPIO);
  
	GPIO_PullResistorConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, GPIO_DV_8MA);
  GPIO_OpenDrainConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, ENABLE);
	GPIO_DirectionConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, GPIO_DIR_OUT);

	GPIO_PullResistorConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, GPIO_DV_8MA);
	GPIO_OpenDrainConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, ENABLE);
	GPIO_DirectionConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, GPIO_DIR_OUT);
}

//wire0
void twowire0_SDA_In()
{
  GPIO_DirectionConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, GPIO_DIR_IN);
  GPIO_InputConfig(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, ENABLE);
}

void twowire0_SDA_High()
{
  GPIO_WriteOutBits(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SDA_PIN, SET);
}

void twowire0_SCL_High()
{
  GPIO_WriteOutBits(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, SET);
}

void twowire0_SCL_Low()
{
  GPIO_WriteOutBits(TWO_WIRE0_GPIO_PORT, TWO_WIRE0_SCL_PIN, RESET);
}

//wire1
void twowire1_SDA_In()
{
  GPIO_DirectionConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, GPIO_DIR_IN);
  GPIO_InputConfig(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, ENABLE);
}

void twowire1_SDA_High()
{
  GPIO_WriteOutBits(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SDA_PIN, SET);
}

void twowire1_SCL_High()
{
  GPIO_WriteOutBits(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, SET);
}

void twowire1_SCL_Low()
{
  GPIO_WriteOutBits(TWO_WIRE1_GPIO_PORT, TWO_WIRE1_SCL_PIN, RESET);
}