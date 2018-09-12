#include "program.h"

void program_init(program_t* program) {
	program->program = glCreateProgram();
}

void program_attach(program_t* program, shader_t* shader) {
	glAttachShader(program->program, shader->shader);
}

void program_link(program_t* program) {
	glLinkProgram(program->program);
	program->matrix = glGetUniformLocation(program->program, "matrix");
}

void program_use(program_t* program) {
	glUseProgram(program->program);
}

void program_matrix(program_t* program, const matrix_t* matrix) {
	glUniformMatrix4fv(program->matrix, 1, GL_TRUE, (GLfloat*)matrix);
}