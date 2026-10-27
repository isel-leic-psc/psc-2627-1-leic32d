#include <stdlib.h>
#include <stdio.h>

extern size_t stringlen(const char * str);

int main(int argc, char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "use %s {word}\n", argv[0]);
		exit(1);
	}
	
	const char * str = argv[1];
	
	size_t len = stringlen(str);
	
	printf("stringlen(\"%s\") == %lu\n", str, len);
	
	return 0;
}
