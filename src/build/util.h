#ifndef UTIL_H_
#define UTIL_H_
#include <array.h>
#include <stdio.h>

void util_string(array_t* array, char c);
_Bool util_input(FILE* file, array_t* line);
void util_output(FILE* file, const char* format, ...);

#endif