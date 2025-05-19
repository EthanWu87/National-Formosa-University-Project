#include"led.h"

void led_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUCLOCK = {{0}};
  CKCUCLOCK.Bit.PC = 1;

  CKCU_PeripClockConfig(CKCUCLOCK, ENABLE);

  GPIO_DirectionConfig(LED_GPIO_GROUP, LED1_GPIO_PIN|LED2_GPIO_PIN, GPIO_DIR_OUT);

  GPIO_WriteOutBits(LED_GPIO_GROUP, LED1_GPIO_PIN|LED2_GPIO_PIN, SET);
}

void led1_On()
{
  GPIO_WriteOutBits(LED_GPIO_GROUP, LED1_GPIO_PIN, RESET);
}

void led1_Off()
{
  GPIO_WriteOutBits(LED_GPIO_GROUP, LED1_GPIO_PIN, SET);
}

void led2_On()
{
  GPIO_WriteOutBits(LED_GPIO_GROUP, LED2_GPIO_PIN, RESET);
}

void led2_Off()
{
  GPIO_WriteOutBits(LED_GPIO_GROUP, LED2_GPIO_PIN, SET);
}