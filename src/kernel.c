#include "screen.h"
#include "pic.h"
#include "keyboard.h"
#include "mem.h"

#include <string.h>

void kmain( void* mbd, unsigned int magic )
{
	init_pic();
	init_keyboard();

	clear();

    print("Welcome to CornOS 0.0.1");
    while(1) {
        print("# ");
        char* line = readline();
        print("You entered:");
        print(line);
    }

    while (1) {}
}
