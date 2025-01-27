/*
*	Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>

int main(void) {
	int c;
	// Print value when not EOF
	while (c = getchar() != EOF) {
		printf("%d\n", c);
	}
	// Print value at EOF
	printf("%d\n", c);
}
