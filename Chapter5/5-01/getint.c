#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getint(int *pn);
char getch(void);
void ungetch(char c);

char buf[BUFSIZE];
int bufp = 0;

int main(void) {

	int x;
	if (getint(&x) > 0) {
		printf("%d\n", x);
	}

}

int getint(int *pn) {

	int c, sign;

	// Skip whitespace
	while (isspace(c = getchar())) {
		;
	}
	// Means not an integer.
	if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
		ungetch(c);
		return 0;
	}
	// Get this sign
	sign = (c == '-') ? -1 : 1;
	// Skip the sign if it is there
	if (c == '-' || c == '+') {
		c = getch();	
	}
	// Next character should be digit.
	if (!isdigit(c) && c != EOF) {
		ungetch(c);
		// Ungetch the sign
		ungetch(sign == -1 ? '-' : '+');
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = *pn * 10 + (c - '0');
	}
	*pn *= sign;
	if (c != EOF) {
		ungetch(c);
	}
	// Returns the character after the last digit
	return c;
}
char getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}
void ungetch(char c) {
	if (bufp < BUFSIZE) {
		buf[bufp++] = c;	
	} else {
		printf("error: buffer is full\n");
	}
}
