/*
Write a program that gets programs as command line arguments, 
and executes them using fork and exec. 
In case execfails or the program it executes exits with 
an error code, report the relevant details standard error. 
Notice in the solution below, the usage of strerror, errno,
wait and WEXITSTATUS in the solution above. 
Read the UNIX manual to understand what they do.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>


int main(int argc, char** argv) {
  int i, status;
  for (i=0; i<argc; i++) {
    if (fork() == 0) {
      if (execlp(argv[i], argv[i], NULL) == -1) {
        fprintf(stderr, "Failed to execute program \"%s\": %s\n", argv[i], strerror(errno));
        exit(0);
      }
    }
    wait(&status);
    if (WEXITSTATUS(status) != 0) {
      fprintf(stderr, "Program \"%s\" failed with exit code %d\n", argv[i], WEXITSTATUS(status));
    }
  }
  return 0;
}
