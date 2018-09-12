#include "shader.h"

void shader_init(shader_t* shader, GLenum type, const char* code) {
	shader->shader = glCreateShader(type);
	glShaderSource(shader->shader, 1, &code, NULL);
	glCompileShader(shader->shader);
}