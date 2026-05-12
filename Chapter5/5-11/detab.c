#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABSTOP 8

enum boolean {NO, YES};
// tab[0] is dummy value. It has no useful meaning in the program
int tab[MAXLINE + 1];

void populate_tab(int arg_count, char **arguments);

int main(int argc, char **argv) {

	populate_tab(argc, argv);

	int pos = 1;
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			while (pos < MAXLINE && tab[pos++] != YES) {
				putchar(' ');
			}
			putchar(' ');
			
		} else if (c == '\n') {
			pos = 1;
			putchar('\n');
		} else {
			putchar(c);
			pos++;
		}
	}

	return 0;
}

void populate_tab(int arg_count, char **arguments) {

	for (int i = 0; i <= MAXLINE; i++) {
		tab[i] = NO;
	}
	if (arg_count > 1) {
		int pos;
		while (--arg_count) {
			pos = atoi(*++arguments);
			if (pos > 0 && pos <= MAXLINE) {
				tab[pos] = YES;
			}
		}
	} else {
		for (int i = 1; i <= MAXLINE; i++) {
			if (i % TABSTOP == 0) {
				tab[i] = YES;
			}
		}
	}
}
