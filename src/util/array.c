#include "array.h"
#include "test.h"
#include "mem.h"
#include <windows.h>

void array_create(array_t* array, int elem_size) {
	array->data = NULL;
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = 0;
}

void array_destroy(array_t* array) {
	mem_destroy(array->data);
}

void* array_add(array_t* array) {
	if (array->size == array->capacity) {
		if (array->capacity == 0) {
			array->capacity = 1;
		} else {
			array->capacity *= 2;
		}
		array->data = mem_resize(array->data, array->capacity * array->elem_size);
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

#ifdef TEST_BUILD

static void test_compare(array_t* array, int size, int* values, const char* name) {
	if (array->size != size) {
		test_fail(name);
	}
	for (int i = 0; i < size; ++i) {
		int* value = array_get(array, i);
		if (*value != values[i]) {
			test_fail(name);
		}
	}
}

void array_test() {
	int compare[] = {1, 2, 3};

	array_t array;
	array_create(&array, sizeof(int));
	test_compare(&array, 0, NULL, "array_create");

	for (int i = 0; i < 3; ++i) {
		int* value = array_add(&array);
		*value = i + 1;
	}
	test_compare(&array, 3, compare, "array_add");

	array_remove(&array, 1);
	compare[1] = 3;
	test_compare(&array, 2, compare, "array_remove");

	int* value = array_get(&array, 1);
	*value = 4;
	compare[1] = 4;
	test_compare(&array, 2, compare, "array_get");

	array_destroy(&array);
}

#endif