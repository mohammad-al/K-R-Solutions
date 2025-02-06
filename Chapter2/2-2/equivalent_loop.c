/*
*	Write a loop equivalent to the for loop above without using && or ||.
*/

/*
	for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
*/

#include <stdio.h>

#define MAXLINE 1000

enum boolean {NO, YES};

int main(void) {
	
	char s[MAXLINE];

	int i = 0;
	int lim = MAXLINE;
	char c;
	enum boolean loop = YES;

	while (loop) {
		if (i >= lim - 1) {
			loop = NO;
		} else if ((c = getchar()) == '\n') {
			loop = NO;
		} else if (c == EOF) {
			loop = NO;
		} else {
			s[i] = c;
			++i;
		}
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	printf("%s", s);

	return 0;
}

