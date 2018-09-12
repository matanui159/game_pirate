local list = {
	"glGenBuffers",
	"glBindBuffer",
	"glBufferData",

	"glGenVertexArrays",
	"glBindVertexArray",
	"glEnableVertexAttribArray",
	"glVertexAttribPointer",

	"glCreateShader",
	"glShaderSource",
	"glCompileShader",

	"glCreateProgram",
	"glAttachShader",
	"glLinkProgram",
	"glUseProgram",

	"glGetUniformLocation",
	"glUniformMatrix4fv"
}

for i, v in ipairs(list) do
	list[i] = {
		func = v,
		type = "PFN" .. v:upper() .. "PROC"
	}
end

local out = io.open(arg[1], "wb")
out:write([[
#ifndef OGL_H_
#define OGL_H_
#include <GL/gl.h>
#include <GL/glext.h>

]])

for i, v in ipairs(list) do
	out:write("extern " .. v.type .. " ogl_" .. v.func .. ";\n")
end

out:write([[

void ogl_init();

]])

for i, v in ipairs(list) do
	out:write("#define " .. v.func .. " ogl_" .. v.func .. "\n")
end

out:write([[

#endif
#ifdef OGL_BUILD
#include <windows.h>

]])

for i, v in ipairs(list) do
	out:write(v.type .. " ogl_" .. v.func .. ";\n");
end

out:write([[

static PROC ogl_proc(const char* name) {
	PROC result = wglGetProcAddress(name);
	if (result == NULL) {
		MessageBox(NULL, name, NULL, MB_ICONERROR);
		ExitProcess(1);
	}
	return result;
}

void ogl_init() {
]])

for i, v in ipairs(list) do
	out:write("\togl_" .. v.func .. " = (" .. v.type .. ")"
		.. "ogl_proc(\"" .. v.func .. "\");\n")
end

out:write([[
}

#endif
]])