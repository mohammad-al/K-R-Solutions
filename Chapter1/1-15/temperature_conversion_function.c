/*
*	Rewrite the temperature conversion program of Section 1.2 to use a
*	function for conversion.
*/

#include <stdio.h>

float fahrToCelsius(float fahr);

int main(void) {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	
	while (fahr <= upper) {
		printf("%3.0f %6.1f\n", fahr, fahrToCelsius(fahr));
		fahr = fahr + step;
	}
}

float fahrToCelsius(float fahr) {
	return (5.0 / 9.0) * (fahr - 32);
}
