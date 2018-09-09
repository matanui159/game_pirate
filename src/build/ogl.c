#include "ogl.h"
#include "util.h"
#include <ctype.h>

static void gen_type(const char* func, array_t* type) {
	type->size = 0;
	util_string(type, 'P');
	util_string(type, 'F');
	util_string(type, 'N');

	for (; func != '\0'; ++func) {
		util_string(type, toupper(*func));
	}

	util_string(type, 'P');
	util_string(type, 'R');
	util_string(type, 'O');
	util_string(type, 'C');
	util_string(type, '\0');
}

void ogl() {
	FILE* in = fopen("ogl.txt", "r");
	FILE* out = fopen("graphics/ogl.h", "w");
	array_t func;
	array_t type;
	array_init(&func, 1);
	array_init(&type, 1);

	util_output(out, "#ifndef OGL_H_");
	util_output(out, "#define OGL_H_");
	util_output(out, "#include \"context.h\"");
	util_output(out, "#include <GL/gl.h>");
	util_output(out, "#include <GL/glext.h>");

	while (util_input(in, &func)) {
		gen_type(func.data, &type);
		output_write(out, "extern %s ogl_%s;", type.data, func.data);
		output_write(out, "#define %s ogl_%s", func.data, func.data);
	}

	output_write(out, "void ogl_init();");
	output_write(out, "#endif");
	output_write(out, "#ifdef OGL_BUILD");
	
	while (util_input(in, &func)) {
		gen_type(func.data, &type);
		output_write(out, "%s ogl_%s;", type.data, func.data);
	}

	output_write(out, "void ogl_init() {");

	while (input_read(in, &func)) {
		gen_type(func.data, &type);
		output_write(out, "\togl_%s = (%s)context_func(\"%s\");",
			func.data, type.data, func.data);
	}

	output_write(out, "}");
	output_write(out, "#endif");
}