#include <stdlib.h>
#include <stdio.h>
int main(void) {
	int *data = malloc(100 * sizeof(int));
	data[100] = 0;
	free(data);
	printf("%d", data[0]);
	return 0;
}
