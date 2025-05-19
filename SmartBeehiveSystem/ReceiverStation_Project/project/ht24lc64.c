#include "ht24lc64.h"

void ht24lc64_Configuration()
{
  i2c_Configuration();
}

void ht24lc64_ClearData()
{
  u16 address = 0x0000;

  float clearData[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  for(u16 i = 0; i < 3; i++)
  {
    ht24lc64_WriteData(clearData, address, 4);
    delay_ms(10);
    address += 0x0020;
  }
}

void ht24lc64_WriteData(float *floatData, u16 address, u16 floatLength)
{
  u8  byteData[floatLength * 4];
  u16 byteLength = floatLength * 4;

  for(u8 i = 0; i < floatLength; i++)
  {
    memcpy(&byteData[i * 4], &floatData[i], 4);
  }

  I2C_ClearFlag(I2C_MASTER_PORT, I2C_FLAG_RXNACK);

  I2C_TargetAddressConfig(I2C_MASTER_PORT, HT24LC64_ADDRESS, I2C_MASTER_WRITE);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TRANSMITTER_MODE));

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, (address >> 8) & 0xFF);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, address & 0xFF);

  for(u16 i = 0; i < byteLength; i++)
  {
    while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
    I2C_SendData(I2C_MASTER_PORT, byteData[i]);
  }

  I2C_GenerateSTOP(I2C_MASTER_PORT);
  while(I2C_ReadRegister(I2C_MASTER_PORT, I2C_REGISTER_SR) & 0x80000);
}

void ht24lc64_ReadData(float *floatData, u16 address, u16 floatLength)
{
  u8  byteData[floatLength * 4];
  u16 byteLength = floatLength * 4;

  I2C_ClearFlag(I2C_MASTER_PORT, I2C_FLAG_RXNACK);

  I2C_TargetAddressConfig(I2C_MASTER_PORT, HT24LC64_ADDRESS, I2C_MASTER_WRITE);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TRANSMITTER_MODE));

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, (address >> 8) & 0xFF);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_TX_EMPTY));
  I2C_SendData(I2C_MASTER_PORT, address & 0xFF);

  //開始讀取
  I2C_AckCmd(I2C_MASTER_PORT, ENABLE);

  I2C_TargetAddressConfig(I2C_MASTER_PORT, HT24LC64_ADDRESS, I2C_MASTER_READ);

  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_SEND_START));
  while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_RECEIVER_MODE));

  for(u16 i = 0; i < byteLength; i++)
  {
    if(i == byteLength - 1) I2C_AckCmd(I2C_MASTER_PORT, DISABLE);

    while(!I2C_CheckStatus(I2C_MASTER_PORT, I2C_MASTER_RX_NOT_EMPTY));

    byteData[i] = I2C_ReceiveData(I2C_MASTER_PORT);
  }

  I2C_GenerateSTOP(I2C_MASTER_PORT);
  while(I2C_ReadRegister(I2C_MASTER_PORT, I2C_REGISTER_SR) & 0x80000);

  for(u8 j = 0; j < floatLength; j++)
  {
    memcpy(&floatData[j], &byteData[j * 4], 4);
  }
}