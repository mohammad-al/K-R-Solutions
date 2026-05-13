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
	int num_tabs = 0;
	int num_spaces = 0;
	int c;
	while ((c = getchar()) != EOF) {
		

		if (c == ' ') {
			if (tab[pos] == YES) {
				num_tabs++;
				num_spaces = 0;
			} else {
				num_spaces++;
			}
			
		} else {
			for (int i = 0; i < num_tabs; i++) {
				putchar('\t');
			}
			if (c == '\t') {
				num_spaces = 0;
			} else {
				for (int i = 0; i < num_spaces; i++) {
					putchar(' ');
				}
			}

			putchar(c);
			if (c == '\n') {
				pos = 0;
			} else if (c == '\t') {
				while (tab[pos] != YES) {
					pos++;
				}
			}
			num_tabs = 0;
			num_spaces = 0;

		}
		pos++;
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
