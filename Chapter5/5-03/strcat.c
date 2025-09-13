#include <stdio.h>

void my_strcat(char *s, char *t);

int main(void) {

	char s[15] = "hello";
	my_strcat(s, " world");
	printf("%s\n", s);
}

void my_strcat(char *s, char *t) {

	// Get pointer s to go to end of string
	for (; *s; s++) {
		;
	}
	// Add t to end of s
	for (; *s = *t; s++, t++) {
		;
	}
}
