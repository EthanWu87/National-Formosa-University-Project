#include "rylr896.h"

void rylr896_Configuration()
{
  usart_Configuration();
}

void rylr896_Send(u8 boxID, u8 *method)
{
  extern u32 gFeedWeight;

  static u8 usart1TxData[128];
  static u8 data[128];
  u32 dataLength = 0;

  memset(data, 0, 128);
  sprintf((char *)data, "%s,%u", method, gFeedWeight);

  dataLength = strlen((char *)data);
  
  memset(usart1TxData, 0, 128);
  sprintf((char *)usart1TxData, "AT+SEND=%d,%u,%s\r\n", boxID, dataLength, data);

  usart_SendStr(USART1_PORT, usart1TxData);
}

void rylr896_Receive()
{
  extern u8   gUsart1RxData[];
  extern vu32 gUsart1RxReady;

  extern vu32 gEEPROMReady;

  extern float gBoxData[];
  extern vu32  gBoxReady;

  const char *data;
  u8 index = 1;

  if(gUsart1RxReady == true)
  {
    data = strtok((char *)gUsart1RxData, "=");
    data = strtok(NULL, ",");
    gBoxData[0] = atof(data);
    data = strtok(NULL, ",");

    while(data != NULL && index < 6)
    {
      data = strtok(NULL, ",");
      gBoxData[index] = atof(data);

      index++;
    }

    // for (u8 j = 0; j < 6; j++) {
    //   printf("%f\r\n", gBoxData[j]);
    // }

    gBoxReady = true;
    gEEPROMReady = true;
    gUsart1RxReady = false;
  }
}