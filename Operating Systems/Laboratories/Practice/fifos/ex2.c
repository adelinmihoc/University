#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// write to a pipe

int main() {
  char* fifo1 = "fifo1"; // FIFO path

  // create fifo
  int res = mkfifo(fifo1, 0666);
  if (res == -1) {
    perror("mkfifo() error");
    exit(EXIT_FAILURE);
  }

  // open the fifo
  int fd = open(fifo1, O_WRONLY);
  if (fd == -1) { 
    perror("open() error");
    exit(EXIT_FAILURE);
  }

  // write a string to FIFO
  char msg[] = "Hello from fifo";
  write(fd, msg, sizeof(msg));

  close(fd);

  // remove the FIFO
  unlink(fifo1);

  return 0;
}
