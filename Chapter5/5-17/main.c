#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lines.h"

// max number of lines that can be stored
#define MAXLINES 5000

#define MAXSTORAGE 10000

#define MAXSTR 1000

int numeric = 0;
int reverse = 1;
int fold = 0;
int directory_order = 0;

int field_1 = 0;
int field_2 = 0;

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
void get_substring(char *s, char *sub);
int parse_arguments(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	// Number of input lines read
	int nlines;


	if (parse_arguments(argc, argv)) {
		return 1;
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

	char string[MAXSTR];

	get_substring(s1, string);
	v1 = atof(string);

	get_substring(s2, string);
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

	int s1_len = strlen(s1);
	if (field_1 > s1_len || field_2 > s1_len) {
		printf("error: invalid fields. not within range\n");
		exit(1);
	}

	int s2_len = strlen(s2);
	if (field_1 > s2_len || field_2 > s2_len) {
		printf("error: invalid fields. not within range\n");
		exit(1);
	}

	// Set the start of s1 and s2 when doing comparisons
	s1 += field_1 - 1;
	s2 += field_1 - 1;

	// Set the end of s1 and s2 that we need to traverse up to
	char *end_s1 = field_2 > 0 ? s1 + (field_2 - field_1) : s1 + s1_len;
	char *end_s2 = field_2 > 0 ? s2 + (field_2 - field_1) : s2 + s2_len;

	
	// Go character by character and do strcmp manually
	while (s1 < end_s1 && s2 < end_s2) {

		// If directory order, skip current characters if they are not alphanum or space
		if (directory_order) {
			while (s1 < end_s1 && !isalnum(*s1) && !isspace(*s1)) {
				s1++;
			}
			while (s2 < end_s2 && !isalnum(*s2) && !isspace(*s2)) {
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

int parse_arguments(int argc, char *argv[]) {

	for (int i = 1; i < argc; i++) {
		char *argument = argv[i];
		int c = *argument;
		if (c == '-' && !isdigit(argument[1])) {
			while (*++argument) {
				switch(*argument) {
					case 'n':
						numeric = 1;
						break;
					case 'r':
						reverse = -1;
						break;
					case 'f':
						fold = 1;
						break;
					case 'd':
						directory_order = 1;
						break;
					default:
						printf("error: illegal argument of %d\n", *argument);
						return 1;
				}
			}
		// Means got a -NUMBER
		} else if (c == '-') {
			field_2 = atoi(&argument[1]);
		// Means got a +NUMBER
		} else if (c == '+') {
			field_1 = atoi(&argument[1]);
		}
	}
	if (field_1 > field_2) {
		printf("error: field 1 cannot be greater than field 2\n");
		return 1;
	}
	return 0;
}

void get_substring(char *s, char *sub) {

	int final_field = strlen(s);
	// Means field_2 is beyond the string end
	if (field_2 > 0 && final_field < field_2) {
		printf("error: field 2 is too large\n");
		exit(1);
	// Update final field to be field_2 if provided
	} else if (field_2 > 0 && final_field > field_2) {
		final_field = field_2;
	}
	int j = 0;
	for (int i = field_1; i < final_field; i++, j++) {
		sub[j] = s[i];
	}
	sub[j] = '\0';
}
