/*
*	Write a program to copy its input to its output, replacing each string of
*	one or more blanks by a single blank.
*/

#include <stdio.h>

#define YES 1
#define NO 0

int main(void) {

	int c;

	// If a space has just been sent to stdout, this will be set to YES,
	// otherwise will be set to no
	int placedSpace = NO;

	while((c = getchar()) != EOF) {
		// If the current char is space, and previous isn't, then can putchar
		if (c == ' ') {
			if (placedSpace == NO) {
				putchar(c);
				placedSpace = YES;
			}
		}
		if (c != ' ' ) {
			putchar(c);
			placedSpace = NO;
		}
	}
}
