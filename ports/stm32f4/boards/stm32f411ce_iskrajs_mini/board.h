/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ha Thach for Adafruit Industries
 * Copyright (c) 2022 Roman Samusevich(kekcheburec) for Amperka Robots LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BOARD_H_
#define BOARD_H_

//--------------------------------------------------------------------+
// LED
//--------------------------------------------------------------------+

#define LED_PORT              GPIOB
#define LED_PIN               GPIO_PIN_12
#define LED_STATE_ON          1

//--------------------------------------------------------------------+
// Neopixel
//--------------------------------------------------------------------+

// Number of neopixels
#define NEOPIXEL_NUMBER       0

//--------------------------------------------------------------------+
// Flash
//--------------------------------------------------------------------+

// Flash size of the board
#define BOARD_FLASH_SIZE      (512 * 1024)
#define BOARD_FLASH_SECTORS   8

#define CUSTOM_BOARD_FLASH_APP_START 0x08008000

//--------------------------------------------------------------------+
// Security (future)
//--------------------------------------------------------------------+

#define PROTECT_BOOTLOADER    0

//--------------------------------------------------------------------+
// USB UF2
//--------------------------------------------------------------------+

#define USB_VID           0x239A
#define USB_PID           0x0069
#define USB_MANUFACTURER  "Amperka"
#define USB_PRODUCT       "IskraJS Mini"

#define UF2_PRODUCT_NAME  USB_MANUFACTURER " " USB_PRODUCT
#define UF2_BOARD_ID      "STM32F411-IskraJS-Mini"
#define UF2_VOLUME_LABEL  "IskraJSMini"
#define UF2_INDEX_URL     "https://amperka.ru/product/iskra-js-mini"
#define UF2_DESCRIPTION   "Для обновления прошивки, скопируйте файл с расширением UF2 на диск " UF2_VOLUME_LABEL

#define USB_NO_VBUS_PIN   1

//--------------------------------------------------------------------+
// UART
//--------------------------------------------------------------------+

#define UART_DEV              USART1
#define UART_CLOCK_ENABLE     __HAL_RCC_USART1_CLK_ENABLE
#define UART_CLOCK_DISABLE    __HAL_RCC_USART1_CLK_DISABLE
#define UART_GPIO_PORT        GPIOB
#define UART_GPIO_AF          GPIO_AF7_USART1
#define UART_TX_PIN           GPIO_PIN_6
#define UART_RX_PIN           GPIO_PIN_7

//--------------------------------------------------------------------+
// RCC Clock
//--------------------------------------------------------------------+
static inline void clock_init(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = HSE_VALUE/1000000;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

#endif