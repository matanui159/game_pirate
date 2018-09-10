#include "graphics/window.h"
#include "graphics/context.h"
#include <ogl.h>

void entry() {
	window_init();
	context_init();
	for (;;) {
		window_update();

		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		context_update();
	}
}