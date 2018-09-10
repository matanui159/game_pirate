#include "array.h"
#include <windows.h>

static HANDLE g_heap;

void array_init(array_t* array, int elem_size) {
	if (g_heap == NULL) {
		g_heap = GetProcessHeap();
	}
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = 8;
	array->data = HeapAlloc(g_heap, 0, array->capacity * elem_size);
}

void* array_add(array_t* array) {
	if (array->size == array->capacity) {
		array->capacity *= 2;
		array->data = HeapReAlloc(g_heap, 0, array->data,
			array->capacity * array->elem_size);
	}
	return array_get(array, array->size++);
}

void array_remove(array_t* array, int index) {
	unsigned char* ptr = array_get(array, index);
	unsigned char* end = array_get(array, --array->size);
	for (; ptr != end; ++ptr) {
		ptr[0] = ptr[array->elem_size];
	}
}

void* array_get(array_t* array, int index) {
	return array->data + index * array->elem_size;
}