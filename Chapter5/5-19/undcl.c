#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXTOKEN 100
#define MAXOUT 1000
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

// Output string
char out[MAXOUT];

int getch();
void ungetch(int c);


int main(void) {

	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {
			if (type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if (type == '*') {
				sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);
			}
		}
		printf("%s\n", out);
	}
	
	return 0;
}

int gettoken(void) {
	
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
