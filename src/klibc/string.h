#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void *memset(void *dst, int c, size_t n);
void *memmove(void *dst_void, const void *src_void, size_t length);
size_t strlen(const char *str);
void itoa(int value, char *sp, int radix);

#endif

