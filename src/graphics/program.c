#include "program.h"
#include "../util.h"

void program_init(program_t* program) {
	program->program = glCreateProgram();
}

void program_attach(program_t* program, shader_t* shader) {
	glAttachShader(program->program, shader->shader);
}

void program_link(program_t* program) {
	glLinkProgram(program->program);

	char infolog[256];
	glGetProgramInfoLog(program->program, sizeof(infolog), NULL, infolog);
	util_print(infolog);
}

void program_use(program_t* program) {
	glUseProgram(program->program);
}