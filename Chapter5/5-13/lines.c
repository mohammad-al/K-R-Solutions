#include <stdio.h>
#include "alloc.h"
#include "lines.h"
#include "string.h"

// Maximum length of any given line
#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines) {
	
	// Number of lines read
	int nlines = 0;

	// Lenght of each line
	int len;

	char *p;
	char line[MAXLEN];


	// if we read a line, then handle it
	while ((len = my_getline(line, MAXLEN)) > 0) {
		// We do p = alloc(len) to get memory to store the line into.
		// alloc memory exists outside this function unline line variable
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			// Remove the newline character from the line
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}
	return nlines;
}

int my_getline(char line[], int lim) {
	
	int i;
	int c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i++] = '\n';
	}
	line[i] = '\0';
	return i;
}
