#include "util.h"
#include <stdarg.h>

void util_string(array_t* array, char c) {
	*(char*)array_add(array) = c;
}

_Bool util_input(FILE* file, array_t* line) {
	int c = fgetc(file);
	if (c == -1) {
		fseek(file, 0, SEEK_SET);
		return 0;
	}

	line->size = 0;
	while (c != -1 && c != '\n') {
		util_string(line, c);
		c = fgetc(file);
	}
	util_string(line, '\0');
	return 1;
}

void util_output(FILE* file, const char* format, ...) {
	va_list list;
	va_start(list, format);
	vfprintf(file, format, list);
	va_end(list);
	fputc('\n', file);
}