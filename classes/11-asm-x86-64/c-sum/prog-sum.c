
extern int printf(const char * str, ...);

// declaração da função fsum
extern int fsum(int a, int b);

// definição da função main
int main() {
	
	int x = 4;
	int y = 21;
	
	int res = fsum(x, y);
	
	printf("res: %d\n", res);
	
	return 0;
}

