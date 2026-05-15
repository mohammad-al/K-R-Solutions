#include <stdio.h>
#include "alloc.h"

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(unsigned int n) {
	
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return NULL;
	}
}
