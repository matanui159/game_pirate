#include "context.h"
#include "window.h"
#include <ogl.h>
#include <GL/wglext.h>

typedef PFNWGLCREATECONTEXTATTRIBSARBPROC create_context_t;

static HDC g_dc;

void context_init() {
	HWND wnd = window_get();
	g_dc = GetDC(wnd);

	PIXELFORMATDESCRIPTOR format = {};
	format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	format.nVersion = 1;
	format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	format.cColorBits = 24;
	format.cAlphaBits = 8;
	format.cDepthBits = 24;
	format.cStencilBits = 8;
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
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	context = create_context(g_dc, NULL, attribs);
	if (context == NULL) {
		window_error(NULL);
	}
	wglMakeCurrent(g_dc, context);
	ogl_init();
	// glViewport(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

void context_update() {
	#define OGL_ERROR(error) case GL_##error: window_error(#error); break
	GLenum error = glGetError();
	switch (error) {
		OGL_ERROR(OUT_OF_MEMORY);
		OGL_ERROR(INVALID_VALUE);
		OGL_ERROR(INVALID_ENUM);
		OGL_ERROR(INVALID_OPERATION);
		OGL_ERROR(INVALID_FRAMEBUFFER_OPERATION);
		default:
			if (error != GL_NO_ERROR) {
				window_error("OpenGL Error");
			}
			break;
	}
	SwapBuffers(g_dc);
}