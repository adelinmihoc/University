#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Inițializați un vector cu numerele de la 1 la N (citit de la tastatură). 
// Programul inițial trebuie să producă un proces copil și fiecare să calculeze suma a jumătate din numere 
// (ex. părintele să adune numerele pare, copilul cele impare) adun�nd la o variabilă globală comună. 
// Explicați rezultatul 


int main() {
  int sum =0;
  int n, i, p, j;
  printf("N=");
  scanf("%d", &n);
  int* arr;
  arr = (int*)malloc(n * sizeof(int));
  
  for (i = 0; i < n; i++) {
    printf("input number\n>>>");
    scanf("%d", &arr[i]);
  }

  p = fork();
  if (p == 0) {
    for (i = 0; i < n; i++) {
      if (arr[i]%2 == 0) {
        sum += arr[i];
      }
    }
    printf("sum after child=%d\n", sum);
    exit(0);
  }
  //wait(0);
  for (j = 0; j < n; j++) {
    if (arr[j] % 2 == 1) {
      sum += arr[j];
    }
  }
  printf("sum after parent=%d\n", sum);
  free(arr);
  wait(0);
  printf("The sum is %d\n", sum);
  return 0;
}
