#include "ht32.h"
#include "bftm.h"
#include "rylr896.h"
#include "fsr400.h"
#include <string.h>

int timeOffset0 = 0;

void HTCFG_BFTM_IRQHandler()
{
  extern vu32 gFeedReady;
  extern vu32 gFeedWeight;

  if(BFTM_GetFlagStatus(HT_BFTM0) != RESET)
  {
    timeOffset0++;

    if(timeOffset0 == 60000)  //自動餵食計數
    {
      // gFeedWeight = 50;
      // gFeedReady = true;

      timeOffset0 = 0;
    }

    BFTM_ClearFlag(HT_BFTM0);
  }
}

void HTCFG_ADC_IRQHandler()
{
  extern vu32 gAdcReady;
  extern int  gAdcValue[2];

  ADC_ClearIntPendingBit(ADC0_PORT, ADC_FLAG_SUB_GROUP_EOC);

  if(ADC_GetFlagStatus(ADC0_PORT, ADC_FLAG_CYCLE_EOC))
  {
    for(u8 i = 0; i < 2; i++)
    {
      gAdcValue[i] = (ADC0_PORT->DR[i] & 0x0FFF);
    }

    gAdcReady = true;
  }
}

void HTCFG_UART_IRQHandler()
{
  extern vu32 gUsart1RxReady;
  extern u8   gUsart1RxData[];

  static u8 rxIndex = 0;

  if(USART_GetFlagStatus(USART1_PORT, USART_FLAG_RXDR))
  {
    gUsart1RxData[rxIndex] = USART_ReceiveData(USART1_PORT);
        
    if(gUsart1RxData[rxIndex] == '\n')
    {
      if(strncmp((char *)gUsart1RxData, "+RCV=", 5) == 0)
      {
        gUsart1RxReady = true;
      }

      rxIndex = 0;
    }
    else
    {
      rxIndex++;
    }
  }
}