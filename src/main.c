#include "graphics/window.h"
#include "graphics/context.h"
#include "res.h"
#include <ogl.h>

int main() {
	window_init();
	context_init();
	res_init();

	matrix_t matrix = matrix_identity();
	matrix = matrix_perspective(&matrix, 1, 100, 60, window_ratio());
	matrix = matrix_translate(&matrix, 0, -5, 20);
	matrix = matrix_roty(&matrix, 120);

	for (;;) {
		window_update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program_use(&g_res_program_wood);
		program_matrix(&g_res_program_wood, &matrix);
		mesh_draw(&g_res_mesh_Wood);

		context_update();
	}
}