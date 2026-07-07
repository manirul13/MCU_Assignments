/*
 * File:   main.c
 * Author: Manirul 
 * Assignmeent: SSD self counter upto 9999
 */
#include <xc.h>
#include "ssd.h"
#include "eeprom.h"

#pragma config WDTE = OFF    // Watchdog Timer Enable bit

static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};

static void init_config(void) {
    init_ssd();
    TRISB1 = 1;  // Make RB1 (DKPS2) input
}

void main(void) {
    unsigned int count = 0;
    unsigned char delay = 50;
    unsigned char prev_key = 0;

    init_config();

    // Read count from EEPROM (address 0x00 high byte, 0x01 low byte)
    unsigned char high_byte = eeprom_read(0x00);
    unsigned char low_byte = eeprom_read(0x01);
    count = ((unsigned int)high_byte << 8) | low_byte;

    while (1) {
        // Convert count to digits for SSD
        ssd[0] = digit[count / 1000];
        ssd[1] = digit[(count / 100) % 10];
        ssd[2] = digit[(count / 10) % 10];
        ssd[3] = digit[count % 10];

        if (--delay == 0) {
            delay = 50;
            count++;
            if (count > 9999)
                count = 0;
        }

        display(ssd);

        // Store count if DKPS2 (RB1) is pressed (falling edge detection)
        if (DKPS2 == 1 && prev_key == 0) {
            // Save current count to EEPROM
            eeprom_write(0x00, (count >> 8) & 0xFF);  // High byte
            eeprom_write(0x01, count & 0xFF);         // Low byte
            prev_key = 1;
        } else if (DKPS2 == 0) {
            prev_key = 0;
        }
    }
}
