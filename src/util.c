#include "util.h"
#include <windows.h>

void util_print(const char* message) {
	static HANDLE file;
	if (file == NULL) {
		file = CreateFileW(L"util.log", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, 0, NULL);
	}
	WriteFile(file, message, lstrlenA(message), NULL, NULL);

	char newline = '\n';
	WriteFile(file, &newline, 1, NULL, NULL);
}