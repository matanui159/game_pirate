#include "test.h"
#include <windows.h>

#ifdef TEST_BUILD

void test_fail(const char* name) {
	HANDLE stderr = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteFile(stderr, "Failed: ", 8, NULL, NULL);
	WriteFile(stderr, name, lstrlenA(name), NULL, NULL);

	char newline = '\n';
	WriteFile(stderr, &newline, 1, NULL, NULL);
	ExitProcess(1);
}

#endif