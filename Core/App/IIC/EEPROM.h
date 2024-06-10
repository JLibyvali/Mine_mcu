#ifndef __EEPROM_H
#define __RRPROM_H

//AT24C02 8Bytes/Page, total 2048bytes
/*
Device Address:
1 0 1 0 A2 A1 A0 R/W
1 0 1 0 0  0  0  0 = 0XA0       Write Adress
1 0 1 0 0  0  0  1 = 0XA1       Read Address 



*/

#include "main.h"
#include "IIC.h"


#define EEPROM_Wadd 0xA0
#define EEPROM_PG 8
#define EEPROM_PG_NUM 256
#define EEPROM_I2C_RD 1
#define EEPROM_I2C_WT 0



uint8_t ee_ReadB(uint8_t* ReadBuf, uint16_t Addr, uint16_t size);
uint8_t ee_WriteB(uint8_t* WriteBuf, uint16_t Addr, uint16_t size);
uint8_t ee_CheckDev(uint16_t Addr);

void ee_Erase(uint16_t Addr);
uint8_t ee_Wait(void);
uint8_t ee_test(void);





#endif