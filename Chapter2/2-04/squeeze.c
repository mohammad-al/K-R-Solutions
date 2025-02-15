/*
*	Write an alternate version of squeeze(s1, s2) that deletes each character
*	in s1 that matches any character in the string s2.
*/

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void) {

	char first_string[] = "hello there";
	char second_string[] = "hey";

	squeeze(first_string, second_string);

	// Should print out "llo tr".
	printf("%s\n", first_string);

}

void squeeze(char s1[], char s2[]) {
	
	int k;
	for (int i = 0; s2[i] != '\0'; i++) {
		k = 0;
		for (int j = 0; s1[j] != '\0'; j++) {
			if (s2[i] != s1[j]) {
				s1[k++] = s1[j];
			}
		}
		s1[k] = '\0';
	}
}
