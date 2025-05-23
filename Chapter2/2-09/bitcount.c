/*
*	In a two's complement number system, x &= (x - 1) deletes the rightmost
*	1-bit in x. Explain why. Use this observation to write a faster version
*	of bitcount.
*/

#include <stdio.h>

int bitcount(unsigned int x);

int main(void) {

	// Should print out 3.
	printf("%d\n", bitcount(7));

}
int bitcount(unsigned int x) {
	int b;

	for (b = 0; x != 0; x &= (x - 1)) {
		b++;
	}
	return b;
}

/*
	To understand why x &= (x - 1) deletes the rightmost 1-bit in x, we must
	first look at the relationship between x and (x - 1) in terms of their
	bits. From basic arithmetic, we know that

	x = (x - 1) + 1.

	Now, in terms of binary addition, what does it mean to add 1 to a number?
	Let us take the example below and see if we notice anything.

	011001010 +
		1
	_________
	011001011

	Well, it seems as though the rightmost zero of the first operand becomes a
	one after completing the addition. Let us take another example, namely one
	with carrying, to reaffirm this conclusion. 

             1
	01010111001 +
		  1
	___________
	01010111010

	Once again it seems as the the rightmost zero in the first operand becomes
	a one in the result of the addition, namely, the rightmost 1. All other
	bits remain the same.

	So, in x = (x - 1) + 1, we can conclude that the rightmost zero in (x - 1)
	corresponds to the rightmost 1 in x, and all other bits are identical.
	Thus, x & (x - 1) will delete the rightmost 1 in x, since 1 & 0 = 0. All
	other bits will remain the same since a & a = a, where a is 1 or 0.
*/
