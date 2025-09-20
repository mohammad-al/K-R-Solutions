#include <stdio.h>

int my_getline(char *s, int lim);

int main(void) {

	char line[100];
	if (my_getline(line, 100)) {
		printf("%s\n", line);
	}

}

int my_getline(char *s, int lim) {

	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
		*(s + i) = c;
	}
	if (c == '\n') {
		*(s + i) = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
