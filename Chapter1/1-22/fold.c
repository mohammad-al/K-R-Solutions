/*
*	Write a program to "fold" long input lines into two or more shorter lines
*	after the last non-blank character that occurs before the n-th column of
*	input. Make sure your program does something intelligent with very long
*	lines, and if there are no blanks or tabs before the specified column.
*/

#include <stdio.h>

#define MAXCOL 25
#define TABSTOP 8

void printLine(char line[], int pos);
int findLastBlank(char line[], int pos);
int rearrange(char line[], int pos);

int main(void) {

	char line[MAXCOL];

	// Position will start at 0 so indexing is simple
	int pos = 0;
	int c;

	while ((c = getchar()) != EOF) {
		// Just put the character in the line array/string
		if (pos < MAXCOL && c != '\n' && c != '\t') {
			line[pos] = c;
			++pos;
		} else if (c == '\t') {
			int numBlanks = TABSTOP - (pos % TABSTOP);
			for (int i = 0; i < numBlanks && pos < MAXCOL; ++i, ++pos) {
				line[pos] = ' ';
			}
			// Not enough space to expand tab
			if (pos >= MAXCOL) {
				printLine(line, MAXCOL);
				pos = 0;
			}
		} else if (c == '\n') {
			// Only print line if there are other characters in the line
			if (pos != 0) {
				printLine(line, pos);
			}
			pos = 0;
		} else {
			pos = findLastBlank(line, pos);
			printLine(line, pos);
			pos = rearrange(line, pos + 1);
			line[pos] = c;
			++pos;
		}
	}
}
void printLine(char line[], int pos) {
	for (int i = 0; i < pos; ++i) {
		putchar(line[i]);
	}
	putchar('\n');
}
int findLastBlank(char line[], int pos) {
	while (pos >= 0 && line[pos] != ' ') {
		--pos;
	}
	// Means never found a blank
	if (pos < 0) {
		return MAXCOL;
	}
	return pos;
}
int rearrange(char line[], int pos) {
	if (pos >= MAXCOL) {
		return 0;
	}
	int j = pos;
	int i;
	for (i = 0; j < MAXCOL; ++i, ++j) {
		line[i] = line[j];
	}
	return i;
}

// 012345678
// hello     
