/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example computes the length of two strings without relying on the standard strlen() function.
 * The key detail to observe is that strings in C are terminated by the null character '\0', and pointer arithmetic lets us walk the character array one byte at a time.
 *
 * Compile with:
 *     gcc -o strings strings.c
 * Run with:
 *     ./strings
 *
  */

#include <stdio.h>

unsigned xstrlen(char *str) {
	unsigned len = 0;
	unsigned i;
	for (i = 0; *(str + i) != '\0'; ++i) {
		/* Each character before the terminator increases the counter. */
		++len;
	}
	return len;
}

int main() {
	char *str1 = "Hello!";
	char *str2 = "LEIC32D";
	
	unsigned len1 = xstrlen(str1);
	unsigned len2 = xstrlen(str2);
	
	printf("strlen(str1) : %u\n", len1);
	printf("strlen(str2) : %u\n", len2);
	
	return 0;
}