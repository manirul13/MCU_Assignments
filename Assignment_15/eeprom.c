#include "eeprom.h"
#include "i2c.h"
#include <xc.h>
#define _XTAL_FREQ 20000000
unsigned char ext_eeprom_24C02_read(unsigned char addr)
{
    unsigned char data;

    //sending start bit in i2c bus
    i2c_start();
    //sending the slave address byte with write bit LSB
    i2c_write(SLAVE_WRITE_EEPROM);
    //writing the address to the slave to write the data in that address
    i2c_write(addr);  
    //restarting the I2C bus
    i2c_rep_start();    
    //sending the slave address byte with read bit LSB
    i2c_write(SLAVE_READ_EEPROM);    
    //reading the data from SSPBUFF
    data = i2c_read(0);   
    //sending stop bit to make ready the I2C bus for further transmissions  
    i2c_stop();

    return data;
}

void ext_eeprom_24C02_byte_write(unsigned char addr, char data)
{
    //sending start bit in I2C bus
    i2c_start();  
    //sending the slave address byte with write bit LSB
    i2c_write(SLAVE_WRITE_EEPROM);   
    //writing the address to the slave to write the data in that address
    i2c_write(addr);   
    //sending stop bit to make ready the I2C bus further transmissions
    i2c_write(data);    
    //sending stop bit to make ready the I2C bus for further transmissions
    i2c_stop();
    __delay_ms(5);
}
