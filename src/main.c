#include "graphics/window.h"
#include "graphics/context.h"
#include "res.h"
#include "game.h"

int main() {
	window_init();
	context_init();
	res_init();
	game_init();

	for (;;) {
		window_update();
		game_update();
		context_update();
	}
}