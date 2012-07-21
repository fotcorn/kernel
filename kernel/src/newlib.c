#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#undef errno
extern int errno;

#include "screen.h"

int write(int file, char *ptr, int len) {
	print("write");
	int i;
	for(i = 0; i < len; i++) {
		putch(*ptr);
		ptr++;
	}
	return len;
}

caddr_t sbrk(int incr) {
	print("sbrk");
	putint(incr);

	static char *heap_end = (char*)0x00200000;

	char *prev_heap_end;
	prev_heap_end = heap_end;

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

int read(int file, char *ptr, int len) {
	print("read");
	return 0;
}

int close(int file) {
	print("close");
	return -1;
}

int lseek(int file, int ptr, int dir) {
	print("lseek");
    return 0;
}

int isatty(int file) {
	print("isatty");
	return 1;
}

int fstat(int file, struct stat *st) {
	print("fstat");
	st->st_mode = S_IFCHR;
	return 0;
}
