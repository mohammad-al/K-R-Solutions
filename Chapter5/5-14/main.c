#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lines.h"

// max number of lines that can be stored
#define MAXLINES 5000

#define MAXSTORAGE 10000

int reverse = 1;

// Pointers to text lines
char *lineptr[MAXLINES];

char line_storage[MAXSTORAGE];

void swap(void *v[], int i, int j);
void my_qsort(
	char *v[],
	int left,
	int right,
    int (*comp)(void *, void *)
);

int numcmp(char *, char *);
int my_strcmp(char *, char *);

int main(int argc, char *argv[]) {

	// Number of input lines read
	int nlines;

	// 1 if numeric sort
	int numeric = 0;

	for (int i = 0; i < argc; i++) {
		if (argc > 1 && strcmp(argv[1], "-n") == 0) {
			numeric = 1;
		}
		if (argc > 1 && strcmp(argv[1], "-r") == 0) {
			reverse = -1;
		}
	}

	// Means do numeric sort
	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		numeric = 1;
	}
	if (argc > 2 && strcmp(argv[2], "-r") == 0) {
		reverse = -1;
	}

	// Means we read a line
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		my_qsort(lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : my_strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

void swap(void *v[], int i, int j) {
	
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void my_qsort(
	char *v[],
	int left,
	int right,
    int (*comp)(void *, void *)
) {
	
	int i, last;
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (comp(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	my_qsort(v, left, last - 1, comp);
	my_qsort(v, last + 1, right, comp);
}


int numcmp(char *s1, char *s2) {
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2) {
		return -1 * reverse;
	} else if (v1 > v2) {
		return 1 * reverse;
	} else {
		return 0;
	}
}
int my_strcmp(char *s1, char *s2) {
	return strcmp(s1, s2) * reverse;
}
