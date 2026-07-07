/*
 * File:   main.c
 * Author: Manirul
 * Assignmeent: CLCD show right scrolling of message WELCOME or else
 */

#include <xc.h>
#include "clcd.h"
#include <string.h>

#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void)
{
    init_clcd();
}

void delay_ms(unsigned int ms)
{
    while (ms--)
        __delay_ms(1);
}

void main(void)
{
    init_config();

    const char *message = "WELCOME";
    char display[17]; // 16 characters + null terminator
    int i;

    while (1)
    {
        for (i = 0; i <= (16 - 1); i++)
        {
            for (int j = 0; j < 16; j++)
                display[j] = '_'; /// fill buffer with underscore
            display[16] = '\0';

            for (int k = 0; message[k] != '\0' && (i + k) < 16; k++)
            {
                display[i + k] = message[k];
            }

            clcd_print("RIGHT SCROLLING:", LINE1(0));
            clcd_print(display, LINE2(0));

            __delay_ms(SCROLL_DELAY_MS); // 0.5 Hz
        }
    }
    return;
}
