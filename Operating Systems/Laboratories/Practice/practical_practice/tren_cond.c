#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//In gara A intră simultan maximum m trenuri care vor să ajungă în gara B. 
//Intre A şi B există simultan n linii, m > n, dar în gară se pot afla simultan doar n trenuri. 
//Fiecare tren intră în A la un interval aleator. 
//Dacă are linie liberă între A şi B, o ocupă şi pleacă către B, durata de timp a trecerii este una aleatoare. 
//Să se simuleze aceste treceri. 
//Soluiile, una folosind variabile condiţionale, cealaltă folosind semafoare, sunt prezentate în tabelul următor. 

#define N 5
#define M 13
#define SLEEP 4

pthread_mutex_t mut, mutcond;
pthread_cond_t cond;
int linie[N], tren[M];
pthread_t tid[M];
int liniilibere;

void* trece(void* tren) {
  int i, s, t, l;
  t = *(int*)tren;
  s = 1 + rand() % SLEEP;

  pthread_mutex_lock(&mutcond);
  for ( ; liniilibere == 0; ) {
    pthread_cond_wait(&cond, &mutcond);
  }
  pthread_mutex_unlock(&mutcond);

  pthread_mutex_lock(&mut);
  for (l = 0; l < N; l++) {
    if (linie[l] == -1) break;
  }
  linie[l] = t;
  liniilibere--;
  
  printf("Trenul %d pe linie %d pentru %d secunde. Trenuri in gara:", t, l, s);
  for (i = 0; i < N; i++) {
    if (linie[i] != -1) {
      printf(" %d", linie[i]);
    }
  }
  printf(".\n");
  fflush(stdout);;
  pthread_mutex_unlock(&mut);

  sleep(s);

  pthread_mutex_lock(&mut);
  linie[l] = -1;
  liniilibere++;
  pthread_mutex_unlock(&mut);

  pthread_mutex_lock(&mutcond);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutcond);

  return 0;
}



int main() {
  int i;
  pthread_mutex_init(&mut, NULL);
  pthread_mutex_init(&mutcond, NULL);
  pthread_cond_init(&cond, NULL);

  liniilibere = N;

  for (i = 0; i < N; linie[i] = -1, i++);
  for (i = 0; i < M; tren[i] = i, i++);

  for(i = 0; i < M; i++) pthread_create(&tid[i], NULL, trece, &tren[i]);
  for(i = 0; i < M; i++) pthread_join(tid[i], NULL);

  pthread_mutex_destroy(&mut);
  pthread_mutex_destroy(&mutcond);
  pthread_cond_destroy(&cond);

  return 0;
}
