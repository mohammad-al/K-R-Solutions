/*
*	Write the function itob(n, s, b) that converts the integer n into a base b
*	character representation in the string s. In particular, itob(n, s, 16)
*	formats n as a hexadecimal integer in s.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {

	char string[5];
	itob(255, string, 16);
	// Should print 'ff'
	printf("%s\n", string);

	return 0;
}

void itob(int n, char s[], int b) {
	
	int i, sign;

	if (n < 0) {
		sign = -1;
	} else {
		sign = 1;
	}
	do {
		int j = abs(n % b);
		s[i++] = (j <= 9) ? j + '0' : j - 10 + 'a';
	} while (n /= b);
	if (sign == -1) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[]) {
	
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
