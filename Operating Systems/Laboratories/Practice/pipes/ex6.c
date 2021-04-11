#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

// Sa se implementeze un proces care creeaza un proces copil cu care comunica
// prin pipe. Procesul parinte trimite prin pipe procesului copil doua numere
// intregi, iar procesul copil returneaza prin pipe suma lor. 

int main() {
  int fd[2], fd_sum[2], res1, res2, pid, a, b, sum;
  res1 = pipe(fd);
  if (res1 == -1) {
    perror("pipe() error");
    exit(EXIT_FAILURE);
  }

  res2 = pipe(fd_sum);
  if (res2 == -1) {
    perror("pipe() error");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {
    perror("fork() error");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    close(fd_sum[0]);
    close(fd[1]);

    if (read(fd[0], &a, sizeof(int)) < 0) {
      perror("read() error");
      exit(EXIT_FAILURE);
    }
    if (read(fd[0], &b, sizeof(int)) < 0) {
      perror("read() error");
      exit(EXIT_FAILURE);
    }
    close(fd[0]);
    sum = a + b;
    if (write(fd_sum[1], &sum, sizeof(int)) < 0) {
      perror("write() fail");
      exit(EXIT_FAILURE);
    }
    close(fd_sum[1]);
    exit(0);
  }

  close(fd_sum[1]);
  close(fd[0]);
  printf("[IN PARENT] Input a:\n>>>");
  scanf("%d", &a);
  printf("[IN PARENT] Input b:\n>>>");
  scanf("%d", &b);

  if (write(fd[1], &a, sizeof(int)) < 0) {
    perror("write() error");
    exit(EXIT_FAILURE);
  }
  if (write(fd[1], &b, sizeof(int)) < 0) {
    perror("write() error");
    exit(EXIT_FAILURE);
  }
  close(fd[1]);
  printf("[IN PARENT] a and b were send successfully\n");
  
  int status;
  wait(&status);

  if (read(fd_sum[0], &sum, sizeof(int)) < 0) {
    perror("read() error");
    exit(EXIT_FAILURE);
  }
  close(fd_sum[0]);
  printf("[IN PARENT] Sum is %d\n", sum);

  return 0;
}
