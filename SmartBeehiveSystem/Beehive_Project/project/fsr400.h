#ifndef _FSR400_H_
#define _FSR400_H_

#include "ht32.h"
#include "math.h"

#define V_REF 5.0
#define R_M 10000

#define ADC_GPIO_GROUP  (GPIO_PA)
#define ADC0_AFIO_PIN   (AFIO_PIN_2)
#define ADC1_AFIO_PIN   (AFIO_PIN_3)
// #define ADC2_AFIO_PIN   (AFIO_PIN_6)
// #define ADC3_AFIO_PIN   (AFIO_PIN_7)

#define ADC0_CH         (ADC_CH_2)
#define ADC1_CH         (ADC_CH_3)
// #define ADC2_CH         (ADC_CH_6)
// #define ADC3_CH         (ADC_CH_7)

#define ADC0_CKCU_ADCPRE      (CKCU_ADCPRE_ADC0)
#define ADC0_PORT             (HT_ADC0)
#define ADC0_IRQn             (ADC0_IRQn)
#define HTCFG_ADC_IRQHandler  (ADC_IRQHandler)

void adc_Configuration();
// float adc_To_Voltage(float adcValue);
// float voltage_To_Resistance(float voltage);
// float resistance_To_Pressure(float resistance);
float adc_To_Pressure(float adcValue1, float adcValue2);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif
