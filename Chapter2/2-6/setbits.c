/*
*	Write a function setbits(x, p, n, y) that returns x with the n bits that
*	begin at position p set to the rightmost n bits of y, leaving the other
*	bits unchanged. 
*/

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, int unsigned y);

int main(void) {

	// Should print 947
	printf("%d\n", setbits((unsigned int)851, 7, 3, (unsigned int)693));

	return 0;
}

unsigned int setbits(unsigned int x, int p, int n, int unsigned y) {

	// Shift the n rightmost bits of y to position starting at p
	unsigned int y_rightmost = (~(~0 << n) & y) << (p - n + 1);
	// Get x to have the same bits as before, expect from position p,
	// the next n bits will be 0
	x = x & ~((~(~0 << n)) << (p - n + 1));
	return x | y_rightmost;
}
