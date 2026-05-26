#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXWORD 100
#define MAXBUF 100

struct ll_node {
	int line;
	struct ll_node *next;
};

struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *right;
	struct ll_node *lines;
};


struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *);
int getword(char *, int);
char getch(void);
void ungetch(char c);
bool is_noise_word(char *s);
struct ll_node *append_node(struct ll_node *head, int val);

int bufp = 0;
char buf[MAXBUF];

void remove_inline_comment(void);
void remove_block_comment(void);

int line_num;

int main(int argc, char *argv[]) {

	struct tnode *root;
	char word[MAXWORD];

	line_num = 1;

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]) && !is_noise_word(word)) {
			root = addtree(root, word);
		} else if (word[0] == '\n') {
			line_num++;
		}
	}
	treeprint(root);

	return 0;
}

int getword(char *word, int lim) {
	int c;
	char *w = word;

	// Skip whitespace
	while (isspace(c = getch()) && c != '\n') {
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

struct tnode *addtree(struct tnode *p, char *w) {
	
	int cond;
	if (p == NULL) {
		p = talloc(); // Make a new node
		p->word = strdup(w); // Alloc memory and copy w there
		p->left = NULL;
		p->right = NULL;
		p->lines = append_node(NULL, line_num);
	// Compare word with current node word. Only adds unique words
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->lines = append_node(p->lines, line_num);
	} else if ((cond = strcmp(w, p->word)) > 0) {
		p->right = addtree(p->right, w);
	} else {
		p->left = addtree(p->left, w);
	}
	return p;
}

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);

		struct ll_node *curr = p->lines;
		while (curr != NULL) {
			printf("%d ", curr->line);
			curr = curr->next;
		}
		printf("\t%s\n", p->word);

		treeprint(p->right);
	}
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}


bool is_noise_word(char *s) {
	
	char *noisy_words[] = {
		"a",
		"and",
		"from",
		"is",
		"of",
		"that",
		"the",
		"them",
		"they",
		"to"
	};
	int low = 0;
	int high = 9;
	int mid;
	int cond;
	while (low <= high) {

		mid = (low + high) / 2;

		if ((cond = strcmp(s, noisy_words[mid])) > 0) {
			low = mid + 1;
		} else if (cond < 0) {
			high = mid - 1;
		} else {
			return true;
		}
	}
	return false;
}

struct ll_node *append_node(struct ll_node *head, int val) {

	struct ll_node *new_node = malloc(sizeof(struct ll_node));
	if (new_node == NULL) {
		printf("error: couldn't allocate memory\n");
		exit(1);
	}
	new_node->line = val;
	new_node->next = NULL;
	
	if (head == NULL) {
		return new_node;
	}
	struct ll_node *curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_node;

	return head;
}
