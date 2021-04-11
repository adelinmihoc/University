#include <stdlib.h>
#include <stdio.h>


int main() {
	//bidimensional array 
	//using an array of pointers
	int rows = 4, colms = 3, i, j, count = 0;
	int *arr[rows];
	for (i = 0; i < rows; i++) {
		arr[i] = (int*)malloc(colms * sizeof(int));
	}
	for (i = 0; i < rows; i++) {
		for (j = 0; j < colms; j++) {
			arr[i][j] = ++count;
		}
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < colms; j++) {
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
	for (i = 0; i < rows; i++) {
		free(arr[i]);
	}
	//free(arr[rows]);
	return 0;
}
