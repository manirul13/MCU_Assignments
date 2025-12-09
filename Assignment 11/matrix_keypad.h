/* 
 * File:   matrix_keypad.h
 */

#ifndef MATRIX_KEYPAD_H
#define	MATRIX_KEYPAD_H

#define MATRIX_KEYPAD_COLUMN_PORT_DDR           TRISB
#define MATRIX_KEYPAD_ROW_PORT_DDR              TRISD

#define ROW1                                    RD3
#define ROW2                                    RD2
#define ROW3                                    RD1
#define ROW4                                    RD0

#define COL1                                    RB0
#define COL2                                    RB1
#define COL3                                    RB2

#define HI                                      1
#define LOW                                     0

#define STATE                                   1
#define LEVEL                                   0

#define MAX_MSG_LEN     16

// Key mapping
#define KEY_UP_LEFT                             1   // MKS1
#define KEY_DOWN_RIGHT                          2   // MKS2
#define KEY_START_STOP                          3   // MKS3
#define KEY_EDIT                                4   // MKS4
#define KEY_ACCEPT                              5   // MKS5
#define KEY_BACKSPACE                           6   // MKS6

// Modes
#define MODE_PRESET                             0
#define MODE_MARQUEE                            1

// Scroll direction
#define DIR_LEFT                                0
#define DIR_RIGHT                               1


#define ALL_RELEASED                            0xFF

unsigned char read_matrix_keypad(unsigned char mode);
void init_matrix_keypad(void);

#endif	/* MATRIX_KEYPAD_H */

