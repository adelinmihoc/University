#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

// Write 2 c programs A and B.
// A will create 2 processes p1 and p2.
// p1 will have provided (by any means) a file containing only numbers then it will read from the 
// standard input a number n. p1 will send the first n numbers from the file to p2 via pipe.
// p2 will send the sum of all the odd numbers received to B, via FIFO.
// B will display on the standard output the numbers received.
// the source file must be compiled using -Wall -g without warnings and syntax errors.
// Memory leaks and zombie processes are not allowed.


int main() {
  int fd[2], p1, p2, n, a, sum = 0, f = 0;
  FILE *fp;
  pipe(fd);

  f = open("file.txt", O_WRONLY);

  p1 = fork();
  if (p1 == -1) {
    perror("fork() error");
    exit(EXIT_FAILURE);
  }
  if (p1 == 0) {
    close(fd[0]);
    fp = fopen("/home/adelin/OneDirToRuleThemAll/os/test_practice/data.txt", "r");
    printf("Input n:\n>>>");
    scanf("%d", &n);
    write(fd[1], &n, sizeof(int));
    while(n--) {
      fscanf(fp, "%d", &a);
      write(fd[1], &a, sizeof(int));
    }
    close(fd[1]);
    exit(0);
  }

  p2 = fork();
  if (p2 == -1) {
    perror("fork() error");
    exit(EXIT_FAILURE);
  }
  if (p2 == 0) {
    close(fd[1]);
    read(fd[0], &n, sizeof(int));
    while(n--) {
      read(fd[0], &a, sizeof(int));
      if (a % 2 == 1) {
        sum += a;
      }
    }
    close(fd[0]);
    printf("Sum is %d\n", sum);

    write(f, &sum, sizeof(int));


    close(f);
    exit(0);
  }
  close(fd[0]);
  close(fd[1]);

  wait(0);
  wait(0);

  return 0;
}
