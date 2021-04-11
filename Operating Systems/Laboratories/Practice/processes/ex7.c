#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>


// calculate sum of numbers from 0 to n

#define MAX_LENGTH 10

int main() {
  int sum = 0, i, pid;
  int* numbers = (int*)malloc(MAX_LENGTH * sizeof(int));

  if (numbers == NULL) {
    perror("malloc() error");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < MAX_LENGTH; i++) {
    numbers[i] = i;
  }

  pid = fork();
  if (pid == -1) {
    perror("fork() error");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    printf("\n[IN CHILD] I started...\n");
    printf("[IN CHILD] My PID is %d\tParent pid id %d\n", getpid(), getppid());

    for (i = 0; i < MAX_LENGTH; i++) {
      if (numbers[i] % 2 == 0) {
        sum += numbers[i];
      }
    }
    printf("[IN CHILD] Sum: %d\n", sum);

    printf("[IN CHILD] I finished my job.\n");
    exit(sum);
  } else {
    printf("\n[IN PARENT] I started...\n");
    printf("[IN PARENT] My PID is%d\tParent pid is %d\n", getpid(), getppid());

    for (i = 0; i < MAX_LENGTH; i++) {
      if (numbers[i] % 2 == 1) {
        sum += numbers[i];
      }
    }
    printf("[IN PARENT] Final sum: %d\n", sum);
    printf("[IN PARENT] I finished my job.\n");
  }
  return 0;
}
