/*
*	Write a function reverse(s) that reverses the character string s. Use it
*	to write a program that reverses its input a line at a time.
*/

#include <stdio.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char line[]);

int main(void) {
	
	int len;
	char line[MAXLINE];

	while ((len = myGetline(line, MAXLINE)) > 0) {
		reverse(line);
		printf("%s", line);
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

void reverse(char s[]) {
	// Will by index into the last character to be reversed
	int i = 0;

	// Go to the very end of the line
	while (s[i] != '\0') {
		++i;
	}
	--i;
	// Back off again since we don't need to move newline character
	if (s[i] == '\n') {
		--i;
	}
	int j = 0;
	// Perform swaps
	while (j < i) {
		char temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		--i;
		++j;
	}
}
