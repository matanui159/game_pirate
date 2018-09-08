#include "mem.h"
#include "test.h"
#include <windows.h>

void* mem_create(int size) {
	return mem_resize(NULL, size);
}

void mem_destroy(void* ptr) {
	mem_resize(ptr, 0);
}

void* mem_resize(void* ptr, int size) {
	static HANDLE heap = NULL;
	if (heap == NULL) {
		heap = HeapCreate(0, 0, 0);
	}

	if (ptr == NULL && size == 0) {
		return NULL;
	} else if (ptr == NULL) {
		return HeapAlloc(heap, 0, size);
	} else if (size == 0) {
		HeapFree(heap, 0, ptr);
		return NULL;
	} else {
		return HeapReAlloc(heap, 0, ptr, size);
	}
}

#ifdef TEST_BUILD

static void test_compare(int* left, int* right, int size, const char* name) {
	for (int i = 0; i < size; ++i) {
		if (left[i] != right[i]) {
			test_fail(name);
		}
	}
}

void mem_test() {
	int compare[] = {1, 2};
	
	int* mem = mem_create(sizeof(int));
	mem[0] = 1;
	test_compare(mem, compare, 1, "mem_create");

	mem = mem_resize(mem, sizeof(int) * 2);
	mem[1] = 2;
	test_compare(mem, compare, 2, "mem_resize");

	mem_destroy(mem);
}

#endif