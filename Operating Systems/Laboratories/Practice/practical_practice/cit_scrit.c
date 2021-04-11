#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Problema cititorilor si a scriitorilor

#define S 5
#define C 5
#define CSLEEP 2
#define SSLEEP 3

pthread_t tid[C + S];
int c[C], s[S], nt[C + S];

pthread_mutex_t mutcond, exclusafis;
pthread_cond_t cond;
int cititori;

// afiseazs starea curenta a cititorilor si scriitorilor 
void afiseaza() {
  int i;
  pthread_mutex_lock(&exclusafis);
  for (i = 0; i < C; i++) printf("C%d_%d\t", i, c[i]);
  for (i = 0; i < S; i++) printf("S%d_%d\t", i, s[i]);
  printf("\n");
  fflush(stdout);
  pthread_mutex_unlock(&exclusafis);
}

// rutina thread citittor
void* cititor(void* nrc) {
  int indc = *(int*)nrc;
  for ( ; ; ) {
    c[indc] = -1; // asteapta sa citeasca
    pthread_mutex_lock(&mutcond);
    cititori++;
    c[indc] = 0; // citeste
    afiseaza();
    pthread_mutex_unlock(&mutcond);
    sleep(1 + rand() % CSLEEP);
    c[indc] = -2; // a citit si doarme
    pthread_mutex_lock(&mutcond);
    cititori--;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutcond);

    sleep(1 + rand() % CSLEEP);
  }
  return NULL;
}

// rutina thread scrritor
void* scriitor(void*nrs) {
  int inds = *(int*)nrs;
  for ( ; ; ) {
    s[inds] = -1; // asteapta sa scrie

    pthread_mutex_lock(&mutcond);
    for ( ; cititori > 0; ) {
      pthread_cond_wait(&cond, &mutcond);
    }
    s[inds] = 0; // scrie
    afiseaza();
    sleep(1 + rand() % SSLEEP);
    s[inds] = -2; // a scris si doarme
    pthread_mutex_unlock(&mutcond);

    sleep(1 + rand() % SSLEEP);
  }
  return NULL;
}


int main() {
  pthread_mutex_init(&exclusafis, NULL);
  pthread_mutex_init(&mutcond, NULL);
  pthread_cond_init(&cond, NULL);
  int i;
  for (i = 0; i < C; c[i] = -3, nt[i] = i, i++); //-3 : nu a pornit
  for (i = 0; i < S; s[i] = -3, nt[i + C] = i, i++);

  for (i = 0; i < C; i++) pthread_create(&tid[i], NULL, cititor, &nt[i]);
  for (i = C; i < C + S; i++) pthread_create(&tid[i], NULL, scriitor, &nt[i]);

  for (i = 0; i < C + S; i++) pthread_join(tid[i], NULL);

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutcond);
  pthread_mutex_destroy(&mutcond);

  return 0;
}
