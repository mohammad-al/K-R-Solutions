/*
*	Write a program to remove trailing blanks and tabs from each line of
*	input, and to delete entirely blank lines.
*/

#include <stdio.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);
void copy(char to[], char from[]);
int removeTrailing(char line[]);

int main(void) {
	
	int len;
	char line[MAXLINE];

	while ((len = myGetline(line, MAXLINE)) > 0) {
		if (removeTrailing(line) > 0) {
			printf("%s", line);
		}
	}
}

int myGetline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy(char to[], char from[]) {
	int i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}

// Removes trainling blanks for line and returns new line length
int removeTrailing(char s[]) {
	
	int i = 0;
	while (s[i] != '\n' && s[i] != '\0') {
		++i;
	}
	// Means that no newline character encountered. So, no trailing blanks.
	if (s[i] == '\0') {
		return i;
	}
	// Step back and keep stepping back while on blank or tab
	--i;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
		--i;
	}
	// Means must have encountered non-blank character
	if (i >= 0) {
		++i;
		s[i] = '\n';
		++i;
		s[i] = '\0';
	}
	return i;
}
