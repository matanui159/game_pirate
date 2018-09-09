#ifndef CONTEXT_H_
#define CONTEXT_H_
#include <windows.h>

void context_init();
void context_update();
PROC context_func(const char* name);

#endif