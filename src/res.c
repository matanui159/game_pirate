#include "res.h"
#include <mesh_data.h>

mesh_t g_res_mesh_Wood;

program_t g_res_program_wood;

void res_init() {
	shader_t shader_vertex;
	shader_t shader_fragment;

	SHADER_INIT(&shader_vertex, GL_VERTEX_SHADER, 
		layout(location = 0) in vec3 vertex;
		layout(location = 1) in vec3 normal;
		out vec3 vnormal;

		uniform mat4 matrix;

		void main() {
			vnormal = normalize(matrix * vec4(normal, 0)).xyz;
			gl_Position = matrix * vec4(vertex, 1);
		}
	);

	SHADER_INIT(&shader_fragment, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;
		in vec3 vnormal;

		void main() {
			float light = dot(vnormal, vec3(0, 0, -1));
			color = vec4(vec3(light), 1);
		}
	);

	MESH_INIT(&g_res_mesh_Wood, g_mesh_Wood);
	
	program_init(&g_res_program_wood);
	program_attach(&g_res_program_wood, &shader_vertex);
	program_attach(&g_res_program_wood, &shader_fragment);
	program_link(&g_res_program_wood);
}