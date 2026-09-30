/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example introduces the minimal structure of a C program and the role of the main() function.
 * The key point to observe is that puts() writes a string to standard output and that returning 0 indicates success.
 *
 * Compile with:
 *     gcc -o hello hello.c
 * Run with:
 *     ./hello
 *
 */

#include <stdio.h>

int main() {
	/* The main() function is the program entry point. */
	puts("Hello, world!");
	return 0;
}
