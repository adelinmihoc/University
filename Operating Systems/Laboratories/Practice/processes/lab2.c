#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Scrieți un program care fork()-uie procese copil recursiv c�tă vreme PID-ul fiecărui copil e par.

void recursiv_fork() {
  int p = fork();
  if (p == 0) {
    if (getpid()%2) {
      printf("invalid pid stop!\n");
      return;
    } else {
      printf("new fork for pid=%d", getpid());
      recursiv_fork();
    }
    exit(0);
  }
  wait(0);
}

int main () {
  recursiv_fork();
  return 0;
}
