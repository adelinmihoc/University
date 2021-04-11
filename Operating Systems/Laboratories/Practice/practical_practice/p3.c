#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// two independent programs A and B --- fifos
// A:
//  sends to B a number 70>n>10
// B:
//  receives the number substracts 3 and sends it to A
// A:
//  reads the number from B divides by 2 sends to B
//...so on
// until number has 1 digit
// print intermediari result in each process

int main() {

  int A, B, fa2b, fb2a;

  mkfifo("fifoa2b", 0666);
  mkfifo("fifob2a", 0666);

  A = fork();
  if (A == 0) {
    int x;
    printf("Input a number:\n>>>");
    scanf("%d", &x);
    fa2b = open("fifoa2b", O_WRONLY);
    fb2a = open("fifob2a", O_RDONLY);

    write(fa2b, &x, sizeof(int));
    printf("[A] initial number: %d\n", x);

    while(x > 9) {
      read(fb2a, &x, sizeof(int));
      printf("[A] read: %d\n", x);
      x = x / 2;
      write(fa2b, &x, sizeof(int));
      printf("[A] wrote: %d\n", x);
    }
    
    close(fb2a);
    close(fa2b);
    exit(0);
  }

  B = fork();
  if (B == 0) {
    int x;
    fa2b = open("fifoa2b", O_RDONLY);
    fb2a = open("fifob2a", O_WRONLY);

    while(1) {
      read(fa2b, &x, sizeof(int));
      printf("[B] read: %d\n", x);
      if (x < 10) {
        break;
      }
      x = x - 3;
      write(fb2a, &x, sizeof(int));
      printf("[B] wrote: %d\n", x);
    }
    close(fb2a);
    close(fa2b);
    exit(0);
  }

  wait(0); wait(0);

  return 0;
}
