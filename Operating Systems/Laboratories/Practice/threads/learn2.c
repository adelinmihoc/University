#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// sending parameters to thread

#define THR_COUNT 20 // define a constant for the number of threads


// function that will be executed by each thread
void* thread_function(void *param) {
  int nr = *(int*) param;
  printf("I am thread %lu and I receive the value %d\n", (ulong)pthread_self(), nr);
  return 0;
}


int main() {
  int i = 0;

  pthread_t thr[THR_COUNT];

  int thr_param[THR_COUNT];

  // creates threads
  for (i = 0; i < THR_COUNT; i++) { 
    // prepare the parameter
    thr_param[i] = i;

    pthread_create(&thr[i], NULL, thread_function, (void*)&thr_param[i]);

  }

  // wait for the threads to terminate
  for (i = 0; i < THR_COUNT; i++) {
    pthread_join(thr[i], NULL);

  }
    
  return 0;
}
