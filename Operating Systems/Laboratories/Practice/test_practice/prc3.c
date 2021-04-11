#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main () {
  int pid, fd[2];
  char str[100];
  pipe(fd);

  pid = fork();
  if (pid == 0) {
    close(fd[1]);
    
    while (read(fd[0], str, 100) > 0) {
      printf("\n[FROM CHILD] string read is %s\n", str);
    }
    close(fd[0]);
    exit(0);
  }

  close(fd[0]);
  while(1) {
    printf("Input string:");
    scanf("%s", str);
    if (strcmp(str, "stop") == 0) {
      close(fd[1]);
      break;
    }
    write(fd[1], str, strlen(str) + 1);
  }

  wait(0);
  return 0;
}
