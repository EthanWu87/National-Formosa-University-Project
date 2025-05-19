#include "ht32.h"
#include "bftm.h"
#include "rylr896.h"
#include <string.h>

int timeOffset = 0;

void HTCFG_BFTM_IRQHandler()
{
  extern u8  gMainIndex;
  extern int gCurrentTime;

  if(BFTM_GetFlagStatus(HT_BFTM0) != RESET)
  {
    gCurrentTime++;
    timeOffset++;

    if(timeOffset == 15000) 
    {
      gMainIndex = 1;
      timeOffset = 0;
    }

    BFTM_ClearFlag(HT_BFTM0);
  }
}

void HTCFG_UART0_IRQHandler()
{
  extern u8   gUsart0RxData[];
  extern vu32 gUsart0RxReady;
  
  static u8 tempData[128];
  static u8 index = 0;
  
  if(USART_GetFlagStatus(USART0_PORT, USART_FLAG_RXDR))
  {
    tempData[index] = USART_ReceiveData(USART0_PORT);
        
    if(tempData[index] == '\n')
    {
      if((strncmp((char *)tempData, "{\"feed", 6) == 0) || (strncmp((char *)tempData, "+CGPSINFO:", 10) == 0))
      {
        strcpy((char *)gUsart0RxData, (char *)tempData);
      
        gUsart0RxReady = true;
      }

      index = 0;
      memset(tempData, 0, 128);
    }
    else
    {
      index++;
    }
  }
}

void HTCFG_UART1_IRQHandler()
{
  extern u8   gUsart1RxData[];
  extern vu32 gUsart1RxReady;

  static u8 tempData[128];
  static u8 index = 0;

  if(USART_GetFlagStatus(USART1_PORT, USART_FLAG_RXDR))
  {
    tempData[index] = USART_ReceiveData(USART1_PORT);
        
    if(tempData[index] == '\n')
    {
      if(strncmp((char *)tempData, "+RCV=", 5) == 0)
      {
        strcpy((char *)gUsart1RxData, (char *)tempData);  //Save correct data.

        gUsart1RxReady = true;
      }

      index = 0;
      memset(tempData, 0, 128);
    }
    else
    {
      index++;
    }
  }
}