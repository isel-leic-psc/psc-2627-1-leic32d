#define TEXT MESSAGE

#define MESSAGE "Hello, world!" 
#define OK 0

#define number int

#define entry main

#define noargsf () {
#define endf       }

extern int puts(const char * str);

number entry
noargsf
	puts(MESSAGE);
	puts(TEXT);
	return OK;
endf 
