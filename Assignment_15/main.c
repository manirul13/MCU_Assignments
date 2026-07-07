/*
 * File:   main.c
 * Author: Manirul 
 * Assignmeent: SSD numbering and store in eeprom when press the key and later can show stored number by pressing other key
 */
#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"
#include "eeprom.h"
#include "i2c.h"

#pragma config WDTE = OFF

#define _XTAL_FREQ 20000000
#define LONG_PRESS_LIMIT 40 // ~2 seconds at 50ms tick

static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};

static void init_config(void) {
    init_ssd();
    init_digital_keypad();
    init_i2c(100000); // 100 kHz I2C speed
}

void load_count_from_eeprom(int *count) {
    unsigned char high = ext_eeprom_24C02_read(0x00);
    unsigned char low = ext_eeprom_24C02_read(0x01);
    *count = (high << 8) | low;

    if (*count > 9999) // Invalid stored value
        *count = 0;
}

void store_count_to_eeprom(int count) {
    unsigned char high = (count >> 8) & 0xFF;
    unsigned char low = count & 0xFF;
    ext_eeprom_24C02_byte_write(0x00, high);
    ext_eeprom_24C02_byte_write(0x01, low);
}

void main(void) {
    int count = 0;
    unsigned char key;
    unsigned char key_press = 0;
    int time = 0;
    int delay = 50; // 50ms display refresh

    init_config();

    // Load stored value from EEPROM at startup
    load_count_from_eeprom(&count);

    while (1) {
        // Refresh SSD periodically
        if (--delay == 0) {
            delay = 50;
            ssd[0] = digit[count / 1000];
            ssd[1] = digit[(count / 100) % 10];
            ssd[2] = digit[(count / 10) % 10];
            ssd[3] = digit[count % 10];
        }
        display(ssd);

        key = read_digital_keypad(LEVEL);

        // --- DKPS1: count / reset ---
        if (key == SW1) // Key held
        {
            if (key_press == 0) // First press
            {
                key_press = 1;
                time = 0;
            } else {
                time++;
                if (time > LONG_PRESS_LIMIT) // Long press 
                {
                    count = 0; // Reset counter in RAM only
                    time = 0;
                    key_press = 0;
                }
            }
        } else // Key released
        {
            if (key_press == 1 && time > 0 && time <= LONG_PRESS_LIMIT) // Short press
            {
                count++;
                if (count > 9999)
                    count = 0;
            }
            key_press = 0;
            time = 0;
        }

        // --- DKPS2: store ---
        if (key == SW2) {
            store_count_to_eeprom(count);
        }
    }
}
