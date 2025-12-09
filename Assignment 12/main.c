#include <xc.h>
#include <stdio.h>
#include "adc.h"
#include "clcd.h"

#pragma config WDTE = OFF       // Disable Watchdog Timer
#define _XTAL_FREQ 20000000     // 20 MHz crystal

void init_config(void)
{
    init_clcd();    // Initialize LCD
    init_adc();     // Initialize ADC
}

void main(void)
{
    char buffer[17];
    unsigned short adc_value;
    unsigned int temperature;

    init_config();

    clcd_print("ROOM TEMPERATURE", LINE1(0));

    while (1)
    {
        // Read LM35 from AN0 channel
        adc_value = read_adc(0);

        // Convert ADC value to temperature in Celsius
        // LM35: 10 mV per °C, Vref = 5V, 10-bit ADC (0?1023)
        //To make 27 degree celcius multiple by 310 with adc_value
        temperature = (adc_value * 310) / 1023;

        // Format output: Unsigned integer, degree symbol, C for Celcius
        sprintf(buffer, "%d \xDF""C", temperature);

        // Display on second line
        clcd_print(buffer, LINE2(0));

        __delay_ms(500); // Update every 0.5 sec
    }
}
