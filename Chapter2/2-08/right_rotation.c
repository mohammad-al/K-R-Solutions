/*
*	Write a function rightrot(x, n) that returns the value of the integer x
*	rotated to the right by n bit positions.
*/

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
int size_of_unsigned_int(void);

int main(void) {

	// Should print 402653210
	printf("%u\n", rightrot(835, 5));

	return 0;
}

unsigned int rightrot(unsigned int x, int n) {

	// Get the last n bits in a separate variable
	unsigned int last_n_bits = x & ~(~0 << n);

	int num_bits = size_of_unsigned_int();

	// Shift x by n bits and set the first n bits
	return (x >> n) | (last_n_bits << (num_bits - n));
}

// Returns the number of bits in an usigned int
int size_of_unsigned_int(void) {

	// This will be an unsigned integer with 1's as all of its bits
	unsigned int x = ~0;

	int num_bits = 0;

	// Keep removing 1's from x until x is 0.
	while (x != 0) {
		x = x << 1;
		num_bits++;
	}
	return num_bits;
}
