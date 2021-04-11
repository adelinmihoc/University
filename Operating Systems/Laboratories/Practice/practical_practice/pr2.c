#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//program cu 2 tipuri de threaduri
//A-1 nr random/sec de 10 ori
//B-printeaza valoarea generata de A de 2 ori pe secunda de 20 de ori
//executie cu mai multe threaduri de fiecare tip+sincronizare cu mutex simplu. 

#define N 10

int nr;

pthread_mutex_t mutex;

void* genereaza(void* a) {
  int i;

  for (i = 0; i < N; i++) {
    pthread_mutex_lock(&mutex);
    nr = rand() % 1000;
    pthread_mutex_unlock(&mutex);
    
    printf("generated:%d\n", nr);
    sleep(1);
   // pthread_mutex_unlock(&mutex);
    }
  return a;
}

void* printeaza(void*a) {
  int i;
  for (i = 0; i < 2 * N; i++) {
    pthread_mutex_lock(&mutex);
    printf("Printed: %d\n", nr);
    printf("Printed: %d\n", nr);
    pthread_mutex_unlock(&mutex);
    
    sleep(1);
  }
  return a;
}

int main() {
  srand(time(NULL));
  int i;
  pthread_t a[N];
  pthread_t b[N];
  pthread_mutex_init(&mutex, NULL);

  for (i = 0; i < N; i++) {
    pthread_create(&a[i], NULL, genereaza, NULL);
    pthread_create(&b[i], NULL, printeaza, NULL);
  }
    //for (i = 0; i < N; i++) pthread_create(&b[i], NULL, printeaza, (void*)&nr);

  for (i = 0; i < N; i++) pthread_join(a[i], NULL);
  for (i = 0; i < N; i++) pthread_join(b[i], NULL);

  pthread_mutex_destroy(&mutex);
  return 0;
}
