#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

//Scrieți un program care lansează două procese copil și apoi citește cuvinte de la tastatură p�nă c�nd primește un șir gol.
//Cuvintele ce conțin diftongul � oa � le va transmite prin pipe primului copil, restul celui de-al doilea; 
//fiecare copil va contoriza lungimea totală a cuvintelor primite și o va afișa la final (fork, gets, strstr, strlen). 

int main() {
  char word[100];
  int p2c1[2], p2c2[2];
  
  printf("Input a word:\n>>>");
  gets(word);
  while(word[0] != '\0') {
    printf("\nThe word is %s", word);
    printf("Input a word:\n>>>");
    gets(word);
  }
  return 0;
}
