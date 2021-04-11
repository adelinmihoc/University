#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
  int p1, p2;
  p1=fork();
  if (p1 == 0) {
    printf("This is the first child with pid=%d, ppid=%d\n", getpid(), getppid());
    p2=fork();
    if (p2 == 0) {
      printf("This is the second child with pid=%d, ppid=%d\n", getpid(), getppid());
      exit(0);
    }
    wait(0); // wait for first child 
    exit(0);
  }
  printf("This is the parent with pid=%d, ppid=%d\n", getpid(), getppid());
  wait(0); // wait for child in parent
  return 0;
}
