#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Sa se afiseze cate numere prime sunt in intervalul 1-2,000,000,000.

#define NTHREADS 8
#define MAX_INTERVAL 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int global_counter = 0;

int prim(int n) {
  printf("%d\n", n);
  int i;
  if (n <= 1) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  if (n % 2 == 0) {
    return 0;
  }
  for (i = 3; i < n; i+=2) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

typedef struct {
  int idx_start;
  int idx_end;
} THR_PARAM;

void* function(void* param) {
  THR_PARAM thr_param;
  thr_param = *(THR_PARAM*)param;
  int i;

  int local_counter = 0;

  for (i = thr_param.idx_start; i < thr_param.idx_end; i++) {
    if (prim(i)) {
      local_counter += 1;
    }
  }

  pthread_mutex_lock(&mutex);
  global_counter += local_counter;
  pthread_mutex_unlock(&mutex);

  return 0;
}


int main () {
  int i;
  pthread_t thr[NTHREADS];
  THR_PARAM thr_param[NTHREADS];

  time_t t1 = time(NULL);
  for (i = 0; i < NTHREADS; i++) {
    thr_param[i].idx_start = (MAX_INTERVAL / NTHREADS) * i;
    thr_param[i].idx_end = (MAX_INTERVAL / NTHREADS) * (i + 1);

    pthread_create(&thr[i], NULL, function, (void*)&thr_param[i]);
  }

  for (i = 1; i < NTHREADS; i++) {
    pthread_join(thr[i], NULL);
  }
  time_t t2 = time(NULL);
  double x = difftime(t2, t1);
  printf("Total prime numbers: %d\n", global_counter);
  printf("Total time: %f\n", x);
  return 0;
}
