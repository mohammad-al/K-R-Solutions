/*
*	Write a function escape(s, t) that converts characters like newline and
*	tab into visible escape sequences like \n and \t as it copies the string
*	t to s. Use a switch. Write a function for the other direction as well,
*	converting escape sequences into the real characters.
*/

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void) {

	// Tab in between "hello" and "there"
	char first_string[] = "hello	there\n";
	char second_string[14];

	escape(second_string, first_string);

	// Should print "hello\tthere\n"
	printf("%s\n", second_string);

	unescape(second_string, first_string);

	// Should print "hello	there" with a newline at the end, and a tab in
	// between "hello" and "there"
	printf("%s\n", second_string);

	return 0;
}

// escape: copies the string t to s, converting characters to visible escape
// sequences
void escape(char s[], char t[]) {

	// i will be used to index into t, and j will be used to index into s	
	int i, j;

	j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		
		switch (t[i]) {
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		default:
			s[j++] = t[i];
		}
	}
	s[j] = '\0';
}	
// escape: copies the string t to s, converting visible escape sequences to
// their literal characters
void unescape(char s[], char t[]) {

	// i will be used to index into t, and j will be used to index into s	
	int i, j;

	j = 0;
	for (i = 0; t[i] != '\0'; i++) {

		// We may have an escape sequence if this is true
		if (t[i] == '\\') {

			// Increment i to check the character after the backslash
			i++;

			switch (t[i]) {
			case 't':
				s[j++] = '\t';
				break;
			case 'n':
				s[j++] = '\n';
				break;
			default:
				s[j++] = '\\';
				s[j++] = t[i];
			}
		} else {
			s[j++] = t[i];
		}
	}
	s[j] = '\0';
}	
