#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXTOKEN 100
#define BUFSIZE 100

// Anonymous enum. Just defines NAME 0, PARENS 1, and BRACKETS 2. These are token types
enum { NAME, PARENS, BRACKETS };

int tokentype;

char buf[BUFSIZE];
int bufp = 0;

void dcl(void);
void dirdcl(void);

int gettoken(void);

// Current token string that was just parsed/read
char token[MAXTOKEN];

// Name of the identifier
char name[MAXTOKEN];

// Data type of the decleration
char datatype[MAXTOKEN];

// Output string
char out[1000];

int getch();
void ungetch(int c);

void parse_arguments(void);

int read_prev_token = 0;

int valid_specifier_or_type(void);

int main(void) {
	while (gettoken() != EOF) {

		// First token we read is the datatype
		strcpy(datatype, token);

		// Initialize out to be empty string
		out[0] = '\0';

		dcl();

		if (tokentype != '\n') {
			printf("syntax error\n");

			// Skip the line and go to next statement
			while (tokentype != '\n') {
				gettoken();
			}
		} else {
			printf("%s: %s %s\n", name, out, datatype);
		}
	}
	return 0;
}

void dcl(void) {
	
	int ns;

	for (ns = 0; gettoken() == '*'; ) {
		ns++;
	}
	dirdcl();
	while (ns-- > 0) {
		strcat(out, " pointer to");
	}
}

void dirdcl(void) {
	
	int type;

	// A direct dcl starts with either a name, or a paranthesized dcl
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
		}
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		read_prev_token = 1;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
		if (type == PARENS) {
			strcat(out, " function returning");
		} else if (type == '(') {
			strcat(out, " function expecting arguments");
			parse_arguments();
			strcat(out, " returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}

int gettoken(void) {
	if (read_prev_token) {
		read_prev_token = 0;
		return tokentype;
	}
	
	int c;
	char *p = token;

	// Skip whitespace
	while ((c = getch()) == ' ' || c == '\t') {
		;
	}
	if (c == '(') {
		// Means we read parantheses. Basically, a function
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			// Ungetch the character after the '(' character
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		// Note, the below loop is equivalent to the book's one, however, in my opinion the below appraoch is more readable
		
		// Store [ in token
		*p++ = c;
		while ((*p++ = getch()) != ']') {
			;
		}
		*p = '\0';
		return tokentype = BRACKETS;

	// Means we need to read a name
	} else if (isalpha(c)) {

		// Again, different from book approach, but in my opinion this is more readable

		// Copy first character into token
		*p++ = c;
		while (isalnum(c = getch())) {
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else {
		return tokentype = c;
	}
}
void parse_arguments(void) {

	gettoken();
	// Outer while loop goes through every argument
	while (tokentype != ')') {

		char temp[MAXTOKEN];
		temp[0] = '\0';

		// Inner while loop goes through every word in the argument
		while (tokentype != ')' && tokentype != ',') {

			if (tokentype != NAME) {
				read_prev_token = 1;
				dcl();
			} else if (valid_specifier_or_type()) {
				strcat(temp, " ");
				strcat(temp, token);
				gettoken();
			} else {
				printf("error: unkown type in argument list\n");
				exit(1);
			}
		}

		strcat(out, temp);
		if (tokentype == ',') {
			strcat(out, ",");
			gettoken();
		}
	}
}

int valid_specifier_or_type(void) {

	if (strcmp(token, "char") == 0 || 
		strcmp(token, "int") == 0 || 
		strcmp(token, "void") == 0) {
		
		return 1;
	}
	if (strcmp(token, "volatile") == 0 || 
		strcmp(token, "const") == 0) {
		return 1;
	}
	return 0;

}

int getch() {

	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {

	if (bufp >= BUFSIZE) {
		printf("error: too many characters on buffer\n");
	} else {
		buf[bufp++] = c;
	}
}

/*
	dcl: optional pointers direct-dcl

	direct-dcl:
		name - Like a function or variable name
		(dcl) - A dcl wrapped in brackets is a direct-dcl
		direct-dcl() - A function
		direct-dcl[] - An array

	A dcl is preceeded by a type such as char, int, void, etc

	Pseudo-code
	
	main function
	while there are declerations
		
		get datatype

		parse declerator using dcl

		if valid:
			print:
				name + description + datatype



	dcl function
	count number of * (pointers)
	parse direct decleartor using dirdcl()

	for each *
		add "pointer to" to output

	direct-dcl function

	We notice that a direct-dcl starts with either a name or an open bracket
	if token is '('
		parse inner dcl
		if token is not ')'
			error
	
	else if token is NAME
		store variable name
	
	else
		error: expected name of (dcl)
	
	while next token is:
		PARENS or BRACKETS:

		if PARENS:
			append "function returning"

		if BRACKETS:
			append "array ... of"
*/
