#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 

#define FILOSOFI 5
#define MANANCA 1
#define CUGETA 2
#define FLAMAND 3
#define TRUE 1
#define FALSE 0

int stare[FILOSOFI];
int nt[FILOSOFI];
pthread_t t[2 * FILOSOFI];
pthread_cond_t cond[FILOSOFI];
pthread_mutex_t mutex[FILOSOFI];

int poateManca(int i) {
  int stanga = (i - 1 + FILOSOFI) % FILOSOFI;
  int dreapta = (i + 1) % FILOSOFI;

  if (stare[i] == FLAMAND && stare[stanga] != MANANCA && stare[dreapta] != MANANCA) {
    stare[i] = MANANCA;
    pthread_cond_signal(&cond[i]);
    return TRUE;
  } else {
    return FALSE;
  }
}

void* mananca(void* n) {
  int i = *((int*)n);

  while (TRUE) {
    pthread_mutex_lock(&mutex[i]);
    stare[i] = FLAMAND;
    while (poateManca(i) == FALSE) {
      pthread_cond_wait(&cond[i], &mutex[i]);
    }
    printf("%d mananca\n", i);
    pthread_mutex_unlock(&mutex[i]);
    sleep(abs(rand() % 2));
  }

  return 0;
}


void* cugeta(void* n) {
  int i = *((int*)n);

  while (TRUE) {
    pthread_mutex_lock(&mutex[i]);
    stare[i] = CUGETA;
    printf("%d cugeta\n", i);
    pthread_mutex_unlock(&mutex[i]);
    sleep(abs(rand() % 5));
  }

}

int main() {
  int i;

  for ( i = 0; i < FILOSOFI; i++) {
    nt[i] = i;
    stare[i] = CUGETA;
    pthread_cond_init(&cond[i], NULL);
    pthread_mutex_init(&mutex[i], NULL);
  }

  for (i = 0; i < FILOSOFI; i++) {
    pthread_create(&t[i], NULL, mananca, &nt[i]);
    pthread_create(&t[i + FILOSOFI], NULL, cugeta, &nt[i]);
  }

  for (i = 0; i < 2 * FILOSOFI; i++) {
    pthread_join(t[i], NULL);
  }

  return 0;
}








