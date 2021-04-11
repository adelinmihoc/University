#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//program cu 2 tipuri de threaduri
//A-1 nr random/sec de 10 ori
//B-printeaza valoarea generata de A de 2 ori pe secunda de 20 de ori
//executie cu mai multe threaduri de fiecare tip. 

#define N 10

void* genereaza(void* a) {
  int* temp = (int*)a;
  int i;

  for (i = 0; i < N; i++) {
    *temp = rand() % 1000;
    sleep(1);
  }
  return NULL;
}

void* printeaza(void*a) {
  int *nr = (int*)a;
  int i;
  for (i = 0; i < 2 * N; i++) {
    printf("%d\n", *nr);
    usleep(500000);
  }
  return NULL;
}

int main() {
  srand(time(NULL));
  int nr = 0, i;

  pthread_t a[N];
  pthread_t b[N];

  pthread_create(a, NULL, genereaza, (void*)&nr);
  pthread_create(b, NULL, printeaza, (void*)&nr);

  pthread_join(a, NULL);
  pthread_join(b, NULL);


  return 0;
}
