#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main() {
  fork();
  fork();
  wait(0);
  fork();
  wait(0);
  printf("#\n");
  return 0;
}
