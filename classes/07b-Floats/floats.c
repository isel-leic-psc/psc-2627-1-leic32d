/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example reinterprets a 32-bit integer as a float to illustrate how IEEE-754 values are stored in memory.
 * The important point is that the bit pattern in value is not a number in the integer sense; it is a float representation when accessed through a float pointer.
 *
 * Compile with:
 *     gcc -o floats floats.c
 * Run with:
 *     ./floats
 *
 */

#include <stdint.h>
#include <stdio.h>

int main() {
	/* This bit pattern corresponds to a floating-point value when reinterpreted as a float. */
	uint32_t value = (-2 + 127) << 23 | 0x680000;
	uint32_t *pv = &value;
	float *pf = (float *)pv;
	float fval = *pf;

	printf("f: %f\n", fval);
	return 0;
}