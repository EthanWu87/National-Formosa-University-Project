#include "rylr896.h"

u8 TxData[128];

void rylr896_Configuration()
{
  usart_Configuration();
}

void rylr896_UpdateData(int fsrValue1, u32 hx711_0_Value, u32 hx711_1_Value, float temperature, float humidity)
{
  char data[128];

  u32 dataLength = 0;

  sprintf(data, "%d,%u,%u,%.1f,%.1f",
    fsrValue1,
    hx711_0_Value,
    hx711_1_Value,
    temperature,
    humidity
  );

  dataLength = strlen(data);

  sprintf((char *)TxData, "AT+SEND=69,%u,%s\r\n", dataLength, data);
}

void rylr896_Receive()
{
  extern vu32 gUsart1RxReady;
  extern u8   gUsart1RxData[];

  extern vu32 gResponseReady;
  extern vu32 gFeedReady;
  extern u32  gFeedWeight;

  const char *data;
  const char *feedRequire;
  
  if(gUsart1RxReady == true)
  {
    data = strtok((char *)gUsart1RxData, ",");
    data = strtok(NULL, ",");
    data = strtok(NULL, ",");
    feedRequire = data;
    // printf("Method: %s\r\n", feedRequire);

    data = strtok(NULL, ",");
    gFeedWeight = atoi(data);
    // printf("Weight: %u\r\n", gFeedWeight);

    if(!strcmp(feedRequire, "Response"))
    {
      gResponseReady = true;
    }
    else if(!strcmp(feedRequire, "Feed"))
    {
      gFeedReady = true;
    }

    gUsart1RxReady = false;
  }
}

void rylr896_Send()
{
  usart_SendStr(USART1_PORT, TxData);
}
