#include "graphics/window.h"
#include "graphics/context.h"
#include "res.h"
#include <ogl.h>

int main() {
	window_init();
	context_init();
	res_init();

	matrix_t matrix = matrix_identity();
	matrix_t perspective = matrix_identity();
	perspective.m32 = -1;
	perspective.m33 = 0;
	matrix = matrix_multiply(&matrix, &perspective);
	matrix = matrix_scale(&matrix, 1, 1, 0.1);
	// matrix = matrix_translate(&matrix, 0.1, 0, 0);
	// matrix = matrix_roty(&matrix, 90);
	matrix = matrix_scale(&matrix, 0.1, 0.1, 0.1);

	for (;;) {
		window_update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program_use(&g_res_program_wood);
		program_matrix(&g_res_program_wood, &matrix);
		mesh_draw(&g_res_mesh_Wood);

		context_update();
	}
}