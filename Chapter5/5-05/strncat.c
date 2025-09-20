#include <stdio.h>

void my_strncat(char *s, char *t, int n);

int main(void) {

	char s[20] = "hello ";
	char *t = "there mate";
	my_strncat(s, t, 5);
	printf("%s\n", s);

}

void my_strncat(char *s, char *t, int n) {

	int num_copied;

	while (*s) {
		s++;
	}

	for (num_copied = 0; num_copied < n && (*s++ = *t++); num_copied++) {
		;
	}
	while (num_copied < n) {
		*s++ = '\0';
		num_copied++;
	}

}
