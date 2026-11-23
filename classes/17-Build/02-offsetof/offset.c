//#include <stddef.h>  // Official offsetof is in stddef.h

#define offsetof(TYPE, MEMBER) \
  ((unsigned int)(unsigned long)&(((TYPE *)0)->MEMBER))

extern int printf(const char * fmt, ...);

struct type {
	int value;
	char * text;
	short num;
};

int main() {
	
	unsigned int sizeOfType = 
		sizeof (struct type);
		
	unsigned int offsetOfText =
		offsetof(struct type, text);
	
	unsigned int offsetOfNum =
		offsetof(struct type, num);
		
	printf(
		"size: %u; text: %u; num: %u\n",
		sizeOfType,
		offsetOfText,
		offsetOfNum
	);
	
	return 0;
}