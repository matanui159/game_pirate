#ifndef PROGRAM_H_
#define PROGRAM_H_
#include "shader.h"
#include <ogl.h>

typedef struct program_t {
	GLuint program;
} program_t;

void program_init(program_t* program);
void program_attach(program_t* program, shader_t* shader);
void program_link(program_t* program);
void program_use(program_t* program);

#endif