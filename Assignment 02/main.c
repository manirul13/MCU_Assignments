/*
 * File:   main.c
 * Author: Emertxe
 * Problem Statement : Write a Embedded C program to display the multiple patterns on the LEDs controlled by the switches.
 *                     For every switch, dedicate a LEDs glow pattern.The pattern should change on key press
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF

static void init_config(void) {
    /*To keep all LEDS OFF initially*/
    LED_ARRAY1 = OFF;

    /*To configure PORTD as output PORT*/
    LED_ARRAY1_DDR = 0x00;

    /* Initializing digital keypad */
    init_digital_keypad();

}

void main(void) {
    //Variable declaration
    unsigned char key, key_copy;

    init_config();

    while (1) {

        /*To read key press*/
        key = read_digital_keypad(STATE);

        /*If switch is pressed, then only update key_copy*/
        if (key != ALL_RELEASED) {
            key_copy = key;
        }
        glow_on_press(key_copy);
    }

    return;
}

void glow_on_press(unsigned char key) {

    unsigned char static flag = 0;
    static unsigned int wait = 0;
    static unsigned char step = 0;
    static unsigned char direction = 0;

    wait++;
    if (key == SW1) {
        if (wait == 50000) {
            wait = 0;

            if (direction == 0) // Left to Right ON
            {
                LED_ARRAY1 |= (1 << step);
                step++;
                if (step >= 8) {
                    step = 0;
                    direction = 1;
                }
            } else if (direction == 1) // Left to Right OFF
            {
                LED_ARRAY1 &= ~(1 << step);
                step++;
                if (step >= 8) {
                    step = 7;
                    direction = 2;
                }
            } else if (direction == 2) // Right to Left ON
            {
                LED_ARRAY1 |= (1 << step);
                if (step == 0) {
                    step = 7; // Reset for OFF phase
                    direction = 3;
                } else {
                    step--;
                }
            } else if (direction == 3) // Right to Left OFF
            {
                LED_ARRAY1 &= ~(1 << step);
                if (step == 0) {
                    step = 0;
                    direction = 0; // Restart from Left to Right ON
                } else {
                    step--;
                }
            }
        }
    }
    else if (key == SW2) {
        //Code for pattern2
        //The LEDs should glow from left to Right and switch off from left to right, no direction control/ direction change
        if (wait == 50000) {
            wait = 0;
            if (direction == 0) {
                LED_ARRAY1 |= (1 << step); // Turn ON left to right
                step++;
                if (step >= 8) {
                    step = 0;
                    direction = 1; // Switch to OFF mode
                }
            } else if (direction == 1) {
                LED_ARRAY1 &= ~(1 << step); // Turn OFF left to right
                step++;
                if (step >= 8) {
                    step = 0;
                    direction = 0; // Switch back to ON mode
                }
            }
        }
    }
    else if (key == SW3) {
        //Code for pattern3
        //The LEDs should blink alternately
        if (wait == 30000) {
            wait = 0;
            flag = !flag;
            LED_ARRAY1 = (flag) ? 0xAA : 0x55;
        }
    } else if (key == SW4) {
        //Code for pattern4
        //The LEDs has to blink nibble wise, i.e first 4 LEDs will be ON, next 4 LEDs will be OFF, 
        //after first 4 LEDs will be OFF, next 4 LEDs will be ON.
        if (wait == 30000) {
            wait = 0;
            flag = !flag;
            LED_ARRAY1 = 0xF0;
        }
        if (flag) {
            LED_ARRAY1 = 0x0F;
        }

    }

}

