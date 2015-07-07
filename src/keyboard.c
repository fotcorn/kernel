#include "keyboard.h"
#include "screen.h"
#include "pic.h"
#include "io.h"

void init_keyboard() {
    outb(KEYBOARD_CMD, 0xAD); // disable first PS/2 port
    outb(KEYBOARD_CMD, 0xA7); // disable second PS/2 port

    outb(KEYBOARD_CMD, 0x20); // read keyboard configuration
    while (!(inb(KEYBOARD_CMD) & 0x1)); // wait until data is in output buffer
    unsigned char config = inb(KEYBOARD_DATA); // read data

    config &= ~(1 << 6); // disable translation from scancode set 2 to 1

    outb(KEYBOARD_CMD, 0x60); // set keyboard configuration
    while ((inb(KEYBOARD_CMD) & 0x2)); // wait until data input buffer is clear
    outb(KEYBOARD_DATA, config); // write configuration

    outb(KEYBOARD_CMD, 0xAE); // enable first PS/2 port
    outb(KEYBOARD_CMD, 0xA8); // enable second PS/2 port
}

void keyboard_interrupt() {
	static char flags = 0;
	pic_eoi(0x1);

	unsigned char scancode = inb(KEYBOARD_DATA);
	putint(scancode);
}
