#include <stdbool.h>

int printf(const char * fmt, ...);

bool also_add_c = true;

int c = 78;

int add(int m, int n) {
	return m + n;
}

int main() {

	int a = 5, b = 4, res;

	res = add(a, b);
	if (also_add_c) {
		res = add(res, c);
	}

	printf("res: %d\n", res);

	return 0;
}
