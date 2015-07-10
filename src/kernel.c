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

    println("Welcome to CornOS 0.0.1");
    while(1) {
        char* line = readline();
        println("");
        println("You entered:");
        println(line);
        free(line);
    }

    while (1) {}
}
