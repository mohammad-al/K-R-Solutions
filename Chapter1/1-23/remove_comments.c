/*
*	Write a program to remove all comments from a C program. Don't forget to
*	handle quoted strings and character constants properly. C comments do not
*	nest.
*/

#include <stdio.h>

void remove_inline_comment(void);
void remove_block_comment(void);
void expand_double_quotes(void);
void expand_single_quotes(void);

int main(void) {

	int c;
	while ((c = getchar()) != EOF) {
		// Check for comment
		if (c == '/') {
			int d = getchar();
			if (d == '/') {
				remove_inline_comment();
			} else if (d == '*') {
				remove_block_comment();
			} else {
				putchar(c);
				putchar(d);
			}
		// Inside a string literal
		} else if (c == '"') { 
			putchar(c);
			expand_double_quotes();	
		} else if (c == '\'') {
			putchar(c);
			expand_single_quotes();
		} else {
			putchar(c);
		}
	}
}

void remove_inline_comment(void) {
	
	// Keep reading until we have reached the end of the line
	while (getchar() != '\n') {
		;
	}	
	putchar('\n');
}
void remove_block_comment(void) {

	int c = getchar();
	int d = getchar();

	// Keep reading characters until reached end of comment
	while (c != '*' || d != '/') {
		// This makes sure we go character by character and not two at a time
		c = d;
		d = getchar();
	}
}
void expand_double_quotes(void) {
	int c;
	while ((c = getchar()) != '"') {
		putchar(c);
		if (c == '\\') {
			putchar(getchar());
		}
	}
	putchar(c);
}

void expand_single_quotes(void) {
	
	int c;
	while ((c = getchar()) != '\'') {
		putchar(c);
		if (c == '\\') {
			putchar(getchar());
		}
	}
	putchar(c);
}

