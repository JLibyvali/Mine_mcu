#include "GPIO.h"
#include "main.h"


void LED_GPIO_Init(void)
{

    GPIO_InitTypeDef LED_Init;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    LED_Init.Pin   = LED1_PIN;
    LED_Init.Mode  = GPIO_MODE_OUTPUT_PP;
    LED_Init.Pull  = GPIO_PULLDOWN;
    LED_Init.Speed = GPIO_SPEED_FREQ_HIGH; // High for 50Mhz

    HAL_GPIO_Init(LED1_PORT, &LED_Init);
    HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
}

void EXIT_GPIO_Init(void)
{
    // using GPIOB4 ---> GPIOB3, to test the external interrupt
    GPIO_InitTypeDef GPIOInit = {0};

    // Enable clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // interrupt gpio pin3
    GPIOInit.Pin   = EXIT_GPIO_PIN;
    GPIOInit.Mode  = GPIO_MODE_IT_RISING; // rising edge
    GPIOInit.Pull  = GPIO_NOPULL;
    GPIOInit.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(EXIT_GPIO_PORT, &GPIOInit);
    HAL_GPIO_WritePin(EXIT_GPIO_PORT, EXIT_GPIO_PIN, GPIO_PIN_SET);

    HAL_NVIC_SetPriority(EXIT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXIT_IRQn);

    // send data pin4
    GPIOInit.Pin   = SEND_DATA_PIN;
    GPIOInit.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIOInit.Pull  = GPIO_PULLDOWN;
    GPIOInit.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(SEND_DATA_PORT, &GPIOInit);
    HAL_GPIO_WritePin(SEND_DATA_PORT, SEND_DATA_PIN, GPIO_PIN_SET);
}


void Prac2(void){

    HAL_Init();
    // SystemClock_Config();
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    // GPIO
    LED_GPIO_Init();
    EXIT_GPIO_Init();

    while (1) {
       HAL_GPIO_TogglePin(SEND_DATA_PORT, SEND_DATA_PIN); 
       HAL_Delay(300);
    }


}