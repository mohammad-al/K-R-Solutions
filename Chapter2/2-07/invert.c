/*
*	Write a function invert(x, p, n) that returns x with the n bits that begin
*	at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the
*	others unchanged.
*/

#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

int main(void) {

	// Should print 981
	printf("%u\n", invert(821, 7, 3));

	return 0;

}

unsigned int invert(unsigned int x, int p, int n) {


	// Just do a bitwise exclusive OR with x and a bitmask with n 1's starting
	// at p, and 0's everywhere else. This is because 1 ^ x = ~ x and 0 ^ x = x
	return x ^ (~(~0 << n) << (p - n + 1));
}
