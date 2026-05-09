#include <stdio.h>
#include "alloc.h"
#include "lines.h"
#include "string.h"

// Maximum length of any given line
#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines, char *line_storage, int maxstorage) {
	
	int nlines = 0;
	int len;
	char *p = line_storage;
	char line[MAXLEN];

	char *final_address = line_storage + maxstorage - 1; 

	// if we read a line, then handle it
	while ((len = my_getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || p + len - 1 > final_address) {
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

void writelines(char *lineptr[], int nlines) {
	
	int i;
	for (i = 0; i < nlines; i++) {
		printf("%s\n", lineptr[i]);
	}
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
