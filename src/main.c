#include "graphics/window.h"
#include "graphics/context.h"
#include "res.h"
#include <ogl.h>

void entry() {
	window_init();
	context_init();
	res_init();

	matrix_t matrix;
	matrix_identity(&matrix);

	for (;;) {
		window_update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program_use(&g_res_program_wood);
		program_matrix(&g_res_program_wood, &matrix);
		mesh_draw(&g_res_mesh_Wood);

		context_update();
	}
}