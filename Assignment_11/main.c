/*
 * File:   main.c
 * Author: Manirul
 * Assignmeent: CLCD show right scrolling of message WELCOME or else
 *
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include <string.h>

#pragma config WDTE = OFF    // Watchdog Timer Disable

// Character set for editing
const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define CHARSET_LEN (sizeof(charset) - 1)

// Globals
unsigned char mode = MODE_PRESET;
unsigned char scroll_dir = DIR_LEFT;
char message[MAX_MSG_LEN + 1] = {0};
unsigned char cursor_pos = 0;
unsigned char msg_len = 1; // At least 1 char
unsigned char blink_state = 1;
unsigned int blink_delay = 0;
unsigned int scroll_delay = 0;

unsigned char marquee_index = 0;  // Current scroll position
unsigned char scrolling = 0;      // 0 = stopped, 1 = running

// Functions
void init_config(void);
void preset_mode(void);
void marquee_mode(void);
void show_edit_prompt(void);
unsigned char find_char_index(char ch);

void init_config(void) {
    init_clcd();
    init_matrix_keypad();

    clcd_print(" My Marquee Sys ", LINE1(0));

    // Initialize message with '0'
    memset(message, '0', MAX_MSG_LEN);
    message[MAX_MSG_LEN] = '\0';

    show_edit_prompt();
}

void show_edit_prompt(void) {
    clcd_print("Enter:", LINE2(0));
    clcd_putch(message[cursor_pos], LINE2(6 + cursor_pos));
}

unsigned char find_char_index(char ch) {
    for (unsigned char i = 0; i < CHARSET_LEN; i++) {
        if (charset[i] == ch)
            return i;
    }
    return 0; // Default to '0' if not found
}

void preset_mode(void) {
    unsigned char key = read_matrix_keypad(LEVEL);

    // Blinking cursor without timer
    if (++blink_delay > 30000) { // Adjust for ~0.5Hz blink
        blink_delay = 0;
        blink_state = !blink_state;
        clcd_putch(blink_state ? message[cursor_pos] : ' ', LINE2(6 + cursor_pos));
    }

    if (key != ALL_RELEASED) {
        unsigned char index = find_char_index(message[cursor_pos]);

        switch (key) {
            case KEY_UP_LEFT: // Increment char
              index = (index + 1) % CHARSET_LEN;
                message[cursor_pos] = charset[index];
                clcd_putch(message[cursor_pos], LINE2(6 + cursor_pos));
                break;

            case KEY_DOWN_RIGHT: // Decrement char
                index = (index == 0) ? CHARSET_LEN - 1 : index - 1;
                message[cursor_pos] = charset[index];
                clcd_putch(message[cursor_pos], LINE2(6 + cursor_pos));
                break;

            case KEY_ACCEPT: // Move forward
                if (cursor_pos < MAX_MSG_LEN - 1) {
                    cursor_pos++;
                    message[cursor_pos] = '0';
                    msg_len = cursor_pos + 1;
                    clcd_putch(message[cursor_pos], LINE2(6 + cursor_pos));
                }
                break;

            case KEY_BACKSPACE: // Move back
                if (cursor_pos > 0) {
                    cursor_pos--;
                    message[cursor_pos] = '0';
                    msg_len = cursor_pos + 1;
                    clcd_putch(message[cursor_pos], LINE2(6 + cursor_pos));
                }
                break;

            case KEY_START_STOP: // Start scrolling
                mode = MODE_MARQUEE;
                marquee_index = 0;
                scrolling = 1;
                break;
        }
    }
}

void marquee_mode(void) {
    unsigned char key = read_matrix_keypad(LEVEL);

    if (key != ALL_RELEASED) {
        switch (key) {
            case KEY_UP_LEFT:
                scroll_dir = DIR_LEFT;
                break;
            case KEY_DOWN_RIGHT:
                scroll_dir = DIR_RIGHT;
                break;
            case KEY_START_STOP: // Pause/Resume
                scrolling = !scrolling;
                break;
            case KEY_EDIT: // Back to editing
                mode = MODE_PRESET;
                cursor_pos = 0;
                show_edit_prompt();
                return;
        }
    }

    if (!scrolling) return;

    // Build scroll buffer = message + spaces
    char scroll_buf[MAX_MSG_LEN + 17] = {0}; // message + 16 spaces
    strcpy(scroll_buf, message);
    for (int i = msg_len; i < msg_len + 16; i++) {
        scroll_buf[i] = ' ';
    }
    scroll_buf[msg_len + 16] = '\0';

    // Update scroll position every ~0.5s
    if (++scroll_delay > 1000) {
        scroll_delay = 0;

        char display_buf[17] = {0};
        for (int i = 0; i < 16; i++) {
            int pos;
            if (scroll_dir == DIR_LEFT) {
                pos = (marquee_index + i) % (msg_len + 16);
            } else { // DIR_RIGHT
                pos = (marquee_index - i + (msg_len + 16)) % (msg_len + 16);
            }
            display_buf[i] = scroll_buf[pos];
        }
        display_buf[16] = '\0';
        clcd_print(display_buf, LINE2(0));

        // Update index for next scroll
        if (scroll_dir == DIR_LEFT) {
            marquee_index = (marquee_index + 1) % (msg_len + 16);
        } else {
            marquee_index = (marquee_index + 1) % (msg_len + 16);
        }
    }
}

void main(void) {
    init_config();

    while (1) {
        if (mode == MODE_PRESET)
            preset_mode();
        else
            marquee_mode();
    }
}
