#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

// read fro FIFO

#define MAX_BUF 1024

int main() {
  // fifo path
  char* fifo1 = "fifo1";
  
  // open fifo
  int fd = open(fifo1, O_RDONLY);
  if (fd == -1) {
    perror("open( error)");
    exit(EXIT_FAILURE);
  }

  // read from fifo
  char buf[MAX_BUF];
  read(fd, buf, MAX_BUF);
  printf("Message: %s\n", buf);

  close(fd);

  return 0;
}
