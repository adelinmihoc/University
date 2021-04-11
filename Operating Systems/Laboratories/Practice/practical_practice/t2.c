#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


// program 4 threads:
// 3?2?? global variables: v5, v2;
// Each thread:
//  generates a random number:
//      if number % 2 == 0 --> v2 += 1;
//      if number % 5 == 0 --> v5 += 1;
//  prints generated numbers
//  each stop when they have 5 numbers generated
// Main prints v2 and v5;

#define N 4
int v2 = 0;
int v5 = 0;

pthread_mutex_t mutex;

void* function(void*param) {
  int generated = 0;
  srand(time(NULL));
  while(generated <= 5) {
    int rand_int = rand() % 101;
    printf("Thread %ld generated: %d\n", pthread_self(), rand_int);
    if (rand_int % 5 == 0) {
      pthread_mutex_lock(&mutex);
      v5 += 1;
      pthread_mutex_unlock(&mutex);
      generated += 1;
    } else if (rand_int % 2 == 0) {
      pthread_mutex_lock(&mutex);
      v2 += 1;
      pthread_mutex_unlock(&mutex);
      generated += 1;
    }
  }

  return param;
}


int main() {
  int i;
  pthread_t tid[N];

  for (i = 0; i < N; i++) pthread_create(&tid[i], NULL, function, NULL);
  for (i = 0; i < N; i++) pthread_join(tid[i], NULL);

  printf("[Main] v2 = %d\n       v5 = %d\n", v2, v5);

  return 0;
}
