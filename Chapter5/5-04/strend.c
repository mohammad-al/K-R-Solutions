#include <stdio.h>

int strend(char *s, char *t);

int main(void) {

	char *s = "hello there mate";
	char *t = "mate";
	printf("%d\n", strend(s, t));

}

int strend(char *s, char *t) {

	char *original_s = s;
	char *original_t = t;


	// Move pointers to end of the strings
	for (; *s; s++) {
		;
	}
	for (; *t; t++) {
		;
	}

	for (; *s == *t && s >= original_s && t >= original_t; s--, t--) {
		;
	}
	// Only if we gone through all of t, then we have match
	if (t == original_t - 1) {
		return 1;
	} else {
		return 0;
	}
}
