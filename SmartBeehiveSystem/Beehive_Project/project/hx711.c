#include "hx711.h"

//box1_0 8777853, 426
//box1_1 8536689, 378

//box2_0 8543544, 437
//box2_1 8480186, 218

int SCALE_FACTOR0 = 437;
int OFFSET0 = 8543544;

int SCALE_FACTOR1 = 218;
int OFFSET1 = 8480186;

void hx711_Configuration()
{
  twowire_Configuration();
}

int hx711_0_ReadData()
{
  u8 i;
  int data = 0;

  twowire0_SDA_In();

  twowire0_SCL_Low();

  while(TWO_WIRE0_SDA_Read());

  for(i = 0; i < 24; i++)
  {
    twowire0_SCL_High();
    delay_us(1);
    twowire0_SCL_Low();
    delay_us(1);

    data <<= 1;

    if(TWO_WIRE0_SDA_Read()) data++;
  }

  twowire0_SCL_High();
  delay_us(1);

  data = data ^ 0x800000;

  twowire0_SCL_Low();
  delay_us(1);

  return data;
}

long hx711_0_DataAverage(u8 times)
{
  long sum = 0;
  for(u8 i = 0; i < times; i++)
  {
    sum += hx711_0_ReadData();
  }

  sum /= times;

  return sum;
}

int hx711_0_GetWeight()
{
  int Data = hx711_0_DataAverage(1) - OFFSET0;
  Data /= SCALE_FACTOR0;

  if(Data >= 5000 || Data <= 0) return 0;
  else return Data;
}

void hx711_0_Calibration()
{
  OFFSET0 = hx711_0_DataAverage(50);
  printf("The offset weight: %d\r\n", OFFSET0);
  delay_s(5);

  printf("Put the 100g weight\r\n");
  delay_s(5);
  long known_weight_data = hx711_0_DataAverage(50);

  SCALE_FACTOR0 = (known_weight_data - OFFSET0) / 100.0;
  printf("The scale: %d\r\n", SCALE_FACTOR0);
  delay_s(5);
}

//wire1
int hx711_1_ReadData()
{
  u8 i;
  int data = 0;

  twowire1_SDA_In();
  
  twowire1_SCL_Low();

  while(TWO_WIRE1_SDA_Read());

  for(i = 0; i < 24; i++)
  {
    twowire1_SCL_High();
    delay_us(1);
    twowire1_SCL_Low();
    delay_us(1);

    data <<= 1;

    if(TWO_WIRE1_SDA_Read()) data++;
  }

  twowire1_SCL_High();
  delay_us(1);

  data = data ^ 0x800000;

  twowire1_SCL_Low();
  delay_us(1);

  return data;
}

long hx711_1_DataAverage(u8 times)
{
  long sum = 0;
  for(u8 i = 0; i < times; i++)
  {
    sum += hx711_1_ReadData();
  }

  sum /= times;

  return sum;
}

int hx711_1_GetWeight()
{
  int Data = hx711_1_DataAverage(1) - OFFSET1;
  Data /= SCALE_FACTOR1;

  if(Data >= 5000 || Data <= 0) return 0;
  else return Data;
}

void hx711_1_Calibration()
{
  OFFSET1 = hx711_1_DataAverage(50);
  printf("The offset weight: %d\r\n", OFFSET1);
  delay_s(5);

  printf("Put the 100g weight\r\n");
  delay_s(5);
  long known_weight_data = hx711_1_DataAverage(50);

  SCALE_FACTOR1 = (known_weight_data - OFFSET1) / 100.0;
  printf("The scale: %d\r\n", SCALE_FACTOR1);
  delay_s(5);
}