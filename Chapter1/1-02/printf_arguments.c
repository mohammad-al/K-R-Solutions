/*
*	Experiment to find out what happens when printf's arguments string contains
*	is some character not listed above.
*/

#include <stdio.h>

int main(void) {
	printf("hello, world\v");
}
