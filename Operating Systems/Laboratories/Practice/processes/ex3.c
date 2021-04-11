#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 Write a C program to execute the shell command ls -l.
*/

int main() {
  char* argv[3];
  argv[0] = "/bin/ls";
  argv[1] = "-l";
  argv[2] = NULL;
  execv("/bin/ls", argv);
  return 0;
}
