
//Add four numbers in parallel using FIFO.Use two related processes.
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>                            
#include <signal.h>                              
#include <string.h> 
#include <fcntl.h>

int main() {

  int a[] = {1,2,3,4}, f;
  mkfifo("/tmp/fifo1", 0666);
  if (fork() == 0) {
    f = open("/tmp/fifo1", O_WRONLY);
    a[0]+=a[1];
    write(f, &a[0], sizeof(int));
    close(f);
    exit(0);
  }
  f = open("/tmp/fifo1", O_RDONLY);
  a[2]+=a[3];
  read(f, &a[0], sizeof(int));
  close(f);
  wait(0);
  a[0]+=a[2];
  printf("The sum is %d\n", a[0]);
  unlink("/tmp/fifo1");
  return 0;


  return 0;
}


