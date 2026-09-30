/*
 * Instituto Superior de Engenharia de Lisboa
 * Licenciatura em Engenharia Informática e de Computadores
 * Programação de Sistemas Computacionais
 *
 * This example converts Celsius temperatures into Fahrenheit using a loop and symbolic constants, in a traditional imperative style.
 * Note that the expression 9.0 / 5 * tc + 32 uses floating-point arithmetic, but the final result is stored in an int, so the decimal part is truncated.
 *
 * Compile with:
 *     gcc -o temps temps.c
 * Run with:
 *     ./temps
 *
 */

#include <stdio.h>

#define LOWT  -5
#define HIGHT 55
#define STEPT  5
 
/*
const int LOWT  = -5;
const int HIGHT = 55;
const int STEPT =  5;
*/

int main() {
	int tc;

	for (tc = LOWT; tc < HIGHT; tc += STEPT) {
		/* Each iteration computes one conversion for the current Celsius value. */
		int tf = 9.0 / 5 * tc + 32;
		printf("%d C => %d F\n", tc, tf);
	}

	return 0;
}
