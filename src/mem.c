#include "mem.h"

extern char* heap;

void* malloc(size_t size) {
	char* return_heap = heap;
	heap = heap + size;
	return return_heap;
}

void free(void *ptr) {
	// noop
}
