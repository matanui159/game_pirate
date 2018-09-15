#ifndef RES_H_
#define RES_H_
#include "graphics/mesh.h"
#include "graphics/program.h"

extern mesh_t g_res_mesh_Wood;
extern mesh_t g_res_mesh_Dark_metal;
extern mesh_t g_res_mesh_Grey_metal_1;
extern mesh_t g_res_mesh_Grey_metal_3;
extern mesh_t g_res_mesh_Cloth;

extern program_t g_res_program_wood;
extern program_t g_res_program_metal;
extern program_t g_res_program_black;
extern program_t g_res_program_cloth;

void res_init();

#endif