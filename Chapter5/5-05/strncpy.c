#include <stdio.h>

void my_strncpy(char *s, char *t, int n);

int main(void) {

	char s[20] = "";
	char *t = "world and people";
	my_strncpy(s, t, 7);
	printf("%s\n", s);

}

// Copies at most the first n characters of t into s. If space left in s, then
// it is filled with \0 i.e. nul terminator
void my_strncpy(char *s, char *t, int n) {

	int num_copied;

	// Copy characters from t to s. If encounter nul in t or copied more than
	// n characters, stop copying
	for (num_copied = 0; num_copied < n && (*s++ = *t++); num_copied++) {
		;
	}

	// If still more characters we can operate on, padd with nul
	while (num_copied < n) {
		*s++ = '\0';
		num_copied++;
	}
}
