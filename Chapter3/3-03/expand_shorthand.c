/*
*	Write a function expand(s1, s2) that expands shorthand notation like a-z in
*	the string s1 into the equivalent complete list abc...xyz in s2. Allow for
*	letters of either case and digits, and be prepared to handle cases like
*	a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
*	literally.
*/

#include <stdio.h>

void expand(char s1[], char s2[]);

int main(void) {

	char first_string[] = "hello there, the alphabet is a-z\n";
	char second_string[30];

	expand(first_string, second_string);

	printf("%s", second_string);

	return 0;
}

void expand(char s1[], char s2[]) {

	// i will be the index into s1, and j will be the index into s2
	int i, j, c;
	i = j = 0;

	while ((c = s1[i]) != '\0') {
	
		// Check if we have the correct conditions to expand characters
		if (s1[i + 1] == '-' && s1[i + 2] > c) {
			// Go to the character after the dash '-'
			i += 2;
			while (c <= s1[i]) {
				s2[j++] = c++;
			}
			++i;
		} else {
			s2[j++] = s1[i++];
		}
	}
	s2[j] = '\0';
}
