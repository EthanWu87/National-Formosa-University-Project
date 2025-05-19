#include "ht32.h"
#include "ht32_board.h"
#include "delay.h"
#include "bftm.h"
#include "rylr896.h"
#include "am2320.h"
#include "hx711.h"
#include "fsr400.h"
#include "jgb37.h"

vu32 gAdcReady = false;
int  gAdcValue[2];

vu32 gUsart1RxReady = false;
u8   gUsart1RxData[128];

vu32 gResponseReady = false;
vu32 gFeedReady = false;
u32  gFeedWeight = 0;

void hx711Loop(u32* hx711_0_Value, u32* hx711_1_Value)
{
  *hx711_0_Value = hx711_0_GetWeight();
  *hx711_1_Value = hx711_1_GetWeight();
}

int main()
{
  int   fsrValue1, fsrValue2, weightTemp, currentWeight;
  float temperature = 0.0, humidity = 0.0;

  vu32  feedFlag = true;
  u32   hx711_0_Value = 0, hx711_1_Value = 0;

  RETARGET_Configuration();
  bftm_Configuration();
  rylr896_Configuration();
  am2320_Configuration();
  hx711_Configuration();
  adc_Configuration();
  jgb37_Configuration();

  while(1)
  { 
    rylr896_Receive();
    
    // hx711_0_Calibration();
    // hx711_1_Calibration();
    // hx711Loop(&hx711_0_Value, &hx711_1_Value);

    // printf("%u\r\n", hx711_0_Value);

    // printf("ADC0 %d\r\n", gAdcValue[0]);
    // printf("ADC1 %d\r\n", gAdcValue[1]);
    // delay_s(1);
    if(gResponseReady)
    {
      hx711Loop(&hx711_0_Value, &hx711_1_Value);

      am2320_GetTemperatureHumidity(&temperature, &humidity);
      
      fsrValue1 = adc_To_Pressure(gAdcValue[0], gAdcValue[1]);

      rylr896_UpdateData(fsrValue1, hx711_0_Value, hx711_1_Value, temperature, humidity);
      rylr896_Send();

      gResponseReady = false;
    }
    
    if(gFeedReady)
    {
      if(feedFlag)
      {
        weightTemp = hx711_0_GetWeight();
        // printf("Weight temp: %u\r\n", weightTemp);

        feedFlag = false;
      }

      // printf("gFeedWeight: %u\r\n", gFeedWeight);
      // printf("weightTemp: %u\r\n", weightTemp);

      currentWeight = hx711_0_GetWeight();
      // printf("currentWeight: %u\r\n", currentWeight);

      if((weightTemp + gFeedWeight) > currentWeight)
      {
        jgb37_Start();
      }
      else
      {
        jgb37_Stop();

        feedFlag = true;
        gFeedReady = false;
      }
    }
    delay_ms(50);
  }
}