#include <stdio.h>
#include <dlfcn.h>

#include "parser_interface.h"
#include "colors.h"


int main()
{
	void* lib_parser = dlopen("./lib_csv_parser.so", RTLD_LAZY);
	if (lib_parser == NULL)
	{
		printf(RED "failed to load csv_parser library\n" RESET_COLOR);
		return -1;
	}

	test_foo = dlsym(lib_parser, "test_foo");


	test_foo();

	return 0;
}
