#include "screen.h"
#include "pic.h"
#include "keyboard.h"
#include "mem.h"

void kmain( void* mbd, unsigned int magic )
{
	init_pic();
	init_keyboard();

	clear();

    putch('A');
    putch('B');
    putch('\n');
    putch('A');
    putch('\n');

    print("test");
    print("pyos 0.001");

    char* str = malloc(8);
    memset(str, 'a', 7);
    str[7] = '\0';

    print(str);

    while (1) {}
}
