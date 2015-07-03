#include "io.h"

unsigned char inb(unsigned short port) {
    unsigned char ret;
	/*
	 * "a" -> save returned data in al
	 * "Nd" -> N = Constant in range 0 to 255, d = port in dx
	 */
    __asm__ volatile( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void outb(unsigned short port, unsigned char data) {
	/*
	 * "a" -> data in al
	 * "Nd" -> N = Constant in range 0 to 255, d = port in dx
	 */
	__asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

