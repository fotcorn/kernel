#include "screen.h"

#include <string.h>

static unsigned char* video_memory = (unsigned char*)0xb8000;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_BLACK 0x07

unsigned int cursor_x, cursor_y;


void setpos(int x, int y)
{
    cursor_x = x;
    cursor_y = y;
}

void print(const char* str)
{
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++)
	{
		putch(str[i]);
	}
}

void println(const char* str) {
    print(str);
    putch('\n');
}

void putch(char c)
{
    if (c == '\n' || c == '\r')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        unsigned int position = cursor_y * SCREEN_WIDTH + cursor_x;
        unsigned char* memory = video_memory + position*2;
        *memory = c;
        *(memory+1) = WHITE_BLACK;
        cursor_x++;
        if (cursor_x == SCREEN_WIDTH)
        {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y == SCREEN_HEIGHT) {
    	memmove(video_memory, video_memory + (SCREEN_WIDTH * 2), (SCREEN_WIDTH * (SCREEN_HEIGHT - 1)) * 2);
    	memset(video_memory + ((SCREEN_WIDTH * (SCREEN_HEIGHT - 1)) * 2), 0, SCREEN_WIDTH * 2);
    	cursor_y--;
    }
}

void backspace(void) {
    if (cursor_x != 0) {
        cursor_x--;
        putch(' ');
        cursor_x--;
    }
}

void putint(int i) {
	char c[30];
	itoa(i, c, 16);
	print(c);
}

void clear(void) {
	unsigned char* memory = video_memory;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		*memory = ' ';
		*(memory+1) = WHITE_BLACK;
		memory += 2;
	}
	cursor_x = 0;
	cursor_y = 0;
}
