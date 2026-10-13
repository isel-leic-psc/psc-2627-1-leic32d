#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#define WORD_SIZE 64
#define MAX_WORDS 16384

struct word_entry {
	unsigned count;
	char word[WORD_SIZE];
};

struct word_entry allWords[MAX_WORDS]; 
size_t numWords = 0;

size_t findWordIndex(char * word) {
	int idx;
	for (idx = 0; idx < numWords; ++idx) {
		if (strcmp(word, allWords[idx].word) == 0) {
			break;
		}
	}
	return idx;
}

void processWord(char * word) {
	size_t wordIndex = findWordIndex(word);
	if (wordIndex < numWords) {
		allWords[wordIndex].count += 1;
	} else {
		if (numWords == MAX_WORDS) {
			fprintf(stderr, "MAX_WORDS reached\n");
			exit(5);
		}
		strcpy(allWords[wordIndex].word, word);
		allWords[wordIndex].count = 1;
		numWords += 1;
	}
}

enum WordsParseStates { IN_SPACE, IN_WORD };

bool isSeparator(char c) {
	return strchr(" \t\r\n<{[()]}>*+=-#\"'?!,.:;|\\/&", c) != NULL; 
}

void processFile(FILE * file) {
	
	int state = IN_SPACE;
	
	char word[WORD_SIZE];
	size_t index = 0;

	int c;
	while ((c = fgetc(file)) != EOF) {
		c = tolower(c);
		if (isSeparator(c)) {
			if (state == IN_WORD) {
				word[index] = '\0';
				processWord(word);
				index = 0;
				state = IN_SPACE;
			}
		} else {
			word[index++] = c;
			state = IN_WORD;
		}
	}
}

void showResults() {
	for (unsigned i = 0; i < numWords; ++i) {
		printf(
			"%4u : %s\n",
			allWords[i].count,
			allWords[i].word
		);
	}
}

void printUsage(const char * progName) {
	fprintf(
		stderr,
		"use: %s [-i input-file-name]\n",
		progName
	);
}

int main(int argc, char * argv[]) {
	char * inputFileName = NULL;
	FILE * inputFile = stdin;
	
	int optc;
	while ((optc = getopt(argc, argv, ":i:")) != -1) {
		switch (optc) {
			case 'i':
				inputFileName = optarg;
				break;
			case '?':
				fprintf(stderr,
				        "Invalid option: -%c\n", optopt);
				printUsage(argv[0]);
				exit(2);
			case ':':
				fprintf(
					stderr,
				    "Option -%c requires an argument\n",
					optopt
				);
				printUsage(argv[0]);
				exit(3);
			default:
				fprintf(stderr, "Unexpected error\n");
				printUsage(argv[0]);
				exit(4);
		}
	}
	
	if (inputFileName != NULL) {
		inputFile = fopen(inputFileName, "r");
		if (inputFile == NULL) {
			fprintf(stderr, "Failed to open \"%s\"\n", inputFileName);
			exit(1);
		}
	}

	processFile(inputFile);
	
	if (inputFile != stdin) {
		fclose(inputFile);
	}
	
	showResults();

	return 0;
}
