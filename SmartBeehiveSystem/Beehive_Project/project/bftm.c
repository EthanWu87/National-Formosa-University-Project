#include "bftm.h"

void bftm_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BFTM0 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  NVIC_SetPriority(BFTM0_IRQn, 2);
  NVIC_EnableIRQ(BFTM0_IRQn);

  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_SetCompare(HT_BFTM0, SystemCoreClock / 1000);    //1ms
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);
}