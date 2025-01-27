/*
*	Write a program to print all input lines that are longer than 80 characters.
*/

#include <stdio.h>

#define MAXLINE 1000

int myGetline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void) {

	int len;
	char line[MAXLINE];

	while ((len = myGetline(line, MAXLINE)) > 0) {
		if (len > 80) {
			printf("%s", line);
		}
	}
	return 0;
}

int myGetline(char s[], int lim) {
	
	int i, c;

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
