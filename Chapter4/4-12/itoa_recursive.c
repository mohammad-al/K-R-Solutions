/*
*	Adapt the ideas of printd to write a recursive version of itoa; that is
*	convert an integer into a string by calling a recursive routine.
*/

#include <stdio.h>
#include <stdlib.h>

void itoa(int n, char s[]);

int main(void) {
	
	// Can hold maximum of three digit number
	char s[6];

	itoa(-125, s);

	printf("The number 123 as a string is %s\n", s);

}

void itoa(int n, char s[]) {

	static int i;

	// Base case. Means we have only one digit
	if ((n / 10) == 0) {
		i = 0;
		if (n < 0) {
			s[i++] = '-';
			n = -n;
		}
	// Recursive case
	} else {
		itoa(n / 10, s);
	}
	s[i++] = abs(n % 10) + '0';
	s[i] = '\0';
}
