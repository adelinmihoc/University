#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
  
// program:
// creates 7 threads and a global array of 10 integer = SUM
//  SUM: stores the sum of numbers beased on %10
//  each thread: generates random numbers 0-100, adds each n to SUM[x] (x=n%10)
//    thread stops: there are 5 numbers generated - last digit = 5
//  main: prints sum from array for each digit (print SUM[x] = nr - x=0..9 - nr: sum of all numbers with remainder x
//
//  use synchronization print also the numbers that make up the sum
// 
// example : SUM[2] = 12 + 22 = 34
//           SUM[4] = 84 + 24 + 64 = 172
//

#define N 7
int SUM[10];
int a[10][100];

pthread_mutex_t mutex, mutcond;
pthread_cond_t cond;

void* function(void* param) {
  srand(time(NULL));
  while(1) {
    if (a[5][0] >= 5) break;
    int rand_num = rand() % 101;
    printf("thread%ld rand %d\n", pthread_self(), rand_num);
    pthread_mutex_lock(&mutex);
    SUM[rand_num % 10] += rand_num;
    a[rand_num % 10][0] += 1;
    a[rand_num % 10][a[rand_num % 10][0]] = rand_num;
    pthread_mutex_unlock(&mutex);
  }

  return param;
}

pthread_t tid[N];

int main() {
  int i, j;

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&mutcond, NULL);
  pthread_cond_init(&cond, NULL);

  for (i = 0; i < N; i++) {
    pthread_create(&tid[i], NULL, function, NULL);
  }

  for (i = 0; i < N; i++) {
    pthread_join(tid[i], NULL);
  }
  
  for (i = 0; i < 10; i++) {
    printf("SUM[%d]=", i);
    for (j = 1; j <= a[i][0]; j++) {
      printf("%d", a[i][j]);
      if (j != a[i][0]) {
      printf("+");
      }
    }
    printf("=%d", SUM[i]);
    printf("\n");
  }

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutcond);
  pthread_mutex_destroy(&mutex);

  return 0;
}
