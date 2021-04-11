#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Write a program that creates 5 threads, 
// giving each thread a string as parameter. 
// Each thread will count and add to the global variables v 
// and n as follows: 
// the number of vowels contained by the string added to v, 
// and the number of digits contained in the string added to n.

#define THR_COUNT 5

typedef struct {
  char* str;
  int idx_start;
  int idx_end;
} THR_PARAM;

int global_v = 0;
int global_n = 0;

pthread_mutex_t mutex;
pthread_mutex_t mutex2;

void* function(void* param) {
  THR_PARAM thr_param = *(THR_PARAM*)param;
  int i;
  int local_v = 0;
  int local_n = 0;

  for (i = thr_param.idx_start; i < thr_param.idx_end; i++) {
    if (strchr("aeiouAEIOU", thr_param.str[i])) {
      local_v += 1;
    } else if (strchr("0123456789", thr_param.str[i])) {
      local_n += 1;
    }
  }
  pthread_mutex_lock(&mutex);
    global_v += local_v;
  //  global_n += local_n;
  pthread_mutex_unlock(&mutex);

  pthread_mutex_lock(&mutex2);
    global_n += local_n;
  pthread_mutex_unlock(&mutex2);

  return 0;
} 

int main() {
  int i = 0;
  pthread_t thr[THR_COUNT];
  char string[] = "aeiqqqouqqqioqqaqeiqouiqqoaqeqquiq237q4q89qqq1q0qqq"; // 18 & 9
  THR_PARAM thr_param[THR_COUNT];
  int len = strlen(string);

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&mutex2, NULL);

  for (i = 0; i < THR_COUNT; i++) { 
    thr_param[i].str = string;
    thr_param[i].idx_start = (len / THR_COUNT) * i;
    thr_param[i].idx_end = (len / THR_COUNT) * (i + 1);

    pthread_create(&thr[i], NULL, function, (void*)&thr_param[i]);
  }

  for (i = 0; i < THR_COUNT; i++) {
    pthread_join(thr[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&mutex2);

  printf("Global v = %d\nGlobal n = %d\n", global_v, global_n);

  return 0;
}

