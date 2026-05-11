/*
	Write the program expr, which evaluates a reverse Polish expression from the command line,
	where each operator or operand is a separate argument. For example, expr 2 3 4 + *
	evaluates 2 x (3 + 4)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Max size of operand or operator
#define MAXOP 100

// Signal that a number was found
#define NUMBER '0'

// Maximum depth of val stack
#define MAXVAL 100

// Next free stack position
int sp = 0;
// Value stack
double val[MAXVAL];

void push(double f);
double pop(void);
int get_type(char *s);


int main(int argc, char **argv) {

	int type;
	double op2;
	char s[MAXOP];

	while (--argc > 0) {
		type = get_type(*++argv);
		switch(type) {
		case NUMBER:
			push(atof(*argv));
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
		case '%':
			op2 = pop();
			push(fmod(pop(), op2));
			break;
		default:
			printf("error: unkown command %s\n", *argv);
			break;
		}
	}
	printf("\t%.8g\n", pop());
	return 0;
}

int get_type(char *s) {

	if (strlen(s) == 1) {
		if (isdigit(s[0])) {
			return NUMBER;
		} else {
			return s[0];
		}
	}

	for (int i = 0; s[i] != '\0'; i++) {

		// Means we have something that is not a number and not a single
		// operator
		if (!isdigit(s[i])) {
			return -1;
		}
	}
	return NUMBER;

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

