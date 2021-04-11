#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>


// program that:
//  creates a child process;
//  pipe.
//  Parent:
//    reads a string >10 characters and send it to the child
//  Child:
//    removes the first character and sends it to the parent and sends to parent
//  Parent removes the last send child 
//  Chlide removes again last 
//  so on 
//  until string contains 3 or less characters.
//
//  print intermediary results string aonly letters 

int main() {
  int p2c[2], c2p[2], pid;
  pipe(p2c);
  pipe(c2p);

  char str[100];

  pid = fork();
  if (pid == 0) {
    close(p2c[1]); close(c2p[0]);
    int len;
    char* ma_string = malloc(111 * sizeof(char));

    read(p2c[0], &len, sizeof(int));
    read(p2c[0], ma_string, 111);

    while(1) {
      if (strlen(ma_string) <= 3) {
        
        break;
      }
      ma_string++;
      len--;
      printf("[Child] string: %s\n", ma_string);

      write(c2p[1], &len, sizeof(int));
      write(c2p[1], ma_string, 111);

      if (len <= 3) {
        break;
      }

      read(p2c[0], &len, sizeof(int));
      read(p2c[0], ma_string, 111);
    }
    close(p2c[0]); close(c2p[1]);

    exit(0);
  }
  
  close(p2c[0]); close(c2p[1]);
  printf("Input a string:\n>>>");
  scanf("%[^\n]", str);
  printf("Initial string: %s\n", str);

  char* ma_string = malloc(111* sizeof(char));
  strcpy(ma_string, str);
 
  while(1) {
    
    if (strlen(ma_string) <= 3) {
      break;
    }

    int len = strlen(ma_string);
    len--;
    ma_string[len] = '\0'; // removes last character
    printf("[Parent] string: %s\n", ma_string);
    
    write(p2c[1], &len, sizeof(int));// write length
    write(p2c[1], ma_string, 111);

    if (len <= 3) {
      break;
    }

    read(c2p[0], &len, sizeof(int));
    read(c2p[0], ma_string, 111);
  }

  close(p2c[1]); close(c2p[0]);
  wait(0);
  return 0;
}
