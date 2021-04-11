#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


// Scrieți programe părinte / copil �n care copilul verifică dacă un număr e prim; 
// părintele afișează numerele prime p�nă la N citit de la tastatură (wait + WEXITSTATUS).


int prim(int n) {
  int i;
  if (n <= 1 || n % 2 == 0) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  for (i = 3; i * i < n; i+=2) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  int n, status, i, p;
  printf("Input N:\n>>>");
  scanf("%d", &n);
  // printf("%d", n);

  for (i = 0; i < n; i++) {
    p = fork();
    if (p == 0) {
      if (prim(i) == 1) {
        exit(0);
      }
      exit(1);
    }
    wait(&status);
    if (WEXITSTATUS(status) == 0) {
      printf("%d\n", i);
    }
  }

  return 0;
}





