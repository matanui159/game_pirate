#include "shader.h"
#include "../util.h"

void shader_init(shader_t* shader, GLenum type, const char* code) {
	util_print(code);
	shader->shader = glCreateShader(type);
	glShaderSource(shader->shader, 1, &code, NULL);
	glCompileShader(shader->shader);

	char infolog[256];
	glGetShaderInfoLog(shader->shader, sizeof(infolog), NULL, infolog);
	util_print(infolog);
}