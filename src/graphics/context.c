#include "context.h"
#include "window.h"
#include <ogl.h>
#include <GL/wglext.h>

#define UNUSED(x) (void)(x)

typedef PFNWGLCREATECONTEXTATTRIBSARBPROC create_context_t;
typedef PFNGLDEBUGMESSAGECALLBACKPROC debug_callback_t;

static HDC g_dc;

#ifndef NDEBUG
static HANDLE g_log;

static void APIENTRY ogl_debug(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message,
		const void* user) {
	UNUSED(source);
	UNUSED(type);
	UNUSED(id);
	UNUSED(user);

	WriteFile(g_log, message, length, NULL, NULL);
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		window_error(message);
	}
}
#endif

void context_init() {
	HWND wnd = window_get();
	g_dc = GetDC(wnd);

	const PIXELFORMATDESCRIPTOR format = {
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.cColorBits = 24,
		.cAlphaBits = 8,
		.cDepthBits = 24,
		.cStencilBits = 8
	};

	int id = ChoosePixelFormat(g_dc, &format);
	if (id == 0) {
		window_error(NULL);
	}
	SetPixelFormat(g_dc, id, &format);

	HGLRC context = wglCreateContext(g_dc);
	if (context == NULL) {
		window_error(NULL);
	}

	wglMakeCurrent(g_dc, context);
	create_context_t create_context
		= (create_context_t)wglGetProcAddress("wglCreateContextAttribsARB");
	wglMakeCurrent(g_dc, NULL);
	wglDeleteContext(context);
	
	const int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		#ifndef NDEBUG
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
		#endif
		0
	};

	context = create_context(g_dc, NULL, attribs);
	if (context == NULL) {
		window_error(NULL);
	}
	wglMakeCurrent(g_dc, context);
	ogl_init();
	
	#ifndef NDEBUG
		g_log = CreateFileW(L"ogl.log", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, 0, NULL);
		debug_callback_t debug_callback
			= (debug_callback_t)wglGetProcAddress("glDebugMessageCallback");
		debug_callback(ogl_debug, NULL);
	#endif

	glEnable(GL_DEPTH_TEST);
}

void context_update() {
	SwapBuffers(g_dc);
}