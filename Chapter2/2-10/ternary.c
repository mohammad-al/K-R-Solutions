/*
*	Rewrite the function lower, which converts upper case letters to lower
*	case, witha conditional expression instead of if-else.
*/

#include <stdio.h>

char lower(char c);

int main(void) {

	// Should print ab
	printf("%c%c\n", lower('a'), lower('B'));

	return 0;
}

char lower(char c) {

	return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;

}
