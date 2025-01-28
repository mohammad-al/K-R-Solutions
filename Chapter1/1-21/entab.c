/*
*	Write a program entab that replaces strings of blanks by the minimum number
*	of tabs and blanks to achieve the same spacing. Use the same tab stops as
*	for detab. When either a tab or a single blank would suffice to reach a tab
*	stop, which should be given preference?
*/

#include <stdio.h>

#define TABSTOP 8

int main(void) {

	int numBlanks = 0;
	int numTabs = 0;

	int pos = 1;
	int c;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (pos % TABSTOP == 0) {
				numBlanks = 0;
				++numTabs;
			} else {
				++numBlanks;
			}
		} else if (c == '\n') {
			putchar(c);
			pos = 0;
		} else {
			// If character is a tab itself, then we no longer need spaces
			if (c == '\t') {
				numBlanks = 0;
			}
			// Place the tabs first
			for (int i = 0; i < numTabs; ++i) {
				putchar('\t');
			}
			// Then place the blanks
			for (int i = 0; i < numBlanks; ++i) {
				putchar(' ');
			}
			// Reset number of blanks and tabs and place character
			numBlanks = 0;
			numTabs = 0;
			putchar(c);
		}
		++pos;
	}
}
