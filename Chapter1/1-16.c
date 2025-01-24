/*
*	Revise the main routine of the longest-line program so it will correctly
*	print the length of arbitrarily long input lines, and as much as possible
*	of the text.
*/

#include <stdio.h>

#define MAXLINE 10 // maximum input line size

int myGetline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void) {
	
	int len; // current line length
	int max; // maximum length seen so far
	char line[MAXLINE]; // current input line
	char longest[MAXLINE]; // longest line saved here

	max = 0;
	while ((len = myGetline(line, MAXLINE)) > 0) {
		printf("Length: %d, Line: %s", len, line);
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) {
		printf("%s", longest);
	}
	return 0;
}

// myGetline: read a line into s, return length
int myGetline(char s[], int lim) {

	int c, i;
	int length = 0;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';
	++i, ++length) {
		s[i] = c;
	}
	// Means line is too long
	if (i >= lim - 1) {
		int j;
		// Keep incrementing length until reached end of line or EOF
		while ((j = getchar()) != EOF && j != '\n') {
			++length;
		}
	} else if (c == '\n') {
		s[i] = c;
		++i;
		++length;
	}
	s[i] = '\0';
	return length;
}

// copy: copy 'from' into 'to'; assume to is big enough
void copy(char to[], char from[]) {
	int i = 0;

	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}
