#include "jgb37.h"

void jgb37_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUCLOCK = {{0}};
  CKCUCLOCK.Bit.PC = 1;

  CKCU_PeripClockConfig(CKCUCLOCK, ENABLE);

  GPIO_DriveConfig(JGB37_GPIO_GROUP, JGB37_GPIO_PIN, GPIO_DV_8MA);
  GPIO_DirectionConfig(JGB37_GPIO_GROUP, JGB37_GPIO_PIN, GPIO_DIR_OUT);
  GPIO_WriteOutBits(JGB37_GPIO_GROUP, JGB37_GPIO_PIN, RESET);
}

void jgb37_Start()
{
  GPIO_WriteOutBits(JGB37_GPIO_GROUP, JGB37_GPIO_PIN, SET);
}

void jgb37_Stop()
{
  GPIO_WriteOutBits(JGB37_GPIO_GROUP, JGB37_GPIO_PIN, RESET);
}