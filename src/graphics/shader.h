#ifndef SHADER_H_
#define SHADER_H_
#include <ogl.h>

typedef struct shader_t {
	GLuint shader;
} shader_t;

void shader_init(shader_t* shader, GLenum type, const char* code);

#define SHADER_INIT(shader, type, code) shader_init(shader, type, \
	"#version 330\n" #code)

#endif