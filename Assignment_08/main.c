/*
 * File:   main.c
 * Author: Manirul 
 * Assignmeent: SSD self counter upto 9999 and for long press (~ 2 sec) goes to reset
 */
#include <xc.h>
#include "ssd.h"

#pragma config WDTE = OFF    // Watchdog Timer Enable bit

static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};

static void init_config(void) {
    init_ssd();
    TRISB0 = 1; // Make RB0 (DKPS1) input
}

void main(void) {

    int count = 0, time = 0;
    int delay = 50;
    unsigned char key_press = 0;

    init_config();

    while (1) {
        
        if (--delay == 0)
        {
            delay = 50;
  
        // Convert & update count to digits for SSD 
        ssd[0] = digit[count / 1000];
        ssd[1] = digit[(count / 100) % 10];
        ssd[2] = digit[(count / 10) % 10];
        ssd[3] = digit[count % 10];
        }
        display(ssd); 
        
        //key pressed 
        if (DKPS1 == 0)
        {
            if (key_press == 0)
            {
                key_press = 1;
                time = 0;
            }
            else
            {
                time ++;
                if (time > 40)  // ~2 seconds long press
                {
                    count = 0;
                    time = 0;
                    key_press = 0;
                }
            }
        }
        else 
        {
            if (key_press == 1 && time > 0 && time <= 40)
            {
                count++;
                if (count > 9999)
                {
                    count = 0;
                }
            }
            
            key_press = 0;
            time = 0;
        }
        
    }
}
