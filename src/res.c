#include "res.h"
#include <mesh_data.h>

mesh_t g_res_mesh_Wood;
program_t g_res_program_wood;

void res_init() {
	shader_t shader_vertex;
	shader_t shader_fragment;

	SHADER_INIT(&shader_vertex, GL_VERTEX_SHADER, 
		layout(location = 0) in vec3 vertex;
		out vec3 vcolor;

		void main() {
			vcolor = vec3(1);
			gl_Position = vec4(vertex, 1);
		}
	);

	SHADER_INIT(&shader_fragment, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;
		in vec3 vcolor;

		void main() {
			color = vec4(vcolor, 1);
		}
	);

	MESH_INIT(&g_res_mesh_Wood, g_mesh_Wood);
	
	program_init(&g_res_program_wood);
	program_attach(&g_res_program_wood, &shader_vertex);
	program_attach(&g_res_program_wood, &shader_fragment);
	program_link(&g_res_program_wood);
}