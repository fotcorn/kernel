#include "screen.h"

#include <string.h>

static unsigned char* video_memory = (unsigned char*)0xb8000;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_BLACK 0x07

unsigned int cursor_x, cursor_y;
unsigned int screen_pos;


void setpos(int x, int y)
{
    cursor_x = x;
    cursor_y = y;
}

void putint(int i)
{
	if (i < 0) {
		putch('-');
		i = -i;
	}

	int j = 1000000000;
	int res = 0;
	for (; j > 0; j -= 10) {
		res = i / j;
		if (res > 0) {
			break;
		}
	}

	for (; j > 0; j -= 10) {
		res = i / j;
		switch(res % 10) {
		case 0:
			putch('0');
			break;
		case 1:
			putch('1');
			break;
		case 2:
			putch('2');
			break;
		case 3:
			putch('3');
			break;
		case 4:
			putch('4');
			break;
		case 5:
			putch('5');
			break;
		case 6:
			putch('6');
			break;
		case 7:
			putch('7');
			break;
		case 8:
			putch('8');
			break;
		case 9:
			putch('9');
			break;
		}
	}
	//char buffer[100];
	//sprintf(buffer, "%d", i);
	//print(buffer);
}

void print(char* str)
{
	int len = strlen(str);
	int i;
	for(i = 0; i < len; i++)
	{
		putch(str[i]);
	}
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
        char* memory = video_memory + position*2;
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

