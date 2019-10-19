#include <stdlib.h>
int main(void) {
	int *data = malloc(100 * sizeof(int));
	data[100] = 0;
	free(data);
	return 0;
}
