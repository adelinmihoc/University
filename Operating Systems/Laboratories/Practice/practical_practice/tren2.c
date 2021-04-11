#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


#define N 5
#define M 13

int linii[N], trenuri[M];
sem_t sem, mut;
pthread_t tid[M];

void* trece(void*tren) {
  int t, l, s, i;
  t = *(int*)tren; // trenul curent
  s = 1 + rand() % 4;
  sem_wait(&sem);

  sem_wait(&mut);
  for (l = 0; l < N; l++) {
    if (linii[l] == -1) break; // gasim o linie libera tre sa fie neaparat
  }
  sem_post(&mut);
  linii[l] = t; // punem trenul pe linie

  printf("Am pus pe linie trenul %d pe linia %d va ajunge in %d secunde in gara B. Alte trenuri in drum spre gara: ", t, l, s);
  for (i = 0; i < N; i++) {
    if (linii[i] != -1) {
      printf(" %d", linii[i]);
    }
  }
  printf(".\n");
  fflush(stdout);

  sleep(s);

  linii[l] = -1;

  sem_post(&sem);

  return NULL;
}

int main() {
  int i;
  sem_init(&sem, 0, N);
  sem_init(&mut, 0, 1);

  srand(time(NULL));

  for (i = 0; i < N; i++) {
    linii[i] = -1; // eliberare linie;
  }
  for (i = 0; i < M; i++) {
    trenuri[i] = i;
  }

  for (i = 0; i < M; i++) pthread_create(&tid[i], NULL, trece, &i);
  for (i = 0; i < M; i++) pthread_join(tid[i], NULL);


  printf("Toate trenele o ajuns\n");

  sem_destroy(&sem);
  sem_destroy(&mut);
  
  return 0;
}
