#include "res.h"
#include <mesh_data.h>

mesh_t g_res_mesh_Wood;
mesh_t g_res_mesh_Grey_metal_1;
mesh_t g_res_mesh_Grey_metal_3;
mesh_t g_res_mesh_Dark_metal;
mesh_t g_res_mesh_Cloth;

program_t g_res_program_wood;
program_t g_res_program_metal;
program_t g_res_program_black;
program_t g_res_program_cloth;

void res_init() {
	shader_t shader_vertex;
	shader_t shader_srgb;
	shader_t shader_light;
	shader_t shader_wood;
	shader_t shader_metal;
	shader_t shader_black;
	shader_t shader_cloth;

	SHADER_INIT(&shader_vertex, GL_VERTEX_SHADER, 
		layout(location = 0) in vec3 vertex;
		layout(location = 1) in vec3 normal;
		out vec3 vnormal;

		uniform mat4 matrix;

		void main() {
			vnormal = normal;
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
			float light = clamp(dot(vnormal, vec3(1, 1, 1)), 0, 1);
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

	SHADER_INIT(&shader_metal, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;

		vec4 frag_light(vec4 prev);
		vec4 frag_srgb(vec4 prev);

		void main() {
			color = frag_srgb(frag_light(vec4(0.2, 0.2, 0.2, 1.0)));
		}
	);

	SHADER_INIT(&shader_black, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;

		void main() {
			color = vec4(0);
		}
	);

	SHADER_INIT(&shader_cloth, GL_FRAGMENT_SHADER,
		layout(location = 0) out vec4 color;

		vec4 frag_light(vec4 prev);
		vec4 frag_srgb(vec4 prev);

		void main() {
			color = frag_srgb(frag_light(vec4(0.9, 0.9, 0.7, 1.0)));
		}
	);

	MESH_INIT(&g_res_mesh_Wood, g_mesh_Wood);
	MESH_INIT(&g_res_mesh_Dark_metal, g_mesh_Dark_metal);
	MESH_INIT(&g_res_mesh_Grey_metal_1, g_mesh_Grey_metal_1);
	MESH_INIT(&g_res_mesh_Grey_metal_3, g_mesh_Grey_metal_3);
	MESH_INIT(&g_res_mesh_Cloth, g_mesh_Cloth);
	
	program_init(&g_res_program_wood);
	program_attach(&g_res_program_wood, &shader_vertex);
	program_attach(&g_res_program_wood, &shader_light);
	program_attach(&g_res_program_wood, &shader_srgb);
	program_attach(&g_res_program_wood, &shader_wood);
	program_link(&g_res_program_wood);

	program_init(&g_res_program_metal);
	program_attach(&g_res_program_metal, &shader_vertex);
	program_attach(&g_res_program_metal, &shader_light);
	program_attach(&g_res_program_metal, &shader_srgb);
	program_attach(&g_res_program_metal, &shader_metal);
	program_link(&g_res_program_metal);

	program_init(&g_res_program_black);
	program_attach(&g_res_program_black, &shader_vertex);
	program_attach(&g_res_program_black, &shader_black);
	program_link(&g_res_program_black);

	program_init(&g_res_program_cloth);
	program_attach(&g_res_program_cloth, &shader_vertex);
	program_attach(&g_res_program_cloth, &shader_light);
	program_attach(&g_res_program_cloth, &shader_srgb);
	program_attach(&g_res_program_cloth, &shader_cloth);
	program_link(&g_res_program_cloth);
}