#include "sim7600x.h"

u8 ResetModule[] = "AT+CRESET\r\n";
u8 StartHTTP[] = "AT+HTTPINIT\r\n";
u8 StopHTTP[] = "AT+HTTPTERM\r\n";
u8 SetBoxURL[] = "AT+HTTPPARA=\"URL\",\"http://140.130.4.49:8089/beehiveData\"\r\n";
u8 SetRcvURL[] = "AT+HTTPPARA=\"URL\",\"http://140.130.4.49:8089/RCVData\"\r\n";
u8 SetFeedURL[] = "AT+HTTPPARA=\"URL\",\"http://140.130.4.49:8089/getFeedStatus\"\r\n";
u8 SetResponseURL[] = "AT+HTTPPARA=\"URL\",\"http://140.130.4.49:8089/feedCommandResponse\"\r\n";
u8 SetGPSURL[] = "AT+HTTPPARA=\"URL\",\"http://140.130.4.49:8089/GPS\"\r\n";
u8 SetConType[] = "AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"\r\n";
u8 SetSizeTimeOut[128]; //"AT+HTTPDATA=77,10000\r\n"; //data size = 77
u8 PostMethod[] = "AT+HTTPACTION=1\r\n";
u8 GetMethod[] = "AT+HTTPACTION=0\r\n";
u8 ReadData[] = "AT+HTTPREAD=2000\r\n";
u8 FeedResponse[] = "success=true\r\n";
u8 EnableGPS[] = "AT+CGPS=1,1\r\n";
u8 GetGPSInfo[] = "AT+CGPSINFO\r\n";
u8 TxData[128];
// u8 TestData[] = "beebox_id=beebox_1&FSR1=520&FSR2=131&HX711=520&temperature=25.6&humidity=60.2\r\n";

char   gpsLatitude[16], gpsLongitude[16];
float  decimalLatitude, decimalLongitude;

void sim7600x_Configuration()
{
  usart_Configuration();
}

void sim7600x_UpdateBoxData(float *eepromData)
{
  extern u8 gBoxID[2];
  u8  boxID[9];
  u32 dataLength = 0;

  for(u8 i = 0; i < sizeof(gBoxID) / sizeof(gBoxID[0]); i++)
  {
    if((u8)eepromData[0] == gBoxID[i]) sprintf((char *)boxID, "beebox_%u", i + 1);
  }

  sprintf((char *)TxData, "beebox_id=%s&FSR1=%.1f&FSR2=%.1f&HX711=%.1f&temperature=%.1f&humidity=%.1f\r\n",
    boxID,
    eepromData[1],
    eepromData[2],
    eepromData[3],
    eepromData[4],
    eepromData[5]
  );

  dataLength = strlen((char *)TxData);
  sprintf((char *)SetSizeTimeOut, "AT+HTTPDATA=%u,10000\r\n", dataLength);
}

void sim7600x_UpdateRcvData(float *eepromData)
{
  u32 dataLength = 0;

  sprintf((char *)TxData, "temperature=%.1f&humidity=%.1f&Lat=%f&Lon=%fr\n",
    eepromData[0],
    eepromData[1],
    decimalLatitude,
    decimalLongitude
  );

  dataLength = strlen((char *)TxData);
  sprintf((char *)SetSizeTimeOut, "AT+HTTPDATA=%u,10000\r\n", dataLength);
}

void sim7600x_BeeBoxSend()
{
  usart_SendStr(USART0_PORT, StartHTTP);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetBoxURL);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetConType);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetSizeTimeOut);
  delay_ms(3);

  usart_SendStr(USART0_PORT, TxData);
  delay_ms(3);

  usart_SendStr(USART0_PORT, PostMethod);
}

void sim7600x_RcvSend()
{
  usart_SendStr(USART0_PORT, StartHTTP);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetRcvURL);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetConType);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetSizeTimeOut);
  delay_ms(3);

  usart_SendStr(USART0_PORT, TxData);
  delay_ms(3);

  usart_SendStr(USART0_PORT, PostMethod);
}

//gUsart0RxData's format: {"feedCommandSent":false,"currentFeedCommand":"feed1","g":"69"}
void sim7600x_Receive()
{ 
  extern u8   gUsart0RxData[];
  extern vu32 gUsart0RxReady;
  extern u8   gFeedRequire;
  extern u32  gFeedWeight;

  const char *data;

  usart_SendStr(USART0_PORT, StartHTTP);
  delay_ms(3);

  usart_SendStr(USART0_PORT, SetFeedURL);
  delay_ms(3);

  usart_SendStr(USART0_PORT, GetMethod);
  delay_ms(100);

  usart_SendStr(USART0_PORT, ReadData);
  delay_ms(50);

  if(gUsart0RxReady == true)
  {
    data = strtok((char *)gUsart0RxData, ":");
    data = strtok(NULL, ",");
    
    if(!strcmp(data, "true"))
    {
      data = strtok(NULL, ":");
      data = strtok(NULL, "d");
      data = strtok(NULL, "\"");  //feed1, feed2
      gFeedRequire = atoi(data);

      data = strtok(NULL, ":");
      data = strtok(NULL, "\"");  //weight
      gFeedWeight = atoi(data);

      usart_SendStr(USART0_PORT, SetResponseURL);
      delay_ms(3);

      usart_SendStr(USART0_PORT, SetConType);
      delay_ms(3);

      sprintf((char *)SetSizeTimeOut, "AT+HTTPDATA=12,10000\r\n");
      usart_SendStr(USART0_PORT, SetSizeTimeOut);
      delay_ms(3);

      usart_SendStr(USART0_PORT, FeedResponse);
      delay_ms(3);

      usart_SendStr(USART0_PORT, PostMethod);
      delay_ms(500);
    }

    gUsart0RxReady = false;
  }
}

void sim7600x_GetGPS()
{
  extern u8   gUsart0RxData[];
  extern vu32 gUsart0RxReady;

  u32 dataLength = 0;
  const char *data;
  float latitude, longitude;
    
  usart_SendStr(USART0_PORT, EnableGPS);
  delay_ms(3);

  usart_SendStr(USART0_PORT, GetGPSInfo);
  delay_ms(500);

  if(gUsart0RxReady == true)
  {
    //+CGPSINFO: <lat>,<N/S>,<long>,<E/W>,<date>,<time>,<altitude>,<speed>,<course>
    data = strtok((char *)gUsart0RxData, ":");
    data = strtok(NULL, ",");
    strcpy((char *)gpsLatitude, data);

    data = strtok(NULL, ",");
    data = strtok(NULL, ",");
    strcpy((char *)gpsLongitude, data);

    latitude = atof((char *)gpsLatitude);
    longitude = atof((char *)gpsLongitude);

    decimalLatitude = sim7600x_GPSToDec(latitude);
    decimalLongitude = sim7600x_GPSToDec(longitude);
    // printf("Decimal Latitude: %.6f\r\n", decimalLatitude);
    // printf("Decimal Longitude: %.6f\r\n", decimalLongitude);
    gUsart0RxReady = false;
  }
}

float sim7600x_GPSToDec(float coordinate) 
{
  int degrees;
  float minutes, decimalDegrees;

  degrees = (int)(coordinate / 100);
  
  minutes = coordinate - (degrees * 100);

  decimalDegrees = degrees + (minutes / 60.0);

  return decimalDegrees;
}