/*
	Suppose that there will never be more than one character of pushback.
	Modify getch and ungetch accordingly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Max size of operand or operator
#define MAXOP 100

// Signal that a number was found
#define NUMBER '0'

// Signal that a mathematical function was found
#define MATH_FUNCTION '1'

// Signal that a variable was found
#define VARIABLE '2'

// Maximum depth of val stack
#define MAXVAL 100

// Buffer size
#define BUFSIZE 100

// Next free stack position
int sp = 0;
// Value stack
double val[MAXVAL];

// An array of 26 variables. Default value of each variable is zero.
double variables[26] = { 0 };

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);
void run_math_function(char s[]);
void ungets(char s[]);

int pushed_back_char = -1;


int main(void) {

	int type;
	double op2;
	char s[MAXOP];

	double top_element;
	double second_top_element;
	char var;
	double most_recently_printed;

	while ((type = getop(s)) != EOF) {
		switch(type) {
		case NUMBER:
			push(atof(s));
			break;
		case MATH_FUNCTION:
			run_math_function(s);
			break;
		case VARIABLE:
			// Push the variable onto the stack
			var = s[0];
			push(variables[var - 'A']);
			break;
		case '=':
			// Get the desired variable value
			op2 = pop();
			// Get the variable off the stack
			pop();
			if (isupper(var)) {
				variables[var - 'A'] = op2;
			} else {
				printf("error: invalid variable name %s\n", s);
			}
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
			most_recently_printed = pop();
			printf("\t%.8g\n", most_recently_printed);
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
			most_recently_printed = top_element;
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
	// If this is true, then there is a pushed back character
	int res;
	if (pushed_back_char != -1) {
		res = pushed_back_char;
		pushed_back_char = -1;
		return res;
	} else {
		return getchar();
	}
}
void ungetch(int c) {
	if (pushed_back_char != -1) {
		printf("ungetch: too many characters\n");
	}

	pushed_back_char = c;
}

int getop(char s[]) {
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	// We could possibly have a library function such as sin
	if (isalpha(c)) {
		int i = 0;		
		while (isalpha(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != EOF) {
			ungetch(c);
		}
		// If the string is not atleast 1 character long, then we can't have
		// a mathematical function
		if (strlen(s) > 1) {
			return MATH_FUNCTION;
		// If only one character long, and is upper case, then it is a variable
		} else if (strlen(s) == 1) {
			return VARIABLE;
		} else {
			return c;	
		}
	}

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

void run_math_function(char s[]) {
	if (strcmp(s, "sin") == 0) {
		push(sin(pop()));
	} else if (strcmp(s, "cos") == 0) {
		push(cos(pop()));
	} else if (strcmp(s, "tan") == 0) {
		push(tan(pop()));
	} else if (strcmp(s, "pow") == 0) {
		double power = pop();
		push(pow(pop(), power));
	}
}
