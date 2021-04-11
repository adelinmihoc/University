#include <stdio.h>
#include <stdlib.h>


int main() {
	//printf("hello\n");
	int rows = 3, colms = 4, i, j, count = 0;
	int **arr = (int **)malloc(rows * sizeof(int *));
	for (i = 0; i < rows; i++) {
		arr[i] = (int *)malloc(colms * sizeof(int));
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < colms; j++) {
			arr[i][j] = ++count;
		}
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < colms; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	
	for (i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}
