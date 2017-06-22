#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	printf("%s\n", "test");
	printf("%s\n", argv[0]);
	printf("%s\n", argv[1]);

	const char* s = getenv("REST");
	printf("PATH :%s\n",(s!=NULL)? s : "getenv returned NULL");
	printf("end test\n");
	return 0;
}