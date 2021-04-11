#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// Write a program that creates 5 threads, giving each thread a string as parameter. 
// Each thread will count and add to the global variables v and n as follows: 
// the number of vowels contained by the string added to v, 
// and the number of digits contained in the string added to n.

int global_v = 0;
int global_n = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* function(void* param) {

  char* string = (char*)param;
  int local_v = 0;
  int local_n = 0;
  int i;
  int length = strlen(string);

  for (i = 0; i < length; i++) {
    if (strchr("aeiouAEIOU", string[i])) {
      local_v += 1;
    } else if(strchr("0123456789", string[i])) {
      local_n += 1;
    }
  }

  pthread_mutex_lock(&mutex);
    global_v += local_v;
    global_n += local_n;
  pthread_mutex_unlock(&mutex);

  return 0;
}

int main(int argc, char** argv) {
  int i;

  if (argc < 6) {
    perror("need 5 string:(");
    exit(1);
  }

  pthread_t thr[5];

  //pthread_mutex_init(&mutex);

  for (i = 0; i < 5; i++) {
    pthread_create(&thr[i], NULL, function, argv[i + 1]);
  }

  for (i = 0; i < 5; i++) {
    pthread_join(thr[i], NULL);
  }

  pthread_mutex_destroy(&mutex);

  printf("Global v = %d\nGlobal n = %d\n", global_v, global_n);

  return 0;
}
