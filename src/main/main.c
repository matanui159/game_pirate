#include "graphics/window.h"
#include <windows.h>

void entry() {
	window_init();
	for (;;) {
		window_update();
	}
}