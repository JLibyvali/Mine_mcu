/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


#include "gpio.h"
#include "stm32_hal_legacy.h"
#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef LED_Init;  
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  LED_Init.Pin = LED1_PIN;
  LED_Init.Mode = GPIO_MODE_OUTPUT_PP;
  LED_Init.Pull = GPIO_PULLUP;
  LED_Init.Speed = GPIO_SPEED_FREQ_HIGH;  // High for 50Mhz

  HAL_GPIO_Init(LED1_PORT, &LED_Init);
  HAL_GPIO_WritePin(LED1_PORT,LED1_PIN, RESET);
 
}
