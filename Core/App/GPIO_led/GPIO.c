#include "GPIO.h"


void LED_GPIO_Init(void)
{

    GPIO_InitTypeDef LED_Init;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    LED_Init.Pin   = LED1_PIN;
    LED_Init.Mode  = GPIO_MODE_OUTPUT_PP;
    LED_Init.Pull  = GPIO_PULLDOWN;
    LED_Init.Speed = GPIO_SPEED_FREQ_HIGH; // High for 50Mhz

    HAL_GPIO_Init(LED1_PORT, &LED_Init);
    HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
}


