#include "graphics/window.h"
#include "graphics/context.h"
#include "res.h"
#include <ogl.h>

void entry() {
	window_init();
	context_init();
	res_init();

	for (;;) {
		window_update();
		
		glClear(GL_COLOR_BUFFER_BIT);
		program_use(&g_res_program_wood);
		mesh_draw(&g_res_mesh_Wood);

		context_update();
	}
}