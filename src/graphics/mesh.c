#include "mesh.h"

void mesh_init(mesh_t* mesh, int size, const float* data) {
	const float mesh_data[] = {
		0, 1, 0,
		-1, -1, 0,
		1, -1, 0
	};

	glGenBuffers(1, &mesh->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffer);
	// glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_data), mesh_data, GL_STATIC_DRAW);
	glGenVertexArrays(1, &mesh->array);
	glBindVertexArray(mesh->array);

	GLsizei stride = sizeof(float) * 6;
	glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	mesh->size = size / 6;
}

void mesh_draw(mesh_t* mesh) {
	glBindVertexArray(mesh->array);
	// glDrawArrays(GL_TRIANGLES, 0, mesh->size);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}