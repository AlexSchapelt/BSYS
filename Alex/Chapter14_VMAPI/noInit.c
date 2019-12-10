#include <stdlib.h>
#include <stdio.h>
int main(void) {
	int *x = (int *)malloc(sizeof(int));
	printf("*x = %d\n", *x);
	return 0;
}
