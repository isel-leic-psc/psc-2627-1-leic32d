/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example demonstrates that writing past the end of an array can corrupt memory and eventually crash the program.
 * The key point is that the pointer continues advancing forever, so the write through *pi eventually targets invalid memory addresses.
 *
 * Compile with:
 *     gcc -o segfault segfault.c
 * Run with:
 *     ./segfault
 *
 */

#include <stdio.h>

int is[4] = { 1, 2, 3, 4 };

int main() {
	int *pi = is;
	for (;;) {
		/* The pointer keeps moving to the next memory location, even after the array ends. */
		printf("pi: 0x%p\n", (void *)pi);
		*pi = 8;
		++pi;
	}
	return 0;
}