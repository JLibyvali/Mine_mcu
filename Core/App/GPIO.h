/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.h
 * @brief   This file contains all the function prototypes for
 *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define LED1_PORT      GPIOC
#define LED1_PIN       GPIO_PIN_13

void LED_GPIO_Init(void); // led display

//###################################################################################
// For external interrupt , REMEMBER: write the handler in xxxxxx_it_.c
// Implement function in ExternalIT.c
//###################################################################################
#define SEND_DATA_PORT GPIOB
#define SEND_DATA_PIN  GPIO_PIN_4
#define EXIT_GPIO_PORT GPIOB
#define EXIT_GPIO_PIN  GPIO_PIN_3

#define EXIT_IRQn      EXTI3_IRQn
#define EXIT_IRQHandler EXTI3_IRQHandler
void EXIT_GPIO_Init(void); // external interrupt






#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
