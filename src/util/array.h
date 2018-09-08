#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct array_t {
	unsigned char* data;
	int elem_size;
	int size;
	int capacity;
} array_t;

void array_init(array_t* array, int elem_size);
void* array_add(array_t* array);
void array_remove(array_t* array, int index);
void* array_get(array_t* array, int index);

#endif