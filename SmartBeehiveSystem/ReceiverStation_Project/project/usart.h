#ifndef _USART_H_
#define _USART_H_

#include  "ht32.h"

#define UASRT_GPIO_GROUP        (GPIO_PA)
#define USART0_TX_AFIO_PIN      (AFIO_PIN_2)
#define USART0_RX_AFIO_PIN      (AFIO_PIN_3)
#define USART0_PORT             (HT_USART0)
#define USART0_IRQn             (USART0_IRQn)
#define HTCFG_UART0_IRQHandler  (USART0_IRQHandler)

#define USART1_TX_AFIO_PIN      (AFIO_PIN_4)
#define USART1_RX_AFIO_PIN      (AFIO_PIN_5)
#define USART1_PORT             (HT_USART1)
#define USART1_IRQn             (USART1_IRQn)
#define HTCFG_UART1_IRQHandler  (USART1_IRQHandler)

void usart_Configuration();
void usart_SendByte(HT_USART_TypeDef* USARTx, u8 data);
void usart_SendStr(HT_USART_TypeDef* USARTx, u8 *str);

#endif
