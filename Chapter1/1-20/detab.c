/*
*	Write a program detab that replaces tabs in the input with the proper number
*	of blanks to space to the next tab stop. Assume a fixed set of tab stops,
*	say every n columns. Should n be a variable or a symbolic parameter?
*/

#include <stdio.h>

#define TABSTOP 8

int detab(int pos);

int main(void) {
	
	int c;
	// Will keep track of the current row character is on
	int pos = 1;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			pos = detab(pos);
		} else if (c == '\n') {
			putchar(c);
			pos = 0;
		} else {
			putchar(c);
		}
		++pos;
	}
}

// Puts spaces until next tabstop and returns new position
int detab(int pos) {

	// Calculate number of blanks to replace tab with
	int numberBlanks = TABSTOP - ((pos - 1) % TABSTOP);
	for (int i = 0; i < numberBlanks; ++i) {
		putchar(' ');
	}
	// Return new position offset by negative one
	// since main loop will increment position
	return pos + numberBlanks - 1;
}
