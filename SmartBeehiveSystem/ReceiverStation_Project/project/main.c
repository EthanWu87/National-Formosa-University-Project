#include "ht32.h"
#include "ht32_board.h"
#include "delay.h"
#include "bftm.h"
#include "rylr896.h"
#include "sim7600x.h"
#include "am2320.h"
#include "ht24lc64.h"
#include <string.h>

//Public Global Variable 
u8    gMainIndex = 0;

u8    gUsart0RxData[128];
vu32  gUsart0RxReady = false;
u8    gUsart1RxData[128];
vu32  gUsart1RxReady = false;

u8    gBoxID[2] = {67, 68};
vu32  gBoxReady = false;
float gBoxData[6];

u8    gFeedRequire;
u32   gFeedWeight;

vu32  gEEPROMReady = false;

int   gCurrentTime = 0;

//Private Global Variable
float RcvData[2];


void boxMainLoop()
{
  static u8 index = 0;

  u8  boxNum = sizeof(gBoxID) / sizeof(gBoxID[0]);
  u8  responseMethod[] = "Response";

  u16 address = 0x0000;
  float readBuffer[6];

  int timer = 0;

  rylr896_Send(gBoxID[index], responseMethod);  //走訪蜂箱
  timer = gCurrentTime;
  // while(!gEEPROMReady)
  // {
  //   if(gCurrentTime - timer > 3000) break;      //蜂箱3秒沒回應就換下一箱

  //   rylr896_Receive();
  //   if(gEEPROMReady)
  //   {
  //     ht24lc64_WriteData(gBoxData, address, sizeof(gBoxData) / sizeof(gBoxData[0]));
  //     delay_ms(20);
  //     ht24lc64_ReadData(readBuffer, address, sizeof(gBoxData) / sizeof(gBoxData[0]));
  //     // for(u8 j = 0; j < 6; j++) {
  //     //   printf("I'm read: %f\r\n", readBuffer[j]);
  //     // }

  //     sim7600x_UpdateBoxData(readBuffer);
  //     sim7600x_BeeBoxSend();
  //   }
  // }
  // gEEPROMReady = false;

  while(gCurrentTime - timer < 3000)
  {
    rylr896_Receive();
    if(gBoxReady)
    {
      sim7600x_UpdateBoxData(gBoxData);
      sim7600x_BeeBoxSend();

      gBoxReady = false;
      break;
    }
  }

  if(index == (boxNum - 1))  //蜂箱回傳完畢
  {
    index = 0;
    gMainIndex = 2;
  }
  else
  {
    index++;
  }
}

void rcvMainLoop()
{
  float temperature = 0.0, humidity = 0.0;

  u16 address = 0x0000;
  float readBuffer[2];
  
  am2320_GetTemperatureHumidity(&temperature, &humidity);
  RcvData[0] = temperature;
  RcvData[1] = humidity;

  sim7600x_GetGPS();

  // ht24lc64_WriteData(RcvData, address, sizeof(RcvData) / sizeof(RcvData[0]));
  // delay_ms(20);
  // ht24lc64_ReadData(readBuffer, address, sizeof(RcvData) / sizeof(RcvData[0]));
  // for(u8 i = 0; i < 2; i++)
  // {
  //   printf("RCV Data: %.1f\r\n", readBuffer[i]);
  // }

  sim7600x_UpdateRcvData(RcvData);
  sim7600x_RcvSend();

  gMainIndex = 0;
}

int main()
{
  u8 feedMethod[] = "Feed";

  RETARGET_Configuration();
  bftm_Configuration();
  rylr896_Configuration();
  sim7600x_Configuration();
  am2320_Configuration();
  ht24lc64_Configuration();

  // u8 ID[] = "AT+NETWORKID=12\r\n";
  // usart_SendStr(USART1_PORT, ID);

  // ht24lc64_ClearData();
  
  while(1)
  {
    sim7600x_Receive(); //接收餵食指令
    if(gFeedRequire != 0)
    {
      rylr896_Send(gBoxID[gFeedRequire - 1], feedMethod);

      delay_s(1);       //這感覺能優化捏?
      gFeedRequire = 0;
    }

    switch(gMainIndex)
    {
      case 1: boxMainLoop(); break;
      case 2: rcvMainLoop(); break;
    }

    delay_ms(1);
  }
}