#ifndef MESH_H_
#define MESH_H_
#include <ogl.h>

typedef struct mesh_t {
	GLuint buffer;
	GLuint array;
	GLsizei size;
} mesh_t;

void mesh_init(mesh_t* mesh, int size, const float* data);
void mesh_draw(mesh_t* mesh);

#define MESH_INIT(mesh, data) mesh_init(mesh, data##_size, data##_data)

#endif