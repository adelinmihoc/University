q#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Compute the sum of an array using threads (with synchronization)

// define a constant for the size of the array
#define ARR_SIZE 10000
// define a constant for the numbers of threads
#define THR_COUNT 4

// define a structure used to send parameters to threads
typedef struct _THR_PARAM {
  int* array;
  int idx_start;
  int idx_end;
}THR_PARAM;

// global variable - the sum of the elements in the array
int global_sum = 0;
// global variable - the mutex used for synchronization
pthread_mutex_t mutex;

// thread function - computes the sum of the elements of an array within a certain range
void* array_sum(void* param) {
  THR_PARAM thr_param;
  int i;
  int local_sum = 0;
  thr_param = *(THR_PARAM*)param;

  for (i = thr_param.idx_start; i < thr_param.idx_end; i++) {
    local_sum = local_sum + thr_param.array[i];
  }

  // aquire the lock
  pthread_mutex_lock(&mutex);

  // the instruction in this area can be executed by a single thread

  global_sum = global_sum + local_sum;

  //release the lock
  pthread_mutex_unlock(&mutex);
 
  return 0;
}


int main() {
  int i;
  int array[ARR_SIZE];
  pthread_t thr[THR_COUNT];
  THR_PARAM thr_param[THR_COUNT];

  // initialize the mutex
  pthread_mutex_init(&mutex, NULL);

  // fill the array with 1s
  for (i = 0; i < ARR_SIZE; i++) {
    array[i] = 1;
  }

  // prepare the params for each thread and create it
  for (i = 0; i < THR_COUNT; i++) {
    // prepare the params
    thr_param[i].array = array;
    thr_param[i].idx_start = (ARR_SIZE / THR_COUNT) * i;
    thr_param[i].idx_end = (ARR_SIZE / THR_COUNT) * (i + 1);
    
    // create the thread
    pthread_create(&thr[i], NULL, array_sum, (void*)&thr_param[i]);
  }
    
  // wait for the threads to finish
  for (i = 0; i < THR_COUNT; i++) {
    pthread_join(thr[i], NULL);
  }

  // destroy the mutex
  pthread_mutex_destroy(&mutex);

  // display the sum
  printf("Sum = %d\n", global_sum); 

  return 0;
}
















