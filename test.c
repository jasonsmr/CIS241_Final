#include <stdio.h> 
#include <stdlib.h>
int main(void) {

	char *(*BuffArray)[50] = malloc(sizeof *BuffArray);
	printf("size = %zu, p = %p\n", sizeof *BuffArray, (void *)BuffArray);
	return 0;
}
