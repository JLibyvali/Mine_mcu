#ifndef __IIC_H
#define __IIC_H

#include "main.h"

#define EEPROM_I2C_PORT GPIOF
#define EEPROM_SCL_PIN GPIO_PIN_6
#define EEPROM_SDA_PIN GPIO_PIN_7

#define I2C_SCL_1       HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SCL_PIN, GPIO_PIN_SET);
#define I2C_SCL_0       HAL_GPIO_WritePin(EEPROM_I2C_PORT,EEPROM_SCL_PIN,GPIO_PIN_RESET);
#define I2C_SDA_1       HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SDA_PIN, GPIO_PIN_SET);
#define I2C_SDA_0       HAL_GPIO_WritePin(EEPROM_I2C_PORT,EEPROM_SDA_PIN,GPIO_PIN_RESET);


extern GPIO_InitTypeDef GPIO_Handle;

void I2C_Delay(void);

void I2CInit(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_sendB(uint8_t Byte);
uint8_t i2c_readB(void);
uint8_t i2c_waitACK(void);
void i2c_ack(void);
void i2c_nack(void);








#endif