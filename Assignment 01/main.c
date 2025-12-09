/* 
 * File:   main.c
 * Author: MANIRUL
 *
 * Created on 28 May, 2025, 11:58 PM
 */

#include <xc.h>
#pragma config WDTE = OFF

void main()
{
    TRISD = 0x00;      // Set PORTD as output
    PORTD = 0x00;      // Initialize PORTD to all LEDs OFF initially

    unsigned char pattern = 0x00;
    unsigned long counter = 0;
    int flag = 0;      //change the mode 
    int i = 0;       

    while (1)
    {
        counter++;
        if (counter >= 50000)
        {
            counter = 0;

            switch (flag)
            {
                case 0: // Turn ON LEDs one by one from D0 to D7
                    pattern |= (1 << i);
                    PORTD = pattern;
                    i++;
                    if (i >= 8)
                    {
                        flag = 1;
                        i = 0;
                    }
                    break;

                case 1: // Turn OFF LEDs one by one from D0 to D7
                    pattern &= ~(1 << i);
                    PORTD = pattern;
                    i++;
                    if (i >= 8)
                    {
                        flag = 2;
                        i = 7;
                    }
                    break;

                case 2: // Turn ON LEDs one by one from D7 to D0
                    pattern |= (1 << i);
                    PORTD = pattern;
                    i--;
                    if (i < 0)
                    {
                        flag = 3;
                        i = 7;
                    }
                    break;

                case 3: // Turn OFF LEDs one by one from D7 to D0
                    pattern &= ~(1 << i);
                    PORTD = pattern;
                    i--;
                    if (i < 0)
                    {
                        flag = 0;
                        i = 0;
                    }
                    break;
            }
        }
    }
}
