#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 100
#define NKEYS 32
#define MAXWORD 100

struct key {
	char *word;
	int count;
};

int binsearch(char *word, struct key tab[], int n);
int getword(char *word, int lim);
char getch(void);
void ungetch(char c);

int bufp = 0;
char buf[MAXBUF];

void remove_inline_comment(void);
void remove_block_comment(void);

struct key keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

int main(void) {

	int n;
	char word[MAXWORD];

	// Get word
	while (getword(word, MAXWORD) != EOF) {
		// If word starts with letter, check it
		if (isalpha(word[0])) {
			// Get index of word in keytab array if it exists
			if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
				keytab[n].count++;
			}
		}
	}

	for (n = 0; n < NKEYS; n++) {
		if (keytab[n].count > 0) {
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
		}
	}

	return 0;
}

int binsearch(char *word, struct key tab[], int n) {
	
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {

		mid = (low + high) / 2;

		cond = strcmp(word, tab[mid].word);

		if (cond < 0) {
			high = mid - 1;
		} else if (cond > 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return -1;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;

	// Skip whitespace
	while (isspace(c = getch())) {
		;
	}
	if (c != EOF) {
		*w++ = c;
	}
	// Means not a word. Word should start with alphanum, underscore, hash, single or double, or forward slash
	if (!isalpha(c) && c != '_' && c != '#' && c != '\'' && c != '"' && c != '/') {
		*w = '\0';
		return c;
	}

	// Means we have a word. A word can start with alphanum, underscore or #define
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++) {
			// valid characters for a word are now alpha numeric and an underscore
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
		}
	// Means we got an open single or double quote
	} else if (c == '\'' || c == '"') {
		for ( ; --lim > 0; w++) {
			// Means next character is a literal character. Handle seperately to avoid exiting early
			if ((*w = getch()) == '\\') {
				*++w = getch();
			// Check if we got enclosing single or double quote
			} else if (*w == c) {
				w++;
				break;
			} else if (*w == EOF) {
				break;
			}
		}
	} else if (c == '/') {
		int d = getch();
		if (d == '/') {
			remove_inline_comment();
		} else if (d == '*') {
			remove_block_comment();
		} else {
			ungetch(d);
		}
	}
	*w = '\0';
	return word[0];
}

char getch(void) {

	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(char c) {
	if (bufp >= MAXBUF) {
		printf("error: buffer is full\n");	
	} else {
		buf[bufp++] = c;
	}
}


void remove_inline_comment(void) {

	int c;
	
	// Keep reading until we have reached the end of the line or EOF
	while ((c = getch()) != '\n' && c != EOF) {
		;	
	}	
}
void remove_block_comment(void) {

	int c = getch();
	int d = getch();

	// Keep reading characters until reached end of comment
	while (c != '*' || d != '/') {
		// This makes sure we go character by character and not two at a time
		c = d;
		d = getch();
	}
}
