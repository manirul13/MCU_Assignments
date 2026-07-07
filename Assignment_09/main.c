/*
 * File:   main.c
 * Author: Manirul 
 * Assignmeent: SSD self counter upto 0 to 9, if SW1 is press left marquee, else SW2 is press right marquee
 *              and SW3 is for STOP left and right marquee;
 */
#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF    // Watchdog Timer Disable

#define _XTAL_FREQ 20000000  // 20 MHz Crystal

/* Hardcoded number + spaces for marquee */
unsigned char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SPACE, SPACE};

unsigned char ssd[MAX_SSD_CNT];
int direction = 1; // 1 = left, -1 = right
int pos = 0;       // Current scroll start index
unsigned char running = 1; // 1 = scrolling, 0 = stopped

void init_config(void)
{
    init_ssd();
    init_digital_keypad();
}

void update_display()
{
    for (int i = 0; i < MAX_SSD_CNT; i++)
    {
        int index = (pos + i) % sizeof(digits);
        if (index < 0) index += sizeof(digits); // Handle negative for right scroll
        ssd[i] = digits[index];
    }
}

void main(void)
{
    init_config();
    unsigned long delay_count = 0;

    while (1)
    {
        unsigned char key = read_digital_keypad(STATE_DETECTION);

        if (key == SW1) // Left
        {
            direction = 1;
            running = 1;
        }
        else if (key == SW2) // Right
        {
            direction = -1;
            running = 1;
        }
        else if (key == SW3) // Start/Stop toggle
        {
            running = !running;
        }

        if (++delay_count >= 1000) // Adjust for ~0.5Hz
        {
            delay_count = 0;

            if (running)
            {
                pos += direction;
                if (pos >= sizeof(digits)) pos = 0;
                else if (pos < 0) pos = sizeof(digits) - 1;
            }
        }

        update_display();
        display(ssd);
    }
}
