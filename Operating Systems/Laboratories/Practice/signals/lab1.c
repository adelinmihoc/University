#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Scrieți un program care așteaptă indefinit și nu poate fi omor�t cu SIGTERM. Mai poate fi oprit?

void f(int sign) {
  printf("Signal derived\n");
}

int main() {
  signal (SIGTERM, f);
  while(1) {
    sleep(1);
  }

  return 0;
}
