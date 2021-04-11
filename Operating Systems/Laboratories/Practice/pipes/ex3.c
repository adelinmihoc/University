#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

//Write a program to execute who |sortby creating two 
//child processes that each launch 
//who and sort and redirect their input/output accordingly.

int main() {
  FILE *w2p;
  FILE *p2s;
  w2p=popen("who", "r");
  p2s=popen("sort", "w");
  char line[50];
  while (fgets(line, 50, w2p)) {
    fprintf("p2s", "%s", line);

  }
  pclose(w2p);
  pclose(p2s);
	return 0;
}
