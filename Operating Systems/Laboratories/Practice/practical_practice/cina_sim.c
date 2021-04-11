#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//

#define N 5

int nt[N];
pthread_t t[N];
pthread_mutex_t mutex[N];

void* filosof(void* n) {
  int i = *((int*)n);

  for ( ; ; ) {
  pthread_mutex_lock(&mutex[i]);
  pthread_mutex_lock(&mutex[(i + 1) % N]);

  printf("%d mananca\n", i);
  
  pthread_mutex_unlock(&mutex[(i + 1) % N]);
  pthread_mutex_unlock(&mutex[i]);

  sleep(rand() % 2);
  printf("%d cugeta\n", i);
  sleep(rand() %3 );
  }

  return 0;
}

int main() {
  int i;
  for (i = 0; i < N; i++) {
    nt[i] = i;
    pthread_mutex_init(&mutex[i], NULL);
  }

  for (i = 0; i < N; i++) pthread_create(&t[i], NULL, filosof, &nt[i]);
  for (i = 0; i < N; i++) pthread_join(t[i], NULL);

  return 0;
}
