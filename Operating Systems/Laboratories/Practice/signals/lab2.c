#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

//Scrieți un program care afișează 
//data + ora curentă c�nd primește semnalul HUP (signal(), time() + ctime()).

void f() {
  time_t current_time;
  time(&current_time);

  printf("Signal received at time = %s", ctime(&current_time));
}

int main() {
  signal(SIGHUP, f);
  while(1);
  return 0;
}
