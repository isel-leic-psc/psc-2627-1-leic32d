/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example shows the difference between global, local, and dynamically allocated memory in C.
 * The important point is that the global object lives for the whole program, the local object is created per function call, and the heap allocation from malloc() must be released with free().
 *
 * Compile with:
 *     gcc -o memory memory.c
 * Run with:
 *     ./memory
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 256

struct student {
	unsigned int number;
	char name[NAME_LEN];
};

struct student s = { 1234, "Pedro" };
struct student *ps = &s;

void f(int i) {
	/* Each recursive call creates a new local student object in the stack frame. */
	struct student ls = { 1234 + i, "Pedro" };

	printf("local student at: 0x%p\n", (void *)&ls);

	/* malloc() requests memory from the heap; it remains valid until free() is called. */
	struct student *ps = malloc(sizeof(struct student));

	printf("dynamic student at: 0x%p\n", (void *)ps);

	if (i > 0) {
		f(i - 1);
	}

	free(ps);
}

int main() {
	printf("global student at: 0x%p\n", (void *)&s);
	f(2);
	return 0;
}
