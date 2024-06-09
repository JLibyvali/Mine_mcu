#ifndef __DMA_H
#define __DMA_H

#include "main.h"

#define DMASIZE 20
void DMA_Init();
int8_t BufferCMP(const uint32_t* src, uint32_t* dst, uint32_t Len);
void Prac_DMA(void);




#endif 