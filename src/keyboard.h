#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_interrupt();
void init_keyboard();

#define R_SHIFT 1
#define L_SHIFT 2
#define CAPSLOCK 3

#define KEYBOARD_DATA 0x60
#define KEYBOARD_CMD 0x64

#endif
