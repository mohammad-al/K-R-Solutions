/*
	Modify getop so that it doesn't need to use ungetch. Hint: use an internal
	static variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Max size of operand or operator
#define MAXOP 100

// Signal that a number was found
#define NUMBER '0'

// Maximum depth of val stack
#define MAXVAL 100

// Buffer size
#define BUFSIZE 100

// Next free stack position
int sp = 0;
// Value stack
double val[MAXVAL];
// Buffer for ungetch
char buf[BUFSIZE];
int bufp = 0;

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);

int main(void) {

	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0) {
				push(pop() / op2);
			} else {
				printf("error: zero divisor\n");
			}
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unkown command %s\n", s);
			break;
		}
	}

	return 0;
}

void push(double f) {
	if (sp <  MAXVAL) {
		val[sp++] = f;
	} else {
		printf("error: stack full, can't push %g\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	} else {
		buf[bufp++] = c;
	}
}

int getop(char s[]) {

	static int pushed_back_char = -1;

	// If there is a pushed back char, get it
	if (pushed_back_char != -1) {
		c = pushed_back_char;
		pushed_back_char = -1;

	// Means no pushed back char. Just use getch()
	} else {
		c = getch();
	}

	
	int i, c;
	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-') {
		return c;
	}
	i = 0;
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch()))
			;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()))
			;
	}
	s[i] = '\0';
	if (c != EOF) {
		pushed_back_char = c;
	}
	
	return NUMBER;
}
