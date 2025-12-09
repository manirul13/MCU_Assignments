#include "main.h"
#include "timers.h"

// 20 MHz ? Fosc/4 = 5 MHz ? 0.2 us per tick
// Timer0: Prescale 1:256 ? 51.2 us per tick
// For 1 ms ? preload TMR0 with 6
void init_timer0(void)
{
    T0CS = 0;  // Internal clock
    PSA = 0;   // Assign prescaler to Timer0
    PS2 = 1; PS1 = 1; PS0 = 1; // 1:256

    TMR0 = 6;  // ~1 ms preload
    TMR0IF = 0;
    TMR0IE = 1;
}

// Timer1: 16-bit, Prescale 1:8 ? 1 tick = 1.6 us
// For 1 ms ? preload 65536 - 625 = 0xFC18
void init_timer1(void)
{
    TMR1CS = 0; // Internal clock
    T1CKPS1 = 1; T1CKPS0 = 1; // 1:8 prescale

    TMR1H = 0xFC;
    TMR1L = 0x18;

    TMR1IF = 0;
    TMR1IE = 1;
    TMR1ON = 1;
}

// Timer2: Prescale 1:16, PR2 = 125 ? ~1 ms period
void init_timer2(void)
{
    T2CKPS0 = 1; T2CKPS1 = 1; // 1:16 prescale
    PR2 = 125 - 1; // ~1 ms

    TMR2IF = 0;
    TMR2IE = 1;
    TMR2ON = 1;
}
