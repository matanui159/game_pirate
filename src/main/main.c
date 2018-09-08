#include "array.h"
#include <windows.h>

void entry() {
	#ifdef TEST_BUILD
		array_test();
	#else
	#endif
	ExitProcess(0);
}