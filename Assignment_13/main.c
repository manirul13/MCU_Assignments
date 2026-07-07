/*
 * File:   main.c
 * Author: Manirul
 * Assignmeent: Show the Authentication using Password, if correct then ok. else Access denied in CLCD screen
 *
 */

#include <xc.h>
#include <string.h>
#include "clcd.h"
#include "digital_keypad.h"

#pragma config WDTE = OFF  // Watchdog Timer Disable



#define LED_PORT        PORTD
#define LED_TRIS        TRISD
#define LED_PIN         0   // RD0

#define LED_ON()        (LED_PORT |= (1 << LED_PIN))
#define LED_OFF()       (LED_PORT &= ~(1 << LED_PIN))
#define LED_TOGGLE()    (LED_PORT ^= (1 << LED_PIN))

 

static const char correct_password[PASSWORD_LENGTH + 1] = "11110000"; // Change as needed
static char entered_password[PASSWORD_LENGTH + 1];

void variable_delay_ms(unsigned int count)
{
    while (count--)
    {
        __delay_ms(1);
    }
}

static void blink_led(unsigned int delay_time)
{
    LED_TOGGLE();
    variable_delay_ms(delay_time);
}

void main(void)
{
    unsigned char key;
    unsigned char index = 0;
    unsigned char attempts_left = 5;
    unsigned int led_delay = 500; // Initial blink delay in ms

    /* Init Hardware */
    init_clcd();
    init_digital_keypad();
    LED_TRIS &= ~(1 << LED_PIN); // RD0 as output
    LED_OFF();

    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    clcd_print("Enter Password", LINE1(0));

    while (1)
    {
        key = read_digital_keypad(STATE);

        // Blinking '_' at password input position
        if ((index < PASSWORD_LENGTH) && ((index % 2) == 0))
        {
            clcd_putch('_', LINE2(4 + index));
        }

        // Enter key 1
        if (key == SW1 && index < PASSWORD_LENGTH)
        {
            entered_password[index] = '1';
            clcd_putch('*', LINE2(4 + index));
            index++;
        }
        // Enter key 2
        else if (key == SW2 && index < PASSWORD_LENGTH)
        {
            entered_password[index] = '0';
            clcd_putch('*', LINE2(4 + index));
            index++;
        }

        // When password is fully entered
        if (index == PASSWORD_LENGTH)
        {
            entered_password[PASSWORD_LENGTH] = '\0'; // Null terminate

            if (strncmp(entered_password, correct_password, PASSWORD_LENGTH) == 0)
            {
                // SUCCESS
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                clcd_print("Login Success", LINE1(0));
                clcd_print("Welcome to INDIA", LINE2(0));
                LED_OFF();
                while (1); // Stop here
            }
            else
            {
                // WRONG PASSWORD
                attempts_left--;

                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                clcd_print("Wrong Password", LINE1(0));
                clcd_print("Attempts Left:", LINE2(0));
                clcd_putch(attempts_left + '0', LINE2(14));
                variable_delay_ms(2000);

                if (attempts_left == 0)
                {
                    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                    clcd_print("Access Denied", LINE1(0));
                    clcd_print("Reset System", LINE2(0));
                    LED_ON();
                    while (1); // Lock system
                }

                // Reset for next attempt
                index = 0;
                memset(entered_password, 0, sizeof(entered_password));
                led_delay /= 2; // Blink faster
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                clcd_print("Enter Password", LINE1(0));
            }
        }

        // LED blinking based on attempts
        blink_led(led_delay);
    }
}
