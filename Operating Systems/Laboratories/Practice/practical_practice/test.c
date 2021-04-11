#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
// program:
// citeste de la tastatura: nume dir si n-numar natural n<=10
// creeaza un thread la 2 secunde genereaza o litera 'a'-'z'
// creeaza inca n threaduri parameru = numele dir --thread rand afiseaza doar acele fisiere care incep cu litera generata in acel moment--
// generare litera noua <--- toate fisierele cu acea litera listate

#define N 5

pthread_t tid[N];

int main (int argc, char** argv) {
  printf("%s\n", argv[1]);
  char *str[3];
  str[0] = "/bin/ls";
  str[1] = argv[1];
  execl("/bin/ls", "/bin/ls", "asd", "| grep \"a\"", NULL);
  printf("hello?");
  return 0;
}
