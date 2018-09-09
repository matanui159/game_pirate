#include "ogl.h"
#include <array.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static inline void array_addc(array_t* array, char c) {
	*(char*)array_add(array) = c;
}

static void output_write(FILE* output, const char* format, ...) {
	va_list list;
	va_start(list, format);
	vfprintf(output, format, list);
	va_end(list);
	fputc('\n', output);
}

static FILE* input_init() {
	return fopen("ogl.txt", "r");
}

static _Bool input_read(FILE* input, array_t* func, array_t* type) {
	int c = fgetc(input);
	if (c == -1) {
		fclose(input);
		return 0;
	}

	func->size = 0;
	type->size = 0;
	array_addc(type, 'P');
	array_addc(type, 'F');
	array_addc(type, 'N');

	do {
		array_addc(func, c);
		array_addc(type, toupper(c));
		c = fgetc(input);
	} while (c != -1 && c != '\n');

	array_addc(func, '\0');
	array_addc(type, 'P');
	array_addc(type, 'R');
	array_addc(type, 'O');
	array_addc(type, 'C');
	array_addc(type, '\0');
	return 1;
}

void ogl() {
	FILE* output = fopen("graphics/ogl.h", "w");
	FILE* input;
	array_t func;
	array_t type;
	array_init(&func, 1);
	array_init(&type, 1);

	output_write(output, "#ifndef OGL_H_");
	output_write(output, "#define OGL_H_");
	output_write(output, "#include \"context.h\"");
	output_write(output, "#include <GL/gl.h>");
	output_write(output, "#include <GL/glext.h>");

	input = input_init();
	while (input_read(input, &func, &type)) {
		output_write(output, "extern %s ogl_%s;", type.data, func.data);
		output_write(output, "#define %s ogl_%s", func.data, func.data);
	}

	output_write(output, "void ogl_init();");
	output_write(output, "#endif");
	output_write(output, "#ifdef OGL_BUILD");
	
	input = input_init();
	while (input_read(input, &func, &type)) {
		output_write(output, "%s ogl_%s;", type.data, func.data);
	}

	output_write(output, "void ogl_init() {");

	input = input_init();
	while (input_read(input, &func, &type)) {
		output_write(output, "\togl_%s = (%s)context_func(\"%s\");",
			func.data, type.data, func.data);
	}

	output_write(output, "}");
	output_write(output, "#endif");
}