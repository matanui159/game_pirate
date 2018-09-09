#include "mesh_data.h"
#include "util.h"

typedef struct vertex_t {
	float x;
	float y;
	float z;
} vertex_t;

void mesh_data() {
	FILE* in = fopen("mesh.obj", "r");
	FILE* out = fopen("graphics/mesh_data.h", "w");
	int mesh_size = 0;
	array_t line;
	array_t vertices;
	array_t normals;
	array_t mesh_vertices;
	array_t mesh_normals;
	array_init(&line, 1);
	array_init(&vertices, sizeof(vertex_t));
	array_init(&normals, sizeof(vertex_t));
	array_init(&mesh_vertices, sizeof(float));
	array_init(&mesh_normals, sizeof(float));

	util_output(out, "#ifndef MESH_DATA_H_");
	util_output(out, "#define MESH_DATA_H_");
	util_output(out, "extern int mesh_size;");
	util_output(out, "extern float* mesh_vertices;");
	util_output(out, "extern float* mesh_normals;");
	util_output(out, "#endif");
	util_output(out, "#ifdef MESH_DATA_BUILD");

	while (util_input(in, &line)) {
		
	}

	util_output(out, "#endif");
}