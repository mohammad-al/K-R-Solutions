/*
*	Write a version of itoa that accepts three arguments instead of two. The
*	third argument is a minimum field width; the converted number must be
*	padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void) {

	char string[10];
	itoa(371, string, 7);

	// Should print '    371'
	printf("%s\n", string);

	return 0;
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[], int w) {
	
	int i, sign;

	if (n < 0) {
		sign = -1;
	} else {
		sign = 1;
	}
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while (n /= 10);

	if (sign == -1) {
		s[i++] = '-';
	}
	while (i < w) {
		s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}
