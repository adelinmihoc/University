/*
Write a program that creates three child processes that just loop forever. 
When the parent process gets SIGUSR1 it sends SIGUSR2 to the child processes. 
When the parent process gets SIGUSR2, it sends SIGKILL to the child processes.
The child processes should report the signals received. 
Note in the solution below that the child process does not
override the SIGKILL handler, as it will not have any effect.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void waiter(int signum) {
  wait(0);
}

int children[3];

void h_parent(int sgn) {
  int i;
  if (sgn == SIGUSR1) {
    printf("%d: sending SIGUSR2\n", getpid());
    for (i = 0; i < 3; i++) {
      kill(children[i], SIGUSR2);
    }
  } else if(sgn == SIGUSR1) {
    printf("%d: sending SIGKILL\n", getpid());
    for (i = 0; i < 3; i++) {
      kill(children[i], SIGINT);
    }
  }
}

void h_children(int sgn) {
  if (sgn == SIGUSR2) {
    printf("%d: Received SIGUSR2\n", getpid());
  }
}

int main() {
  int i;
  signal(SIGUSR1, h_parent);
  signal(SIGUSR2, h_parent);
  for (i = 0; i < 3; i++) {
    children[i]=fork();
    //printf("i=%d fork()=%d\n", i, children[i]);
    if (children[i] == 0) {
      printf("asd");
      signal(SIGUSR2, h_children);
      while(1);
      exit(0);
    }
  }
  signal(SIGCHLD, waiter);
  return 0;
}
