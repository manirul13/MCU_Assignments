#include "main.h"

volatile unsigned int tick_count = 0; // Shared counter for all timers

void __interrupt() isr(void)
{
    // Timer0 ISR
    if (TMR0IF)
    {
        TMR0 = 6;
        TMR0IF = 0;
        tick_count++;
    }

    // Timer1 ISR
    if (TMR1IF)
    {
        TMR1H = 0xFC;
        TMR1L = 0x18;
        TMR1IF = 0;
        tick_count++;
    }

    // Timer2 ISR
    if (TMR2IF)
    {
        TMR2IF = 0;
        tick_count++;
    }

    // Toggle LEDs every 500 ms
    if (tick_count >= 500)
    {
        LED0 = !LED0;
        LED1 = !LED1;
        LED2 = !LED2;
        tick_count = 0;
    }
}
