/*
3906 times per second
  Convert times = 1 / (48MHz / 64) * 12 * 4 = 64us
  Total sample frequency =  1 / 64us = 15625 time per second
  Per peripheral sample frequency = 15625 / 4 = 3906 times per second
*/
#include "fsr400.h"  

void adc_Configuration()
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO = 1;
  CKCUClock.Bit.ADC0 = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(ADC_GPIO_GROUP, ADC0_AFIO_PIN | ADC1_AFIO_PIN, AFIO_FUN_ADC0);

  CKCU_SetADCnPrescaler(ADC0_CKCU_ADCPRE, CKCU_ADCPRE_DIV64); //48 MHz / 64 = 750 kHz

  ADC_RegularGroupConfig(ADC0_PORT, CONTINUOUS_MODE, 2, 0);

  ADC_SamplingTimeConfig(ADC0_PORT, 0);

  ADC_RegularChannelConfig(ADC0_PORT, ADC0_CH, 0, 0);
  ADC_RegularChannelConfig(ADC0_PORT, ADC1_CH, 1, 0);
  // ADC_RegularChannelConfig(ADC0_PORT, ADC2_CH, 2, 0);
  // ADC_RegularChannelConfig(ADC0_PORT, ADC3_CH, 3, 0);

  ADC_RegularTrigConfig(ADC0_PORT, ADC_TRIG_SOFTWARE);

  ADC_IntConfig(ADC0_PORT, ADC_INT_SINGLE_EOC, ENABLE);

  NVIC_SetPriority(ADC0_IRQn, 1);
  NVIC_EnableIRQ(ADC0_IRQn);

  ADC_Cmd(ADC0_PORT, ENABLE);
  ADC_SoftwareStartConvCmd(ADC0_PORT, ENABLE);
}

// float adc_To_Voltage(float adcValue)
// {
//   return (adcValue/ 4095) * V_REF;
// }

// float voltage_To_Resistance(float voltage) {
//   return R_M * (V_REF / voltage) - R_M;
// }

// float resistance_To_Pressure(float resistance) 
// {
//     float pressure = 0.0;
//     float A = 10000000000.0;
//     float B = 1.7;

//     pressure = A / pow(resistance, B);
    
//   return pressure;
// }

float adc_To_Pressure(float adcValue1, float adcValue2)
{
  float pressure = 0.0;

  pressure = (map(adcValue1, 0, 4095, 0, 500) + map(adcValue2, 0, 4095, 0, 500)) / 2;

  if(pressure <= 0) return 0;
  else return pressure;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}