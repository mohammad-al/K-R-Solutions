#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void do_reverse(char s[], int i, int j);

int main(void) {

	char s[] = "hello, world";
	printf("%s\n", s);
	reverse(s);
	printf("%s\n", s);
}

void reverse(char s[]) {
	int i = 0;
	int j = strlen(s) - 1;
	do_reverse(s, i, j);
}
void do_reverse(char s[], int i, int j) {

	if (i < j) {
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		do_reverse(s, ++i, --j);
	}
}
