#ifndef MEM_H_
#define MEM_H_

void* mem_create(int size);
void mem_destroy(void* ptr);
void* mem_resize(void* ptr, int size);
void mem_test();

#endif