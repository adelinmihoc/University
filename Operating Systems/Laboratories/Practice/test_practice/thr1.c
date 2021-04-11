#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// write a c program that receives as command line arguments as many triplets containing a file f, a number n and a char c
// for each such triplet the program will create a thread
// each thread will check if the n th character of the file is the same as the character c, 
// from its coressponding triplet 
// if n is too large or f is too small the proper message will be written in the standard output


int checks = 0;
pthread_mutex_t mutex;

typedef struct {
  char* path;
  int n;
  char c;
}Triplet;


void* function(void* param) {
  Triplet trip = *(Triplet*)param;
  int i;
  char last_c;
  FILE* fd;

  fd = fopen(trip.path, "r");

  for (i = 0; i < trip.n; i++) {
    fscanf(fd, "%c", &last_c);
  }

  if (last_c == trip.c) {
    pthread_mutex_lock(&mutex);
    checks += 1;
    pthread_mutex_unlock(&mutex);
  }

  return 0;               
}              


int main(int argc, char** argv) {
  int n, i;
  char c;

  if ((argc - 1) % 3 == 1) {
    perror("not good triplet");
    exit(EXIT_FAILURE);
  }

  pthread_t thr[argc - 1];
  Triplet triplets[argc - 1];

  pthread_mutex_init(&mutex, NULL);

  for (i = 1; i < argc; i+=3) {

    char* path = argv[i];
    n = strtol(argv[i + 1], NULL, 10);
    c = argv[i + 2][0];
    triplets[i].path = path;
    triplets[i].n = n;
    triplets[i].c = c;
  
    pthread_create(&thr[i - 1], NULL, function, (void*)&triplets[i]);
  }

  for (i = 1; i < argc; i+=3) {
    pthread_join(thr[i-1], NULL);
  }

  pthread_mutex_destroy(&mutex);

  printf("Total checks: %d\n", checks);

  return 0;
}
