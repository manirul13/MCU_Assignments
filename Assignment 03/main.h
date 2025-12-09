/* 
 * File:   main.h
 * Author: MANIRUL
 *
 * Created on 31 May, 2025, 6:09 PM
 */

#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

#define _XTAL_FREQ 20000000

// LED macros
#define LED_ARRAY1_DDR TRISD
#define LED_ARRAY1     PORTD

#define LED0 RD0 // Timer0 LED
#define LED1 RD1 // Timer1 LED
#define LED2 RD2 // Timer2 LED

#endif
