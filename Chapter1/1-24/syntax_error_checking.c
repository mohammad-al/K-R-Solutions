/*
*	Write a program to checka C program for rudimentary syntax errors like
*	unbalanced parentheses, brackets and braces. Don't forget about quotes,
*	both single and double, escape sequences, and comments. (This program
*	is hard if you do it in full generality.)
*/

#include <stdio.h>

#define STACK_SIZE 100

void skip_inline_comment(void);
void skip_block_comment(void);
void skip_string(void);
void skip_character_constant(void);

char stack[STACK_SIZE];
int stackPos = 0;

void push(char c);
char pop(void);

int main(void) {

	int c;

	while ((c = getchar()) != EOF) {

		if (c == '/') {
			int d = getchar();
			if (d == '/') {
				skip_inline_comment();
			} else if (d == '*') {
				skip_block_comment();
			}
		} else if (c == '"') {
			skip_string();
		} else if (c == '\'') {
			skip_character_constant();
		// Push any opening brace, bracket or parantheses
		} else if (c == '(' || c == '{' || c == '[') {
			push(c);
		// If encounter unbalanced brace, bracket or parantheses, print error
		// message and terminate program
		} else if (c == ')' || c == '}' || c == ']') {
			int temp = pop();
			if (c == ')' && temp != '(') {
				printf("Unbalanced parentheses!\n");
				return 1;
			} else if (c == '}' && temp != '{') {
				printf("Unbalanced braces!\n");
				return 1;
			} else if (c == ']' && temp != '[') {
				printf("Unbalanced brackets!\n");
				return 1;
			}
		}
	}
	if (stackPos == 0) {
		printf("No errors!");
	// If stack is still empty, then there must be atleast one missing closing
	// brace, bracket or parantheses
	} else {
		c = pop();
		if (c == '{') {
			printf("Missing closing brace!\n");
		} else if (c == '(') {
			printf("Missing closing parentheses!\n");
		} else if (c == '[') {
			printf("Missing closing bracket!\n");
		}
		return 1;
	}
}

void push(char c) {
	if (stackPos < STACK_SIZE) {
		stack[stackPos] = c;
		++stackPos;
	} else {
		printf("Error: Not enough memory\n");
	}
}
char pop(void) {
	if (stackPos > 0) {
		--stackPos;
		return stack[stackPos];
	} else {
		return 0;
	}
}

void skip_inline_comment(void) {
	int c;
	while ((c = getchar()) != EOF && c != '\n') {
		putchar(c);
	}
}
void skip_block_comment(void) {

	int c = getchar();
	int d = getchar();
	
	while (c != '*' || d != '/') {
		c = d;
		d = getchar();
	}
}

void skip_string(void) {
	int c;
	while ((c = getchar()) != '"') {
		if (c == '\\') {
			getchar();
		}
	}
}
void skip_character_constant(void) {
	int c;
	while ((c = getchar()) != '\'') {
		if (c == '\\') {
			getchar();
		}
	}
}
