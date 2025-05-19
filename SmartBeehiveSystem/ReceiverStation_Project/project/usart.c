#include "usart.h"

void usart_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO = 1;
  CKCUClock.Bit.PA = 1;
  CKCUClock.Bit.USART0 = 1;
  CKCUClock.Bit.USART1 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(UASRT_GPIO_GROUP, USART0_TX_AFIO_PIN | USART1_TX_AFIO_PIN, AFIO_FUN_USART_UART);
  AFIO_GPxConfig(UASRT_GPIO_GROUP, USART0_RX_AFIO_PIN | USART1_RX_AFIO_PIN, AFIO_FUN_USART_UART);
  
  //USART0
  USART_InitTypeDef USART0_InitStructure = {0};
  USART0_InitStructure.USART_BaudRate = 115200;
  USART0_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART0_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART0_InitStructure.USART_Parity = USART_PARITY_NO;
  USART0_InitStructure.USART_Mode = USART_MODE_NORMAL;
  USART_Init(USART0_PORT, &USART0_InitStructure);

  NVIC_SetPriority(USART0_IRQn, 0);
  NVIC_EnableIRQ(USART0_IRQn);

  USART_IntConfig(USART0_PORT, USART_INT_RXDR, ENABLE);

  USART_TxCmd(USART0_PORT, ENABLE);
  USART_RxCmd(USART0_PORT, ENABLE);
  
  //USART1
  USART_InitTypeDef USART1_InitStructure = {0};
  USART1_InitStructure.USART_BaudRate = 115200;
  USART1_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART1_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART1_InitStructure.USART_Parity = USART_PARITY_NO;
  USART1_InitStructure.USART_Mode = USART_MODE_NORMAL;
  USART_Init(USART1_PORT, &USART1_InitStructure);

  NVIC_SetPriority(USART1_IRQn, 1);
  NVIC_EnableIRQ(USART1_IRQn);
  
  USART_IntConfig(USART1_PORT, USART_INT_RXDR, ENABLE);

  USART_TxCmd(USART1_PORT, ENABLE);
  USART_RxCmd(USART1_PORT, ENABLE);
}

void usart_SendByte(HT_USART_TypeDef* USARTx, u8 data)
{
  USART_SendData(USARTx, data);
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXDE) == RESET);
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXC) == RESET);
}

void usart_SendStr(HT_USART_TypeDef* USARTx, u8 *str)
{
  for(u8 i = 0; str[i] != '\0'; i++)
  {
    usart_SendByte(USARTx, str[i]);
  }
}