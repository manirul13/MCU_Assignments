#include "main.h"
#include "timers.h"

#pragma config WDTE = OFF  // Disable Watchdog

static void init_config(void) {
    LED_ARRAY1_DDR = 0x00; // PORTD as output
    LED_ARRAY1 = 0x00;     // LEDs OFF

    // Initialize all timers
    init_timer0();
    init_timer1();
    init_timer2();

    // Enable interrupts
    PEIE = 1;
    GIE = 1;
}

void main(void) {
    init_config();

    while (1) {
        // All LED toggling handled in ISR
    }
}
