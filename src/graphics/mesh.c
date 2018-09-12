#include "mesh.h"

void mesh_init(mesh_t* mesh, int size, const float* data) {
	glGenBuffers(1, &mesh->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	glGenVertexArrays(1, &mesh->array);
	glBindVertexArray(mesh->array);

	GLsizei stride = sizeof(float) * 6;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		stride, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		stride, (void*)(stride / 2));
	mesh->size = size / 6;
}

void mesh_draw(mesh_t* mesh) {
	glBindVertexArray(mesh->array);
	glDrawArrays(GL_TRIANGLES, 0, mesh->size);
}