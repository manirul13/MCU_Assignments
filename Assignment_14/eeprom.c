
#include <xc.h>
#include "eeprom.h"

void eeprom_write(unsigned char address, unsigned char data) {
    while (WR);  // wait for previous write
    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;  // data memory
    //EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;

    INTCONbits.GIE = 0;  // disable interrupt
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;

    EECON1bits.WREN = 0;
}

unsigned char eeprom_read(unsigned char address) {
    EEADR = address;
    EECON1bits.EEPGD = 0;
    //EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    return EEDATA;
}
