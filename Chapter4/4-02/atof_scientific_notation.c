/*
*	Extend atof to handle scientific notation of the form 123.45e-6 where a
*	floating-point number may be followed by e or E and an optionally signed
*	exponent.
*/

#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main(void) {

	char num[] = "123.45e-6";
	// Should print out 0.00012345
	printf("%g\n", atof(num));

	return 0;
}

double atof(char s[]) {

	int i, sign;

	// Skip white space
	for (i = 0; isspace(s[i]); i++) {
		;
	}
	sign = (s[i] == '-') ? -1 : 1;
	// Skip the sign if it is there
	if (s[i] == '-' || s[i] == '+') {
		i++;
	}

	double val;

	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
	}
	// Skip the decimal point if it is there
	if (s[i] == '.') {
		i++;
	}
	double power;
	// Handle the fractional component
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power *= 10;
	}
	val = sign * val / power;

	// Check if the number is given in scientific notation. If so, handle
	// accordingly
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		int exponent_sign;
		exponent_sign = (s[i] == '-') ? -1 : 1;
		// Skip the sign if it is there
		if (s[i] == '-' || s[i] == '+') {
			i++;
		}
		int j, exponent;
		j = 0;
		exponent = s[i] - '0';
		if (exponent_sign == -1) {
			while (j < exponent) {
				val /= 10;
				j++;
			}
		} else {
			while (j < exponent) {
				val *= 10;
				j++;
			}
		}

	}
	return val;
}
