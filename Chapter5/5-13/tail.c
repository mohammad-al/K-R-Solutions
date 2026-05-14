#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lines.h"

#define MAXLINES 10000
#define DEFAULT 10

// Array of strings. Each string is a line
char *lineptr[MAXLINES];

int main(int argc, char *argv[]) {

	int num_lines_to_print;
	if (argc == 1) {
		num_lines_to_print = DEFAULT;
	} else if (argc == 2 && argv[1][0] == '-') {
		num_lines_to_print = atoi(argv[1] + 1);
	} else {
		printf("Usage: tail [-n]\n");
		return 1;
	}

	if (num_lines_to_print > MAXLINES) {
		num_lines_to_print = MAXLINES;
	}

	int nlines;

	nlines = readlines(lineptr, MAXLINES);
	if (nlines < 0) {
		printf("error: input too big\n");
	}

	// Adjust num lines to print, if we didn't read enough lines
	if (nlines < num_lines_to_print) {
		num_lines_to_print = nlines;
	}

	int last_line_index = nlines - 1;
	int first_line_index = last_line_index - num_lines_to_print + 1;

	for (int i = 0; i < num_lines_to_print; i++) {
		printf("%s\n", lineptr[first_line_index + i]);
	}

	return 0;
}
