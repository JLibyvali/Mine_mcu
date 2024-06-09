#include "DMA.h"
#include "GPIO.h"
#include "USART.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>

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

DMA_HandleTypeDef DMAInit;

void DMA_Init(uint32_t* dst)
{

    HAL_StatusTypeDef DMA_State = HAL_ERROR;

    // clock
    __HAL_RCC_DMA1_CLK_ENABLE();

    DMAInit.Instance = DMA1_Channel6;

    DMAInit.Init.Direction        = DMA_MEMORY_TO_MEMORY;
    DMAInit.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DMAInit.Init.MemInc           = DMA_MINC_ENABLE;

    DMAInit.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DMAInit.Init.PeriphInc           = DMA_PINC_ENABLE;
    DMAInit.Init.Mode                = DMA_NORMAL;
    DMAInit.Init.Priority            = DMA_PRIORITY_MEDIUM;

    HAL_DMA_Init(&DMAInit);
    DMA_State = HAL_DMA_Start(&DMAInit, (uint32_t)SRC_DATA, (uint32_t)dst, DMASIZE);

    if (DMA_State != HAL_OK) {

        while (1) {
            HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
            HAL_Delay(200);
        }
    }
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


void Prac_DMA(void)
{

    uint32_t DST_DATA[DMASIZE];

    memset(DST_DATA,0,DMASIZE);

    USART1_Init();
    DMA_Init(DST_DATA);

    printf("hello world\n");

    int8_t res;
    uint8_t len = DMASIZE;

    while (__HAL_DMA_GET_FLAG(&DMAInit, DMA_FLAG_TC6) == RESET) {
    }

   res = BufferCMP(SRC_DATA, DST_DATA, len) ;
    if(res)
        HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
    else 
        HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);

    while (1) {
            if(len){
                uint32_t* dst = DST_DATA; 
                uint32_t num;
                while (len--) {
                    num = *dst++;
                    printf("Data: %lx at[%p], len:%d\n",num,dst,len);
                    HAL_Delay(1000);
                }
            }

            len  = DMASIZE;
    }
    
}