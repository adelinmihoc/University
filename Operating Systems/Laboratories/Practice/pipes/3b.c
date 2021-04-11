#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>


// a) Scrieți un program care fork()-uie un proces copil, 
//citește de la tastatură două numere și le trimite către copil. 
//Copilul primește numerele, calculează și afișează suma (fork, pipe, write, read).
// b) Modificați programul astfel �nc�t copilul să returneze suma către părinte și acesta din urmă să facă afișarea. 

int main() {
  int sum = 0, p2c[2], c2p[2], a, b;
  pipe(p2c); // parent to child
  pipe(c2p); // child to pipe

  if (fork() == 0) {
    close(p2c[1]); // close the writing 
    close(c2p[0]); // close the reading

    read(p2c[0], &a, sizeof(int)); // we read from p2c integer a
    read(p2c[0], &b, sizeof(int)); // we read from p2c integer b
    close(p2c[0]); // close the reading

    sum = a + b;
    printf("*child sum=%d\n", sum);

    write(c2p[1], &sum, sizeof(int)); // write in c2p the sum
    close(c2p[1]); // close writing

    exit(0);
  }

  close(p2c[0]); // close reading
  close(c2p[1]); // close writing

  printf("input a:\n>>>");
  scanf("%d", &a);
  printf("input b:\n>>>");
  scanf("%d", &b);

  write(p2c[1], &a, sizeof(int));
  write(p2c[1], &b, sizeof(int));
  close(p2c[1]);

  wait(0);

  read(c2p[0], &sum, sizeof(int));
  close(c2p[0]);
  printf("*parent* sum is %d\n", sum);

  return 0;
}
