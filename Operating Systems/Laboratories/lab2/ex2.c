#include <stdlib.h>
#include <stdio.h>


int main() {
	int n, i, j;
	printf("Insert n:\n>>>");
	scanf("%d", &n);
	//printf("%d", n);
	int *v = (int*)malloc(n * n * sizeof(int));
	//v = (int**)malloc(n * sizeof(int*));
	int count = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			*(v + i * n + j) = ++count;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", *(v + i * n + j));
		}
		printf("\n");
	}
	//printf("Hello!\n");
	free(v);
	return 0;
}
