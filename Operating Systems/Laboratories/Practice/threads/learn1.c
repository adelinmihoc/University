#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// example creating threads

#define THR_COUNT 20 // define a constant for the number of threads


// function that will be executed by each thread
void* thread_function(void *param) {
  printf("I am thread %lu\n", (ulong)pthread_self());
  return 0;
}


int main() {
  int i = 0;

  pthread_t thr[THR_COUNT];

  // creates threads
  for (i = 0; i < THR_COUNT; i++) { 
    pthread_create(&thr[i], NULL, thread_function, NULL);

  }

  // wait for the threads to terminate

  for (i = 0; i < THR_COUNT; i++) {
    pthread_join(thr[i], NULL);

  }
    
  return 0;
}
