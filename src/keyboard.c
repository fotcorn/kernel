#include "keyboard.h"
#include "screen.h"
#include "pic.h"
#include "io.h"
#include "mem.h"
#include "scancodes.h"

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

static int line_ready = 0;
static int line_length = 0;
static char line[256];

static unsigned int multi_scancode = 0;




void keyboard_interrupt() {
	pic_eoi(0x1);

	unsigned char scancode = inb(KEYBOARD_DATA);
	//putint(scancode);
    if (scancode == 0xE0) {
        multi_scancode = scancode;
    } else if (scancode == 0xF0) {
        multi_scancode = scancode;
    } else {
        if (multi_scancode) {
            multi_scancode = 0;
        } else {
            scancode = SCANCODES[scancode];
            if (scancode != 0) {
                line[line_length] = scancode;
                line_length += 1;
                line_ready = 1;
            }
        }
    }
}

char* readline() {
    while (!line_ready);
    line_ready = 0;
    char* ret = (char*)malloc(line_length + 1);

    for (int i = 0; i < line_length; i++) {
        ret[i] = line[i];
    }
    ret[line_length] = '\0';

    line_length = 0;
    line_ready = 0;
    return ret;
}

