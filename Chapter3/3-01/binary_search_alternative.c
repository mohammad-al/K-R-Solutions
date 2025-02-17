/*
*	Our binary search makes two tests inside the loop, where one would
*	suffice (at the price of more tests outside). Write a version with
*	only one test inside the loop measure the difference in run-time.
*/

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void) {

	int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// Should print out 2
	printf("The index of 3 is %d\n", binsearch(3, numbers, 10));

	return 0;
}

// binsearch: find x in v[0] <= v[1] <= ... <= v[n - 1]
int binsearch(int x, int v[], int n) {

	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;

	while (low <= high && v[mid] != x) {
		if (v[mid] < x) {
			low = mid + 1;
		} else {
			high = mid - 1;
		} 	
		mid = (low + high) / 2;
	}
	if (v[mid] == x) {
		return mid;
	}
	return -1;
}
