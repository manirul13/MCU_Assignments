/*
 * File:   main.c
 * Author: MANIRUL
 * Problem: 
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#pragma config WDTE = OFF      // Watchdog Timer Enable bit (WDT disabled)

#define PERIOD  100            // PWM period (max loop count)

// Function to control LED brightness using software PWM
void glow_led(unsigned short adc_reg_val)
{
    static unsigned char duty_cycle = 0;    // Current duty cycle (0-100)
    static unsigned short prev_adc_val = 0; // Store previous ADC value
    static unsigned char loop_counter = 0;  // PWM counter

    // Update duty cycle only if ADC value changes significantly
    if ((adc_reg_val > prev_adc_val + 2) || (adc_reg_val < prev_adc_val - 2))
    {
        // Map 10-bit ADC (0-1023) to duty cycle (0-100)
        duty_cycle = (adc_reg_val) / 10.23;
        prev_adc_val = adc_reg_val;
    }

    // Software PWM logic
    if (loop_counter < duty_cycle)
    {
        LED_ARRAY1 = ON;   // LED ON
    }
    else
    {
        LED_ARRAY1 = OFF;  // LED OFF
    }

    loop_counter++;
    if (loop_counter >= PERIOD)
    {
        loop_counter = 0; // Restart PWM cycle
    }
}

// Configuration function
static void init_config(void) {
    LED_ARRAY1 = OFF;
    LED_ARRAY1_DDR = 0x00;   // Set PORTD as output
    init_adc();
}

// Main function
void main(void) {
    unsigned short adc_reg_val;
    init_config();

    while (1) 
    {
        adc_reg_val = read_adc();    // Read potentiometer value
        glow_led(adc_reg_val);       // Adjust LED brightness
    }
}
