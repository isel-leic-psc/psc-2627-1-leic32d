/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example compares two different ways of interpreting the same bit pattern: as an integer and as a float, and also by using bitfields.
 * The important detail is that a union stores the same memory location in multiple ways, which is useful to inspect the sign, exponent, and mantissa fields of a float.
 *
 * Compile with:
 *     gcc -o unions unions.c
 * Run with:
 *     ./unions
 *
 */

#include <stdint.h>
#include <stdio.h>

/* Bitfields split a single integer into named sections with fixed widths. */
struct fbits {
	uint32_t mts : 23;
	uint32_t exp : 8;
	uint32_t sgn : 1;
};

union number {
	uint32_t ival;
	float    fval;
};

union numbits {
	struct fbits ival;
	float        fval;
};

int main() {
	union number value;
	value.ival = (-2 + 127) << 23 | 0x680000;
	printf("f: %f\n", value.fval);

	union numbits valbits;
	/* These fields reconstruct the same binary float layout using field names. */
	valbits.ival.sgn = 0;
	valbits.ival.exp = -2 + 127;
	valbits.ival.mts = 0x680000;
	printf("f: %f\n", valbits.fval);
	return 0;
}
