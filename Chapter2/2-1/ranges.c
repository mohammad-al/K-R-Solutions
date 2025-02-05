/*
*	Write a program to determine the ranges of char, short, int, and long
*	variables, both signed and unsigned, by printing appropriate values from
*	standard headers and by direct computation. Harder if you compute them:
*	 determine the ranges of the various floating-point types.
*/

#include <stdio.h>
#include <limits.h>

int main(void) {
	
	printf("The range of a signed char is from %d to %d.\n", SCHAR_MAX, SCHAR_MIN);
	printf("The range of an unsigned char is from 0 to %u.\n", UCHAR_MAX);
	printf("The range of a signed short is from %d to %d.\n", SHRT_MIN, SHRT_MAX);
	printf("The range of an unsigned short is from 0 to %u.\n", USHRT_MAX);
	printf("The range of a signed int is from %d to %d.\n", INT_MIN, INT_MAX);
	printf("The range of an unsigned int is from 0 to %u.\n", UINT_MAX);
	printf("The range of a signed long is from %ld to %ld.\n", LONG_MIN, LONG_MAX);
	printf("The range of an unsigned long is from 0 to %lu.\n", ULONG_MAX);

	return 0;
}
