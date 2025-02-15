/*
*	Write the function htoi(s), which converts a string of hexadecimal digits
*	(including an optional 0x or 0X) into its equivalent integer value. The
*	allowable digits are 0 through 9, a through f, and A through F.
*/

#include <stdio.h>
#include <ctype.h>

enum boolean {NO, YES};

int htoi(char s[]);

int main(void) {

	printf("The integer value of 0xfa is %d\n", htoi("0xfa"));

	return 0;
}

int htoi(char s[]) {

	int i = 0;

	// Skip the 0x or 0X if it is there 
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
		i = i + 2;
	}

	int n = 0;

	enum boolean inside_hex = YES;

	while (inside_hex) {
		int hex_digit;
		if (isdigit(s[i])) {
			hex_digit = s[i] - '9';
			n = 16 * n + hex_digit;
		} else if (s[i] >= 'a' && s[i] <= 'f') {
			hex_digit = s[i] - 'a' + 10;
			n = 16 * n + hex_digit;
		} else if (s[i] >= 'A' && s[i] <= 'F') {
			hex_digit = s[i] - 'A' + 10;
			n = 16 * n + hex_digit;
		} else {
			inside_hex = NO;
		}
		++i;
	}
	return n;
}
