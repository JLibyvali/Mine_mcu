#include "USART.h"
#include "stm32f1xx_hal_uart.h"


UART_HandleTypeDef UARTHandle;

void USART1_Init(void){

    UARTHandle.Instance = USART1;

    UARTHandle.Init.BaudRate = BAUDRATE;
    UARTHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UARTHandle.Init.Mode = UART_MODE_TX_RX;
    UARTHandle.Init.Parity = UART_PARITY_NONE;
    UARTHandle.Init.StopBits = UART_STOPBITS_1;
    UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;


    HAL_UART_Init(&UARTHandle);
    __HAL_UART_ENABLE_IT(&UARTHandle,UART_IT_RXNE);

}

// MspInit() all are _weak_define, So if you  define yours, 
void HAL_UART_MspInit(UART_HandleTypeDef *huart){

   GPIO_InitTypeDef GPIOInit;

    // GPIOA9 ----> USART1_TX
    // GPIOA10 ---> USART1_RX
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();


   GPIOInit.Pin = USART1_TX_PIN;
   GPIOInit.Mode = GPIO_MODE_AF_PP;
   GPIOInit.Pull = GPIO_PULLUP;
   GPIOInit.Speed = GPIO_SPEED_FREQ_HIGH;

   HAL_GPIO_Init(USART1_TX_PORT, &GPIOInit);

   GPIOInit.Pin = USART1_RX_PIN;
   GPIOInit.Mode = GPIO_MODE_AF_INPUT;

   HAL_GPIO_Init(USART1_RX_PORT, &GPIOInit);

   HAL_NVIC_SetPriority(USART1_IRQn, 0 , 1);
   HAL_NVIC_EnableIRQ(USART1_IRQn);

}


// re-directed of stdio
void USART_String(uint8_t *str){

    uint8_t k = 0;

    do{
        HAL_UART_Transmit(&UARTHandle, (uint8_t*)(str+k), 1, 1000);
        k++;
    }while(*(str+k) != '\0');

}

int fputc(int ch, FILE *f){

    HAL_UART_Transmit(&UARTHandle, (uint8_t*)(ch), 1, 1000);
    return (ch);

}

int fgetc(FILE *f){

    int ch = 0;
    HAL_UART_Transmit(&UARTHandle, (uint8_t*)(&ch), 1, 1000);

    return (ch);

}



void Prac_USART(void){

    USART1_Init();
    printf("Welcome to STM32f1xxxxxx\n");
    USART_String((uint8_t*)("Hell, World\n"));


    while (1) {
    
    }

}
