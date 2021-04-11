#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Write a program that creates 5 threads, giving each thread a string as parameter. 
// Each thread will count and add to the global variables v and n as follows: 
//    the number of vowels contained by the string added to v, 
//    and the number of digits contained in the string added to n.

#define THR_COUNT 5

typedef struct {
  char* string;
  int idx_start;
  int idx_end;
}THR_PARAM;

int global_v = 0;
int global_n = 0;

pthread_mutex_t mutex;

void* function(void* param) {
  int i;
  int local_sum_v = 0;
  int local_sum_n = 0;
  char vowels[] = "aeiou";
  char digits[] = "0123456789";
  THR_PARAM thr_param = *(THR_PARAM*)param;

  for (i = thr_param.idx_start; i < thr_param.idx_end; i++) {
    if (strchr(vowels, thr_param.string[i])) {
      local_sum_v += 1;
    } else if (strchr(digits, thr_param.string[i])){
      local_sum_n += 1;
    }
  }

  // aquire lock
  pthread_mutex_lock(&mutex);
    
  global_v = global_v + local_sum_v;
  global_n = global_n + local_sum_n;

  // unlock mutex
  pthread_mutex_unlock(&mutex);
  return 0;
}

int main() {
  int i;
  char string[] = "aeaviabiomuopi275t920r174q9dff";
  pthread_t thr[THR_COUNT];
  THR_PARAM thr_param[THR_COUNT];

  pthread_mutex_init(&mutex, NULL);

  for (i = 0; i < THR_COUNT; i++) {
    thr_param[i].string = string;
    thr_param[i].idx_start = (strlen(string) / THR_COUNT) * i; 
    thr_param[i].idx_end = (strlen(string) / THR_COUNT) * (i + 1);

    pthread_create(&thr[i], NULL, function, (void*)&thr_param[i]);
  }

  for (i = 0; i < THR_COUNT; i++) {
    pthread_join(thr[i], NULL);
  }

  pthread_mutex_destroy(&mutex);

  printf("Sum v: %d\n", global_v);
  printf("Sum n: %d\n", global_n);
  
  return 0;
}








