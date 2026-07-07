/* 
 * File:   main.h
 * Author: MANIRUL
 *
 * Created on 18 July, 2025, 6:11 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include <string.h>
#include "eeprom.h"


#define DASHBOARD_SCREEN   0x00
#define LOGIN_SCREEN       0x01

#define RESET_PASSWORD     0x02  
#define RESET_NOTHING      0x03 
#define RESET_MENU         0X04

#define MAIN_MENU_SCREEN   0x11
#define RETURN_BACK        0x22
#define LOGIN_SUCCESS      0x33

#define VIEW_LOG_SCREEN        0x44
#define CLEAR_LOG_SCREEN       0x55
#define DOWNLOAD_LOG_SCREEN    0x66
#define SET_TIME_SCREEN        0x77
#define CHANGE_PASSWORD_SCREEN 0x88

#define ALL_RELEASED            INPUT_LINES


#endif	/* MAIN_H */

