#include "IIC.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>

GPIO_InitTypeDef GPIO_Handle;
void I2C_Delay(void)
{
    // miliseconds
    HAL_Delay(1U);
}

void i2c_start(void)
{

    // When SCL high, SDA drop down means Signal 'S'
    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SCL_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SDA_PIN, GPIO_PIN_SET);
    I2C_Delay();

    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SDA_PIN, GPIO_PIN_RESET);
    I2C_Delay();
    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SCL_PIN, GPIO_PIN_RESET);
    I2C_Delay();
}
void i2c_stop(void)
{

    // When SCL High, SDA rise up means Signal 'P'
    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SDA_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SCL_PIN, GPIO_PIN_SET);
    I2C_Delay();

    HAL_GPIO_WritePin(EEPROM_I2C_PORT, EEPROM_SDA_PIN, GPIO_PIN_SET);
}

void i2c_sendB(uint8_t Byte)
{

    uint8_t i;
    for (i = 0; i < 8; i++) {

        // High 7 bits
        // Send bits, the first output bit as the highest bit
        if (Byte & 0x80)
            I2C_SDA_1
        else
            I2C_SDA_0

        I2C_Delay();
        I2C_SCL_1

        I2C_Delay();
        I2C_SCL_0

        if (i == 7) {
            // for ank Signal
            I2C_SDA_1
        }

        Byte <<= 1;
        I2C_Delay();
    }
}
uint8_t i2c_readB(void)
{

    uint8_t i;
    uint8_t res;

    res = 0;
    for (i = 0; i < 8; i++) {
        // read bits, First input bis as the highest  bit
        res <<= 1;
        I2C_SCL_1

        I2C_Delay();

        if (HAL_GPIO_ReadPin(EEPROM_I2C_PORT, EEPROM_SDA_PIN)) {
            res++;
        }

        I2C_SCL_0

        I2C_Delay();
    }

    return res;
}

uint8_t i2c_waitACK(void)
{

    uint8_t re;

    I2C_SDA_1
    I2C_Delay();
    I2C_SCL_1
    I2C_Delay();

    if (HAL_GPIO_ReadPin(EEPROM_I2C_PORT, EEPROM_SDA_PIN))
        re = 1;
    else
        re = 0;

    I2C_SCL_0
    I2C_Delay();

    return re;
}

void i2c_ack(void)
{

    // When after the data-bytes
    // SCL high , SDA  low is ACK
    I2C_SDA_0
    I2C_Delay();

    I2C_SCL_1
    I2C_Delay();
    I2C_SCL_0

    I2C_Delay();
    I2C_SDA_1
}
void i2c_nack(void)
{

    // When after the data-bytes
    // SCL high, SDA high is NOACK

    I2C_SDA_1
    I2C_Delay();

    I2C_SCL_1
    I2C_Delay();
    I2C_SCL_0

    I2C_Delay();
}

void I2CInit(void)
{

    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_Handle.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_Handle.Pin   = EEPROM_SCL_PIN | EEPROM_SDA_PIN;
    GPIO_Handle.Pull  = GPIO_NOPULL;
    GPIO_Handle.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(EEPROM_I2C_PORT, &GPIO_Handle);

    i2c_stop();
}
