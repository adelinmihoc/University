#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define N 5
#define M 13

int linie[N], tren[M];
sem_t sem, mut;
pthread_t tid[M];

void* trece(void*tren) {
  int i, s, t, l;
  t = *(int*)tren; // trenul ii numarul threadului cand a fost creat
  s = 1 + rand() % 4;

  sem_wait(&sem); // lasa doar N threaduri la chestia de mai jos 

  sem_wait(&mut);
  for (l = 0; l < N; l++) {
    if (linie[l] == -1) break;
  } // gaseste prima linie libera == -1;
  linie[l] = t; // pune trenul pe linie
  printf("Trenul %d pe linia %d pentru %d. Trenuri in gara:", t, l, s); // trenuri care nu sunt chiar in gara da ma rog;
  for (i = 0; i < N; i++) {
    if (linie[i] != -1)
      printf(" %d", linie[i]);
  } // printeaza toate trenurile de pe linii
  printf(".\n");
  fflush(stdout);
  sem_post(&mut);

  sleep(s); // acuma trenul merge pe linie si de asta pare ca doarme programul

  sem_wait(&mut);
  linie[l] = -1; // zice ca linia cu trenul ala s-a eliberat ca gen a ajuns in gara
  sem_post(&mut);

  sem_post(&sem); // odata ce threadul a termina asta global in alta dimensiune lasa alt thread sa intre

  return NULL;
}


int main() {
  int i;
  sem_init(&sem, 0, N); // permits n treads to pass
  sem_init(&mut, 0, 1); // premits 1 thread to pass (mutex)

  for (i = 0; i < N; linie[i] = -1, i++);
  for (i = 0; i < M; tren[i] = i, i++);

  for (i = 0; i < M; i++) pthread_create(&tid[i], NULL, trece, &tren[i]);
  for (i = 0; i < M; i++) pthread_join(tid[i], NULL);

  sem_destroy(&sem);
  sem_destroy(&sem);

  return 0;
}
