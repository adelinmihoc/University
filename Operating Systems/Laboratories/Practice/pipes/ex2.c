#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


int main() {
	int p[2];
  pipe(p);
  if (fork() == 0) {
    dup2 (p[1], 1); // redirect standard output
    close(p[0]);
    execlp ("who", "who", NULL);
    exit(1);
  } else if (fork() == 0) {
    dup2 (p[0], 0); // redirect standard input
    close(p[1]);
    execlp ("sort", "sort", NULL);
    exit(1);
  } else {
    close(p[1]);
    close(p[0]);
    wait(0);
    wait(0);
  }
	return 0;
}
