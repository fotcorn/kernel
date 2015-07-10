#ifndef SCREEN_H
#define SCREEN_H

void setpos(int x, int y);
void putch(char c);
void putint(int i);
void print(const char* str);
void println(const char* str);
void backspace(void);
void clear();

#endif
