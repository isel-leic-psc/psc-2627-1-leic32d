/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example extracts bit fields from an integer using shifts and masks.
 * The key concept is that right-shifting and masking with ((1 << n) - 1) isolates a selected range of bits without changing the rest of the value.
 *
 * Compile with:
 *     gcc -o getbits getbits.c
 * Run with:
 *     ./getbits
 *
 */

#include <stdio.h>

unsigned getbits(unsigned value, unsigned pos, unsigned n) {
	/* Shift to the desired position and mask the bit field to keep only the n bits we want. */
	return (value >> pos) & ((1 << n) - 1);
}

int main() {
	unsigned x = 0xE7BA896C;
	
	unsigned v1 = getbits(x, 3, 6);
	unsigned v2 = getbits(x, 6, 2);
	unsigned v3 = getbits(x, 12, 5);
	unsigned v4 = getbits(x, 29, 3);
	
	printf("v1: %x\n", v1);
	printf("v2: %x\n", v2);
	printf("v3: %x\n", v3);
	printf("v4: %x\n", v4);
	
	return 0;
}
