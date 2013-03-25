#include "screen.h"
#include "pic.h"
#include "keyboard.h"

void kmain( void* mbd, unsigned int magic )
{
	init_pic();
	init_keyboard();

    putch('A');
    putch('B');
    putch('\n');
    putch('A');
    putch('\n');

    print("test");
    print("pyos 0.001");

    while (1) {}
}
