#include "mem.h"
#include "array.h"
#include <windows.h>

void entry() {
	#ifdef TEST_BUILD
		mem_test();
		array_test();
	#else
	#endif
	ExitProcess(0);
}