/*
*	Write a program to print a histogram of the lengths of words in its input.
*	It is easy to draw the histogram with the bars horizontal; a vertical
*	orientation is more challenging.
*	
*	===============================================
*	========HORIZONTAL ORIENTATION SOLUTION========
*	===============================================
*
*/

#include <stdio.h>

#define MAX_LENGTH 10

int main(void) {
	
	// Will store frequencies of different word lengths.
	int wordLengths[MAX_LENGTH + 1] = { 0 };

	// Will store number of characters in the current word.
	int numCharacters = 0;

	// Will store number of words that are too long in length to store
	int numOverflow = 0;

	int c;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			// Check if length of word is within valid bounds
			if (numCharacters > 0 && numCharacters <= MAX_LENGTH) {
				++wordLengths[numCharacters];
			// Check if the word length is too long
			} else if (numCharacters > MAX_LENGTH) {
				++numOverflow;
			}
			numCharacters = 0;
		} else {
			++numCharacters;
		}
	}
	for (int i = 1; i < MAX_LENGTH; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < wordLengths[i]; ++j) {
			putchar('*');
		}
		putchar('\n');
	}
	putchar('\n');
	printf("Number of words overflow in length: %d\n", numOverflow);
}
