#include "window.h"
#include <stdlib.h>

static HWND g_window;
static _Bool g_grab = 1;

static LRESULT CALLBACK window_proc(HWND wnd, UINT msg,
		WPARAM wpm, LPARAM lpm) {
	switch (msg) {
		case WM_DESTROY:
			exit(EXIT_SUCCESS);
		case WM_KEYDOWN:
			switch (wpm) {
				case VK_ESCAPE:
					exit(EXIT_SUCCESS);
				case VK_F1:
					g_grab = !g_grab;
					ShowCursor(!g_grab);
					break;
			}
			break;
	}
	return DefWindowProcW(wnd, msg, wpm, lpm);
}

void window_error(const char* msg) {
	if (msg == NULL) {
		DWORD flags = 0
			| FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_IGNORE_INSERTS
			| FORMAT_MESSAGE_ALLOCATE_BUFFER;
		FormatMessageA(flags, NULL, GetLastError(), 0, (char*)&msg, 0, NULL);
	}
	MessageBox(g_window, msg, NULL, MB_ICONERROR);
	exit(EXIT_FAILURE);
}

void window_init() {
	const WCHAR class_name[] = L"window";
	HMODULE module = GetModuleHandleW(NULL);

	const WNDCLASSW wndclass = {
		.hInstance = module,
		.lpszClassName = class_name,
		.lpfnWndProc = window_proc,
		.style = CS_OWNDC,
		.hCursor = LoadCursorA(NULL, IDC_ARROW)
	};

	if (RegisterClassW(&wndclass) == 0) {
		window_error(NULL);
	}

	#ifdef NDEBUG
		DWORD style = WS_POPUP;
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
	#else
		DWORD style = WS_CAPTION | WS_SYSMENU;
		int width = 1280;
		int height = 720;
	#endif

	g_window = CreateWindowExW(
		0,
		class_name,
		L"Pirate Game",
		style | WS_VISIBLE,
		0,
		0,
		width,
		height,
		NULL,
		NULL,
		module,
		NULL
	);
	if (g_window == NULL) {
		window_error(NULL);
	}
	ShowCursor(0);
}

void window_update() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		DispatchMessageW(&msg);
	}
}

HWND window_get() {
	return g_window;
}

float window_ratio() {
	RECT rect;
	GetWindowRect(g_window, &rect);
	return (float)(rect.right - rect.left) / (rect.bottom - rect.top);
}

void window_cursor(float* x, float* y) {
	if (g_grab && GetFocus() == g_window) {
		POINT cursor;
		RECT rect;
		GetCursorPos(&cursor);
		GetWindowRect(g_window, &rect);
		
		int midx = (rect.left + rect.right) / 2;
		int midy = (rect.top + rect.bottom) / 2;
		*x = cursor.x - midx;
		*y = cursor.y - midy;
		SetCursorPos(midx, midy);
	} else {
		*x = 0;
		*y = 0;
	}
}