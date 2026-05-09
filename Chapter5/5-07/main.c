#include <stdio.h>
#include <string.h>
#include "lines.h"

// max number of lines that can be stored
#define MAXLINES 5000

#define MAXSTORAGE 10000

// Pointers to text lines
char *lineptr[MAXLINES];

char line_storage[MAXSTORAGE];

void swap(char *v[], int i, int j);
void qsort(char *lineptr[], int left, int right);

int main(void) {

	// Number of input lines read
	int nlines;

	// Means we read a line
	if ((nlines = readlines(lineptr, MAXLINES, line_storage, MAXSTORAGE)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

void swap(char *v[], int i, int j) {
	
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void qsort(char *v[], int left, int right) {
	
	int i, last;
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (strcmp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

