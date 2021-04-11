#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Write a c program that receive as command line arguments as many triplets formed by a 
//  file f (contains only numbers)
//  2 numbers (n, m)
//
//For each such triplet the programam will create a thread .
//Each thread will receive the triplet and will display the first n numbers of f smaller than m from the corresponding triplet


//pthread_mutex_t mutex;


typedef struct {
  char* path;
  int n;
  int m;
} Triplet;


void* function(void* param) {
  Triplet t = *(Triplet*)param;
  int i, a;
  FILE* fp;
  fp = fopen(t.path, "r");
  for (i = 0; i < t.n; i++) {
    fscanf(fp, "%d", &a);
    if (a < t.m) {
      printf("%d ", a);
    }
  }
  printf("\n");
  return 0;
}


int main(int argc, char** argv) {
  int i;
  if ((argc - 1) % 3 == 1) {
    perror("Invalid arguments");
    exit(EXIT_FAILURE);
  }

  Triplet thr_param[(argc-1) / 3];
  pthread_t thr[(argc - 1) / 3];

  for (i = 1; i < argc; i += 3) {
    thr_param[i / 3].path = argv[i];
    thr_param[i / 3].n = strtol(argv[i + 1], NULL, 10);
    thr_param[i / 3].m = strtol(argv[i + 2], NULL, 10);

    pthread_create(&thr[i / 3], NULL, function, (void*)&thr_param[i/3]);
  }

  for (i = 1; i < argc; i+=3) {
    pthread_join(thr[i/3], NULL);
  }

  return 0;
}
