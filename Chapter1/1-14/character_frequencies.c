/*
*	Write a prgram to print a histogram of the frequencies of different
*	characters in its input.
*/

#include <stdio.h>
#include <ctype.h>

#define MAX_CHAR 128

int main(void) {

	int charFreq[MAX_CHAR] = { 0 };

	int c;
	while ((c = getchar()) != EOF) {
		if (c < MAX_CHAR) {
			++charFreq[c];
		}
	}
	for (int i = 0; i < MAX_CHAR; ++i) {
		if (isprint(i)) {
			printf("ASCII - %c, Decimal - %3d: ", i, i);
		} else {
			printf("ASCII -  , Decimal - %3d: ", i);
		}
		if (charFreq[i] > 0) {
			for (int j = 0; j < charFreq[i]; ++j) {
				printf(" * ");
			}
		}
		putchar('\n');
	}
}
