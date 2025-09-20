/*
*	Write the function strrindex(s, t), which returns the position of the
*	rightmost occurrence of t in s, or -1 if there is none.
*/

#include <stdio.h>

#define MAXLINE 1000

int my_getline(char *s, int lim);
int strrindex(char *s, char *t);

int main(void) {

	int found = 0;
	char line[MAXLINE];
	char pattern[] = "ould";

	while (my_getline(line, MAXLINE)) {
		if (strrindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}

int my_getline(char *s, int lim) {
	
	int i, c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		*(s + i) = c;
	}
	if (c == '\n') {
		*(s + i) = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

int strrindex(char s[], char t[]) {

	int i, j, k;
	// Initialize rightmost to -1, such that if we never find a match,
	// we still return -1
	int rightmost = -1;
	for (i = 0; *(s + i) != '\0'; i++) {
		for (j = i, k = 0; *(t + k) != '\0' && *(s + j) == *(t + k); j++, k++) {
			;
		}
		// If we found a match, update the righmost value. We also check that
		// is larger than zero, such that empty strings are not incorrectly
		// matched
		if (k > 0 && *(t + k) == '\0') {
			rightmost = i;
		}
	}
	return rightmost;
}
