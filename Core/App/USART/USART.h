#ifndef __USART_H
#define __USART_H

#include "GPIO.h"
#include "main.h"


// USART configuration
#define BAUDRATE 115200
void USART1_Init(void);

// for re-directed stdio
void USART_String(uint8_t *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

void Prac_USART(void);



#endif