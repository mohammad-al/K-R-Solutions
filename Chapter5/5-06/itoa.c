#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int n, char *s);
void reverse(char *s);

int main(void) {

	char num[5];
	itoa(-341, num);

	// Should print -341 as a string
	printf("%s\n", num);

	return 0;
}

void itoa(int n, char *s) {
	
	int i, sign;

	if (n < 0) {
		sign = -1;
	} else {
		sign = 1;
	}
	i = 0;
	do {
		*(s + i) = abs(n % 10) + '0';
		i++;
	} while (n /= 10);
	if (sign == -1) {
		*(s + i) = '-';
		i++;
	}
	*(s + i) = '\0';
	reverse(s);
}

void reverse(char *s) {

	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {

		c = *(s + i);
		*(s + i) = *(s + j);
		*(s + j) = c;
	}
}
