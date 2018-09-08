#include "test.h"
#include <windows.h>

#ifdef TEST_BUILD

void test_fail(const char* msg) {
	HANDLE stderr = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteFile(stderr, msg, lstrlenA(msg), NULL, NULL);
	char newline = '\n';
	WriteFile(stderr, &newline, 1, NULL, NULL);
	ExitProcess(1);
}

#endif