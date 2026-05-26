#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXWORD 100
#define MAXBUF 100

struct tnode {
	char *word;
 	// Store match boolean value. If part of matching group, set to true
	bool match;
	struct tnode *left;
	struct tnode *right;
};


struct tnode *addtree(struct tnode *, char *, int);
struct tnode *talloc(void);
void treeprint(struct tnode *);
int getword(char *, int);
char getch(void);
void ungetch(char c);
int custom_strcmp(struct tnode *node, char *s, int n);

int bufp = 0;
char buf[MAXBUF];

void remove_inline_comment(void);
void remove_block_comment(void);

// Bool to be used to set matched value. So that the leaf node can 'remember' if it hit a match as it went down
// the tree insertion route
bool found = false;

int main(int argc, char *argv[]) {

	struct tnode *root;
	char word[MAXWORD];

	int n = 6;
	if (argc == 2 && argv[1][0] == '-') {
		if (!isdigit(argv[1][1])) {
			printf("error: argument needs to be a number\n");
			return 1;
		}
		n = atoi(argv[1] + 1);
	}

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word, n);
		}
		found = false;
	}
	treeprint(root);

	return 0;
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

struct tnode *addtree(struct tnode *p, char *w, int n) {
	
	int cond;
	if (p == NULL) {
		p = talloc(); // Make a new node
		p->match = found;
		p->word = strdup(w); // Alloc memory and copy w there
		p->left = NULL;
		p->right = NULL;
	// Compare word with current node word
	} else if ((cond = custom_strcmp(p, w, n)) > 0) {
		p->right = addtree(p->right, w, n);
	} else if (cond < 0) {
		p->left = addtree(p->left, w, n);
	}
	return p;
}

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		if (p->match) {
			printf("\t%s\n", p->word);
		}
		treeprint(p->right);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

int custom_strcmp(struct tnode *node, char *s, int n) {

	char *t = node->word;
	int i = 0;
	for (; s[i] == t[i]; i++) {
		if (s[i] == '\0') {
			return 0;
		}
	}
	// Means got at least first n characters matching
	if (i >= n) {
		node->match = true;
		found = true;
	}
	return s[i] - t[i];
}
