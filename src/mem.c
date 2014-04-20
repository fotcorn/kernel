#include "mem.h"

extern void* heap;

void* malloc(size_t size) {
	void* return_heap = heap;
	heap = heap + size;
	return return_heap;
}

void free(void *ptr) {
	// noop
}
