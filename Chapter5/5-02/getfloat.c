/*
*	Write getfloat, the floating-point analog of getint. What type does
*	getfloat return as its function value?
*/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getfloat(float *pn);
char getch(void);
void ungetch(char c);

char buf[BUFSIZE];
int bufp = 0;

int main(void) {

	float x;
	if (getfloat(&x) > 0) {
		printf("%f\n", x);
	}

}

int getfloat(float *pn) {

	int c, sign;

	// Skip whitespace
	while (isspace(c = getchar())) {
		;
	}
	// Means not a float
	if (!isdigit(c) && c != EOF && c != '-' && c != '+' && c != '.') {
		ungetch(c);
		return 0;
	}
	// Get this sign
	sign = (c == '-') ? -1 : 1;
	// Skip the sign if it is there
	if (c == '-' || c == '+') {
		c = getch();	
		// If there is a sign, next character should be digit
		if (!isdigit(c) && c != EOF) {
			ungetch(c);
			ungetch(sign == -1 ? '-' : '+');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = *pn * 10 + (c - '0');
	}
	if (c == '.') {
		c = getchar();
	}
	double power;
	for (power = 1; isdigit(c); c = getch()) {
		*pn = *pn * 10 + (c - '0');
		power *= 10;
	}

	*pn *= (sign / power);

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
