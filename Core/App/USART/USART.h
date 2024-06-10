#ifndef __USART_H
#define __USART_H

#include "main.h"

// USART configuration
#define BAUDRATE 115200
void USART1_Init(void);

// for re-directed stdio
void USART_String(uint8_t *str);


// For buffer receive
#define BUFSIZE 10
extern UART_HandleTypeDef UARTHandle;
extern GPIO_InitTypeDef  GPIOInit;
extern char Buffer[BUFSIZE];
extern uint16_t Rxlen;
extern uint8_t Rxflag;

void USART1_Init_DMA(void);





void Prac_USART_Buffer(void);
void Prac_USART(void);
void Prac_USART_LED(void);



#endif