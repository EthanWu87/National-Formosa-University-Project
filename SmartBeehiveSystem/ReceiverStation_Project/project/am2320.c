#include "am2320.h"

void am2320_Configuration()
{
  i2c_Configuration();
}

void am2320_Wake()
{
  I2C_TargetAddressConfig(I2C_MASTER_PORT, AM2320_ADDRESS, I2C_MASTER_WRITE);
  
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  
  delay_us(800);

  I2C_GenerateSTOP(I2C_MASTER_PORT);
  while(I2C_ReadRegister(I2C_MASTER_PORT, I2C_REGISTER_SR) & 0x80000);
}

void am2320_ReadData(u8 *data, u8 length)
{
  am2320_Wake();

  I2C_ClearFlag(I2C_MASTER_PORT, I2C_FLAG_RXNACK);

  I2C_TargetAddressConfig(I2C_MASTER_PORT, AM2320_ADDRESS, I2C_MASTER_WRITE);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TRANSMITTER_MODE));

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, 0x03);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));  
  I2C_SendData(I2C_MASTER_PORT, 0x00);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, 0x04);

  I2C_GenerateSTOP(I2C_MASTER_PORT);
  while(I2C_ReadRegister(I2C_MASTER_PORT, I2C_REGISTER_SR) & 0x80000);

  //開始讀取
  I2C_AckCmd(I2C_MASTER_PORT, ENABLE);

  I2C_TargetAddressConfig(I2C_MASTER_PORT, AM2320_ADDRESS, I2C_MASTER_READ);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_RECEIVER_MODE));

  for(u8 i = 0; i < length; i++) 
  {
    if(i == length - 1) I2C_AckCmd(I2C_MASTER_PORT, DISABLE);

    while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_RX_NOT_EMPTY));
    data[i] = I2C_ReceiveData(I2C_MASTER_PORT);
  }

  I2C_GenerateSTOP(I2C_MASTER_PORT);
  while(I2C_ReadRegister(I2C_MASTER_PORT, I2C_REGISTER_SR) & 0x80000);
}

void am2320_GetTemperatureHumidity(float *temperature, float *humidity)
{
  u8 data[8];
  int temp_raw, hum_raw;
  
  am2320_ReadData(data, 8);

  hum_raw = (data[2] << 8) | data[3];
  *humidity = hum_raw / 10.0;

  temp_raw = (data[4] << 8) | data[5];
  if(temp_raw & 0x8000) temp_raw = -(temp_raw & 0x7FFF);  //負轉正
  *temperature = temp_raw / 10.0;
}