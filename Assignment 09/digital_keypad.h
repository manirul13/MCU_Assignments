#ifndef DIGITAL_KEYPAD_H
#define	DIGITAL_KEYPAD_H

#define LEVEL_DETECTION         0
#define LEVEL                   0

#define STATE_DETECTION         1
#define STATE                   1

#define KEYPAD_PORT             PORTB
#define KEYPAD_PORT_DDR         TRISB

#define INPUT_LINES             0x07  // Only 3 keys used: RB0, RB1, RB2

#define SW1                     0x06  // RB0 pressed (Left)
#define SW2                     0x05  // RB1 pressed (Right)
#define SW3                     0x03  // RB2 pressed (Start/Stop)

#define ALL_RELEASED            INPUT_LINES

unsigned char read_digital_keypad(unsigned char mode);
void init_digital_keypad(void);

#endif	/* DIGITAL_KEYPAD_H */
