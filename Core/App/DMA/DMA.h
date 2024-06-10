#ifndef __DMA_H
#define __DMA_H

#include "main.h"
#include <stdint.h>

#define DMASIZE 20
void DMA_Init_M2M(uint32_t* dst);
void DMA_Init_M2P(void);

int8_t BufferCMP(const uint32_t* src, uint32_t* dst, uint32_t Len);

void Prac_DMA(void);
void Prac_DMA_2(void);




#endif 