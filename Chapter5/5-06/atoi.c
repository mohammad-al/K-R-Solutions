#include <stdio.h>
#include <ctype.h>

int atoi(char *s);

int main(void) {

	int x = atoi("543");
	printf("%d\n", x);

}

int atoi(char *s) {

	int n, i, sign;

	// Skip whitespace
	while (isspace(*s)) {
		s++;
	}
	sign = (*s == '-' ? -1 : 1);
	// Skip sign if it is there
	if (*s == '-' || *s == '+') {
		s++;
	}
	for (n = 0; isdigit(*s); s++) {
		n = 10 * n + *s - '0';
	}
	return n * sign;
}
