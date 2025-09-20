#include <stdio.h>

int my_strncmp(char *s, char *t, int n);

int main(void) {
	
	char *s = "hello mate";
	char *t = "hello there";
	printf("%d\n", my_strncmp(s, t, 7));
	printf("%d\n", my_strncmp(s, t, 5));

}

int my_strncmp(char *s, char *t, int n) {

	int num_compared;

	for (num_compared = 0; num_compared < n && (*s == *t); num_compared++, s++, t++) {
		if (*s == '\0') {
			return 0;
		}
	}
	return *s - *t;

}
