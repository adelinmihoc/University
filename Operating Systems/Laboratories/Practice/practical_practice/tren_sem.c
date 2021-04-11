#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// In gara A intră simultan maximum m trenuri care vor să ajungă în gara B. 
// Intre A şi B există simultan n linii, m > n, dar în gară se pot afla simultan doar n trenuri. 
// Fiecare tren intră în A la un interval aleator. Dacă are linie liberă între A şi B, 
// o ocupă şi pleacă către B, durata de timp a trecerii este una aleatoare. Să se simuleze aceste treceri.
// Soluiile, una folosind variabile condiţionale, cealaltă folosind semafoare, sunt prezentate în tabelul următor.


#define N 5
#define M 13
#define SLEEP 4

sem_t sem, mut;
int linie[N], tren[M];
pthread_t tid[M];


void* trece(void* tren) {
  int i, s, t, l;
  t = *(int*)tren;
  s = 1 + rand() % SLEEP;

  sem_wait(&sem);

  sem_wait(&mut);
  for (l = 0; l < N; l++) {
    if (linie[l] == -1) break;
  }
  linie[l] = t;

  printf("Trenul %d pe linia %d pentru %d secunde, Trenuri in gara:", t, l, s);
  for (i = 0; i < N; i++) {
    if (linie[i] != -1) {
      printf(" %d", linie[i]);
    }
  }
  printf(".\n");
  fflush(stdout);
  sem_post(&mut);

  sleep(s);

  sem_wait(&mut);
  linie[l] = -1;
  sem_post(&mut);

  sem_post(&sem);

  return 0;
}


int main() {
  int i;
  sem_init(&sem, 0, N);
  sem_init(&mut, 0, 1);
  for (i = 0; i < N; linie[i] = -1, i++);
  for (i = 0; i < M; tren[i] = i, i++);

  for (i = 0; i < M; i++) pthread_create(&tid[i], NULL, trece, &tren[i]);
  for (i = 0; i < M; i++) pthread_join(tid[i], NULL);

  sem_destroy(&sem);
  sem_destroy(&mut);

  return 0;
}
