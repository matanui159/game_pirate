#include "game.h"
#include "res.h"
#include "graphics/window.h"
#include <ogl.h>

static matrix_t g_matrix;
static float g_roty = 0;
static float g_rotx = 0;

void game_init() {
	g_matrix = matrix_identity();
	g_matrix = matrix_perspective(&g_matrix, 1, 100, 60, window_ratio());
	g_matrix = matrix_translate(&g_matrix, 0, 0, 20);
}

void game_update() {
	float dx;
	float dy;
	window_cursor(&dx, &dy);
	g_roty += dx / 10;
	g_rotx += dy / 10;
	if (g_rotx < -90) {
		g_rotx = -90;
	}
	if (g_rotx > 0) {
		g_rotx = 0;
	}

	matrix_t matrix = matrix_rotx(&g_matrix, g_rotx);
	matrix = matrix_roty(&matrix, g_roty);
	matrix = matrix_translate(&matrix, 0, -3, -1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_use(&g_res_program_wood);
	program_matrix(&g_res_program_wood, &matrix);
	mesh_draw(&g_res_mesh_Wood);

	program_use(&g_res_program_metal);
	program_matrix(&g_res_program_metal, &matrix);
	mesh_draw(&g_res_mesh_Grey_metal_1);
	mesh_draw(&g_res_mesh_Grey_metal_3);

	program_use(&g_res_program_black);
	program_matrix(&g_res_program_black, &matrix);
	mesh_draw(&g_res_mesh_Dark_metal);

	program_use(&g_res_program_cloth);
	program_matrix(&g_res_program_cloth, &matrix);
	mesh_draw(&g_res_mesh_Cloth);
}