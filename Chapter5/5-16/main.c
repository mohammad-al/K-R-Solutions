#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lines.h"

// max number of lines that can be stored
#define MAXLINES 5000

#define MAXSTORAGE 10000

int reverse = 1;
int fold = 0;
int directory_order = 0;

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
		if (argc > 1 && strcmp(argv[1], "-f") == 0) {
			fold = 1;
		}
		if (argc > 1 && strcmp(argv[1], "-d") == 0) {
			directory_order = 1;
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
	
	// Go character by character and do strcmp manually
	while (*s1 != '\0' && *s2 != '\0') {

		// If directory order, skip current characters if they are not alphanum or space
		if (directory_order) {
			while (*s1 != '\0' && !isalnum(*s1) && !isspace(*s1)) {
				s1++;
			}
			while (*s2 != '\0' && !isalnum(*s2) && !isspace(*s2)) {
				s2++;
			}
		}
		int compare_result = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
		// Means characters are equal. Should move along to next characters
		if (compare_result == 0) {
			s1++;
			s2++;
		} else {
			return compare_result * reverse;
		}

	}

	// If we reach here, then one of the strings has reached the end
	int compare_result = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
	return compare_result * reverse;
}
