#include "res.h"
#include <mesh_data.h>

mesh_t g_res_mesh_Wood;

program_t g_res_program_wood;

void res_init() {
	shader_t shader_vertex;
	shader_t shader_srgb;
	shader_t shader_light;
	shader_t shader_wood;

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

	SHADER_INIT(&shader_srgb, GL_FRAGMENT_SHADER,
		vec4 frag_srgb(vec4 prev) {
			return pow(prev, vec4(vec3(1 / 2.2), 1));
		}
	);

	SHADER_INIT(&shader_light, GL_FRAGMENT_SHADER,
		in vec3 vnormal;

		vec4 frag_light(vec4 prev) {
			float light = clamp(dot(vnormal, vec3(0, 0, -1)), 0, 1);
			return prev * (light * 0.9 + 0.1);
		}
	);

	SHADER_INIT(&shader_wood, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;

		vec4 frag_light(vec4 prev);
		vec4 frag_srgb(vec4 prev);

		void main() {
			color = frag_srgb(frag_light(vec4(0.5, 0.3, 0.1, 1.0)));
		}
	);

	MESH_INIT(&g_res_mesh_Wood, g_mesh_Wood);
	
	program_init(&g_res_program_wood);
	program_attach(&g_res_program_wood, &shader_vertex);
	program_attach(&g_res_program_wood, &shader_light);
	program_attach(&g_res_program_wood, &shader_srgb);
	program_attach(&g_res_program_wood, &shader_wood);
	program_link(&g_res_program_wood);
}