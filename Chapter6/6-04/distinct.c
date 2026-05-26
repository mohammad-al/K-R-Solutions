#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXWORD 100
#define MAXBUF 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct word_and_count {
	char *word;
	int count;
};


struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
int getword(char *, int);
char getch(void);
void ungetch(char c);
int num_nodes_in_tree(struct tnode *root);

int bufp = 0;
char buf[MAXBUF];

void remove_inline_comment(void);
void remove_block_comment(void);

void tree_to_array(struct tnode *root, struct word_and_count *);

int compare_fn(const void *, const void *);

int main(int argc, char *argv[]) {

	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word);
		}
	}
	int size_of_tree = num_nodes_in_tree(root);
	struct word_and_count *words_array = malloc(size_of_tree * sizeof(struct word_and_count));
	if (words_array == NULL) {
		printf("error: couldn't allocate memory\n");
		exit(1);
	}
 	tree_to_array(root, words_array);
	qsort(words_array, size_of_tree, sizeof(struct word_and_count), compare_fn);

	for (int i = 0; i < size_of_tree; i++) {
		printf("%d\t%s\n", words_array[i].count, words_array[i].word);
	}

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

struct tnode *addtree(struct tnode *p, char *w) {
	
	int cond;
	if (p == NULL) {
		p = talloc(); // Make a new node
		p->word = strdup(w); // Alloc memory and copy w there
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
	} else if ((cond = strcmp(w, p->word)) > 0) {
		p->right = addtree(p->right, w);
	} else {
		p->left = addtree(p->left, w);
	}
	return p;
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

int num_nodes_in_tree(struct tnode *root) {
	if (root == NULL) {
		return 0;
	} else {
		return 1 + num_nodes_in_tree(root->left) + num_nodes_in_tree(root->right);
	}
}

void tree_to_array(struct tnode *root, struct word_and_count *array) {

	static int index = 0;

	if (root == NULL) {
		return;
	}
	tree_to_array(root->left, array);
	struct word_and_count element = {root->word, root->count};
	array[index++] = element;
	tree_to_array(root->right, array);

}

int compare_fn(const void *a, const void *b) {
	
	struct word_and_count *a_arg = (struct word_and_count *)a;
	struct word_and_count *b_arg = (struct word_and_count *)b;

	return  b_arg->count - a_arg->count; 

}
