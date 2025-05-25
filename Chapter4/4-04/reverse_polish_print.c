/*
	Add commands to print the op element of the stack without popping, to
	duplicate it, and to swap the top two elements. Add a command to clear
	the stack.
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

	double top_element;
	double second_top_element;

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
		case '%':
			op2 = pop();
			push(fmod(pop(), op2));
			break;
		// Prints the top element without popping it
		case 'p':
			top_element = pop();	
			printf("The top element is: %lf\n", top_element);
			push(top_element);
			break;
		// Swaps the top two elements on the stack
		case 's':
			top_element = pop();
			second_top_element = pop();
			push(top_element);
			push(second_top_element);
			break;
		// Duplicates the top element on the stack
		case 'd':
			top_element = pop();
			push(top_element);
			push(top_element);
			break;
		// Clears the stack
		case 'c':
			sp = 0;
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
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	// We could possibly have a negative number, or minus sign
	if (c == '-') {
		// If this is true, we have a minus sign. Just return '-'
		if (!isdigit(c = getch()) && c != '.') {
			if (c != EOF) {
				ungetch(c);
			}
			return '-';
		}
		// Ungetch the digit we just read
		if (c != EOF) {
			ungetch(c);
		}
	}

	if (!isdigit(c) && c != '.') {
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
		ungetch(c);
	}
	return NUMBER;
}
