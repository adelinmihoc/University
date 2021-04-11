#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// A C program receives command line args numbers, 
// and creates for each a thread that checks is the numbers are multiple of 2 or 5, 
// incrementing a global variable. (use atoi) 

int global_n = 0;

pthread_mutex_t mutex;

void* function(void* param) {
  char* param_str = (char*)param;
  int number = atoi(param_str);

  int local_n = 0;

  if (number % 2 == 0 || number % 5 == 0) {
    local_n += 1;
  }

  pthread_mutex_lock(&mutex);
    global_n += local_n;
  pthread_mutex_unlock(&mutex);


  return 0;
}

int main(int argc, char** argv) {
  int i;

  if (argc < 2) {
    perror("Need at least a number!");
    exit(EXIT_FAILURE);
  }

  pthread_mutex_init(&mutex, NULL);

  pthread_t thr[argc - 1];

  for (i = 0; i < argc - 1; i++) {
    pthread_create(&thr[i], NULL, function, argv[i + 1]);
  }

  for (i = 0; i < argc - 1; i++) {
    pthread_join(thr[i], NULL);
  }

  pthread_mutex_destroy(&mutex);

  printf("The result is %d\n", global_n);

  return 0;
}
