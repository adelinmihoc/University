#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>


//
// IPC - Using half-duplex pipe (pipe() system call)
//
// A half-duplex pipe resides within the kernel itself,
// and not within the bounds of any physical file system.
// 

int main() {
  int fd[2], pid;                  // file descriptors
  int a[] = {1, 2, 3, 4};

  int res = pipe(fd);              // fail to create pipe
  if (res == -1) {
    perror("pipe() error");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {                 // fail to create fork
    perror("fork() error");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {                  // in child process
    close(fd[0]);                  // close read descriptor

    a[0] += a[1];
    printf("[IN CHILD] Sum: %d\n", a[0]);

    write(fd[1], &a[0], sizeof(int));   // write partial sum in pipe

    close(fd[1]);                       // close write descriptor
    exit(0);
  }

  close(fd[1]);                         // close write dexcriptor

  a[2] += a[3];

  read(fd[0], &a[0], sizeof(int));      // read partial sum

  int status;
  wait(&status);

  printf("\n[IN PARENT] Child has finished with exit satuts: %d\n", status);

  a[0] += a[2];

  printf("[IN PARENT] Sum:%d\n", a[0]);

  close(fd[0]);

  return 0;
}
