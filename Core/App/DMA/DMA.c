#include "DMA.h"
#include "GPIO.h"
#include "USART.h"
#include "stm32_hal_legacy.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_dma_ex.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_uart.h"
#include <stdint.h>

DMA_HandleTypeDef DMAInit_M2M;
DMA_HandleTypeDef DMAInit_M2PHandle;

void DMA_Init_M2M(uint32_t *dst)
{

    // clock
    __HAL_RCC_DMA1_CLK_ENABLE();

    DMAInit_M2M.Instance = DMA1_Channel6;

    DMAInit_M2M.Init.Direction = DMA_MEMORY_TO_MEMORY;
    DMAInit_M2M.Init.Mode      = DMA_NORMAL;
    DMAInit_M2M.Init.Priority  = DMA_PRIORITY_MEDIUM;

    DMAInit_M2M.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DMAInit_M2M.Init.MemInc           = DMA_MINC_ENABLE;

    DMAInit_M2M.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DMAInit_M2M.Init.PeriphInc           = DMA_PINC_ENABLE;

    HAL_DMA_Init(&DMAInit_M2M);
}

void DMA_Init_M2P(void)
{

    __HAL_RCC_DMA1_CLK_ENABLE();

    DMAInit_M2PHandle.Instance       = DMA1_Channel4;
    DMAInit_M2PHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    DMAInit_M2PHandle.Init.Mode      = DMA_NORMAL;
    DMAInit_M2PHandle.Init.Priority  = DMA_PRIORITY_HIGH;

    DMAInit_M2PHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    DMAInit_M2PHandle.Init.MemInc           = DMA_MINC_ENABLE;

    DMAInit_M2PHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DMAInit_M2PHandle.Init.PeriphInc           = DMA_PINC_DISABLE;

    HAL_DMA_Init(&DMAInit_M2PHandle);

    __HAL_LINKDMA(&UARTHandle, hdmatx, DMAInit_M2PHandle); // LINK DMA to Peripherals
}

int8_t BufferCMP(const uint32_t *src, uint32_t *dst, uint32_t Len)
{

    while (Len--) {

        if (*src != *dst)
            return -1;

        src++;
        dst++;
    }

    return 0;
}

extern int __io_putchar(int ch);
extern int __io_getchar(void);

const static uint32_t SRC_DATA[DMASIZE] = {
    0xdddddd00,
    0xdddddd01,
    0xdddddd02,
    0xdddddd03,
    0xdddddd04,
    0xdddddd05,
    0xdddddd06,
    0xdddddd07,
    0xdddddd08,
    0xdddddd09,
};

void Prac_DMA(void)
{

    uint32_t DST_DATA[DMASIZE];
    memset(DST_DATA, 0, DMASIZE);

    DMA_Init_M2M(DST_DATA);
    USART1_Init();

    printf("hello world\n");

    int8_t res;
    uint8_t len = DMASIZE;

    while (__HAL_DMA_GET_FLAG(&DMAInit_M2M, DMA_FLAG_TC6) == RESET) {
    }

    res = BufferCMP(SRC_DATA, DST_DATA, len);
    if (res)
        HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);

    while (1) {
        if (len) {
            uint32_t *dst = DST_DATA;
            uint32_t num;
            while (len--) {
                num = *dst++;
                printf("Data: %lx at[%p], len:%d\n", num, dst, len);
                HAL_Delay(1000);
            }
        }

        len = DMASIZE;
    }
}

static char SRC_BYTE[DMASIZE];

void Prac_DMA_2(void)
{

    USART1_Init_DMA();
    DMA_Init_M2P();

    memset(SRC_BYTE, 'Z', DMASIZE - 2);
    SRC_BYTE[DMASIZE - 1] = '\n';

    HAL_StatusTypeDef st = HAL_UART_Transmit_DMA(&UARTHandle, (uint8_t *)SRC_BYTE, DMASIZE);
    while (1) {
        HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
        HAL_Delay(1000);
    }
}