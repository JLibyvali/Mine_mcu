#include "EEPROM.h"
#include "IIC.h"
#include <stdint.h>

uint8_t ee_CheckDev(uint16_t Addr)
{

    uint8_t ack;
    i2c_start();

    i2c_sendB(Addr | EEPROM_I2C_WT);
    ack = i2c_waitACK();

    i2c_stop();
    return ack;
}

uint8_t ee_ReadB(uint8_t *ReadBuf, uint16_t Addr, uint16_t size)
{
}
uint8_t ee_WriteB(uint8_t *WriteBuf, uint16_t Addr, uint16_t size){




    
}