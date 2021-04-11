#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// A and B - c programs
// A - 2 processes: p1 and p2
//    p1 - file with numbers. reads n. send first n numbers from file to p2 via pipe 
//    p2 - send divisors of the numbers to B via fifo
// B - display the received numbers


void print_div(int n) {
  for (int i = 1; i <= n; i++) {
    if (n % i == 0) {
      printf("%d ", i);
    }
  }
}


int main () {
  int fd[2], p1, p2, n, a, i;
  FILE* fp;
  pipe(fd);

  p1 = fork();
  if (p1 == 0) {
    close(fd[0]);
    fp = fopen("data.txt", "r");
    printf("Input n:\n>>>");
    scanf("%d", &n);
    write(fd[1], &n, sizeof(int));
    for (i = 0; i < n; i++) {
      fscanf(fp, "%d", &a);
      write(fd[1], &a, sizeof(int));
    }
    close(fd[1]);
    fclose(fp);
    exit(0);
  }

  p2 = fork();
  if (p2 == 0) {
    close(fd[1]);
    read(fd[0], &n, sizeof(int));
    for (i = 0; i < n; i++) {
      read(fd[0], &a, sizeof(int));
      print_div(a);
      printf("\n");
    }
    close(fd[0]);
    exit(0);
  }

  close(fd[0]);
  close(fd[1]);

  wait(0);
  wait(0);

  return 0;
}
