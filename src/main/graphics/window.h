#ifndef WINDOW_H_
#define WINDOW_H_
#include <windows.h>

void window_error(const char* msg);
void window_init();
void window_update();
HWND window_get();

#endif