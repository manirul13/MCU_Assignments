/*
 * File:   main.c
 * Author: Manirul 
 * Assignmeent: This problem show the usage of UART communication
 * 
 */
#include <xc.h>
#include "uart.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

#define LINE_LENGTH 16

static char line1[LINE_LENGTH + 1] = {0};
static char line2[LINE_LENGTH + 1] = {0};
static unsigned char pos1 = 0;
static unsigned char pos2 = 0;

static void init_config(void) {
    init_uart(9600);
    init_clcd();

    clcd_print("UART CLCD Test", LINE1(0));
    clcd_print("Type in TeraTerm", LINE2(0));

    __delay_ms(2000);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
}

// Shift line2 ? line1

static void shift_lines(void) {
    for (unsigned char i = 0; i < LINE_LENGTH; i++) {
        line1[i] = line2[i];
    }
    pos1 = LINE_LENGTH;

    // Clear line2
    for (unsigned char i = 0; i < LINE_LENGTH; i++) {
        line2[i] = ' ';
    }
    pos2 = 0;

    // Refresh display
    clcd_print(line1, LINE1(0));
    clcd_print(line2, LINE2(0));
}

void main(void) {
    unsigned char ch;

    init_config();

    while (1) {
        ch = getchar(); // Wait for UART character
        putchar(ch); // Echo to Tera Term

        // Accept only printable characters (space to ~)
        if (ch >= 32 && ch <= 126) {
            if (pos1 < LINE_LENGTH) {
                line1[pos1++] = ch;
                clcd_putch(ch, LINE1(pos1 - 1));
            }
            else if (pos2 < LINE_LENGTH) {
                line2[pos2++] = ch;
                clcd_putch(ch, LINE2(pos2 - 1));
            }
            else {
                // Line2 full ? Shift to line1
                shift_lines();
                line2[pos2++] = ch;
                clcd_putch(ch, LINE2(pos2 - 1));
            }
        }
    }
}
