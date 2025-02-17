/*
*	In a two's complement number representation, our version of itoa does not
*	handle the largest negative number, that is, the value of n equal to
*	-(2^(wordsize - 1)). Explain why not. Modify it to print that value
*	correctly , regardless of the machine on which it runs.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {

	char num[5];
	itoa(-341, num);

	// Should print -341 as a string
	printf("%s\n", num);

	return 0;
}

void itoa(int n, char s[]) {
	
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

/*
	The reason that the largest negative ingteger doesn't work is because of
	numbers are stored in a two's complement number representation. In a two's
	complement number representation, with n bits, the range of representable
	numbers are from:

	-(2^(n - 1)) to (2^(n - 1)) - 1.

	In the original itoa function, if the number is negative, we mulitply by
	negative one to turn it positive. In the case that we have the largest
	negative number, after mulitplication, we get the number

	(2^(n - 1)) which is one number larger than our maximum possible number.
	Therefore, the previous implementation of itoa cannot handle the case 
	where we give the largest negative number. The above solution resolves
	this issue.
*/
