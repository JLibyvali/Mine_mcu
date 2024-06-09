#include "USART.h"
#include "GPIO.h"
#include "stm32f1xx_hal_uart.h"
#include <stdint.h>

UART_HandleTypeDef UARTHandle;
char Buffer[BUFSIZE];
uint16_t Rxlen;
uint8_t Rxflag;

void USART1_Init(void)
{

    UARTHandle.Instance = USART1;

    UARTHandle.Init.BaudRate   = BAUDRATE;
    UARTHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UARTHandle.Init.Mode       = UART_MODE_TX_RX;
    UARTHandle.Init.Parity     = UART_PARITY_NONE;
    UARTHandle.Init.StopBits   = UART_STOPBITS_1;
    UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;

    if (HAL_UART_Init(&UARTHandle) != HAL_OK) {
        printf("USART1 Init fail\n");
    }
    // Use the RXNE and IDLE interrupt
    // __HAL_UART_ENABLE_IT(&UARTHandle, UART_IT_RXNE);
    // __HAL_UART_ENABLE_IT(&UARTHandle, UART_IT_IDLE);
    // __HAL_UART_CLEAR_IDLEFLAG(&UARTHandle);
}

// MspInit() all are _weak_define, So if you  define yours,
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

    GPIO_InitTypeDef GPIOInit;

    // GPIOA9 ----> USART1_TX
    // GPIOA10 ---> USART1_RX
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIOInit.Pin   = USART1_TX_PIN;
    GPIOInit.Mode  = GPIO_MODE_AF_PP;
    GPIOInit.Pull  = GPIO_PULLUP;
    GPIOInit.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(USART1_TX_PORT, &GPIOInit);

    GPIOInit.Pin  = USART1_RX_PIN;
    GPIOInit.Mode = GPIO_MODE_AF_INPUT;

    HAL_GPIO_Init(USART1_RX_PORT, &GPIOInit);

    // HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(USART1_IRQn);
}

// re-directed of stdio
void USART_String(uint8_t *str)
{

    uint8_t k = 0;

    do {
        HAL_UART_Transmit(&UARTHandle, (uint8_t *)(str + k), 1, 1000);
        k++;
    } while (*(str + k) != '\0');
}

// Overwrite of 'IO' systemcalls, re-directed printf() and scanf() to USART
int __io_putchar(int ch)
{

    HAL_UART_Transmit(&UARTHandle, (uint8_t *)(&ch), 1, 1000);
    return (ch);
}

int __io_getchar(void)
{

    uint8_t ch = 0;
    HAL_UART_Receive(&UARTHandle, &ch, 1, 1000);
    return ch;
}

void Prac_USART(void)
{

    USART1_Init();
    printf("Welcome to STM32f1xxxxxx\n");

    while (1) {
    }
}

void Prac_USART_LED(void)
{

    USART1_Init();
    printf("Welcome to STM32f1xxxxxx\n");

    printf("Input num 1 for LED off\n");
    printf("Input num 0 for LED on\n");

    // use the interrupt
    while (1) {
    }
}

void Prac_USART_Buffer(void)
{

    USART1_Init();
    printf("Helo\n");

    // Ready for receiving data
    HAL_UART_Receive_IT(&UARTHandle, (uint8_t*)&Buffer, BUFSIZE);


    while(1){

            if(Rxflag == 1){
                printf("Total received bytes: %d\n",Rxlen);
                Rxlen  = Rxlen > BUFSIZE ? BUFSIZE : Rxlen;

                HAL_UART_Transmit(&UARTHandle,(uint8_t*)&Buffer,Rxlen,1000);
                memset(Buffer,0,Rxlen);

                // After receive data once, restart.
                HAL_UART_Receive_IT(&UARTHandle, (uint8_t*)&Buffer, BUFSIZE);
                Rxflag  = 0;
                Rxlen = 0;
            }

    }
}

/**
 * @brief  Rx Transfer completed callbacks.
 * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
 *                the configuration information for the specified UART module.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1){
        
        // When one time data-recevie completed,
        Rxlen += UARTHandle.RxXferSize;
        HAL_UART_Receive_IT(&UARTHandle, (uint8_t*)&Buffer, BUFSIZE);

    }
}
