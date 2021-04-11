/*
Write a program that reads from the command line (arguments) 
a list of text files.
Modify these files such that each word is capitalized. 
Use a separate process for each file.
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

int main(int argc, char* argv[]) {
  int i, pid;
  for (i = 1; i < argc; i++) {
    pid=fork();
    if (pid == 0) {
      execl("./capit.sh", "./capit.sh", argv[i], NULL);
      printf("Error\n"); // this appears only if execl failed
      exit(1);
    } else {
        printf("Parent, launched child:%d ----> %s \n", pid, argv[i]);
    }
  }
  for (i = 1; i < argc; i++) {
    signal(SIGCHLD, waiter);
  } 
  printf("Launched symultaneously %d processes for capitalization/n", argc - 1);
  return 0;
}
