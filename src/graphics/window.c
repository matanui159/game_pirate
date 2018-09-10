#include "window.h"

static HWND g_window;

static LRESULT CALLBACK window_proc(HWND wnd, UINT msg,
		WPARAM wpm, LPARAM lpm) {
	if (msg == WM_CLOSE || (msg == WM_KEYDOWN && wpm == VK_ESCAPE)) {
		ExitProcess(0);
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
	ExitProcess(1);
}

void window_init() {
	const WCHAR class_name[] = L"window";
	HMODULE module = GetModuleHandleW(NULL);

	WNDCLASSW wndclass = {};
	wndclass.hInstance = module;
	wndclass.lpszClassName = class_name;
	wndclass.lpfnWndProc = window_proc;
	wndclass.style = CS_OWNDC;
	wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
	if (RegisterClassW(&wndclass) == 0) {
		window_error(NULL);
	}

	g_window = CreateWindowExW(
		0,
		class_name,
		L"Pirate Game",
		WS_POPUP | WS_VISIBLE,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		module,
		NULL
	);
	if (g_window == NULL) {
		window_error(NULL);
	}
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