#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
//

#define N 10
int total = 0;

pthread_mutex_t mutex, mutcond;
pthread_cond_t cond;
int a[10][100];

void* function(void* param) {

  while(total <= 30) {
    int rand_int = 10 + rand() % 100;
    printf("Thread %ld generated %d\n", pthread_self(), rand_int);
    pthread_mutex_lock(&mutex);
    if (total >= 30) {
      pthread_mutex_unlock(&mutex);
      break;
    }
    a[rand_int/10][0] += 1;
    a[rand_int/10][a[rand_int/10][0]] = rand_int;
    total += 1;
    pthread_mutex_unlock(&mutex);
  }

  return param;
}

int main() {
  srand(time(NULL));
  int i, j;
  pthread_t tid[N];
  pthread_mutex_init(&mutex, NULL);

  for (i = 0; i < N; i++) pthread_create(&tid[i], NULL, function, NULL);
  for (i = 0; i < N; i++) pthread_join(tid[i], NULL);

  pthread_mutex_destroy(&mutex);

  printf("total: %d", total);

  for (i = 0; i < 10; i++) {
    printf("t[%d] = ", i);
    for (j = 1; j <= a[i][0]; j++) {
      printf("%d, ", a[i][j]);
    }
    printf("\n");
  }

  return 0;
}
