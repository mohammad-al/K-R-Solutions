#include <stdio.h>

int my_getline(char *s, int lim);

int main(void) {

	char line[100];
	if (my_getline(line, 100)) {
		printf("%s\n", line);
	}

}

int my_getline(char *s, int lim) {

	char *original_s = s;
	int c;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = '\n';
	}
	*s = '\0';

	return s - original_s;
}
