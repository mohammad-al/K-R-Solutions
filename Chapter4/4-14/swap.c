#include <stdio.h>

#define swap(t, x, y) {\
	t temp = x;\
	x = y;\
	y = temp;\
}

int main(void) {

	int x = 5;
	int y = 6;
	printf("Before swap: x = %d and y = %d\n", x, y);
	swap(int, x, y);
	printf("After swap: x = %d and y = %d\n", x, y);
}
