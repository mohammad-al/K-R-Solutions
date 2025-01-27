/*
*	Write a program to print a histogram of the lengths of words in its input.
*	It is easy to draw the histogram with the bars horizontal; a vertical
*	orientation is more challenging.
*	
*	===============================================
*	=========VERTICAL ORIENTATION SOLUTION=========
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
	// Find the word length that occurs most often
	int max = 0;
	for (int i = 0; i <= MAX_LENGTH; ++i) {
		if (wordLengths[i] > max) {
			max = wordLengths[i];
		}
	}
	printf("\n\n");
	for (int row = max; row > 0; --row) {
		printf("%d | ", row);
		for (int col = 1; col <= MAX_LENGTH; ++col) {
			if (wordLengths[col] >= row) {
				printf(" * ");
			} else {
				printf("   ");
			}
		}
		putchar('\n');
	}
	printf("    ");
	for (int i = 1; i <= MAX_LENGTH; i++) {
		printf("___");
	}
	putchar('\n');
	printf("    ");
	for (int i = 1; i <= MAX_LENGTH; i++) {
		printf(" %d ", i);
	}
	printf("\n\n");
	printf("Number of words overflow in length: %d\n", numOverflow);
}
