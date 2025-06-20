/*********************************************************************************************************//**
 * @file    bm53a367a_dvb.h
 * @version $Rev:: 5814         $
 * @date    $Date:: 2022-04-13 #$
 * @brief   The header file of BM18B367A Development Board.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __BM18B367A_DVB_H
#define __BM18B367A_DVB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup HT32_Board
  * @{
  */

/** @addtogroup BM18B367A_DVB
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup BM18B367A_DVB_Exported_Constants BM18B367A Development Board exported constants
  * @{
  */
extern HT_GPIO_TypeDef* const GPIO_PORT[GPIO_PORT_NUM];

/** @addtogroup BM18B367A_DVB_LED
  * @{
  */
#define LEDn                        (3)

#define LED1_GPIO_ID                (GPIO_PC)               // D13
#define LED1_GPIO_PIN               (GPIO_PIN_2)
#define LED1_AFIO_MODE              (AFIO_FUN_GPIO)

#define LED2_GPIO_ID                (GPIO_PA)               // A0/D14
#define LED2_GPIO_PIN               (GPIO_PIN_1)
#define LED2_AFIO_MODE              (AFIO_FUN_GPIO)

#define LED3_GPIO_ID                (GPIO_PA)               // A1/D15
#define LED3_GPIO_PIN               (GPIO_PIN_2)
#define LED3_AFIO_MODE              (AFIO_FUN_GPIO)

typedef enum
{
  HT_LED1 = 0,
  HT_LED2 = 1,
  HT_LED3 = 2
} LED_TypeDef;
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_BUTTON
  * @{
  */
#define BUTTONn                     (3)

#define WAKEUP_BUTTON_GPIO_ID       (GPIO_PA)               // A3/D17
#define WAKEUP_BUTTON_GPIO_PIN      (GPIO_PIN_4)
#define WAKEUP_BUTTON_AFIO_MODE     (AFIO_FUN_GPIO)
#define WAKEUP_BUTTON_EXTI_CHANNEL  (4)

#define KEY1_BUTTON_GPIO_ID         (GPIO_PA)               // A6/D31
#define KEY1_BUTTON_GPIO_PIN        (GPIO_PIN_5)
#define KEY1_BUTTON_AFIO_MODE       (AFIO_FUN_GPIO)
#define KEY1_BUTTON_EXTI_CHANNEL    (5)

#define KEY2_BUTTON_GPIO_ID         (GPIO_PA)               // A7/D32
#define KEY2_BUTTON_GPIO_PIN        (GPIO_PIN_6)
#define KEY2_BUTTON_AFIO_MODE       (AFIO_FUN_GPIO)
#define KEY2_BUTTON_EXTI_CHANNEL    (6)

typedef enum
{
  BUTTON_WAKEUP = 0,
  BUTTON_KEY1   = 1,
  BUTTON_KEY2   = 2
} BUTTON_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} BUTTON_MODE_TypeDef;
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_BUZZER
  * @{
  */
#define BUZZER_GPIO_ID              (GPIO_PA)               // D16
#define BUZZER_AFIO_PIN             (AFIO_PIN_3)
#define BUZZER_AFIO_MODE            (AFIO_FUN_MCTM_GPTM)
#define BUZZER_GPIO_CLK(CK)         (CK.Bit.PA)

#define BUZZER_TM_CLK(CK)           (CK.Bit.GPTM0)
#define BUZZER_TM                   (HT_GPTM0)
#define BUZZER_TM_CHANNEL           (TM_CH_3)
#define BUZZER_IRQn                 (GPTM0_IRQn)
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_COM
  * @{
  */
#define COM_NUM                     (1)

#define COM1_CLK(CK)                (CK.Bit.USART0)
#define COM1_PORT                   (HT_USART0)
#define COM1_IRQn                   (USART0_IRQn)
#define COM1_IRQHandler             (USART0_IRQHandler)

#define COM1_TX_GPIO_ID             (GPIO_PA)               // D1
#define COM1_TX_AFIO_PIN            (AFIO_PIN_8)
#define COM1_TX_AFIO_MODE           (AFIO_FUN_USART_UART)

#define COM1_RX_GPIO_ID             (GPIO_PA)               // D0
#define COM1_RX_AFIO_PIN            (AFIO_PIN_10)
#define COM1_RX_AFIO_MODE           (AFIO_FUN_USART_UART)

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_SPI_FLASH
  * @{
  */
#define FLASH_SPI_CLK(CK)           (CK.Bit.QSPI)
#define FLASH_SPI                   (HT_QSPI)

#define FLASH_SPI_SCK_GPIO_ID       (GPIO_PA)               // D4
#define FLASH_SPI_SCK_AFIO_PIN      (AFIO_PIN_15)
#define FLASH_SPI_SCK_AFIO_MODE     (AFIO_FUN_SPI)

#define FLASH_SPI_MOSI_GPIO_ID      (GPIO_PB)               // D5
#define FLASH_SPI_MOSI_AFIO_PIN     (AFIO_PIN_0)
#define FLASH_SPI_MOSI_AFIO_MODE    (AFIO_FUN_SPI)

#define FLASH_SPI_MISO_GPIO_ID      (GPIO_PB)               // D6
#define FLASH_SPI_MISO_AFIO_PIN     (AFIO_PIN_1)
#define FLASH_SPI_MISO_AFIO_MODE    (AFIO_FUN_SPI)

#define FLASH_SPI_SEL_GPIO_ID       (GPIO_PA)               // D3
#define FLASH_SPI_SEL_GPIO_PIN      (GPIO_PIN_14)
#define FLASH_SPI_SEL_AFIO_MODE     (AFIO_FUN_GPIO)
#define FLASH_SPI_SEL_CLK(CK)       (CK.Bit.PA)
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_SPI_LCD
  * @{
  */
#define LCD_SPI_CLK(CK)             (CK.Bit.SPI1)
#define LCD_SPI                     (HT_SPI1)

#define LCD_SPI_SCK_GPIO_ID         (GPIO_PC)               // D13
#define LCD_SPI_SCK_AFIO_PIN        (AFIO_PIN_2)
#define LCD_SPI_SCK_AFIO_MODE       (AFIO_FUN_SPI)

#define LCD_SPI_MOSI_GPIO_ID        (GPIO_PC)               // D11
#define LCD_SPI_MOSI_AFIO_PIN       (AFIO_PIN_3)
#define LCD_SPI_MOSI_AFIO_MODE      (AFIO_FUN_SPI)

#define LCD_SPI_MISO_GPIO_ID        (GPIO_PB)               // D12
#define LCD_SPI_MISO_AFIO_PIN       (AFIO_PIN_6)
#define LCD_SPI_MISO_AFIO_MODE      (AFIO_FUN_SPI)

#define LCD_SPI_SEL_GPIO_ENABLE     (1)
#define LCD_SPI_SEL_GPIO_ID         (GPIO_PC)               // D10
#define LCD_SPI_SEL_AFIO_PIN        (GPIO_PIN_1)
#define LCD_SPI_SEL_AFIO_MODE       (AFIO_FUN_GPIO)
#define LCD_SPI_SEL_CLK(CK)         (CK.Bit.PC)

#define LCD_SPI_BL_ENABLE           (1)
#define LCD_SPI_BL_GPIO_ID          (GPIO_PB)               // D9
#define LCD_SPI_BL_GPIO_PIN         (GPIO_PIN_2)
#define LCD_SPI_BL_AFIO_MODE        (AFIO_FUN_GPIO)
#define LCD_SPI_BL_CLK(CK)          (CK.Bit.PB)

#define LCD_SPI_RST_GPIO_ID         (GPIO_PD)               // D8
#define LCD_SPI_RST_GPIO_PIN        (GPIO_PIN_3)
#define LCD_SPI_RST_AFIO_MODE       (AFIO_FUN_GPIO)
#define LCD_SPI_RST_CLK(CK)         (CK.Bit.PD)
/**
  * @}
  */

/** @addtogroup BM18B367A_DVB_I2C_EEPROM
  * @{
  */
#define EEPROM_I2C_CLK(CK)          (CK.Bit.I2C1)
#define EEPROM_I2C                  (HT_I2C1)

#define EEPROM_I2C_SCL_GPIO_ID      (GPIO_PC)               // A5/D19
#define EEPROM_I2C_SCL_AFIO_PIN     (AFIO_PIN_4)
#define EEPROM_I2C_SCL_AFIO_MODE    (AFIO_FUN_I2C)

#define EEPROM_I2C_SDA_GPIO_ID      (GPIO_PC)               // A4/D18
#define EEPROM_I2C_SDA_AFIO_PIN     (AFIO_PIN_5)
#define EEPROM_I2C_SDA_AFIO_MODE    (AFIO_FUN_I2C)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup BM18B367A_DVB_Exported_Functions BM18B367A Development Board exported functions
  * @{
  */
#define HT32F_DVB_USBConnect()      USBD_DPpullupCmd(ENABLE)
#define HT32F_DVB_USBDisConnect()   USBD_DPpullupCmd(DISABLE)
#define HT32F_DVB_GPxConfig         AFIO_GPxConfig

#define HT32F_DVB_BuzzerInit(hFreq, bDuty)    HT32F_DVB_BuzzerFun(hFreq, bDuty, 0);
#define HT32F_DVB_BuzzerConfig(hFreq, bDuty)  HT32F_DVB_BuzzerFun(hFreq, bDuty, 1);


void HT32F_DVB_LEDInit(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDOn(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDOff(LED_TypeDef HT_LEDn);
void HT32F_DVB_LEDToggle(LED_TypeDef HT_LEDn);

void HT32F_DVB_PBInit(BUTTON_TypeDef BUTTON_x, BUTTON_MODE_TypeDef BUTTON_MODE_x);
u32 HT32F_DVB_PBGetState(BUTTON_TypeDef BUTTON_x);

void HT32F_DVB_COMInit(COM_TypeDef COMn, USART_InitTypeDef* USART_InitStructure);

void HT32F_DVB_BuzzerFun(u16 hFreq, u8 bDuty, u32 mode);
void HT32F_DVB_BuzzerOutputCmd(ControlStatus Control);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#include "common/i2c_eeprom.h"
#include "common/spi_flash.h"
#include "common/spi_lcd.h"


#ifdef __cplusplus
}
#endif

#endif
