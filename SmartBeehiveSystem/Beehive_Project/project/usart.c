#include "usart.h"

void usart_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO = 1;
  CKCUClock.Bit.PA = 1;
  CKCUClock.Bit.USART1 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  GPIO_PullResistorConfig(HT_GPIOA, USART_RX_GPIO_PIN, GPIO_PR_UP);

  AFIO_GPxConfig(UASRT_GPIO_GROUP, USART1_TX_AFIO_PIN, AFIO_FUN_USART_UART);
  AFIO_GPxConfig(UASRT_GPIO_GROUP, USART1_RX_AFIO_PIN, AFIO_FUN_USART_UART);

  USART_InitTypeDef USART_InitStructure = {0};
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  USART_Init(USART1_PORT, &USART_InitStructure);

  NVIC_SetPriority(USART1_IRQn, 0);
  NVIC_EnableIRQ(USART1_IRQn);
  
  USART_IntConfig(USART1_PORT, USART_INT_RXDR, ENABLE);

  USART_TxCmd(USART1_PORT, ENABLE);
  USART_RxCmd(USART1_PORT, ENABLE);
}

void usart_SendByte(HT_USART_TypeDef* USARTx, u8 data)
{
  USART_SendData(USARTx, data);
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXDE) == RESET);
}

void usart_SendArray(HT_USART_TypeDef* USARTx, u8 *array, u8 num)
{
  u8 i;

  for(i = 0; i < num; i ++)
  {
    usart_SendByte(USARTx, *array);
    array++;
  }
}

void usart_SendStr(HT_USART_TypeDef* USARTx, u8 *str)
{
  u8 i;

  for(i = 0; str[i] != '\0'; i++)
  {
    usart_SendByte(USARTx, str[i]);
  }
}