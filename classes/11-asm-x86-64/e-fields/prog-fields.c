#include <stdio.h>

struct type_a { int g; int h; };
struct type_b { int m; float n; char * s; int x; }; 

// declaração da função fsum
extern int example_sum_of_fields(
	struct type_a * pa,
	struct type_b * pb
); // returns: pa->h + pb->x

// definição da função main
int main() {
	struct type_a obj_a =
		{ .g = 55, .h = 33 };

	struct type_b obj_b =
		{ .m = 3, .n = 5.0, .s = "LEIC32D", .x = 21 };
	
	int res = example_sum_of_fields(&obj_a, &obj_b);
	
	printf("res: %d\n", res);
	
	return 0;
}