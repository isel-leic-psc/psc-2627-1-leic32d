/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example demonstrates how pointers of different types traverse arrays and how pointer arithmetic depends on the pointed type size.
 * The important detail is that pc++, pi++, and pd++ move by one element, not by one byte, and the size of the element determines the address increment.
 *
 * Compile with:
 *     gcc -o pointers pointers.c
 * Run with:
 *     ./pointers
 *
 */

#include <stdio.h>
 
char   cs[4] = { 'a', 'b', 'c', 'd' };
int    is[4] = { 1, 2, 3, 4 };
double ds[4] = { 1.0, 1.5, 2.3, 4.7 };
double dx[4] = { 21.0, 31.5, 42.3, 54.7 };
short  ss[4] = { 1, 2, 3, 4 };

int main() {
	char *pc = cs;
	int *pi = &is[0];
	double *pd = &ds[2];

	for (int i = 0; i < 3; ++i) {
		/* Each pointer advances to the next element of its array. */
		printf(
			"[%d] pc: 0x%p ; pi: 0x%p ; pd: 0x%p\n",
			i, (void *)pc, (void *)pi, (void *)pd
		);
		printf(
			"[%d] *pc: %c ; *pi: %d ; *pd: %f\n",
			i, *pc, *pi, *pd
		);
		pc++;
		pi++;
		pd++;
	}
	return 0;
}