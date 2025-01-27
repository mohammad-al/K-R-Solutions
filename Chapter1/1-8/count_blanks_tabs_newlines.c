/*
*	Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

int main(void) {
	int nb = 0;
	int nt = 0;
	int nl = 0;

	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++nb;
		}
		if (c == '\t') {
			++nt;
		}
		if (c == '\n') {
			++nl;
		}
	}
	printf("Num of blanks: %d\nNum of tabs: %d\nNum of newlines: %d\n",
		nb, nt, nl
	);
}
